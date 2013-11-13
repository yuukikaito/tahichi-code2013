/*
 * COPYRIGHT(c)2009 Afrel Co., Ltd.
 * LineMonitorUnit.h
 * ���C���Ď��N���X
 *
 * �N���X��: LineMonitorUnit(LMU)
 * ����: threshold
 * ����: set_threshold, get_threshold, is_online, is_gray, pre, post
 * �֘A: common
 */

#ifndef __LineMonitorUnit_h__
#define __LineMonitorUnit_h__

#include "./com/common.h"
#include "./com/nxt_config.h"

#define GRAY_PU_MA	(40)		//�O���[��臒l�ɉ��Z�E���Z���āA����Ɖ��������߂�l

/**
 * ���C���Ď���臒l��ݒ肷��
 */
extern void LMU_set_threshold(int threshold);

/**
 * ���C���Ď���臒l���擾����
 * @return int �ݒ肳�ꂽ臒l�̒l��Ԃ�
 */
extern int LMU_get_threshold(void);

/**
 * ���̒l��ݒ肷��
 */
extern void LMU_set_white_value(int value);

/**
 * �O���C�̒l��ݒ肷��
 */
extern void LMU_set_gray_value(int value);

/**
 * ���̒l��ݒ肷��
 */
extern void LMU_set_black_value(int value);

/**
 * �ݒ肳�ꂽ���̒l���擾����
 * @return int �ݒ肳�ꂽ���̒l��Ԃ�
 */
extern int LMU_get_white_value(void);

/**
 * �ݒ肳�ꂽ�O���C�̒l���擾����
 * @return int �ݒ肳�ꂽ�O���C�̒l��Ԃ�
 */
extern int LMU_get_gray_value(void);

/**
 * �ݒ肳�ꂽ���̒l���擾����
 * @return int �ݒ肳�ꂽ���̒l��Ԃ�
 */
extern int LMU_get_black_value(void);

/**
 * ���C���Ď��̏�Ԃ�����
 * @return int 臒l�����Z���T�����̂Ƃ��ɂP
 *�@���̂Ƃ���0
 *�@�O���C�̂Ƃ���1��Ԃ�
 */
extern int LMU_is_online(void);

/**
 * �O���C�̏�Ԃ�����
 * @return int �O���C�ł���΂P
 *�@�O���C�łȂ����0��Ԃ�
 */
extern int LMU_is_gray(void);

/**
 * ���C���̒l������
 */
extern int LMU_is_line_value(void);

/**
 * ���C���Ď��̏���������(���Z���T���A�N�e�B�u�ɂ���)
 */
extern void LMU_pre(void);

/**
 * ���C���Ď��̏I������(���Z���T���p�b�V�u�ɂ���)
 */
extern void LMU_post(void);

#endif /**__LineMonitorUnit_h__ */
