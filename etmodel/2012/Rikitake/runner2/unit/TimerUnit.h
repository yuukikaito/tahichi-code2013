/*
 * COPYRIGHT(c)2009 Afrel Co., Ltd.
 * TimerUnit.h
 * �^�C�}�N���X
 *
 * �N���X��: TimerUnit(TU)
 * ����: timerResult, timerCount, interval, timeOut, timerStart
 * ����: start, finish, is_start, is_timeout
 * �֘A: common
 */

#ifndef __TimerUnit_h__
#define __TimerUnit_h__

#include "./com/common.h"

/**
 * �^�C�}�̊Ď����J�n����
 * @param msec �^�C���A�E�g�܂ł̎���(msec)
 */
extern void TU_start(int msec);

/**
 * �^�C�}�̊Ď����I������
 */
extern void TU_finish(void);

/**
 * �^�C�}�̊Ď���Ԃ�����
 * @return int �Ď�����TRUE(1)�C�Ď����ł͂Ȃ��Ƃ���FALSE(0)��Ԃ�
 */
extern int TU_is_start(void);

/**
 * �^�C�}�̏�Ԃ�����
 * @return int �^�C���A�E�g�̂Ƃ���TRUE(1)��Ԃ��C����ȊO��FALSE(0)��Ԃ�
 */
extern int TU_is_timeout(void);

#endif /**__TimerUnit_h__ */
