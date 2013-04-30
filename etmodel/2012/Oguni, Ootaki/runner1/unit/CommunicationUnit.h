/*
 * COPYRIGHT(c)2009 Afrel Co., Ltd.
 * CommunicationUnit.h
 * ���[������M�N���X
 *
 * �N���X��: CommunicationUnit(CU)
 * ����: �Ȃ�
 * ����: send_mail, pre, post, is_received
 * �֘A: common
 */

#ifndef __CommunicationUnit_h__
#define __CommunicationUnit_h__

#include "./com/common.h"

/**
 * ���M���b�Z�[�W��ݒ肷��
 */
extern void CU_set_sendMSG(int setMSG);

/**
 * ���M���b�Z�[�W���擾����
 * @return int �ݒ肳��Ă��鑗�M���b�Z�[�W��Ԃ�
 */
extern int CU_get_sendMSG(void);

/**
 * ��M���b�Z�[�W��ݒ肷��
 */
extern void CU_set_recvMSG(int setMSG);

/**
 * ��M���b�Z�[�W���擾����
 * @return int �ݒ肳��Ă����M���b�Z�[�W��Ԃ�
 */
extern int CU_get_recvMSG(void);

/**
 * ���[�h�̐ݒ��
 * �X���[�u����Bluetooth�f�o�C�X�A�h���X��ݒ肷��(�}�X�^�[���̎��̂�)
 */
extern void CU_set_mode(int setmode, const unsigned char *setAddr);

/**
 * Bluetooth�ڑ����[�h���擾����
 * @return int �ݒ肳��Ă���Bluetooth�ڑ����[�h��Ԃ�
 */
extern int CU_get_mode(void);

/**
 * ���[���𑗐M����
 */
extern void CU_send_mail(void);

/**
 * ���[����M��Ԃ�����
 * @return int ��M�ς݂̂Ƃ���TRUE(1)�C����M�̂Ƃ���FALSE(0)��Ԃ�
 */
extern int CU_is_received(void);

/**
 * CommUnit�̏���������
 */
extern void CU_pre(void);

/**
 * CommUnit�̏I������
 */
extern void CU_post(void);

#endif /**__CommunicationUnit_h__ */
