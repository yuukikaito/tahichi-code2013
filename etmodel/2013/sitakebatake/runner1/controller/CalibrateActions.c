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

	int black,white,gray;

	while(!ecrobot_get_touch_sensor(NXT_PORT_S1)){
	}
	
		HU_ok_sound();
		black = LMU_is_line_value();
		//LMU_set_black_value(BLACK_VAL);
		LMU_set_black_value(black);
		systick_wait_ms(500);

	while(!ecrobot_get_touch_sensor(NXT_PORT_S1)){
	}
	
		HU_ok_sound();
		white = LMU_is_line_value();
		LMU_set_white_value(white);
		systick_wait_ms(500);

	gray=(white+black)/2;

		LMU_set_gray_value(gray);

		LMU_set_threshold(LIGHT_TH);

		/* BalancerUnit�̃I�t�Z�b�g�l���Z�b�g���� */

	while(!ecrobot_get_touch_sensor(NXT_PORT_S1)){
	}
	
		HU_ok_sound();
		BLNU_set_gyro_offset();
		systick_wait_ms(200);

}

/******************************** END OF FILE ********************************/
