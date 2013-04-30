/*
 * COPYRIGHT(c)2010 Afrel Co., Ltd.
 * RunActions.h
 * RunActionsクラス
 *
 * クラス名: RunActions(RA)
 * 属性:
 * 操作: get_state, do_running, is_exit
 * 関連: LineMonitorUnit(LMU), BalancerUnit(BLNU), common
 */

#ifndef __RunActions_h__
#define __RunActions_h__

#include "./com/common.h"

#include "./unit/LineMonitorUnit.h"
#include "./unit/BalancerUnit.h"
#include "./unit/DisplayUnit.h"
/**
 * RunActionsの初期化処理
 */
extern void RA_pre(void);

/**
 * RunActionsの終了処理
 */
extern void RA_post(void);


/**
 * RunActionsのリレーエリアに移動
 */
extern void RA_takeover(void);

/**
 * RunActionsの走行
 */
extern void RA_watch_goal_tracing(void);

//静止状態の実現
extern	void RA_stoppinglinetrace(void);

/**
 * RunActionsの停止
 */
extern void RA_stop(void);

#endif /* __RunActions_h__ */
