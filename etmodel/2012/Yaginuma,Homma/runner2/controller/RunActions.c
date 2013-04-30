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
#include "../Unit/TimerUnit.h"
#include "../Unit/HornUnit.h"
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

void RA_stoppinglinetrace()
 {
	RA_linetrace_P(0);
	
 	//DU_show_number(10,3,abs((int)((nxt_motor_get_count(NXT_PORT_B) + nxt_motor_get_count(NXT_PORT_C)) / 2)));
 	

 }
void RA_takeover() {
	static int flag =0;
	if(flag ==0) {
	RA_linetrace_P(20);
	}
	else {
		RA_stoppinglinetrace();		
		}
	
	if (!TU_is_start() && flag ==0) {
		/** 4秒のタイマ監視開始 */
		TU_start(4000); 
	}

	if (TRUE == TU_is_timeout()) {
	HU_warn_sound();
		/** タイマ監視を終了させる */
		TU_finish();	
		flag =1; //一回タイマを使ったらもう使わない。
	}
		
		
		
}
	//ある一定距離を走ったら静止状態に持っていきたい。
	
	
	
//リレーのリードをしている状態
//指定された線より超えてはならない


void RA_watch_goal_tracing() {
	/* ライントレースをする */
//	RA_linetrace(25,100);
	RA_linetrace_P(50);
	
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
		BLNU_turn_left(turn_speed);
	} else {
		BLNU_turn_right(turn_speed);
	}
}

/**
 * 黒い線に沿って走る(P制御）
 */
void RA_linetrace_P(int forward_speed) {
	/* 前進する */
	BLNU_forward(forward_speed);

	float hensa;
	

	float Kp = 1.4;
	float cmd_turn = 0;

	
	hensa = LMU_get_threshold() - LMU_is_line_value();
	/* 白いと＋値 */
	/* 黒いと－値 */
	
	

	cmd_turn = Kp * -hensa;

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
void RA_stop(void) {
	RA_stoppinglinetrace();  // 静止実現
	//BLNU_stop();
}

/******************************** END OF FILE ********************************/
