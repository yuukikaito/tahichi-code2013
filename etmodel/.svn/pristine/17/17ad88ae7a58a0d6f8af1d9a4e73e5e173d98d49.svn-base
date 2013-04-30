/*
 * COPYRIGHT(c)2010 Afrel Co., Ltd.
 * Runner.c
 * Runnerクラス
 *
 * クラス名: Runner(RN)
 * 属性:
 * 操作: get_state, do_run
 * 関連: RunActions(RA), CalibrateActions(CA),
 *       BumperUnit(BU), BalancerUnit(BLNU),CommunicationUnit(CU),
 *       TimerUnit(TU), common
 */

#include "Runner.h"

/*
 * スレーブ側のBluetoothデバイスアドレス
 */
const static unsigned char bd_addr[7] = { 0x00, 0x16, 0x53, 0x13, 0xB3, 0x60, 0x00 };

/*
 * システム全体の走行状態
 */
typedef enum {
	RN_STATE_CALIBRATE1,
	RN_STATE_CALIBRATE2,
	RN_STATE_CALIBRATE3,
	RN_STATE_RADY,
	RN_STATE_ZERO_SPEED1,
	RN_STATE_BUMP_RADY,
	RN_STATE_TAKEOVER,
	RN_STATE_ZERO_SPEED2,
	RN_STATE_RUN,
	RN_STATE_FINISH
} RN_STATE;

static RN_STATE RN_state;

/**
 * 状態セット用のプライベート関数
 */
void RN_set_state(int state);

/*
 * 各状態に対応するプライベート関数
 */
void RN_calibrate1();
void RN_calibrate2();
void RN_calibrate3();
void RN_ready();
void RN_zero_speed1();
void RN_bump_ready();
void RN_zero_speed2();
void RN_takeover();
void RN_run();

/**
 * Runnerの初期化処理
 */
void RN_pre(void) {
	RN_set_state(RN_STATE_CALIBRATE1);

	CA_pre();
	RA_pre();

	CU_set_mode(0, bd_addr); /* スレーブに設定 */
	CU_pre(); /* CommUnitの初期化 */

}

/**
 * Runnerの終了処理
 */
void RN_post(void) {
	CA_post();
	RA_post();

	CU_post(); /* CommUnitの終了処理 */

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
	case (RN_STATE_CALIBRATE1):
		RN_calibrate1();
		break;

	case (RN_STATE_CALIBRATE2):
		RN_calibrate2();
		break;

	case (RN_STATE_CALIBRATE3):
		RN_calibrate3();
		break;

	case (RN_STATE_RADY):
		RN_ready();
		break;

	case (RN_STATE_BUMP_RADY):
		RN_bump_ready();
		break;

	case (RN_STATE_ZERO_SPEED1):
		RN_zero_speed1();
		break;

	case (RN_STATE_TAKEOVER):
		RN_takeover();
		break;

	case (RN_STATE_ZERO_SPEED2):
		RN_zero_speed2();
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

void RN_calibrate1() {
	if(TRUE == BU_is_clicked()){
		CA_set_white_val();

		RN_set_state(RN_STATE_CALIBRATE2);
	}
}

void RN_calibrate2() {
	if(TRUE == BU_is_clicked()){
		CA_set_black_val_and_threshold();

		RN_set_state(RN_STATE_CALIBRATE3);
	}
}

void RN_calibrate3() {
	if(TRUE == BU_is_clicked()){
		CA_set_gyro_offset();

		BLNU_balance_start();
		RN_set_state(RN_STATE_RADY);
	}
}

void RN_ready() {
	int nouse;
	
	CU_set_recvMSG(77);
	
	nouse = RA_nomove();
	
	/* タイマが開始されていなかったら */
	if (!TU_is_start()) {
		/** 90秒のタイマ監視開始 */
		TU_start(90000);
	}

	/* スタート準備指示で走り出す */
	if (TRUE == CU_is_received()) {

		CU_set_sendMSG(99);
		CU_send_mail();
		
		TU_finish();

		RN_set_state(RN_STATE_ZERO_SPEED1);
	}
	
	if(TRUE == BU_is_clicked()){
		TU_finish();
		
		RN_set_state(RN_STATE_ZERO_SPEED1);
	}

	/* 90秒経過したら */
	if (TRUE == TU_is_timeout()) {

		/** タイマ監視を終了させる */
		TU_finish();

		RN_set_state(RN_STATE_BUMP_RADY);
	}

}

void RN_bump_ready() {
	int nouse;
	
	nouse = RA_nomove();

	/* 繰り上げスタート準備指示で走り出す */
	if (TRUE == BU_is_clicked()) {
		RN_set_state(RN_STATE_RUN);
	}
}

void RN_zero_speed1() {
	int count;
	
	count = RA_nomove();
	
	if(count == 0){
		RN_set_state(RN_STATE_TAKEOVER);
	}
}

void RN_takeover() {
	int nouse;
	
	CU_set_recvMSG(77);
	
	/* タイマが開始されていなかったら */
	if (!TU_is_start()) {
		/** 6秒のタイマ監視開始 */
		TU_start(6000);
	}
	
	/* 6秒経過したら */
	if (TRUE == TU_is_timeout()) {
		nouse = RA_nomove();
	}else{
		RA_takeover();
	}

	
	/* スタート指示を受けたら次の状態に遷移する */
	if (TRUE == CU_is_received()) {
		RA_stop();

		CU_set_sendMSG(99);
		CU_send_mail();

		RN_set_state(RN_STATE_ZERO_SPEED2);

	}
	
	if(TRUE == BU_is_clicked()){
		TU_finish();
		
		RN_set_state(RN_STATE_ZERO_SPEED2);
	}
}

void RN_zero_speed2() {
	int count;
	
	count = RA_nomove();
	
	if(count == 0){
		RN_set_state(RN_STATE_RUN);
	}
}

void RN_run() {
	RA_watch_goal_tracing();

	/* バンパが押されたら次の状態に遷移する */
	if (TRUE == BU_is_touched()) {
		/* 停止する */
		RA_stop();

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
