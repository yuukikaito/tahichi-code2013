/*
 * COPYRIGHT(c)2010 Afrel Co., Ltd.
 * CalibrateActions.h
 * CalibrateActionsクラス
 *
 * クラス名: CalibrateActions(CA)
 * 属性:
 * 操作: set_threshold
 * 関連: LineMonitorUnit(LMU), BalancerUnit(BLNU), common
 */

#ifndef __CalibrateActions_h__
#define __CalibrateActions_h__

//#define BLACK_VAL	650
//#define WHITE_VAL	470
//#define GRAY_VAL	520
//#define LIGHT_TH	560

#include "./com/common.h"

#include "./unit/LineMonitorUnit.h"
#include "./unit/BalancerUnit.h"

/**
 * CalibrateActionsの初期化処理
 */
extern void CA_pre(void);

/**
 * CalibrateActionsの終了処理
 */
extern void CA_post(void);

/*
 * キャリブレーション用関数
 */
extern void CA_set_threshold(void);

#endif /* __CalibrateActions_h__ */
