/*
 * COPYRIGHT(c)2010 Afrel Co., Ltd.
 * RunActions.h
 * RunActionsクラス
 *
 * クラス名: RunActions(RA)
 * 属性:
 * 操作: get_state, do_running, is_exit
 * 関連: LineMonitorUnit(LMU), BalancerUnit(BLNU),
 *       BumperUnit(BU), BlockMonitorUnit(BMU),
 *       CommunicationUnit(CU), common
 */

#ifndef __RunActions_h__
#define __RunActions_h__

#include "./com/common.h"

#include "./unit/LineMonitorUnit.h"
#include "./unit/BalancerUnit.h"
#include "./unit/BumperUnit.h"
#include "./unit/BlockMonitorUnit.h"
#include "./unit/CommunicationUnit.h"
#include "./unit/TimerUnit.h"

/**
 * RunActionsの初期化処理
 */
extern void RA_pre(void);

/**
 * RunActionsの終了処理
 */
extern void RA_post(void);

/**
 * RunActionsの状態ゲット
 */
extern int RA_get_state(void);

/**
 * RunActionsの状態遷移
 */
extern void RA_do_running(void);

/**
 * RunActionsの最終状態取得
 */
extern int RA_is_exit(void);

#endif /* __RunActions_h__ */
