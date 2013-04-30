/*
 * COPYRIGHT(c)2010 Afrel Co., Ltd.
 * RunActions.h
 * RunActions�N���X
 *
 * �N���X��: RunActions(RA)
 * ����:
 * ����: get_state, do_running, is_exit
 * �֘A: LineMonitorUnit(LMU), BalancerUnit(BLNU),
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
 * RunActions�̏���������
 */
extern void RA_pre(void);

/**
 * RunActions�̏I������
 */
extern void RA_post(void);

/**
 * RunActions�̏�ԃQ�b�g
 */
extern int RA_get_state(void);

/**
 * RunActions�̏�ԑJ��
 */
extern void RA_do_running(void);

/**
 * RunActions�̍ŏI��Ԏ擾
 */
extern int RA_is_exit(void);

#endif /* __RunActions_h__ */
