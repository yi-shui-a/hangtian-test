#ifndef __MISSILE_CONTROL_H
#define __MISSILE_CONTROL_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "trajectory_data.h"

// ����ʱ�� ���ڵ��� 
#define SXGB_DELTA 0
#define YJDH_DELTA 5000
#define YJFL_DELTA 15000
#define EJDH_DELTA 25000
#define EJFL_DELTA 60000      /* �׶�A */

#define DYZK_DELTA  40000 
#define FDGR_DELTA  50000 
#define ZDJD_DELTA  55000     /* �׶�B */
 
#define DTFL_DELTA  10000 
#define LDZD_DELTA  15000 
#define HWZD_DELTA  27000 
#define MBFP_DELTA  28000 
#define DJJD_DELTA  70000     /* �׶�C */

// ��������
void init_trajectory_stepA(uint32_t current); /* �������� */

void init_trajectory_stepB(uint32_t current); /*  */

void init_trajectory_stepC(uint32_t current);

uint16_t update_missile_position(uint32_t current_time);

#endif /* __MISSILE_CONTROL_H */
    