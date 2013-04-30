/*
 * COPYRIGHT(c)2009 Afrel Co., Ltd.
 * DisplayUnit.h
 * 状態表示クラス
 *
 * クラス名: DisplayUnit(DU)
 * 属性: なし
 * 操作: show_string, show_number, clear
 * 関連: common
 */

#ifndef __DisplayUnit_h__
#define __DisplayUnit_h__

#include "./com/common.h"

/**
 * 液晶ディスプレイに文字を表示する
 *　 @param param 液晶ディスプレイに表示する文字
 */
extern void DU_show_string(int x, int y, char *param);

/**
 * 液晶ディスプレイに数字を表示する
 * @param status 液晶ディスプレイに表示する数字
 */
extern void DU_show_number(int x, int y, int status);

/**
 * 液晶ディスプレイをクリアする
 */
extern void DU_clear(void);

#endif /**__DisplayUnit_h__ */
