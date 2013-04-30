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
const static unsigned char bd_addr[7] = { 0x00, 0x16, 0x53, 0x12, 0x27, 0xAD,
		0x00 };
//	dipta:		0016531227AD00
//	katsura:	00165310BBA700

/*
 * 走行中の状態
 */
typedef enum {
	RA_STATE_WATCH_BLOCK,
	RA_STATE_WAIT_PRE_START_CONF,
	RA_STATE_TURN,
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
void RA_turn();
void RA_turn_in_white();
void RA_wait_pre_start_conf();
void RA_wait_start_conf();
void RA_linetrace(int forward_speed, int turn_speed);
void RA_linetrace_P(int forward_speed);
void RA_stop();
void RA_turn_right();
void RA_turn_left();

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

	case (RA_STATE_TURN):
		RA_turn();
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
	//RA_linetrace(60, 100);
	RA_linetrace_P(60);

	/* 超音波センサで壁を認識すると次の状態に遷移する */
	if (TRUE == BMU_is_found()) {
		/* 停止する */
		RA_stop();

		CU_set_sendMSG(77);
		CU_send_mail();
		RA_set_state(RA_STATE_WAIT_PRE_START_CONF);

	}

}

/**
 * 指定した角度だけ右旋回する
 */
void RA_turn() {
	static unsigned char flag1 = 0;
	static unsigned char flag2 = 0;

	/* Trueを返すまで回転する */
	if(!flag1 && !flag2){
		if (BLNU_angle_turn_right(90)) {
			RA_stop();
			//RA_set_state(RA_STATE_TURN_IN_WHITE);
			flag1 = 1;
		}
	}
	else if(flag1 && !flag2){
		BLNU_backward(20);
		if( (0.2*LMU_get_black_value()+0.8*LMU_get_white_value()) <= LMU_is_line_value() ){
			flag2 = 1;
			RA_stop();
		}
	}
	else if(flag1 && flag2){
		if (BLNU_angle_turn_right(70)) {
			RA_stop();
			RA_set_state(RA_STATE_TURN_IN_WHITE);
		}
	}
}

/**
 * 黒い線まで右旋回する
 */
void RA_turn_in_white() {
	/* 右旋回する */
	//RA_turn_right();
	BLNU_forward(15);

	/* 黒を見つけたら次の状態に遷移する */
	//if ((LMU_get_black_value() - 30) <= LMU_is_line_value()) {
	if ((0.2*LMU_get_black_value()+0.8*LMU_get_white_value()) <= LMU_is_line_value()) {
		RA_set_state(RA_STATE_WATCH_GOAL);
	}
}

void RA_watch_goal_tracing() {
	/* ライントレースをする */
	//RA_linetrace(60, 100);
	RA_linetrace_P(25);

	/* バンパが押されたら次の状態に遷移する */
	if (TRUE == BU_is_touched()) {
		/* 停止する */
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

	static const float Kp = 3.0;	//	default 0.7
	static const float Ki = 0.0;	//	default 2.3
	static const float Kd = 0.05;	//	default 0.02

	static float hensa = 0;
	static float i_hensa = 0;
	static float d_hensa = 0;
	static float bf_hensa = 0;
	static U16 bf_rMotor = 0;
	static U16 bf_lMotor = 0;
	static U16 cur_rMotor = 0;
	static U16 cur_lMotor = 0;
	float cmd_turn = 0;

	cur_rMotor = nxt_motor_get_count(R_MOTOR_PORT);
	cur_lMotor = nxt_motor_get_count(L_MOTOR_PORT);
	cmd_turn = (cur_lMotor-bf_lMotor)-(cur_rMotor-bf_rMotor);
	bf_rMotor = cur_rMotor;
	bf_lMotor = cur_lMotor;

	hensa = LMU_get_threshold() - LMU_is_line_value();
	/* 白いと＋値 */
	/* 黒いと－値 */
	i_hensa = i_hensa + (hensa * 0.012);
	d_hensa = (- bf_hensa + hensa )/0.012;
	bf_hensa = hensa;

	cmd_turn += Kp*hensa + Ki*i_hensa + Kd*d_hensa;

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
	BLNU_turn_right(40);
}

/**
 * 左に曲がる
 */
void RA_turn_left() {
	BLNU_backward(0);
	BLNU_turn_left(-40);
}

/******************************** END OF FILE ********************************/
