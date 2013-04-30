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

#define	MIN_DISTANCE (22)		/* 壁感知距離 */
#define KP 0.8
#define KI 0.35
#define KD  0.015

/*
 * スレーブ側のBluetoothデバイスアドレス
 */
const static unsigned char bd_addr[7] = { 0x00, 0x16, 0x53, 0x13, 0xB7, 0xCA,
		0x00 };

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
//void RA_linetrace(int forward_speed, int turn_speed);
void RA_linetrace_L(int forward_speed,float Kp,float Ki,float Kd);
void RA_linetrace_R(int forward_speed,float Kp,float Ki,float Kd);
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
	if(FALSE == TU_is_start())
		TU_start(5000);
	/* ライントレースをする */
	//RA_linetrace(45, 100);
	
	LMU_set_threshold((LMU_get_black_value()+LMU_get_white_value())/2);
	RA_linetrace_L(50,KP,KI,KD);
	//LMU_set_threshold((2*LMU_get_black_value()+LMU_get_white_value())/3);
	//RA_linetrace_L(60,KP,KI,KD);

	/* 超音波センサで壁を認識すると次の状態に遷移する */
	if (TU_is_timeout() && BMU_is_found()) {
		/* 停止する */
		RA_stop();
		TU_finish();

		CU_set_sendMSG(77);
		CU_send_mail();
		//RA_set_state(RA_STATE_TURN);
		RA_set_state(RA_STATE_WAIT_PRE_START_CONF);
	}
}

/**
 * 指定した角度だけ右旋回する
 */
void RA_turn() {
	/* Trueを返すまで回転する */
	if (BLNU_angle_turn_right(180)) {
		RA_stop();
		RA_set_state(RA_STATE_TURN_IN_WHITE);
	}
}

/**
 * 黒い線まで右旋回する
 */
void RA_turn_in_white() {
	BLNU_forward(10);

	/* 黒を見つけたら次の状態に遷移する */
	if ((LMU_get_black_value() - 30) <= LMU_is_line_value()) {
		RA_set_state(RA_STATE_WATCH_GOAL);
	}
}

void RA_watch_goal_tracing() {
	/* ライントレースをする */
	int forward;
	float Kp;
	if(FALSE == TU_is_start()){
		TU_start(2000);
	}

	if(FALSE == TU_is_timeout()){
		forward = 20;
		Kp = 50;
	}else{
		//HU_arrival_sound();
		if(forward <40) forward +=0.2;
		Kp = KP;
	}
	
	LMU_set_threshold((LMU_get_black_value()+3*LMU_get_white_value())/4);
	RA_linetrace_L(forward,Kp, KI, KD);

	/* バンパが押されたら次の状態に遷移する */
	if (TRUE == BU_is_touched()) {
		/* 停止する */
		RA_stop();
		TU_finish();

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

///**
// * 黒い線に沿って走る
// */
//void RA_linetrace(int forward_speed, int turn_speed) {
//	/* 前進する */
//	BLNU_forward(forward_speed);
//
//	/* 白黒の判断をして回転方向を決める */
//	int light_value = 0;
//	light_value = LMU_is_online();
//	if (TRUE != light_value) {
//		BLNU_turn_right(turn_speed);
//	} else {
//		BLNU_turn_left(turn_speed);
//	}
//}

/**
 * 黒い線に沿って走る(P制御）
 */
void RA_linetrace_L(int forward_speed,float Kp,float Ki,float Kd) {
	/* 前進する */

	float hensa = 0;
	float b = 0;

	float cmd_turn = 0;
	float i_hensa = 0;
	float d_hensa = 0;
	float bf_hensa = 0;

	hensa = LMU_get_threshold() - LMU_is_line_value();
	/* 白いと＋値 */
	/* 黒いと－値 */

	i_hensa = i_hensa + (hensa * 0.004);

	d_hensa = (hensa - bf_hensa)/0.004;
	bf_hensa = hensa;

	cmd_turn = Kp*hensa + Ki*i_hensa + Kd*d_hensa + b;

	cmd_turn = Kp * hensa;

	if (-100 > cmd_turn) {
		cmd_turn = -100;
	} else if (100 < cmd_turn) {
		cmd_turn = 100;
	}

	BLNU_forward(forward_speed);
	BLNU_turn(cmd_turn);

	//尻尾走行する場合 !!!他のとこも訂正必要!!!
	//nxt_motor_set_speed(L_MOTOR_PORT, forward_speed + cmd_turn/2, 1);
	//nxt_motor_set_speed(R_MOTOR_PORT, forward_speed - cmd_turn/2, 1);


}

/**
 * 黒い線に沿って走る(P制御）
 */
void RA_linetrace_R(int forward_speed,float Kp,float Ki,float Kd) {
	/* 前進する */

	float hensa = 0;
	float b = 0;

	float cmd_turn = 0;
	float i_hensa = 0;
	float d_hensa = 0;
	float bf_hensa = 0;

	hensa = LMU_get_threshold() - LMU_is_line_value();
	/* 白いと＋値 */
	/* 黒いと－値 */

	i_hensa = i_hensa + (hensa * 0.004);

	d_hensa = (hensa - bf_hensa  )/0.004;
	bf_hensa = hensa;

	cmd_turn = Kp*hensa + Ki*i_hensa + Kd*d_hensa + b;

	cmd_turn = Kp * hensa;

	if (-100 > cmd_turn) {
		cmd_turn = -100;
	} else if (100 < cmd_turn) {
		cmd_turn = 100;
	}

	BLNU_forward(forward_speed);
	BLNU_turn(-cmd_turn);

	//尻尾走行する場合 !!!他のとこも訂正必要!!!
	//nxt_motor_set_speed(L_MOTOR_PORT, forward_speed + cmd_turn/2, 1);
	//nxt_motor_set_speed(R_MOTOR_PORT, forward_speed - cmd_turn/2, 1);
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
