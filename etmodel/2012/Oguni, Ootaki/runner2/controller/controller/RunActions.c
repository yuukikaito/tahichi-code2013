/*
 * COPYRIGHT(c)2010 Afrel Co., Ltd.
 * RunActions.c
 * RunActions�N���X
 *
 * �N���X��: RunActions(RA)
 * ����:
 * ����: get_state, do_running, is_exit
 * �֘A: LineMonitorUnit(LMU), BalancerUnit(BLNU), common
 */

#include "RunActions.h"

/*
 * �e��ԂɑΉ�����v���C�x�[�g�֐�
 */
void RA_linetrace(int forward_speed, int turn_speed);
void RA_linetrace_P(int forward_speed);ma
void RA_tail_linetrace_PID(int forward_speed,float Kp,float Ki,float Kd);

/**
 * RunActions�̏���������
 */
void RA_pre(void) {
}

/**
 * RunActions�̏I������
 */
void RA_post(void) {
}

void RA_takeover() {
	/* ���C���g���[�X������ */
	RA_tail_linetrace_PID(70,1.8,0.0,0.06);

}

void RA_watch_goal_tracing() {
	/* ���C���g���[�X������ */
	RA_tail_linetrace_PID(70,1.8,0.0,0.06);

}

/**
 * �������ɉ����đ���
 */
void RA_linetrace(int forward_speed, int turn_speed) {
	/* �O�i���� */
	//BLNU_forward(forward_speed);
	
	/* �����̔��f�����ĉ�]���������߂� */
	int light_value = 0;
	light_value = LMU_is_online();
	if (TRUE != light_value) {
		//BLNU_turn_right(turn_speed);
		ecrobot_set_motor_speed(NXT_PORT_C,turn_speed);
		ecrobot_set_motor_speed(NXT_PORT_B,turn_speed/2);
	} else {
		//BLNU_turn_left(turn_speed);
		ecrobot_set_motor_speed(NXT_PORT_C,turn_speed/2);
		ecrobot_set_motor_speed(NXT_PORT_B,turn_speed);
	}
}

/**
 * �������ɉ����đ���(P����j
 */
void RA_linetrace_P(int forward_speed) {
	/* �O�i���� */
	//BLNU_forward(forward_speed);
	

	float hensa;
	float Kp = 1.7;
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

	nxt_motor_set_speed(L_MOTOR_PORT, forward_speed + cmd_turn/2, 1);
	nxt_motor_set_speed(R_MOTOR_PORT, forward_speed - cmd_turn/2, 1);
	//BLNU_turn(cmd_turn);

}

void RA_tail_linetrace_PID(int forward_speed,float Kp,float Ki,float Kd){

	static const float b = 0;
	float cmd_turn = 0;
	static float hensa = 0;
	static float i_hensa = 0;
	static float d_hensa = 0;
	static float bf_hensa = 0;
	static float bf_bf_hensa = 0;
	static float bf_cmd_turn = 0;

	BLNU_forward(forward_speed);

	hensa = LMU_get_threshold() - LMU_is_line_value();

	cmd_turn = bf_cmd_turn + (Kp * (hensa - bf_hensa) + Ki * hensa + Kd * ((hensa - bf_hensa) - (bf_hensa - bf_bf_hensa)));
	bf_bf_hensa = bf_hensa;
	bf_hensa = hensa;
	bf_cmd_turn = cmd_turn;

	nxt_motor_set_speed(L_MOTOR_PORT, forward_speed + cmd_turn/2, 1);
	nxt_motor_set_speed(R_MOTOR_PORT, forward_speed - cmd_turn/2, 1);
}

/**
 * ��~����
 */
void RA_stop(void) {
	ecrobot_set_motor_speed(1,0);
	ecrobot_set_motor_speed(2,0);
}

/******************************** END OF FILE ********************************/
