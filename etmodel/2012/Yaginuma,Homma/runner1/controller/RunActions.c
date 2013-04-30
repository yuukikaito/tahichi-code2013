/*
 * COPYRIGHT(c)2010 Afrel Co., Ltd.
 * RunActions.c
 * RunActions�N���X
 *
 * �N���X��: RunActions(RA)
 * ����:
 * ����: get_state, do_running, is_exit
 * �֘A: LineMonitorUnit(LMU), BalancerUnit(BLNU),
 *       BumperUnit(BU), BlockMonitorUnit(BMU),
 *       CommunicationUnit(CU), common
 */

#include "RunActions.h"

#define	MIN_DISTANCE (25)		/* �Ǌ��m���� */

/*
 * �X���[�u����Bluetooth�f�o�C�X�A�h���X
 */
const static unsigned char bd_addr[7] = { 0x00, 0x16, 0x53, 0x12, 0x27, 0xB5,
		0x00 };

/*
 * ���s���̏��
 */
typedef enum {
	RA_STATE_WATCH_BLOCK,
	RA_STATE_WAIT_PRE_START_CONF,
	RA_STATE_SHORT_CUT,
	RA_STATE_TURN,
	RA_STATE_TURN2,
	RA_STATE_TURN_IN_WHITE,
	RA_STATE_WATCH_GOAL,
	RA_STATE_WAIT_START_CONF,
	RA_STATE_FINISH
} RA_STATE;

static RA_STATE RA_state;

/*
 * ��ԃZ�b�g�p�̃v���C�x�[�g�֐�
 */
void RA_set_state(int state);

/*
 * �e��ԂɑΉ�����v���C�x�[�g�֐�
 */
void RA_watch_block_tracing();
void RA_watch_goal_tracing();
void RA_short_cut();
void RA_turn();
void RA_turn2();
void RA_turn_in_white();
void RA_wait_pre_start_conf();
void RA_wait_start_conf();
void RA_linetrace(int forward_speed, int turn_speed);
void RA_linetrace_P(int forward_speed);
void RA_stop();
void RA_turn_right();
void RA_turn_left();
int i;

/**
 * RunActions�̏���������
 */
void RA_pre(void) {
	RA_set_state(RA_STATE_WATCH_BLOCK);

	BMU_pre(); /* BlockMonitorUnit�̏����� */
	BMU_set_threshold(MIN_DISTANCE); /* BlockMonitorUnit��臒l�ݒ� */

	CU_set_mode(1, bd_addr); /* �}�X�^�ɐݒ� */
	CU_pre(); /* CommUnit�̏����� */
}

/**
 * RunActions�̏I������
 */
void RA_post(void) {
	BMU_post(); /* BlockMonitorUnit�̏I������ */

	CU_post(); /* CommUnit�̏I������ */

}

/**
 * RunActions�̏�ԃZ�b�g
 */
void RA_set_state(int state) {
	RA_state = state;
}

/**
 * RunActions�̏�ԃQ�b�g
 */
int RA_get_state(void) {
	return RA_state;
}

/**
 * RunActions�̍ŏI��Ԏ擾
 */
int RA_is_exit(void) {
	if (RA_STATE_FINISH == RA_state) {
		return TRUE;
	} else {
		return FALSE;
	}
}

/**
 * RunActions�̏�ԑJ��
 */
void RA_do_running(void) {
	switch (RA_state) {
	case (RA_STATE_WATCH_BLOCK):
		RA_watch_block_tracing();
		break;

	case (RA_STATE_WAIT_PRE_START_CONF):
		RA_wait_pre_start_conf();
		break;

	case (RA_STATE_SHORT_CUT):
		RA_short_cut();
		break;

	case (RA_STATE_TURN):
		RA_turn();
		break;

	case (RA_STATE_TURN2):
		RA_turn2();
		break;

	case (RA_STATE_TURN_IN_WHITE):
		RA_turn_in_white();
		break;

	case (RA_STATE_WATCH_GOAL):
		RA_watch_goal_tracing();
		break;

	case (RA_STATE_WAIT_START_CONF):
		RA_wait_start_conf();
		break;

	case (RA_STATE_FINISH):
		/* DO NOTHING */
		break;

	default:
		/* DO NOTHING */
		break;
	}
}

