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
#include "../Unit/TimerUnit.h"
#include "../Unit/HornUnit.h"
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

void RA_stoppinglinetrace()
 {
	RA_linetrace_P(0);
	
 	//DU_show_number(10,3,abs((int)((nxt_motor_get_count(NXT_PORT_B) + nxt_motor_get_count(NXT_PORT_C)) / 2)));
 	

 }
void RA_takeover() {
	static int flag =0;
	if(flag ==0) {
	RA_linetrace_P(20);
	}
	else {
		RA_stoppinglinetrace();		
		}
	
	if (!TU_is_start() && flag ==0) {
		/** 4�b�̃^�C�}�Ď��J�n */
		TU_start(4000); 
	}

	if (TRUE == TU_is_timeout()) {
	HU_warn_sound();
		/** �^�C�}�Ď����I�������� */
		TU_finish();	
		flag =1; //���^�C�}���g����������g��Ȃ��B
	}
		
		
		
}
	//�����苗���𑖂�����Î~��ԂɎ����Ă��������B
	
	
	
//�����[�̃��[�h�����Ă�����
//�w�肳�ꂽ����蒴���Ă͂Ȃ�Ȃ�


void RA_watch_goal_tracing() {
	/* ���C���g���[�X������ */
//	RA_linetrace(25,100);
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
		BLNU_turn_left(turn_speed);
	} else {
		BLNU_turn_right(turn_speed);
	}
}

/**
 * �������ɉ����đ���(P����j
 */
void RA_linetrace_P(int forward_speed) {
	/* �O�i���� */
	BLNU_forward(forward_speed);

	float hensa;
	

	float Kp = 1.4;
	float cmd_turn = 0;

	
	hensa = LMU_get_threshold() - LMU_is_line_value();
	/* �����Ɓ{�l */
	/* �����Ɓ|�l */
	
	

	cmd_turn = Kp * -hensa;

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
	RA_stoppinglinetrace();  // �Î~����
	//BLNU_stop();
}

/******************************** END OF FILE ********************************/
