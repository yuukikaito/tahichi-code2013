/*
 * COPYRIGHT(c)2010 Afrel Co., Ltd.
 * RunActions.c
 * RunActionsクラス
 *
 * クラス名: RunActions(RA)
 * 属性:
 * 操作: get_state, do_running, is_exit
 * 関連: LineMonitorUnit(LMU), common
 */

#include "RunActions.h"

/*
 * 各状態に対応するプライベート関数
 */
void RA_linetrace(int forward_speed, int turn_speed);
void RA_linetrace_P(int forward_speed);

/**
 * RunActionsの初期化処理
 */
void RA_pre(void) {
}

/**
 * RunActionsの終了処理
 */
void RA_post(void) {
}

void RA_takeover() {
	/* ライントレースをする */
	RA_linetrace(5, 100);

}

void RA_watch_goal_tracing() {
	/* ライントレースをする */
	RA_linetrace(25, 100);

}

/**
 * 黒い線に沿って走る
 */
void RA_linetrace(int forward_speed, int turn_speed) {
	/* 前進する */
	ecrobot_set_motor_speed(NXT_PORT_B,forward_speed);
	ecrobot_set_motor_speed(NXT_PORT_C,forward_speed);

	/* 白黒の判断をして回転方向を決める */
	int light_value = 0;
	light_value = LMU_is_online();
	if (TRUE != light_value) {
		ecrobot_set_motor_speed(NXT_PORT_B,-turn_speed);
		ecrobot_set_motor_speed(NXT_PORT_C,turn_speed);
	} else {
		ecrobot_set_motor_speed(NXT_PORT_B,turn_speed);
		ecrobot_set_motor_speed(NXT_PORT_C,-turn_speed);
	}
}

/**
 * 黒い線に沿って走る(P制御）
 */
void RA_linetrace_P(int forward_speed) {
	/* 前進する */
	ecrobot_set_motor_speed(NXT_PORT_B,forward_speed);
	ecrobot_set_motor_speed(NXT_PORT_C,forward_speed);

	float hensa;
	float Kp = 0.5;
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
	
	ecrobot_set_motor_speed(NXT_PORT_B,-cmd_turn);
	ecrobot_set_motor_speed(NXT_PORT_C,cmd_turn);

}

/**
 * 停止する
 */
void RA_stop(void) {
	ecrobot_set_motor_speed(NXT_PORT_B,0);
	ecrobot_set_motor_speed(NXT_PORT_C,0);
}

/******************************** END OF FILE ********************************/
