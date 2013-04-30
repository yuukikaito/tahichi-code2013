/*
 * COPYRIGHT(c)2010 Afrel Co., Ltd.
 * RunActions.h
 * RunActions�N���X
 *
 * �N���X��: RunActions(RA)
 * ����:
 * ����: get_state, do_running, is_exit
 * �֘A: LineMonitorUnit(LMU), BalancerUnit(BLNU), common
 */

#ifndef __RunActions_h__
#define __RunActions_h__

#include "./com/common.h"

#include "./unit/LineMonitorUnit.h"
#include "./unit/BalancerUnit.h"
#include "./unit/DisplayUnit.h"
/**
 * RunActions�̏���������
 */
extern void RA_pre(void);

/**
 * RunActions�̏I������
 */
extern void RA_post(void);


/**
 * RunActions�̃����[�G���A�Ɉړ�
 */
extern void RA_takeover(void);

/**
 * RunActions�̑��s
 */
extern void RA_watch_goal_tracing(void);

//�Î~��Ԃ̎���
extern	void RA_stoppinglinetrace(void);

/**
 * RunActions�̒�~
 */
extern void RA_stop(void);

#endif /* __RunActions_h__ */
