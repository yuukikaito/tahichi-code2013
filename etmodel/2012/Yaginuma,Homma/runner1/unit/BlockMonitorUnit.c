/*
 * COPYRIGHT(c)2009 Afrel Co., Ltd.
 * BlockMonitorUnit.c
 * ��Q���Ď��N���X
 *
 * �N���X��: BlockMonitorUnit(BMU)
 * ����: threshold
 * ����: set_threshold, get_threshold, is_found, pre, post
 * �֘A: common
 */

#include "BlockMonitorUnit.h"

/* ��Q����������臒l */
static unsigned int BMU_threshold = 0;

/**
 * ��Q���Ď���臒l��ݒ肷��
 */
void BMU_set_threshold(int threshold) {
	BMU_threshold = threshold;
}

/**
 * ��Q���Ď���臒l���擾����
 * @return int �ݒ肳�ꂽ臒l�̒l��Ԃ�
 */
int BMU_get_threshold(void) {
	return BMU_threshold;
}

/**
 * ��Q���Ď��̏�Ԃ�����
 * @return int 臒l��蒴���g�Z���T�̒l��������(�߂�)�Ƃ���TRUE(1)�C�傫��(����)�Ƃ���FALSE(0)��Ԃ�
 */
int BMU_is_found(void) {
	if ((0 != ecrobot_get_sonar_sensor(BMU_PORT)) && (255
			!= ecrobot_get_sonar_sensor(BMU_PORT))) {
		if (BMU_threshold > ecrobot_get_sonar_sensor(BMU_PORT)) {
			return TRUE;
		}
	}
	return FALSE;
}

/**
 * ��Q���Ď��̏���������(�����g�Z���T�̏���������)
 */
void BMU_pre(void) {
	ecrobot_init_sonar_sensor(BMU_PORT);
}

/**
 * ��Q���Ď��̏I������(�����g�Z���T�̏I������)
 */
void BMU_post(void) {
	ecrobot_term_sonar_sensor(BMU_PORT);
}

