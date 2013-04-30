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
#include "./unit/HornUnit.h"
#include "./unit/BumperUnit.h"


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
	/*
	int time = 0;
		/*LineMonitorUnitにセンサの値をセットする */
		while(1){
			if(BU_is_touched()){
				HU_ok_sound();
				LMU_set_black_value( LMU_is_line_value() );
				systick_wait_ms(500);
				break;
			}
		}
		while(1){
			if(BU_is_touched()){
				HU_ok_sound();
				LMU_set_white_value( LMU_is_line_value() );
				systick_wait_ms(500);
				break;
			}
		}
		LMU_set_gray_value((LMU_get_black_value()+LMU_get_white_value())/2);
		LMU_set_threshold((LMU_get_black_value()+LMU_get_white_value())/2);

		while(1){
			if(BU_is_touched()){
				HU_ok_sound();
				BLNU_set_gyro_offset();
				systick_wait_ms(500);
				break;
			}
		}

		while(1){
			if(BU_is_touched()){
				break;
			}
		}

		//LMU_set_black_value(BLACK_VAL);
		//LMU_set_white_value(WHITE_VAL);
		//LMU_set_gray_value(GRAY_VAL);
		//LMU_set_threshold(LIGHT_TH);

		/* BalancerUnitのオフセット値をセットする */
		//BLNU_set_gyro_offset();

}

/******************************** END OF FILE ********************************/
