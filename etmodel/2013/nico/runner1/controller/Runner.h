/*
 * COPYRIGHT(c)2010 Afrel Co., Ltd.
 * Runner.h
 * Runnerクラス
 *
 * クラス名: Runner(RN)
 * 属性:
 * 操作: get_state, do_run
 * 関連: RunActions(RA), CalibrateActions(CA),
 *       BalancerUnit(BLNU), BumperUnit(BU), common
 */

#ifndef __Runner_h__
#define __Runner_h__

#include "./com/common.h"

#include "RunActions.h"
#include "CalibrateActions.h"
#include "./unit/BalancerUnit.h"
#include "./unit/BumperUnit.h"


/**
 * Runnerの初期化処理
 */
extern void RN_pre(void);

/**
 * Runnerの終了処理
 */
extern void RN_post(void);


/**
 * Runnerの状態ゲット
 */
extern int RN_get_state(void);

/**
 * Runnerの状態遷移
 */
extern void RN_do_run(void);

#endif /* __Runner_h__ */
