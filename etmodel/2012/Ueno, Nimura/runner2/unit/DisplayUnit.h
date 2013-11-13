/*
 * COPYRIGHT(c)2009 Afrel Co., Ltd.
 * DisplayUnit.h
 * ��ԕ\���N���X
 *
 * �N���X��: DisplayUnit(DU)
 * ����: �Ȃ�
 * ����: show_string, show_number, clear
 * �֘A: common
 */

#ifndef __DisplayUnit_h__
#define __DisplayUnit_h__

#include "./com/common.h"

/**
 * �t���f�B�X�v���C�ɕ�����\������
 *�@ @param param �t���f�B�X�v���C�ɕ\�����镶��
 */
extern void DU_show_string(int x, int y, char *param);

/**
 * �t���f�B�X�v���C�ɐ�����\������
 * @param status �t���f�B�X�v���C�ɕ\�����鐔��
 */
extern void DU_show_number(int x, int y, int status);

/**
 * �t���f�B�X�v���C���N���A����
 */
extern void DU_clear(void);

#endif /**__DisplayUnit_h__ */
