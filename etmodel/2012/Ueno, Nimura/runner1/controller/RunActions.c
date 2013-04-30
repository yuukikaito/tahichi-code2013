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

#define	MIN_DISTANCE (22)		/* �Ǌ��m���� */
#define KP 0.8
#define KI 0.35
#define KD  0.015

/*
 * �X���[�u����Bluetooth�f�o�C�X�A�h���X
 */
const static unsigned char bd_addr[7] = { 0x00, 0x16, 0x53, 0x13, 0xB7, 0xCA,
		0x00 };

/*
 * ���s���̏��
 */
typedef enum {
	RA_STATE_WATCH_BLOCK,
	RA_STATE_WAIT_PRE_START_CONF,
	RA_STATE_TURN,
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
void RA_turn();
void RA_turn_in_white();
void RA_wait_pre_start_conf();
void RA_wait_start_conf();
//void RA_linetrace(int forward_speed, int turn_speed);
void RA_linetrace_L(int forward_speed,float Kp,float Ki,float Kd);
void RA_linetrace_R(int forward_speed,float Kp,float Ki,float Kd);
void RA_stop();
void RA_turn_right();
void RA_turn_left();

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

	case (RA_STATE_TURN):
		RA_turn();
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
	if(FALSE == TU_is_start())
		TU_start(5000);
	/* ���C���g���[�X������ */
	//RA_linetrace(45, 100);
	
	LMU_set_threshold((LMU_get_black_value()+LMU_get_white_value())/2);
	RA_linetrace_L(50,KP,KI,KD);
	//LMU_set_threshold((2*LMU_get_black_value()+LMU_get_white_value())/3);
	//RA_linetrace_L(60,KP,KI,KD);

	/* �����g�Z���T�ŕǂ�F������Ǝ��̏�ԂɑJ�ڂ��� */
	if (TU_is_timeout() && BMU_is_found()) {
		/* ��~���� */
		RA_stop();
		TU_finish();

		CU_set_sendMSG(77);
		CU_send_mail();
		//RA_set_state(RA_STATE_TURN);
		RA_set_state(RA_STATE_WAIT_PRE_START_CONF);
	}
}

/**
 * �w�肵���p�x�����E���񂷂�
 */
void RA_turn() {
	/* True��Ԃ��܂ŉ�]���� */
	if (BLNU_angle_turn_right(180)) {
		RA_stop();
		RA_set_state(RA_STATE_TURN_IN_WHITE);
	}
}

/**
 * �������܂ŉE���񂷂�
 */
void RA_turn_in_white() {
	BLNU_forward(10);

	/* �����������玟�̏�ԂɑJ�ڂ��� */
	if ((LMU_get_black_value() - 30) <= LMU_is_line_value()) {
		RA_set_state(RA_STATE_WATCH_GOAL);
	}
}

void RA_watch_goal_tracing() {
	/* ���C���g���[�X������ */
	int forward;
	float Kp;
	if(FALSE == TU_is_start()){
		TU_start(2000);
	}

	if(FALSE == TU_is_timeout()){
		forward = 20;
		Kp = 50;
	}else{
		//HU_arrival_sound();
		if(forward <40) forward +=0.2;
		Kp = KP;
	}
	
	LMU_set_threshold((LMU_get_black_value()+3*LMU_get_white_value())/4);
	RA_linetrace_L(forward,Kp, KI, KD);

	/* �o���p�������ꂽ�玟�̏�ԂɑJ�ڂ��� */
	if (TRUE == BU_is_touched()) {
		/* ��~���� */
		RA_stop();
		TU_finish();

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

///**
// * �������ɉ����đ���
// */
//void RA_linetrace(int forward_speed, int turn_speed) {
//	/* �O�i���� */
//	BLNU_forward(forward_speed);
//
//	/* �����̔��f�����ĉ�]���������߂� */
//	int light_value = 0;
//	light_value = LMU_is_online();
//	if (TRUE != light_value) {
//		BLNU_turn_right(turn_speed);
//	} else {
//		BLNU_turn_left(turn_speed);
//	}
//}

/**
 * �������ɉ����đ���(P����j
 */
void RA_linetrace_L(int forward_speed,float Kp,float Ki,float Kd) {
	/* �O�i���� */

	float hensa = 0;
	float b = 0;

	float cmd_turn = 0;
	float i_hensa = 0;
	float d_hensa = 0;
	float bf_hensa = 0;

	hensa = LMU_get_threshold() - LMU_is_line_value();
	/* �����Ɓ{�l */
	/* �����Ɓ|�l */

	i_hensa = i_hensa + (hensa * 0.004);

	d_hensa = (hensa - bf_hensa)/0.004;
	bf_hensa = hensa;

	cmd_turn = Kp*hensa + Ki*i_hensa + Kd*d_hensa + b;

	cmd_turn = Kp * hensa;

	if (-100 > cmd_turn) {
		cmd_turn = -100;
	} else if (100 < cmd_turn) {
		cmd_turn = 100;
	}

	BLNU_forward(forward_speed);
	BLNU_turn(cmd_turn);

	//�K�����s����ꍇ !!!���̂Ƃ��������K�v!!!
	//nxt_motor_set_speed(L_MOTOR_PORT, forward_speed + cmd_turn/2, 1);
	//nxt_motor_set_speed(R_MOTOR_PORT, forward_speed - cmd_turn/2, 1);


}

/**
 * �������ɉ����đ���(P����j
 */
void RA_linetrace_R(int forward_speed,float Kp,float Ki,float Kd) {
	/* �O�i���� */

	float hensa = 0;
	float b = 0;

	float cmd_turn = 0;
	float i_hensa = 0;
	float d_hensa = 0;
	float bf_hensa = 0;

	hensa = LMU_get_threshold() - LMU_is_line_value();
	/* �����Ɓ{�l */
	/* �����Ɓ|�l */

	i_hensa = i_hensa + (hensa * 0.004);

	d_hensa = (hensa - bf_hensa  )/0.004;
	bf_hensa = hensa;

	cmd_turn = Kp*hensa + Ki*i_hensa + Kd*d_hensa + b;

	cmd_turn = Kp * hensa;

	if (-100 > cmd_turn) {
		cmd_turn = -100;
	} else if (100 < cmd_turn) {
		cmd_turn = 100;
	}

	BLNU_forward(forward_speed);
	BLNU_turn(-cmd_turn);

	//�K�����s����ꍇ !!!���̂Ƃ��������K�v!!!
	//nxt_motor_set_speed(L_MOTOR_PORT, forward_speed + cmd_turn/2, 1);
	//nxt_motor_set_speed(R_MOTOR_PORT, forward_speed - cmd_turn/2, 1);
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
