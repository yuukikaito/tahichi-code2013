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
	TU_finish(); /*TimerUnitの終了処理*/	
}

void CA_set_threshold(void) {

		/* LineMonitorUnitにセンサの値をセットする */
		LMU_set_black_value(BLACK_VAL);
		LMU_set_white_value(WHITE_VAL);
		LMU_set_gray_value(GRAY_VAL);
		LMU_set_threshold(LIGHT_TH);

		/* BalancerUnitのオフセット値をセットする */
		BLNU_set_gyro_offset();
		
		/*Timerのスタート*/
		TU_start(MSEC);	//変更
}

/******************************** END OF FILE ********************************/
