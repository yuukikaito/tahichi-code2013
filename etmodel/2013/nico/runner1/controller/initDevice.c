/*
 * COPYRIGHT(c)2009 Afrel Co., Ltd.
 * initDevice.c
 * �f�o�C�X�������N���X
 *
 * �N���X��: initDevice(C)
 * ����: �Ȃ�
 * ����: ecrobot_device_initialize, ecrobot_device_terminate, user_1ms_isr_type2
 * �֘A: Calibrater(CR)
 */

#include "Runner.h"

/* �J�E���^�̐錾 */
DeclareCounter( SysTimerCnt);

/*--------------------------------------------------------------------------*/
/* Definitions                                                              */
/*--------------------------------------------------------------------------*/
int digits;

/*--------------------------------------------------------------------------*/
/* ECRobot hooks                                                            */
/*--------------------------------------------------------------------------*/
const U8 target_subsystem_name[] = "DesignTest";

void ecrobot_device_initialize() {
	/* write NXT device initializations */
	RN_pre();
}

void ecrobot_device_terminate() {
	/* write NXT device terminations */
	RN_post();
}

/*--------------------------------------------------------------------------*/
/* OSEK hooks                                                               */
/*--------------------------------------------------------------------------*/
void StartupHook(void) {
}
void ShutdownHook(StatusType ercd) {
}
void PreTaskHook(void) {
}
void PostTaskHook(void) {
}
void ErrorHook(StatusType ercd) {
}

/*--------------------------------------------------------------------------*/
/* Function to be invoked from a category 2 interrupt                       */
/*--------------------------------------------------------------------------*/
void user_1ms_isr_type2(void) {
	StatusType ercd;
	/*
	 *  Increment OSEK Alarm System Timer Count
	 */
	ercd = SignalCounter(SysTimerCnt);
	if (ercd != E_OK) {
		ShutdownOS(ercd);
	}
}