void RA_watch_block_tracing() {
	/* ���C���g���[�X������ */
	RA_linetrace_P(45);	//�ύX�ς�
	i++;
	if(250<=i){
		HU_ok_sound();
		CU_set_sendMSG(77);
		CU_send_mail();
		
		i=0;
		RA_set_state(RA_STATE_TURN2);
	}
}


/**
 * �w�肵���p�x�����E���񂷂�
 */
void RA_turn() {

	/* True��Ԃ��܂ŉ�]���� */
	if (BLNU_angle_turn_right(120)) {
		RA_stop();

		RA_set_state(RA_STATE_TURN_IN_WHITE);

	}
}


void RA_turn2() {

	/* True��Ԃ��܂ŉ�]���� */
	if (BLNU_angle_turn_right(10)) {
		RA_stop();
		//BLNU_angle_turn_left(2);
		RA_set_state(RA_STATE_SHORT_CUT);

	}
}

void RA_short_cut(){
	
	BLNU_forward(30);
	i++;
	if(75<=i){
		if ((LMU_get_black_value() - 30) <= LMU_is_line_value()) {
			RA_set_state(RA_STATE_WATCH_GOAL);
		}
	}
}


/**
 * �������܂ŉE���񂷂�
 */
void RA_turn_in_white() {
	/* �E���񂷂� */
	RA_turn_right();

	/* �����������玟�̏�ԂɑJ�ڂ��� */
	if ((LMU_get_black_value() - 30) <= LMU_is_line_value()) {
		RA_set_state(RA_STATE_WATCH_GOAL);
	}
}

void RA_watch_goal_tracing() {
	/* ���C���g���[�X������ */
	RA_linetrace_P(40);	//�ύX��

	/* �o���p�������ꂽ�玟�̏�ԂɑJ�ڂ��� */
	if (TRUE == BU_is_touched()) {
		/* ��~���� */
		
		HU_ok_sound();
		RA_stop();

		/* ��Q���҂��X�^�[�g�����邽�߂ɁA���[���𑗐M���� */
		CU_set_sendMSG(77);
		CU_send_mail();

		RA_set_state(RA_STATE_WAIT_START_CONF);

	}
}

void RA_wait_pre_start_conf() {

	CU_set_recvMSG(99);

	/* �X�^�[�g�����w���m�F���[������M�����玟�̏�ԂɑJ�ڂ��� */
	if (TRUE == CU_is_received()) {

		RA_set_state(RA_STATE_TURN);

	}
}

void RA_wait_start_conf() {

	CU_set_recvMSG(99);

	/* �X�^�[�g�w���m�F���[������M�����玟�̏�ԂɑJ�ڂ��� */
	if (TRUE == CU_is_received()) {

		RA_set_state(RA_STATE_FINISH);

	}
}

/**
 * �������ɉ����đ���
 */
void RA_linetrace(int forward_speed, int turn_speed) {
	/* �O�i���� */
	BLNU_forward(forward_speed);

	/* �����̔��f�����ĉ�]���������߂� */
	int light_value = 0;
	light_value = LMU_is_online();
	if (TRUE != light_value) {
		BLNU_turn_right(turn_speed);
	} else {
		BLNU_turn_left(turn_speed);
	}
}

/**
 * �������ɉ����đ���(P����j
 */
void RA_linetrace_P(int forward_speed) {
	/* �O�i���� */
	BLNU_forward(forward_speed);

	float hensa;
	float Kp = 1.4;	//�ύX��   
	float cmd_turn = 0;

	hensa = LMU_get_threshold() - LMU_is_line_value();
	/* �����Ɓ{�l */
	/* �����Ɓ|�l */

	cmd_turn = Kp * hensa;

	if (-100 > cmd_turn) {
		cmd_turn = -100;
	} else if (100 < cmd_turn) {
		cmd_turn = 100;
	}

	BLNU_turn(cmd_turn);

}

/**
 * ��~����
 */
void RA_stop() {
	BLNU_stop();
}

/**
 * �E�ɋȂ���
 */
void RA_turn_right() {
	BLNU_backward(0);
	BLNU_turn_right(50);
}

/**
 * ���ɋȂ���
 */
void RA_turn_left() {
	BLNU_backward(0);
	BLNU_turn_left(-50);
}

/******************************** END OF FILE ********************************/
