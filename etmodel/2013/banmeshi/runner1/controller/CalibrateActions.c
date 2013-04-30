/*
 * COPYRIGHT(c)2010 Afrel Co., Ltd.
 * CalibrateActions.c
 * CalibrateActions�N���X
 *
 * �N���X��: CalibrateActions(CA)
 * ����:
 * ����: set_threshold
 * �֘A: LineMonitorUnit(LMU), BalancerUnit(BLNU), common
 */


#include "CalibrateActions.h"
#include "./unit/HornUnit.h"
#include "./unit/BumperUnit.h"


/**
 * CalibrateActions�̏���������
 */
void CA_pre(void) {
	LMU_pre(); /* LineMonitorUnit�̏����� */
	BLNU_pre(); /* BalancerUnit�̏����� */
}

/**
 * CalibrateActions�̏I������
 */
void CA_post(void) {
	LMU_post(); /* LineMonitorUnit�̏I������ */
	BLNU_post(); /* BalancerUnit�̏I������ */
}

void CA_set_threshold(void) {
	/*
	int time = 0;
		/*LineMonitorUnit�ɃZ���T�̒l���Z�b�g���� */
		while(1){
			if(BU_is_touched()){
				HU_ok_sound();
				LMU_set_black_value( LMU_is_line_value() );
				systick_wait_ms(500);
				break;
			}
		}
		while(1){
			if(BU_is_touched()){
				HU_ok_sound();
				LMU_set_white_value( LMU_is_line_value() );
				systick_wait_ms(500);
				break;
			}
		}
		LMU_set_gray_value((LMU_get_black_value()+LMU_get_white_value())/2);
		LMU_set_threshold((LMU_get_black_value()+LMU_get_white_value())/2);

		while(1){
			if(BU_is_touched()){
				HU_ok_sound();
				BLNU_set_gyro_offset();
				systick_wait_ms(500);
				break;
			}
		}

		while(1){
			if(BU_is_touched()){
				break;
			}
		}

		//LMU_set_black_value(BLACK_VAL);
		//LMU_set_white_value(WHITE_VAL);
		//LMU_set_gray_value(GRAY_VAL);
		//LMU_set_threshold(LIGHT_TH);

		/* BalancerUnit�̃I�t�Z�b�g�l���Z�b�g���� */
		//BLNU_set_gyro_offset();

}

/******************************** END OF FILE ********************************/
