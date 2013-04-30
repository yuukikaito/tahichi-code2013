/*
 * COPYRIGHT(c)2010 Afrel Co., Ltd.
 * Monitor.h
 * Monitorクラス
 *
 * クラス名: Monitor(M)
 * 属性:
 * 操作: M_inform
 * 関連: Runner(RN),
 *       DisplayUnit(DU), HornUnit(HU), LimeMonitorUnit(LM), common
 */

#ifndef __Monitor_h__
#define __Monitor_h__

#include "./com/common.h"

#include "Runner.h"
#include "./unit/DisplayUnit.h"
#include "./unit/HornUnit.h"
#include "./unit/LineMonitorUnit.h"

/**
 * Monitorの初期化処理
 */
extern void M_pre(void);

/**
 * Monitorの終了処理
 */
extern void M_post(void);

/**
 * 状態とその変化を音で表す
 */
extern void M_inform(void);

#endif /* __Monitor_h__ */
