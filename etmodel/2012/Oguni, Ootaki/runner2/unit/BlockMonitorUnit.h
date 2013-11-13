/*
 * COPYRIGHT(c)2009 Afrel Co., Ltd.
 * BlockMonitorUnit.h
 * 障害物監視クラス
 *
 * クラス名: BlockMonitorUnit(BMU)
 * 属性: threshold
 * 操作: set_threshold, get_threshold, is_found, pre, post
 * 関連: common
 */

#ifndef __BlockMonitorUnit_h__
#define __BlockMonitorUnit_h__

#include "./com/common.h"
#include "./com/nxt_config.h"

/**
 * 障害物監視の閾値を設定する
 */
extern void BMU_set_threshold(int threshold);

/**
 * 障害物監視の閾値を取得する
 * @return int 設定された閾値の値を返す
 */
extern int BMU_get_threshold(void);

/**
 * 障害物監視の状態を示す
 * @return int 閾値より超音波センサの値が小さい(近い)ときにTRUE(1)，大きい(遠い)ときにFALSE(0)を返す
 */
extern int BMU_is_found(void);

/**
 * 障害物監視の初期化処理(超音波センサをアクティブにする)
 */
extern void BMU_pre(void);

/**
 * 障害物監視の終了処理(超音波センサをパッシブにする)
 */
extern void BMU_post(void);

#endif /**__BlockMonitorUnit_h__ */
