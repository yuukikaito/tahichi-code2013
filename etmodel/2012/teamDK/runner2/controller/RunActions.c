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
void RA_linetrace_P(int forward_speed);

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
	RA_linetrace_P(5);


}

void RA_watch_goal_tracing() {
	/* ���C���g���[�X������ */
	RA_linetrace_P(50);
	

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
	static float d_hensa = 0;
	static float bf_hensa = 0;
	float Kp = 4;
	float Kd = 0.02;
	float cmd_turn = 0;

	hensa = LMU_get_threshold() - LMU_is_line_value();
	/* �����Ɓ{�l */
	/* �����Ɓ|�l */
	d_hensa =(bf_hensa - hensa )/0.004;
	bf_hensa = hensa;

	cmd_turn = -1*(Kp * hensa - Kd*d_hensa);

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
void RA_stop(void) {
	BLNU_stop();
}

/******************************** END OF FILE ********************************/
