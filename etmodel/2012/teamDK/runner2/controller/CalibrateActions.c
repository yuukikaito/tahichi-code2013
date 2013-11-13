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

void CA_set_threshold(void) {

		/* LineMonitorUnit�ɃZ���T�̒l���Z�b�g���� */
		while(FALSE == BU_is_touched()){}
		LMU_set_black_value(LMU_is_line_value());
		HU_ok_sound();
		systick_wait_ms(1000);
		while(FALSE == BU_is_touched()){}
		LMU_set_white_value(LMU_is_line_value());
		HU_ok_sound();
		systick_wait_ms(1000);
		/*while(FALSE == BU_is_touched()){}
		LMU_set_gray_value(LMU_is_line_value());
		HU_ok_sound();
		systick_wait_ms(1000);*/
		while(FALSE == BU_is_touched()){}
		LMU_set_threshold(LMU_is_line_value());
		HU_ok_sound();
		systick_wait_ms(1000);
		while(FALSE == BU_is_touched()){}
		systick_wait_ms(500);

		/* BalancerUnit�̃I�t�Z�b�g�l���Z�b�g���� */
		BLNU_set_gyro_offset();

}

/******************************** END OF FILE ********************************/
