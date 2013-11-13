/*
 * COPYRIGHT(c)2010 Afrel Co., Ltd.
 * CalibrateActions.c
 * CalibrateActionsクラス
 *
 * クラス名: CalibrateActions(CA)
 * 属性:
 * 操作: set_threshold
 * 関連: LineMonitorUnit(LMU), BalancerUnit(BLNU), common
 */


#include "CalibrateActions.h"


/**
 * CalibrateActionsの初期化処理
 */
void CA_pre(void) {
	LMU_pre(); /* LineMonitorUnitの初期化 */
	BLNU_pre(); /* BalancerUnitの初期化 */
}

/**
 * CalibrateActionsの終了処理
 */
void CA_post(void) {
	LMU_post(); /* LineMonitorUnitの終了処理 */
	BLNU_post(); /* BalancerUnitの終了処理 */
}

void CA_set_threshold(void) {

		/* LineMonitorUnitにセンサの値をセットする */

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

		/* BalancerUnitのオフセット値をセットする */

	while(!ecrobot_get_touch_sensor(NXT_PORT_S1)){
	}
	
		HU_ok_sound();
		BLNU_set_gyro_offset();
		systick_wait_ms(200);

}

/******************************** END OF FILE ********************************/
