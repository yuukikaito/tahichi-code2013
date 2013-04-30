/*
 * COPYRIGHT(c)2009 Afrel Co., Ltd.
 * HornUnit.c
 * �N���N�V�����N���X
 *
 * �N���X��: HornUnit(HU)
 * ����: �Ȃ�
 * ����: ok_sound, error_sound, warn_sound, confir_sound
 * �֘A: common
 */

#include "HornUnit.h"

/**
 * ����̉���炷
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
 * �����̉���炷
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
 * �G���[���̉���炷
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
 * �x�����̉���炷
 */
void HU_warn_sound(void) {
	ecrobot_sound_tone(329, 64, VOL);
	systick_wait_ms(10);
	ecrobot_sound_tone(492, 512, VOL);
	systick_wait_ms(10);
}

/**
 * �m�F���̉���炷
 */
void HU_confir_sound(void) {
	ecrobot_sound_tone(1230, 256, VOL);
	systick_wait_ms(10);
	ecrobot_sound_tone(1845, 256, VOL);
	systick_wait_ms(10);
}

