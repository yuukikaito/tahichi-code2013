/*
 * COPYRIGHT(c)2009 Afrel Co., Ltd.
 * BlockMonitorUnit.h
 * ��Q���Ď��N���X
 *
 * �N���X��: BlockMonitorUnit(BMU)
 * ����: threshold
 * ����: set_threshold, get_threshold, is_found, pre, post
 * �֘A: common
 */

#ifndef __BlockMonitorUnit_h__
#define __BlockMonitorUnit_h__

#include "./com/common.h"
#include "./com/nxt_config.h"

/**
 * ��Q���Ď���臒l��ݒ肷��
 */
extern void BMU_set_threshold(int threshold);

/**
 * ��Q���Ď���臒l���擾����
 * @return int �ݒ肳�ꂽ臒l�̒l��Ԃ�
 */
extern int BMU_get_threshold(void);

/**
 * ��Q���Ď��̏�Ԃ�����
 * @return int 臒l��蒴���g�Z���T�̒l��������(�߂�)�Ƃ���TRUE(1)�C�傫��(����)�Ƃ���FALSE(0)��Ԃ�
 */
extern int BMU_is_found(void);

/**
 * ��Q���Ď��̏���������(�����g�Z���T���A�N�e�B�u�ɂ���)
 */
extern void BMU_pre(void);

/**
 * ��Q���Ď��̏I������(�����g�Z���T���p�b�V�u�ɂ���)
 */
extern void BMU_post(void);

#endif /**__BlockMonitorUnit_h__ */
