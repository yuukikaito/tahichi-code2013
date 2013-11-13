/*
 * COPYRIGHT(c)2010 Afrel Co., Ltd.
 * Runner.h
 * Runner�N���X
 *
 * �N���X��: Runner(RN)
 * ����:
 * ����: get_state, do_run
 * �֘A: RunActions(RA), CalibrateActions(CA),
 *       BumperUnit(BU), BalancerUnit(BLNU),CommunicationUnit(CU),
 *       TimerUnit(TU), common
 */

#ifndef __Runner_h__
#define __Runner_h__

#include "./com/common.h"

#include "RunActions.h"
#include "CalibrateActions.h"
#include "./unit/BumperUnit.h"
#include "./unit/BalancerUnit.h"
#include "./unit/CommunicationUnit.h"
#include "./unit/TimerUnit.h"

/**
 * Runner�̏���������
 */
extern void RN_pre(void);

/**
 * Runner�̏I������
 */
extern void RN_post(void);

/**
 * Runner�̏�ԃQ�b�g
 */
extern int RN_get_state(void);

/**
 * Runner�̏�ԑJ��
 */
extern void RN_do_run(void);

#endif /* __Runner_h__ */
