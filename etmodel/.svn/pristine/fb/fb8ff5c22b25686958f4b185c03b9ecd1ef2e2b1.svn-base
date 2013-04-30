/*
 * COPYRIGHT(c)2010 Afrel Co., Ltd.
 * Runner.c
 * Runnerクラス
 *
 * クラス名: Runner(RN)
 * 属性:
 * 操作: get_state, do_run
 * 関連: RunActions(RA), CalibrateActions(CA),
 *       BalancerUnit(BLNU), BumperUnit(BU), common
 */

#include "Runner.h"

/*
 * システム全体の走行状態
 */
typedef enum {
	RN_STATE_CALIBRATE, RN_STATE_RADY, RN_STATE_RUN, RN_STATE_FINISH
} RN_STATE;

static RN_STATE RN_state;

/**
 * 状態セット用のプライベート関数
 */
void RN_set_state(int state);

/*
 * 各状態に対応するプライベート関数
 */
void RN_calibrate();
void RN_rady();
void RN_run();

/**
 * Runnerの初期化処理
 */
void RN_pre(void) {
	RN_set_state(RN_STATE_CALIBRATE);

	CA_pre();
	RA_pre();

}

/**
 * Runnerの終了処理
 */
void RN_post(void) {
	CA_post();
	RA_post();
}

/**
 * Runnerの状態セット
 */
void RN_set_state(int state) {
	RN_state = state;
}

/**
 * Runnerの状態ゲット
 */
int RN_get_state(void) {
	return RN_state;
}

/**
 * Runnerの状態遷移
 */
void RN_do_run() {
	switch (RN_state) {
	case (RN_STATE_CALIBRATE):
		RN_calibrate();
		break;

	case (RN_STATE_RADY):
		RN_rady();
		break;

	case (RN_STATE_RUN):
		RN_run();
		break;

	case (RN_STATE_FINISH):
		/* DO NOTHING */
		break;

	default:
		/* DO NOTHING*/
		break;
	}
}

void RN_calibrate() {
	CA_set_threshold();

	BLNU_balance_start();
	RN_set_state(RN_STATE_RUN);
}

void RN_rady() {

	if (TRUE == BU_is_clicked()) {
		RN_set_state(RN_STATE_RUN);
	}

}

void RN_run() {
	RA_do_running();

	if (RA_is_exit()) {
		RN_set_state(RN_STATE_FINISH);
	}
}

/******************************************************************************
 * TASK			: ActionTask
 * ARGUMENT		: none
 * RETURN		: none
 * DESCRIPTION 	: 40msec periodical Task
 *****************************************************************************/
TASK(ActionTask)
{

	RN_do_run();

	TerminateTask();
}

/******************************** END OF FILE ********************************/
