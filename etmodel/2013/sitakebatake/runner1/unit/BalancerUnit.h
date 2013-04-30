/*
 * COPYRIGHT(c)2009 Afrel Co., Ltd.
 * BalancerUnit.h
 * �o�����T�[���j�b�g�N���X
 *
 * �N���X��: BalancerUnit(BLNU)
 * ����: cmd_forward, cmd_turn, gyro_offset
 * ����: pre, post, forward, backward, turn_right, turn_left, stop,
 *       set_gyro_offset, balance_control
 * �֘A: common, nxt_config, balancer
 */

#ifndef __BalancerUnit_h__
#define __BalancerUnit_h__

#include "./com/common.h"
#include "./com/nxt_config.h"
#include "balancer.h"

/**
 * BalancerUnit�̏���������
 */
extern void BLNU_pre(void);

/**
 * BalancerUnit�̏I������
 */
extern void BLNU_post(void);

/**
 * �O�i����
 */
extern void BLNU_forward(S8 command);

/**
 * ��ނ���
 */
extern void BLNU_backward(S8 command);

/**
 * �E�ɉ�]����
 */
extern void BLNU_turn_right(S8 command);

/**
 * ���ɉ�]����
 */
extern void BLNU_turn_left(S8 command);

/**
 * ���E�ɉ�]����
 */
extern void BLNU_turn(S8 command);

/**
 * ��~����
 */
extern void BLNU_stop(void);

/**
 * �W���C���Z���T�I�t�Z�b�g�l�̐ݒ�
 */
extern void BLNU_set_gyro_offset(void);

/**
 * �o�����X�R���g���[���J�n�t���O�Z�b�g
 */
extern void BLNU_balance_start(void);

/**
 * �w�肵���p�x�����A���{�b�g���E��]������
 * ����angle�́A���{�b�g�̉�]�p�x
 */
extern BOOL BLNU_angle_turn_right(F32 angle);

/**
 * �w�肵���p�x�����A���{�b�g������]������
 * ����angle�́A���{�b�g�̉�]�p�x
 */
extern BOOL BLNU_angle_turn_left(F32 angle);

#endif /**__BalancerUnit_h__ */
