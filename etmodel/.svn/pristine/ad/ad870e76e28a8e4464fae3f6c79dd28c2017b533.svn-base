/*
 * COPYRIGHT(c)2010 Afrel Co., Ltd.
 * RunActions.c
 * RunActionsクラス
 *
 * クラス名: RunActions(RA)
 * 属性:
 * 操作: get_state, do_running, is_exit
 * 関連: LineMonitorUnit(LMU), BalancerUnit(BLNU),
 *       BumperUnit(BU), BlockMonitorUnit(BMU),
 *       CommunicationUnit(CU), common
 */

#include "RunActions.h"

#define	MIN_DISTANCE (25)		/* 壁感知距離 */

/*
 * スレーブ側のBluetoothデバイスアドレス
 */
const static unsigned char bd_addr[7] = { 0x00, 0x16, 0x53, 0x12, 0x27, 0xB5,
		0x00 };

/*
 * 走行中の状態
 */
typedef enum {
	RA_STATE_WATCH_BLOCK,
	RA_STATE_WAIT_PRE_START_CONF,
	RA_STATE_SHORT_CUT,
	RA_STATE_TURN,
	RA_STATE_TURN2,
	RA_STATE_TURN_IN_WHITE,
	RA_STATE_WATCH_GOAL,
	RA_STATE_WAIT_START_CONF,
	RA_STATE_FINISH
} RA_STATE;

static RA_STATE RA_state;

/*
 * 状態セット用のプライベート関数
 */
void RA_set_state(int state);

/*
 * 各状態に対応するプライベート関数
 */
void RA_watch_block_tracing();
void RA_watch_goal_tracing();
void RA_short_cut();
void RA_turn();
void RA_turn2();
void RA_turn_in_white();
void RA_wait_pre_start_conf();
void RA_wait_start_conf();
void RA_linetrace(int forward_speed, int turn_speed);
void RA_linetrace_P(int forward_speed);
void RA_stop();
void RA_turn_right();
void RA_turn_left();
int i;

/**
 * RunActionsの初期化処理
 */
void RA_pre(void) {
	RA_set_state(RA_STATE_WATCH_BLOCK);

	BMU_pre(); /* BlockMonitorUnitの初期化 */
	BMU_set_threshold(MIN_DISTANCE); /* BlockMonitorUnitの閾値設定 */

	CU_set_mode(1, bd_addr); /* マスタに設定 */
	CU_pre(); /* CommUnitの初期化 */
}

/**
 * RunActionsの終了処理
 */
void RA_post(void) {
	BMU_post(); /* BlockMonitorUnitの終了処理 */

	CU_post(); /* CommUnitの終了処理 */

}

/**
 * RunActionsの状態セット
 */
void RA_set_state(int state) {
	RA_state = state;
}

/**
 * RunActionsの状態ゲット
 */
int RA_get_state(void) {
	return RA_state;
}

/**
 * RunActionsの最終状態取得
 */
int RA_is_exit(void) {
	if (RA_STATE_FINISH == RA_state) {
		return TRUE;
	} else {
		return FALSE;
	}
}

/**
 * RunActionsの状態遷移
 */
void RA_do_running(void) {
	switch (RA_state) {
	case (RA_STATE_WATCH_BLOCK):
		RA_watch_block_tracing();
		break;

	case (RA_STATE_WAIT_PRE_START_CONF):
		RA_wait_pre_start_conf();
		break;

	case (RA_STATE_SHORT_CUT):
		RA_short_cut();
		break;

	case (RA_STATE_TURN):
		RA_turn();
		break;

	case (RA_STATE_TURN2):
		RA_turn2();
		break;

	case (RA_STATE_TURN_IN_WHITE):
		RA_turn_in_white();
		break;

	case (RA_STATE_WATCH_GOAL):
		RA_watch_goal_tracing();
		break;

	case (RA_STATE_WAIT_START_CONF):
		RA_wait_start_conf();
		break;

	case (RA_STATE_FINISH):
		/* DO NOTHING */
		break;

	default:
		/* DO NOTHING */
		break;
	}
}

