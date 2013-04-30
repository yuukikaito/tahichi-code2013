/*
 * COPYRIGHT(c)2009 Afrel Co., Ltd.
 * BumperUnit.h
 * �o���p�N���X
 *
 * �N���X��: BumperUnit(BU)
 * ����: �Ȃ�
 * ����: is_touched, is_clicked
 * �֘A: common, nxt_config
 */

#ifndef __BumperUnit_h__
#define __BumperUnit_h__

#include "./com/common.h"
#include "./com/nxt_config.h"

/**
 * �o���p�̏�Ԃ�����
 * @return int �o���p��������Ă���Ƃ���TRUE(1)�A������Ă��Ȃ��Ƃ���FALSE(0)��Ԃ�
 */
extern int BU_is_touched(void);

/**
 * �o���p���N���b�N���ꂽ���ǂ���������
 * @return int �o���p���N���b�N���ꂽ�Ƃ���TRUE(1)�A�����łȂ��Ƃ���FALSE(0)��Ԃ�
 */
extern int BU_is_clicked(void);

/**
 * �o���p�̏���������
 */
extern void BU_pre(void);

/**
 * �o���p�̏I������
 */
extern void BU_post(void);

#endif /**__BumperUnit_h__ */
