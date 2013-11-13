/*
 * COPYRIGHT(c)2010 Afrel Co., Ltd.
 * CalibrateActions.h
 * CalibrateActions�N���X
 *
 * �N���X��: CalibrateActions(CA)
 * ����:
 * ����: set_threshold
 * �֘A: LineMonitorUnit(LMU), BalancerUnit(BLNU), common
 */

#ifndef __CalibrateActions_h__
#define __CalibrateActions_h__

#define BLACK_VAL	650
#define WHITE_VAL	470
#define GRAY_VAL	520
#define LIGHT_TH	560
#define MSEC     	10000

#include "./com/common.h"

#include "./unit/LineMonitorUnit.h"
#include "./unit/BalancerUnit.h"
#include "./unit/TimerUnit.h"

/**
 * CalibrateActions�̏���������
 */
extern void CA_pre(void);

/**
 * CalibrateActions�̏I������
 */
extern void CA_post(void);

/*
 * �L�����u���[�V�����p�֐�
 */
extern void CA_set_threshold(void);

#endif /* __CalibrateActions_h__ */
