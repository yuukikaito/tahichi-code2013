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
const static unsigned char bd_addr[7] = { 0x00, 0x16, 0x53, 0x06, 0xCF, 0x80,
		0x00 };

/*
 * �V�X�e���S�̂̑��s���
 */
typedef enum {
	RN_STATE_CALIBRATE,
	RN_STATE_RADY,
	RN_STATE_BUMP_RADY,
	RN_STATE_TAKEOVER,
	RN_STATE_RUN,
	RN_STATE_FINISH,
	RN_STATE_WAIT
} RN_STATE;

static RN_STATE RN_state;

/**
 * ��ԃZ�b�g�p�̃v���C�x�[�g�֐�
 */
void RN_set_state(int state);

/*
 * �e��ԂɑΉ�����v���C�x�[�g�֐�
 */
void RN_calibrate();
void RN_ready();
void RN_bump_ready();
void RN_takeover();
void RN_run();
void RN_wait();

/**
 * Runner�̏���������
 */
void RN_pre(void) {
	RN_set_state(RN_STATE_CALIBRATE);

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
	case (RN_STATE_CALIBRATE):
		RN_calibrate();
		break;

	case (RN_STATE_RADY):
		RN_ready();
		break;

	case (RN_STATE_BUMP_RADY):
		RN_bump_ready();
		break;

	case (RN_STATE_TAKEOVER):
		RN_takeover();
		break;

		/////////
	case (RN_STATE_WAIT):
		RN_wait();
		break;
		/////////

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

void RN_calibrate() {
	CA_set_threshold();

	//BLNU_balance_start();
	RN_set_state(RN_STATE_RADY);
}

void RN_ready() {
	CU_set_recvMSG(77);

	/* �^�C�}���J�n����Ă��Ȃ������� */
	if (!TU_is_start()) {
		/** 90�b�̃^�C�}�Ď��J�n */
		TU_start(90000);
	}

	/* �X�^�[�g�����w���ő���o�� */
	if (CU_is_received()) {

		CU_set_sendMSG(99);
		CU_send_mail();

		TU_finish();
		RN_set_state(RN_STATE_TAKEOVER);
	}

	/* 90�b�o�߂����� */
	if (TU_is_timeout()) {

		/** �^�C�}�Ď����I�������� */
		TU_finish();

		RN_set_state(RN_STATE_BUMP_RADY);
	}

}

void RN_bump_ready() {
	/* �J��グ�X�^�[�g�����w���ő���o�� */
	if (TRUE == BU_is_clicked()) {
		RN_set_state(RN_STATE_TAKEOVER);
		//RN_set_state(RN_STATE_RUN);
	}
}

void RN_takeover() {

	if (!TU_is_start()) {
		/** 2.5�b�̃^�C�}�Ď��J�n */
		TU_start(2500);
	}

	HU_ok_sound();
	RA_takeover();
	
	if (TU_is_timeout()) {

		/** �^�C�}�Ď����I�������� */
		TU_finish();

		RN_set_state(RN_STATE_WAIT);
	}

}

void RN_wait(){

	//HU_ok_sound();
	CU_set_recvMSG(77);
	RA_stop();
	/* �X�^�[�g�w�����󂯂��玟�̏�ԂɑJ�ڂ��� */
	//if (TRUE == CU_is_received()) {
	if (BU_is_touched()){
		/* ��~���� */
		RA_stop();

		CU_set_sendMSG(99);
		CU_send_mail();

		RN_set_state(RN_STATE_RUN);

	}
}

void RN_run() {
	RA_watch_goal_tracing();

	/* �o���p�������ꂽ�玟�̏�ԂɑJ�ڂ��� */
	if (BU_is_touched()) {
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
