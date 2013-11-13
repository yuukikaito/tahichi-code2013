/*
 * COPYRIGHT(c)2010 Afrel Co., Ltd.
 * Runner.c
 * Runner�N���X
 *
 * �N���X��: Runner(RN)
 * ����:
 * ����: get_state, do_run
 * �֘A: RunActions(RA), CalibrateActions(CA),
 *       BumperUnit(BU), BalancerUnit(BLNU),CommunicationUnit(CU),
 *       TimerUnit(TU), common
 */

#include "Runner.h"

/*
 * �X���[�u����Bluetooth�f�o�C�X�A�h���X
 */
const static unsigned char bd_addr[7] = { 0x00, 0x16, 0x53, 0x13, 0xB3, 0x60, 0x00 };

/*
 * �V�X�e���S�̂̑��s���
 */
typedef enum {
	RN_STATE_CALIBRATE1,
	RN_STATE_CALIBRATE2,
	RN_STATE_CALIBRATE3,
	RN_STATE_RADY,
	RN_STATE_ZERO_SPEED1,
	RN_STATE_BUMP_RADY,
	RN_STATE_TAKEOVER,
	RN_STATE_ZERO_SPEED2,
	RN_STATE_RUN,
	RN_STATE_FINISH
} RN_STATE;

static RN_STATE RN_state;

/**
 * ��ԃZ�b�g�p�̃v���C�x�[�g�֐�
 */
void RN_set_state(int state);

/*
 * �e��ԂɑΉ�����v���C�x�[�g�֐�
 */
void RN_calibrate1();
void RN_calibrate2();
void RN_calibrate3();
void RN_ready();
void RN_zero_speed1();
void RN_bump_ready();
void RN_zero_speed2();
void RN_takeover();
void RN_run();

/**
 * Runner�̏���������
 */
void RN_pre(void) {
	RN_set_state(RN_STATE_CALIBRATE1);

	CA_pre();
	RA_pre();

	CU_set_mode(0, bd_addr); /* �X���[�u�ɐݒ� */
	CU_pre(); /* CommUnit�̏����� */

}

/**
 * Runner�̏I������
 */
void RN_post(void) {
	CA_post();
	RA_post();

	CU_post(); /* CommUnit�̏I������ */

}

/**
 * Runner�̏�ԃZ�b�g
 */
void RN_set_state(int state) {
	RN_state = state;
}

/**
 * Runner�̏�ԃQ�b�g
 */
int RN_get_state(void) {
	return RN_state;
}

/**
 * Runner�̏�ԑJ��
 */
void RN_do_run() {
	switch (RN_state) {
	case (RN_STATE_CALIBRATE1):
		RN_calibrate1();
		break;

	case (RN_STATE_CALIBRATE2):
		RN_calibrate2();
		break;

	case (RN_STATE_CALIBRATE3):
		RN_calibrate3();
		break;

	case (RN_STATE_RADY):
		RN_ready();
		break;

	case (RN_STATE_BUMP_RADY):
		RN_bump_ready();
		break;

	case (RN_STATE_ZERO_SPEED1):
		RN_zero_speed1();
		break;

	case (RN_STATE_TAKEOVER):
		RN_takeover();
		break;

	case (RN_STATE_ZERO_SPEED2):
		RN_zero_speed2();
		break;

	case (RN_STATE_RUN):
		RN_run();
		break;

	case (RN_STATE_FINISH):
		/* DO NOTHING */
		break;

	default:
		/* DO NOTHING*/
		break;
	}
}

void RN_calibrate1() {
	if(TRUE == BU_is_clicked()){
		CA_set_white_val();

		RN_set_state(RN_STATE_CALIBRATE2);
	}
}

void RN_calibrate2() {
	if(TRUE == BU_is_clicked()){
		CA_set_black_val_and_threshold();

		RN_set_state(RN_STATE_CALIBRATE3);
	}
}

void RN_calibrate3() {
	if(TRUE == BU_is_clicked()){
		CA_set_gyro_offset();

		BLNU_balance_start();
		RN_set_state(RN_STATE_RADY);
	}
}

void RN_ready() {
	int nouse;
	
	CU_set_recvMSG(77);
	
	nouse = RA_nomove();
	
	/* �^�C�}���J�n����Ă��Ȃ������� */
	if (!TU_is_start()) {
		/** 90�b�̃^�C�}�Ď��J�n */
		TU_start(90000);
	}

	/* �X�^�[�g�����w���ő���o�� */
	if (TRUE == CU_is_received()) {

		CU_set_sendMSG(99);
		CU_send_mail();
		
		TU_finish();

		RN_set_state(RN_STATE_ZERO_SPEED1);
	}
	
	if(TRUE == BU_is_clicked()){
		TU_finish();
		
		RN_set_state(RN_STATE_ZERO_SPEED1);
	}

	/* 90�b�o�߂����� */
	if (TRUE == TU_is_timeout()) {

		/** �^�C�}�Ď����I�������� */
		TU_finish();

		RN_set_state(RN_STATE_BUMP_RADY);
	}

}

void RN_bump_ready() {
	int nouse;
	
	nouse = RA_nomove();

	/* �J��グ�X�^�[�g�����w���ő���o�� */
	if (TRUE == BU_is_clicked()) {
		RN_set_state(RN_STATE_RUN);
	}
}

void RN_zero_speed1() {
	int count;
	
	count = RA_nomove();
	
	if(count == 0){
		RN_set_state(RN_STATE_TAKEOVER);
	}
}

void RN_takeover() {
	int nouse;
	
	CU_set_recvMSG(77);
	
	/* �^�C�}���J�n����Ă��Ȃ������� */
	if (!TU_is_start()) {
		/** 6�b�̃^�C�}�Ď��J�n */
		TU_start(6000);
	}
	
	/* 6�b�o�߂����� */
	if (TRUE == TU_is_timeout()) {
		nouse = RA_nomove();
	}else{
		RA_takeover();
	}

	
	/* �X�^�[�g�w�����󂯂��玟�̏�ԂɑJ�ڂ��� */
	if (TRUE == CU_is_received()) {
		RA_stop();

		CU_set_sendMSG(99);
		CU_send_mail();

		RN_set_state(RN_STATE_ZERO_SPEED2);

	}
	
	if(TRUE == BU_is_clicked()){
		TU_finish();
		
		RN_set_state(RN_STATE_ZERO_SPEED2);
	}
}

void RN_zero_speed2() {
	int count;
	
	count = RA_nomove();
	
	if(count == 0){
		RN_set_state(RN_STATE_RUN);
	}
}

void RN_run() {
	RA_watch_goal_tracing();

	/* �o���p�������ꂽ�玟�̏�ԂɑJ�ڂ��� */
	if (TRUE == BU_is_touched()) {
		/* ��~���� */
		RA_stop();

		RN_set_state(RN_STATE_FINISH);
	}
}

/******************************************************************************
 * TASK			: ActionTask
 * ARGUMENT		: none
 * RETURN		: none
 * DESCRIPTION 	: 40msec periodical Task
 *****************************************************************************/
TASK(ActionTask)
{

	RN_do_run();

	TerminateTask();
}

/******************************** END OF FILE ********************************/