void RA_watch_block_tracing() {
	/* ライントレースをする */
	RA_linetrace_P(45);	//変更済み
	i++;
	if(250<=i){
		HU_ok_sound();
		CU_set_sendMSG(77);
		CU_send_mail();
		
		i=0;
		RA_set_state(RA_STATE_TURN2);
	}
}


/**
 * 指定した角度だけ右旋回する
 */
void RA_turn() {

	/* Trueを返すまで回転する */
	if (BLNU_angle_turn_right(120)) {
		RA_stop();

		RA_set_state(RA_STATE_TURN_IN_WHITE);

	}
}


void RA_turn2() {

	/* Trueを返すまで回転する */
	if (BLNU_angle_turn_right(10)) {
		RA_stop();
		//BLNU_angle_turn_left(2);
		RA_set_state(RA_STATE_SHORT_CUT);

	}
}

void RA_short_cut(){
	
	BLNU_forward(30);
	i++;
	if(75<=i){
		if ((LMU_get_black_value() - 30) <= LMU_is_line_value()) {
			RA_set_state(RA_STATE_WATCH_GOAL);
		}
	}
}


/**
 * 黒い線まで右旋回する
 */
void RA_turn_in_white() {
	/* 右旋回する */
	RA_turn_right();

	/* 黒を見つけたら次の状態に遷移する */
	if ((LMU_get_black_value() - 30) <= LMU_is_line_value()) {
		RA_set_state(RA_STATE_WATCH_GOAL);
	}
}

void RA_watch_goal_tracing() {
	/* ライントレースをする */
	RA_linetrace_P(40);	//変更済

	/* バンパが押されたら次の状態に遷移する */
	if (TRUE == BU_is_touched()) {
		/* 停止する */
		
		HU_ok_sound();
		RA_stop();

		/* 弟２走者をスタートさせるために、メールを送信する */
		CU_set_sendMSG(77);
		CU_send_mail();

		RA_set_state(RA_STATE_WAIT_START_CONF);

	}
}

void RA_wait_pre_start_conf() {

	CU_set_recvMSG(99);

	/* スタート準備指示確認メールを受信したら次の状態に遷移する */
	if (TRUE == CU_is_received()) {

		RA_set_state(RA_STATE_TURN);

	}
}

void RA_wait_start_conf() {

	CU_set_recvMSG(99);

	/* スタート指示確認メールを受信したら次の状態に遷移する */
	if (TRUE == CU_is_received()) {

		RA_set_state(RA_STATE_FINISH);

	}
}

/**
 * 黒い線に沿って走る
 */
void RA_linetrace(int forward_speed, int turn_speed) {
	/* 前進する */
	BLNU_forward(forward_speed);

	/* 白黒の判断をして回転方向を決める */
	int light_value = 0;
	light_value = LMU_is_online();
	if (TRUE != light_value) {
		BLNU_turn_right(turn_speed);
	} else {
		BLNU_turn_left(turn_speed);
	}
}

/**
 * 黒い線に沿って走る(P制御）
 */
void RA_linetrace_P(int forward_speed) {
	/* 前進する */
	BLNU_forward(forward_speed);

	float hensa;
	float Kp = 1.4;	//変更済   
	float cmd_turn = 0;

	hensa = LMU_get_threshold() - LMU_is_line_value();
	/* 白いと＋値 */
	/* 黒いと－値 */

	cmd_turn = Kp * hensa;

	if (-100 > cmd_turn) {
		cmd_turn = -100;
	} else if (100 < cmd_turn) {
		cmd_turn = 100;
	}

	BLNU_turn(cmd_turn);

}

/**
 * 停止する
 */
void RA_stop() {
	BLNU_stop();
}

/**
 * 右に曲がる
 */
void RA_turn_right() {
	BLNU_backward(0);
	BLNU_turn_right(50);
}

/**
 * 左に曲がる
 */
void RA_turn_left() {
	BLNU_backward(0);
	BLNU_turn_left(-50);
}

/******************************** END OF FILE ********************************/
