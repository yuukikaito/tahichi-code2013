/*
 * COPYRIGHT(c)2009 Afrel Co., Ltd.
 * CommunicationUnit.c
 * メール送受信クラス
 *
 * クラス名: CommunicationUnit(CU)
 * 属性: なし
 * 操作: send_mail, pre, post, is_received
 * 関連: common
 */

#include "CommunicationUnit.h"

#define MASTER (1)
#define SLAVE (0)

/** 送受信メッセージ */
static int CU_sendMSG = 0;
static int CU_recvMSG = 0;

/** マスターORスレーブモード
 * スレーブ:0
 * マスター:1
 * 初期状態は、スレーブ:0
 */
static int CU_mode = 0;

/* パスワード */
const char CU_pass[] = "LEJOS-OSEK";

/* Bluetoothデバイスアドレス（スレーブ） */
static unsigned char bd_addr[7];

/**
 * 送信メッセージを設定する
 */
void CU_set_sendMSG(int setMSG) {
	CU_sendMSG = setMSG;
}

/**
 * 送信メッセージを取得する
 * @return int 設定されている送信メッセージを返す
 */
int CU_get_sendMSG(void) {
	return CU_sendMSG;
}

/**
 * 受信メッセージを設定する
 */
void CU_set_recvMSG(int setMSG) {
	CU_recvMSG = setMSG;
}

/**
 * 受信メッセージを取得する
 * @return int 設定されている受信メッセージを返す
 */
int CU_get_recvMSG(void) {
	return CU_recvMSG;
}

/**
 * モードの設定と
 * スレーブ側のBluetoothデバイスアドレスを設定する(マスター側の時のみ)
 */
void CU_set_mode(int setmode, const unsigned char *setAddr) {
	/* モード設定の範囲を超えている場合 */
	if (MASTER < setmode) {
		setmode = SLAVE;
	}

	CU_mode = setmode;

	/* マスターの場合Bluetoothデバイスアドレスを設定する */
	if (MASTER == CU_mode) {
		for (int i = 0; i < 7; i++) {
			bd_addr[i] = setAddr[i];
		}
	}
}

/**
 * Bluetooth接続モードを取得する
 * @return int 設定されているBluetooth接続モードを返す
 */
int CU_get_mode(void) {
	return CU_mode;
}

/**
 * メールを送信する
 */
void CU_send_mail(void) {
	unsigned char bt_send_buf[32];
	int i;

	for (i = 0; i < 32; i++) {
		bt_send_buf[i] = CU_sendMSG;

	}
	ecrobot_send_bt_packet(bt_send_buf, 32);
}

/**
 * メール受信状態を示す
 * @return int 受信済みのときはTRUE(1)，未受信のときはFALSE(0)を返す
 */
int CU_is_received(void) {
	unsigned char bt_receive_buf[32];

	int i;

	ecrobot_read_bt_packet(bt_receive_buf, 32);

	for (i = 0; i < 32; i++) {
		if (CU_recvMSG != bt_receive_buf[i]) {
			return FALSE;
		}
	}
	return TRUE;
}

/**
 * CommUnitの初期化処理
 */
void CU_pre(void) {
	if (SLAVE == CU_mode) {
		ecrobot_init_bt_slave(CU_pass);
	} else {
		ecrobot_init_bt_master(bd_addr, CU_pass);
	}
}

/**
 * CommUnitの終了処理
 */
void CU_post(void) {
	ecrobot_term_bt_connection();
}
