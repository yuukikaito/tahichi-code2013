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

void CA_set_white_val(void) {
	LMU_set_white_value(LMU_is_line_value());
}

void CA_set_black_val_and_threshold(void) {
	int thre;
		/* LineMonitorUnit�ɃZ���T�̒l���Z�b�g���� */
		LMU_set_black_value(LMU_is_line_value());
		LMU_set_gray_value(GRAY_VAL);
	
	thre = (int)((LMU_get_black_value() + LMU_get_white_value())/2);
		LMU_set_threshold(thre);

}

void CA_set_gyro_offset(void) {
		/* BalancerUnit�̃I�t�Z�b�g�l���Z�b�g���� */
		BLNU_set_gyro_offset();
}

/******************************** END OF FILE ********************************/
