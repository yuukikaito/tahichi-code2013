/*
 * COPYRIGHT(c)2009 Afrel Co., Ltd.
 * DisplayUnit.c
 * 状態表示クラス
 *
 * クラス名: DisplayUnit(DU)
 * 属性: なし
 * 操作: show_string, show_number, clear
 * 関連: common
 */

#include "DisplayUnit.h"

/**
 * 液晶ディスプレイに文字を表示する
 * @param param 液晶ディスプレイに表示する文字
 */
void DU_show_string(int x, int y, char *param) {
	display_goto_xy(x, y);
	display_string(param);
	display_update();
}

/**
 * 液晶ディスプレイに数字を表示する
 * @param status 液晶ディスプレイに表示する数字
 */
void DU_show_number(int x, int y, int status) {
	display_goto_xy(x, y);
	display_unsigned(status, 0);
	display_update();
}

/**
 * 液晶ディスプレイをクリアする
 */
void DU_clear(void) {
	display_clear(0);
	display_update();
}
