/*
 * COPYRIGHT(c)2010 Afrel Co., Ltd.
 * RunActions.c
 * RunActionsクラス
 *
 * クラス名: RunActions(RA)
 * 属性:
 * 操作: get_state, do_running, is_exit
 * 関連: LineMonitorUnit(LMU), BalancerUnit(BLNU), common
 */

#include "RunActions.h"

typedef enum {
	RA_LEFT,
	RA_RIGHT,
} RA_STATE;


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

/*
void RA_set_state(int state){
	RA_STATE = state;
}

*/

void RA_takeover() {
	/* ライントレースをする */
	RA_linetrace_P(20);

}

void RA_watch_goal_tracing() {
	/* ライントレースをする */
	RA_linetrace_P(40);

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
	
//	BLNU_forward(forward_speed);

	float hensa;
	float i_hensa;
	float Kp = 1.2;
	float Ki = 0;

	float cmd_turn = 0;

//	if (!TU_is_start() && lineflag == 0) {
//		/** 90秒のタイマ監視開始 */
//		TU_start(10000);
//	}

//	if (TRUE == TU_is_timeout() ) {
//		
//	}

	hensa = LMU_get_threshold() - LMU_is_line_value();
	i_hensa = i_hensa+(hensa*0.004);
	/* 白いと＋値 */
	/* 黒いと−値 */

//	cmd_turn = -(Kp * hensa + Ki * i_hensa);
	cmd_turn = -(Kp *hensa);
	if (-100 > cmd_turn) {
		cmd_turn = -100;
	} else if (100 < cmd_turn) {
		cmd_turn = 100;
	}


//	BLNU_turn(cmd_turn);

	

	/*
	if(lineflag == 0){
	nxt_motor_set_speed(L_MOTOR_PORT, forward_speed - cmd_turn/2, 1);
	nxt_motor_set_speed(R_MOTOR_PORT, forward_speed + cmd_turn/2, 1);}
	else{
	*/
	nxt_motor_set_speed(L_MOTOR_PORT, forward_speed + cmd_turn/2, 1);
	nxt_motor_set_speed(R_MOTOR_PORT, forward_speed - cmd_turn/2, 1);
	//}

	/*
	if(RA_STATE==RA_LEFT){
		if (!TU_is_start()) {
			TU_start(5000);
		}
		nxt_motor_set_speed(L_MOTOR_PORT, forward_speed - cmd_turn/2, 1);
		nxt_motor_set_speed(R_MOTOR_PORT, forward_speed + cmd_turn/2, 1);
		if(TRUE == TU_is_timeout){
			RA_STATE=RA_RIGHT;
		}
	else{
		nxt_motor_set_speed(L_MOTOR_PORT, forward_speed + cmd_turn/2, 1);
		nxt_motor_set_speed(R_MOTOR_PORT, forward_speed - cmd_turn/2, 1);
	}
	
	*/


}

/**
 * 停止する
 */
void RA_stop(void) {
//	BLNU_stop();
	nxt_motor_set_speed(L_MOTOR_PORT, 0, 1);
	nxt_motor_set_speed(R_MOTOR_PORT, 0, 1);
}

/******************************** END OF FILE ********************************/
