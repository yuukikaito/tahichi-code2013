/*
 * COPYRIGHT(c)2009 Afrel Co., Ltd.
 * TimerUnit.c
 * �^�C�}�N���X
 *
 * �N���X��: TimerUnit(TU)
 * ����: timerResult, timerCount, interval, timeOut, timerStart
 * ����: start, finish, isStart, isTimeout
 * �֘A: common
 */

#include "TimerUnit.h"

/** �^�C�}�̏�Ԃ�\���ϐ� �^�C���A�E�g�����Ƃ���TRUE(1)�C�^�C���A�E�g���Ă��Ȃ��Ƃ���FALSE(0)������ */
static int TU_timerResult = FALSE;
/** �^�C�}�̃J�E���g�l��\���ϐ� */
static int TU_timerCount = 0;
/** �^�C�}�Ԋu(ms)��\���ϐ� �^�X�N�̋N�������ƈ�v���� */
static int TU_interval = 10;
/** �^�C�A�E�g(ms)��\���ϐ� */
static int TU_timeOut = 0;
/** �^�C�}�̊Ď���Ԃ�\���ϐ� �Ď�����TRUE(1)�C�Ď����ł͂Ȃ��Ƃ���FALSE(0)������ */
static int TU_timerStart = FALSE;

/**
 * �^�C�}�̊Ď����J�n����
 * @param msec �^�C���A�E�g�܂ł̎���(msec)
 */
void TU_start(int msec) {
	TU_timerCount = 0;
	TU_timerResult = FALSE;
	TU_timeOut = msec;
	TU_timerStart = TRUE;
}

/**
 * �^�C�}�̊Ď����I������
 */
void TU_finish(void) {
	TU_timerCount = 0;
	TU_timerResult = FALSE;
	TU_timeOut = 0;
	TU_timerStart = FALSE;
}

/**
 * �^�C�}�̊Ď���Ԃ�����
 * @return int �Ď�����TRUE(1)�C�Ď����ł͂Ȃ��Ƃ���FALSE(0)��Ԃ�
 */
int TU_is_start(void) {
	return TU_timerStart;
}

/**
 * �^�C�}�̏�Ԃ�����
 * @return int �^�C���A�E�g�̂Ƃ���TRUE(1)��Ԃ��C����ȊO��FALSE(0)��Ԃ�
 */
int TU_is_timeout(void) {
	return TU_timerResult;
}

/**
 * �^�C�}�Ď����s��AlramCallback
 */
ALARMCALLBACK(CountTimer)
{
	if (TU_timerStart) {
		if (TU_timerCount == (TU_timeOut / TU_interval)) {
			TU_timerCount = 0;
			TU_timerResult = TRUE;
		}
		TU_timerCount++;
	}

	/** �^�X�N���I������ */
	TerminateTask();
}

