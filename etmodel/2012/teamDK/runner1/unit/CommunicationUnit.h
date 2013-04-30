/*
 * COPYRIGHT(c)2009 Afrel Co., Ltd.
 * CommunicationUnit.h
 * メール送受信クラス
 *
 * クラス名: CommunicationUnit(CU)
 * 属性: なし
 * 操作: send_mail, pre, post, is_received
 * 関連: common
 */

#ifndef __CommunicationUnit_h__
#define __CommunicationUnit_h__

#include "./com/common.h"

/**
 * 送信メッセージを設定する
 */
extern void CU_set_sendMSG(int setMSG);

/**
 * 送信メッセージを取得する
 * @return int 設定されている送信メッセージを返す
 */
extern int CU_get_sendMSG(void);

/**
 * 受信メッセージを設定する
 */
extern void CU_set_recvMSG(int setMSG);

/**
 * 受信メッセージを取得する
 * @return int 設定されている受信メッセージを返す
 */
extern int CU_get_recvMSG(void);

/**
 * モードの設定と
 * スレーブ側のBluetoothデバイスアドレスを設定する(マスター側の時のみ)
 */
extern void CU_set_mode(int setmode, const unsigned char *setAddr);

/**
 * Bluetooth接続モードを取得する
 * @return int 設定されているBluetooth接続モードを返す
 */
extern int CU_get_mode(void);

/**
 * メールを送信する
 */
extern void CU_send_mail(void);

/**
 * メール受信状態を示す
 * @return int 受信済みのときはTRUE(1)，未受信のときはFALSE(0)を返す
 */
extern int CU_is_received(void);

/**
 * CommUnitの初期化処理
 */
extern void CU_pre(void);

/**
 * CommUnitの終了処理
 */
extern void CU_post(void);

#endif /**__CommunicationUnit_h__ */
