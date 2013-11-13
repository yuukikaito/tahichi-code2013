/*
 * COPYRIGHT(c)2009 Afrel Co., Ltd.
 * HornUnit.c
 * クラクションクラス
 *
 * クラス名: HornUnit(HU)
 * 属性: なし
 * 操作: ok_sound, error_sound, warn_sound, confir_sound
 * 関連: common
 */

#include "HornUnit.h"

/**
 * 正常の音を鳴らす
 */
void HU_ok_sound(void) {
	ecrobot_sound_tone(440, 512, VOL);
	systick_wait_ms(10);
	ecrobot_sound_tone(369, 256, VOL);
	systick_wait_ms(10);
	ecrobot_sound_tone(880, 512, VOL);
	systick_wait_ms(10);
}

/**
 * 到着の音を鳴らす
 */
void HU_arrival_sound(void) {
	ecrobot_sound_tone(277, 64, VOL);
	systick_wait_ms(10);
	ecrobot_sound_tone(329, 64, VOL);
	systick_wait_ms(10);
	ecrobot_sound_tone(554, 64, VOL);
	systick_wait_ms(10);
	ecrobot_sound_tone(880, 64, VOL);
	systick_wait_ms(10);
	ecrobot_sound_tone(492, 64, VOL);
	systick_wait_ms(10);
	ecrobot_sound_tone(658, 64, VOL);
	systick_wait_ms(10);
}

/**
 * エラー時の音を鳴らす
 */
void HU_error_sound(void) {
	ecrobot_sound_tone(293, 64, VOL);
	systick_wait_ms(10);
	ecrobot_sound_tone(293, 64, VOL);
	systick_wait_ms(10);
	ecrobot_sound_tone(293, 64, VOL);
	systick_wait_ms(10);
	ecrobot_sound_tone(273, 64, VOL);
	systick_wait_ms(10);
	ecrobot_sound_tone(329, 64, VOL);
	systick_wait_ms(10);
	ecrobot_sound_tone(293, 512, VOL);
	systick_wait_ms(10);
}

/**
 * 警告時の音を鳴らす
 */
void HU_warn_sound(void) {
	ecrobot_sound_tone(329, 64, VOL);
	systick_wait_ms(10);
	ecrobot_sound_tone(492, 512, VOL);
	systick_wait_ms(10);
}

/**
 * 確認時の音を鳴らす
 */
void HU_confir_sound(void) {
	ecrobot_sound_tone(1230, 256, VOL);
	systick_wait_ms(10);
	ecrobot_sound_tone(1845, 256, VOL);
	systick_wait_ms(10);
}

