/*
 * COPYRIGHT(c)2009 Afrel Co., Ltd.
 * LineMonitorUnit.c
 * ���C���Ď��N���X
 *
 * �N���X��: LineMonitorUnit(LMU)
 * ����: threshold
 * ����: set_threshold, get_threshold, is_online, is_gray, pre, post
 * �֘A: common
 */

#include "LineMonitorUnit.h"

/* ���C������臒l */
static unsigned int LMU_threshold = 0;

/* ���E�O���C�E���̒l */
static unsigned int LMU_white_value = 0;
static unsigned int LMU_gray_value = 0;
static unsigned int LMU_black_value = 0;

/**
 * ���C���Ď���臒l��ݒ肷��
 */
void LMU_set_threshold(int threshold) {
	LMU_threshold = threshold;
}

/**
 * ���C���Ď���臒l���擾����
 * @return int �ݒ肳�ꂽ臒l�̒l��Ԃ�
 */
int LMU_get_threshold(void) {
	return LMU_threshold;
}

/**
 * ���̒l��ݒ肷��
 */
void LMU_set_white_value(int value) {
	LMU_white_value = value;
}

/**
 * �ݒ肳�ꂽ���̒l���擾����
 * @return int �ݒ肳�ꂽ���̒l��Ԃ�
 */
int LMU_get_white_value(void) {
	return LMU_white_value;
}

/**
 * �O���C�̒l��ݒ肷��
 */
void LMU_set_gray_value(int value) {
	LMU_gray_value = value;
}

/**
 * �ݒ肳�ꂽ�O���C�̒l���擾����
 * @return int �ݒ肳�ꂽ�O���C�̒l��Ԃ�
 */
int LMU_get_gray_value(void) {
	return LMU_gray_value;
}

/**
 * ���̒l��ݒ肷��
 */
void LMU_set_black_value(int value) {
	LMU_black_value = value;
}

/**
 * �ݒ肳�ꂽ���̒l���擾����
 * @return int �ݒ肳�ꂽ���̒l��Ԃ�
 */
int LMU_get_black_value(void) {
	return LMU_black_value;
}

/**
 * ���C���Ď��̏�Ԃ�����
 * @return int 臒l�����Z���T�����̂Ƃ��ɂP
 *�@���̂Ƃ���0
 *�@�O���C�̂Ƃ���1��Ԃ�
 */
int LMU_is_online(void) {
	int light_value;
	light_value = ecrobot_get_light_sensor(LMU_PORT);
	if (LMU_threshold > light_value) {
		if ((LMU_gray_value - 20) > light_value) {
			return FALSE;
		} else {
			return TRUE;
		}
	}
	return TRUE;
}

/**
 * �O���C�̏�Ԃ�����
 * @return int �O���C�ł���΂P
 *�@�O���C�łȂ����0��Ԃ�
 */
int LMU_is_gray(void) {
	int light_value;
	light_value = ecrobot_get_light_sensor(LMU_PORT);
	if ((light_value < (LMU_gray_value + GRAY_PU_MA)) && (light_value
			>= (LMU_gray_value - GRAY_PU_MA))) {
		return TRUE;
	}
	return FALSE;
}

/**
 * ���C���̒l������
 */
int LMU_is_line_value(void) {
	return ecrobot_get_light_sensor(LMU_PORT);
}

/**
 * ���C���Ď��̏���������(���Z���T���A�N�e�B�u�ɂ���)
 */
void LMU_pre(void) {
	ecrobot_set_light_sensor_active(LMU_PORT);
}

/**
 * ���C���Ď��̏I������(���Z���T���p�b�V�u�ɂ���)
 */
void LMU_post(void) {
	ecrobot_set_light_sensor_inactive(LMU_PORT);
}

