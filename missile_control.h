#ifndef __MISSILE_CONTROL_H
#define __MISSILE_CONTROL_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "trajectory_data.h"

// ����ʱ�� ���ڵ��� 
#define SXGB_DELTA 0

#define TLJCYQRXH_DELTA 80
#define FSTFLXH_DELTA 400
#define YJFDJGBZLXH_DELTA 3000
#define YJFLJGJSXH_DELTA 30300      /* �׶�A */
#define EJFDJDHXH_DELTA 30380
#define ZLZFLXH_DELTA 60380
#define MZTJGBZLXH_DELTA 80000    /* �׶�A */

#define GXZDXZXH_DELTA  3000 
#define XGZDJZXH_DELTA  50000 
#define DTMCJSXH_DELTA  60000     /* �׶�B */
#define YESFXH_DELTA  210000     /* �׶�B */
 
#define ZRZTTZXH_DELTA  170000 
#define MDZDXZXH_DELTA  174000 
#define YXBXJSXH_DELTA  179400
#define YBZLXH_DELTA    180000


// ��������
void init_trajectory_stepA(uint32_t current); /* �������� */

void init_trajectory_stepB(uint32_t current); /*  */

void init_trajectory_stepC(uint32_t current);

uint16_t update_missile_position(uint32_t current_time);

#endif /* __MISSILE_CONTROL_H */
    