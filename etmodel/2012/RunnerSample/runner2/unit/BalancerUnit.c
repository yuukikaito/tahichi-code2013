/*
 * COPYRIGHT(c)2009 Afrel Co., Ltd.
 * BalancerUnit.c
 * �o�����T�[���j�b�g�N���X
 *
 * �N���X��: BalancerUnit(BLNU)
 * ����: cmd_forward, cmd_turn, gyro_offset
 * ����: pre, post, forward, backward, turn_right, turn_left, stop,
 *       set_gyro_offset, balance_control
 * �֘A: common, nxt_config, balancer
 */

#include "BalancerUnit.h"

#define Max_VALUE 100
#define Min_VALUE -100

#define Robot_WIDTH 157	/* ���{�b�g�̉��� mm */
#define Wheel_DIAMETER 80	/* �^�C���̒��a mm */

static BOOL BLNU_motor_angle_control; /* �p�x����J�n�t���O */
static F32 start_l_motor_rev; /* �p�x����J�n���̃��[�^�p�x(���j */
static F32 start_r_motor_rev; /* �p�x����J�n���̃��[�^�p�x(�E�j */
static F32 finish_motor_rev; /* �p�x����ڕW�̃��[�^�p�x */

/**
 * �o�����X�R���g���[��
 */
void BLNU_balance_control(void);

/**
 * BalancerUnit�̏���������
 */
void BLNU_pre(void) {
	ecrobot_set_motor_rev(L_MOTOR_PORT, 0);
	ecrobot_set_motor_rev(R_MOTOR_PORT, 0);
	balance_init();
	BLNU_motor_angle_control = false;
}

/**
 * BalancerUnit�̏I������
 */
void BLNU_post(void) {
	/* DO NOTHING*/
}

static BOOL BLNU_balance_startflg = FALSE; /* �o�����X�J�n�t���O */
static S8 BLNU_cmd_forward = 0; /* �O�i�R�}���h�l */
static S8 BLNU_cmd_turn = 0; /* ��]�R�}���h�l */
static U32 BLNU_gyro_offset = 0; /* �W���C���Z���T�I�t�Z�b�g�l */

/**
 * �O�i����
 */
void BLNU_forward(S8 command) {
	if (Max_VALUE < command) {
		command = Max_VALUE;
	}

	if (0 > command) {
		command = command * (-1);
	}

	BLNU_cmd_forward = command;
}

/**
 * ��ނ���
 */
void BLNU_backward(S8 command) {
	if (Min_VALUE > command) {
		command = Min_VALUE;
	}

	if (0 < command) {
		command = command * (-1);
	}

	BLNU_cmd_forward = command;
}

/**
 * �E�ɉ�]����
 */
void BLNU_turn_right(S8 command) {
	if (Max_VALUE < command) {
		command = Max_VALUE;
	}

	if (0 > command) {
		command = command * (-1);
	}

	BLNU_cmd_turn = command;
}

/**
 * ���ɉ�]����
 */
void BLNU_turn_left(S8 command) {
	if (command < Min_VALUE) {
		command = Min_VALUE;
	}

	if (0 < command) {
		command = command * (-1);
	}

	BLNU_cmd_turn = command;
}

/**
 * ���E�ɉ�]����
 */
void BLNU_turn(S8 command) {
	BLNU_cmd_turn = command;
}

/**
 * ��~����
 */
void BLNU_stop(void) {
	BLNU_cmd_forward = 0;
	BLNU_cmd_turn = 0;
}

/**
 * �W���C���Z���T�I�t�Z�b�g�l�̐ݒ�
 */
void BLNU_set_gyro_offset(void) {
	BLNU_gyro_offset = (U32) ecrobot_get_gyro_sensor(BLNU_PORT);
}

/**
 * �w�肵���p�x�����A���{�b�g���E��]������
 * ����angle�́A���{�b�g�̉�]�p�x
 */
