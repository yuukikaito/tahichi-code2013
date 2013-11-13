/*
 * COPYRIGHT(c)2009 Afrel Co., Ltd.
 * HornUnit.h
 * �N���N�V�����N���X
 *
 * �N���X��: HornUnit(HU)
 * ����: �Ȃ�
 * ����: ok_sound, error_sound, warn_sound, confir_sound
 * �֘A: common
 */

#ifndef __HornUnit_h__
#define __HornUnit_h__

#include "./com/common.h"

#define VOL 20

/**
 * ����̉���炷
 */
extern void HU_ok_sound(void);

/**
 * �����̉���炷
 */
extern void HU_arrival_sound(void);

/**
 * �G���[���̉���炷
 */
extern void HU_error_sound(void);

/**
 * �x�����̉���炷
 */
extern void HU_warn_sound(void);

/**
 * �m�F���̉���炷
 */
extern void HU_confir_sound(void);

#endif /**__HornUnit_h__ */
