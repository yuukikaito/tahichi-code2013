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

void CA_set_white_val(void) {
	LMU_set_white_value(LMU_is_line_value());
}

void CA_set_black_val_and_threshold(void) {
	int thre;
		/* LineMonitorUnitにセンサの値をセットする */
		LMU_set_black_value(LMU_is_line_value());
		LMU_set_gray_value(GRAY_VAL);
	
	thre = (int)((LMU_get_black_value() + LMU_get_white_value())/2);
		LMU_set_threshold(thre);

}

void CA_set_gyro_offset(void) {
		/* BalancerUnitのオフセット値をセットする */
		BLNU_set_gyro_offset();
}

/******************************** END OF FILE ********************************/
