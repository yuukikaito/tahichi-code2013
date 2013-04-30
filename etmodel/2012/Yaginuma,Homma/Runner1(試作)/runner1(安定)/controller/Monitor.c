/*
 * COPYRIGHT(c)2010 Afrel Co., Ltd.
 * Monitor.c
 * Monitorクラス
 *
 * クラス名: Monitor(M)
 * 属性:
 * 操作: M_inform
 * 関連: Runner(RN), RunActions(RA),
 *       DisplayUnit(DU), HornUnit(HU), LimeMonitorUnit(LM), common
 */

#include "Monitor.h"

/**
 * Monitorの初期化処理
 */
void M_pre(void) {
	/* DO NOTHING */
}

/**
 * Monitorの終了処理
 */
void M_post(void) {
	/* DO NOTHING */
}

/**
 * 状態とその変化を音で表す
 */
void M_inform(void) {
	static int RN_state = 0;
	static int RA_state = 0;

	if (RN_state != RN_get_state()) {
		HU_ok_sound();
		RN_state = RN_get_state();
	}

	if (RA_state != RA_get_state()) {
		HU_ok_sound();
		RA_state = RA_get_state();
	}

	DU_show_string(0, 0, "Runner");
	DU_show_number(10, 0, RN_state);
	DU_show_string(0, 1, "RunAc");
	DU_show_number(10, 1, RA_state);

	DU_show_string(0, 4, "BLACK_Th");
	DU_show_number(10, 4, LMU_get_black_value());

	DU_show_string(0, 5, "WHITE_Th");
	DU_show_number(10, 5, LMU_get_white_value());

	DU_show_string(0, 6, "GRAY_Th");
	DU_show_number(10, 6, LMU_get_gray_value());

}

/******************************************************************************
 * TASK			: DisplayTask
 * ARGUMENT		: none
 * RETURN		: none
 * DESCRIPTION 	: Background(never terminated) Task
 *****************************************************************************/
TASK(DisplayTask)
{
	M_inform();

	TerminateTask();
}

/******************************** END OF FILE ********************************/
