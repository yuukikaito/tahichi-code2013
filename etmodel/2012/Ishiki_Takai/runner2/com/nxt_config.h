/**
 *******************************************************************************
 **	FILE NAME : nxt_config.h
 **
 **	ABSTRUCT  : NXT device configration
 *******************************************************************************
 **/

#ifndef __nxt_confit_h__
#define __nxt_confit_h__

#include "ecrobot_interface.h"

/* NXT motor port configuration */
#define R_MOTOR_PORT	NXT_PORT_B
#define L_MOTOR_PORT	NXT_PORT_C

/* NXT Bluetooth configuration */
#define BT_PASS_KEY		"1234"

/* �o�����T�[�Ɏg�p����W���C���Z���T��ڑ�����|�[�g���w�肷��i�|�[�g4�ɐڑ�����ꍇ�j*/
#define BLNU_PORT		NXT_PORT_S4

/* ��Q���Ď��Ɏg�p���钴���g�Z���T��ڑ�����|�[�g���w�肷��(�|�[�g2�ɐڑ�����ꍇ) */
#define BMU_PORT		NXT_PORT_S2

/* ���C���Ď��Ɏg�p������Z���T��ڑ�����|�[�g���w�肷��(�|�[�g3�ɐڑ�����ꍇ) */
#define LMU_PORT		NXT_PORT_S3

/* �o���p�Ɏg�p����^�b�`�Z���T�̐ڑ��|�[�g���w�肷��(�|�[�g1�ɐڑ�����ꍇ) */
#define BU_PORT			 NXT_PORT_S1

#endif /* __nxt_confit_h__ */
