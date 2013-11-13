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

		/* BalancerUnitのオフセット値をセットする */
		BLNU_set_gyro_offset();

}

/******************************** END OF FILE ********************************/