extern BOOL BLNU_angle_turn_right(F32 angle) {

	/** ���[�^��]�R���g���[�����J�n����Ƃ��ɂ́A
	 *  �ŏ��̉�]�p�x���擾���� */
	if (BLNU_motor_angle_control == false) {
		BLNU_motor_angle_control = true;
		start_l_motor_rev = nxt_motor_get_count(L_MOTOR_PORT); /* ���̃��[�^�̉�]�p�x */
		start_r_motor_rev = nxt_motor_get_count(R_MOTOR_PORT); /* �E�̃��[�^�̉�]�p�x */
		F32 a = Robot_WIDTH; /* ���{�b�g�̉��� mm */
		F32 b = Wheel_DIAMETER; /* �^�C���̒��a mm */
		finish_motor_rev = 2* (a /b)*angle; /* angle�x��]�����邽�߂ɕK�v�ȍ��E�̃��[�^�̉�]�p�x�̍��v�l */
	}

	/** �E�ɉ�]���� */
	BLNU_cmd_forward = 0;
	BLNU_cmd_turn = 50;

	/** ���݂̍��E�̃��[�^��]�p�x�̍��v�l���A�ڕW�l�𒴂�����true��Ԃ� */
	if((nxt_motor_get_count(L_MOTOR_PORT) - start_l_motor_rev)
			+ (start_r_motor_rev - nxt_motor_get_count(R_MOTOR_PORT)) >=finish_motor_rev){
		BLNU_motor_angle_control = false;
		return true;
	}else{
		return false;
	}
}

		/**
		 * �w�肵���p�x�����A���{�b�g������]������
		 * ����angle�́A���{�b�g�̉�]�p�x
		 */
extern BOOL BLNU_angle_turn_left(F32 angle) {

	/** ���[�^��]�R���g���[�����J�n����Ƃ��ɂ́A
	 *  �ŏ��̉�]�p�x���擾���� */
	if (BLNU_motor_angle_control == false) {
		BLNU_motor_angle_control = true;
		start_l_motor_rev = nxt_motor_get_count(L_MOTOR_PORT); /* ���̃��[�^�̉�]�p�x */
		start_r_motor_rev = nxt_motor_get_count(R_MOTOR_PORT); /* �E�̃��[�^�̉�]�p�x */
		F32 a = Robot_WIDTH; /* ���{�b�g�̉��� mm */
		F32 b = Wheel_DIAMETER; /* �^�C���̒��a mm */
		finish_motor_rev = 2* (a /b)*angle; /* angle�x��]�����邽�߂ɕK�v�ȍ��E�̃��[�^�̉�]�p�x�̍��v�l */
	}

	/** ���ɉ�]���� */
	BLNU_cmd_forward = 0;
	BLNU_cmd_turn = -50;

	/** ���݂̍��E�̃��[�^��]�p�x�̍��v�l���A�ڕW�l�𒴂�����true��Ԃ� */
	if((nxt_motor_get_count(R_MOTOR_PORT) - start_r_motor_rev)
	+ (start_l_motor_rev - nxt_motor_get_count(L_MOTOR_PORT)) >= finish_motor_rev) {
		BLNU_motor_angle_control = false;
		return true;
	} else {
		return false;
	}
}

/**
 * �o�����X�R���g���[��
 */
void BLNU_balance_control(void) {
	S8 pwm_l, pwm_r;

	/* NXTway-GS C API balance control function (has to be invoked in 4msec period) */
	balance_control((F32) BLNU_cmd_forward, (F32) BLNU_cmd_turn,
			(F32) ecrobot_get_gyro_sensor(BLNU_PORT), (F32) BLNU_gyro_offset,
			(F32) nxt_motor_get_count(L_MOTOR_PORT), (F32) nxt_motor_get_count(
					R_MOTOR_PORT), (F32) ecrobot_get_battery_voltage(), &pwm_l,
			&pwm_r);
	nxt_motor_set_speed(L_MOTOR_PORT, pwm_l, 1);
	nxt_motor_set_speed(R_MOTOR_PORT, pwm_r, 1);
}

/**
 * �o�����X�R���g���[���J�n�t���O�Z�b�g
 */
extern void BLNU_balance_start(void) {
	BLNU_balance_startflg = TRUE;
}

/******************************************************************************
 * TASK			: BalanceTask
 * ARGUMENT		: none
 * RETURN		: none
 * DESCRIPTION 	: 4msec periodical Task
 *****************************************************************************/
TASK(BalanceTask)
{
	if (TRUE == BLNU_balance_startflg) {
		BLNU_balance_control();
	}

	TerminateTask();
}

/******************************** END OF FILE ********************************/
