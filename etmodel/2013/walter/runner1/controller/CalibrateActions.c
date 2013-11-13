/*
 * COPYRIGHT(c)2010 Afrel Co., Ltd.
 * CalibrateActions.c
 * CalibrateActions�N���X
 *
 * �N���X��: CalibrateActions(CA)
 * ����:
 * ����: set_threshold
 * �֘A: LineMonitorUnit(LMU), BalancerUnit(BLNU), common
 */


#include "CalibrateActions.h"


/**
 * CalibrateActions�̏���������
 */
void CA_pre(void) {
	LMU_pre(); /* LineMonitorUnit�̏����� */
	BLNU_pre(); /* BalancerUnit�̏����� */
}

/**
 * CalibrateActions�̏I������
 */
void CA_post(void) {
	LMU_post(); /* LineMonitorUnit�̏I������ */
	BLNU_post(); /* BalancerUnit�̏I������ */
}

/* void CA_set_threshold(void) { */
void CA_set_threshold(int BLACK_VAL, int WHITE_VAL, int GRAY_VAL, int LIGHT_TH) {
		/* LineMonitorUnit�ɃZ���T�̒l���Z�b�g���� */
		LMU_set_black_value(BLACK_VAL);
		LMU_set_white_value(WHITE_VAL);
		LMU_set_gray_value(GRAY_VAL);
		LMU_set_threshold(LIGHT_TH);

		/* BalancerUnit�̃I�t�Z�b�g�l���Z�b�g���� */
		/* BLNU_set_gyro_offset(); */

}

/******************************** END OF FILE ********************************/
