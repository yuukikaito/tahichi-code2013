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
void RA_linetrace1(int forward_speed);
void RA_linetrace2(int forward_speed);

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

int RA_nomove(void) {
	static int count = 0;
	static int speed = 0;
	
	if(count < 22){
		speed = (int)(count/4) - 3;
	}else{
		speed = (int)((44-count)/4) - 3;
	}
	
	count += 1;
	if(count >= 44){
		count = 0;
	}
	RA_linetrace1(speed);
	
	return count-12;
}

void RA_takeover() {
	/* ���C���g���[�X������ */
	RA_linetrace1(30);
}

void RA_watch_goal_tracing() {
	/* ���C���g���[�X������ */
	static int count = 0;
	
	if(count < 200){
		RA_linetrace2((int)(count/4));
		count += 1;
	}else{
		RA_linetrace2(50);
	}
}

/*
 * �������ɉ����đ���(PD����)
 */

void RA_linetrace1(int speed) {
	/* �O�i���� */
	if(speed >= 0){
		BLNU_forward(speed);
	}else{
		BLNU_backward(speed);
	}

	static float hensa = 0;
	static float d_hensa = 0;
	static float bf_hensa = 0;
	float Kp = 0.9;
	float Kd = 0.003;
	float cmd_turn = 0;

	hensa = LMU_is_line_value() - LMU_get_threshold();
	d_hensa = (hensa - bf_hensa)/0.004;
	bf_hensa = hensa;
	/* ������-�l */
	/* ������+�l */
	
	cmd_turn = Kp * hensa + Kd * d_hensa;

	if (-100 > cmd_turn) {
		cmd_turn = -100;
	} else if (100 < cmd_turn) {
		cmd_turn = 100;
	}
	
	BLNU_turn(cmd_turn);
}

void RA_linetrace2(int speed) {
	/* �O�i���� */
	if(speed >= 0){
		BLNU_forward(speed);
	}else{
		BLNU_backward(speed);
	}

	static float hensa = 0;
	static float d_hensa = 0;
	static float bf_hensa = 0;
	float Kp = 0.9;
	float Kd = 0.003;
	float cmd_turn = 0;
	static int count = 0;

	hensa = LMU_is_line_value() - LMU_get_threshold();
	/* ������-�l */
	/* ������+�l */
	
	if(hensa >= 30){
		
		if(count < -10){
			BLNU_forward(speed + ((int)(count/2) + 5));
			count += 1;
		}else if(count > 60){
			BLNU_forward(speed - 25);
		}else if(count >= 10){
			BLNU_forward(speed - ((int)(count/2) - 5));
			count += 1;
		}
	}else if(hensa <= -30){
		
		if(count > 10){
			BLNU_forward(speed - ((int)(count/2) - 5));
			count -= 1;
		}else if(count < -60){
			BLNU_forward(speed - 25);
		}else if(count <= -10){
			BLNU_forward(speed + ((int)(count/2) + 5));
			count -= 1;
		}
	}else{
		hensa = 0;
	}
	d_hensa = (hensa - bf_hensa)/0.004;
	bf_hensa = hensa;

	cmd_turn = Kp * hensa + Kd * d_hensa;

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
