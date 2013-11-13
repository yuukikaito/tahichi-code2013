/*
 * COPYRIGHT(c)2009 Afrel Co., Ltd.
 * HornUnit.h
 * クラクションクラス
 *
 * クラス名: HornUnit(HU)
 * 属性: なし
 * 操作: ok_sound, error_sound, warn_sound, confir_sound
 * 関連: common
 */

#ifndef __HornUnit_h__
#define __HornUnit_h__

#include "./com/common.h"

#define VOL 20

/**
 * 正常の音を鳴らす
 */
extern void HU_ok_sound(void);

/**
 * 到着の音を鳴らす
 */
extern void HU_arrival_sound(void);

/**
 * エラー時の音を鳴らす
 */
extern void HU_error_sound(void);

/**
 * 警告時の音を鳴らす
 */
extern void HU_warn_sound(void);

/**
 * 確認時の音を鳴らす
 */
extern void HU_confir_sound(void);

#endif /**__HornUnit_h__ */
