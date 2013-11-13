/*
 * COPYRIGHT(c)2009 Afrel Co., Ltd.
 * BlockMonitorUnit.c
 * 障害物監視クラス
 *
 * クラス名: BlockMonitorUnit(BMU)
 * 属性: threshold
 * 操作: set_threshold, get_threshold, is_found, pre, post
 * 関連: common
 */

#include "BlockMonitorUnit.h"

/* 障害物距離判別閾値 */
static unsigned int BMU_threshold = 0;

/**
 * 障害物監視の閾値を設定する
 */
void BMU_set_threshold(int threshold) {
	BMU_threshold = threshold;
}

/**
 * 障害物監視の閾値を取得する
 * @return int 設定された閾値の値を返す
 */
int BMU_get_threshold(void) {
	return BMU_threshold;
}

/**
 * 障害物監視の状態を示す
 * @return int 閾値より超音波センサの値が小さい(近い)ときにTRUE(1)，大きい(遠い)ときにFALSE(0)を返す
 */
int BMU_is_found(void) {
	if ((0 != ecrobot_get_sonar_sensor(BMU_PORT)) && (255
			!= ecrobot_get_sonar_sensor(BMU_PORT))) {
		if (BMU_threshold > ecrobot_get_sonar_sensor(BMU_PORT)) {
			return TRUE;
		}
	}
	return FALSE;
}

/**
 * 障害物監視の初期化処理(超音波センサの初期化処理)
 */
void BMU_pre(void) {
	ecrobot_init_sonar_sensor(BMU_PORT);
}

/**
 * 障害物監視の終了処理(超音波センサの終了処理)
 */
void BMU_post(void) {
	ecrobot_term_sonar_sensor(BMU_PORT);
}

