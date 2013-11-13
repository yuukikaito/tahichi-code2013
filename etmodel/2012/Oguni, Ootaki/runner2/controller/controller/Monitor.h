/*
 * COPYRIGHT(c)2010 Afrel Co., Ltd.
 * Monitor.h
 * Monitor�N���X
 *
 * �N���X��: Monitor(M)
 * ����:
 * ����: M_inform
 * �֘A: Runner(RN),
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
 * Monitor�̏���������
 */
extern void M_pre(void);

/**
 * Monitor�̏I������
 */
extern void M_post(void);

/**
 * ��ԂƂ��̕ω������ŕ\��
 */
extern void M_inform(void);

#endif /* __Monitor_h__ */
