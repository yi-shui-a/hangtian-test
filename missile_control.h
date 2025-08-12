#ifndef __MISSILE_CONTROL_H
#define __MISSILE_CONTROL_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "trajectory_data.h"

// �¼�����
#define SXGB_DELTA 0
// �����׶�
#define TLJCYQRXH_DELTA 60 // ���������ȷ���ź�
#define FSTFLXH_DELTA 250  // ����̨�����ź�

// ���ƶ�
#define YJFDJGBZLXH_DELTA 18000 // һ���������ػ�ָ���ź�
#define YJFLJGJSXH_DELTA 18200  // һ��������������ź�
#define EJFDJDHXH_DELTA 18400   // ��������������ź�
#define ZLZFLXH_DELTA 38500    // �����ַ����ź�
#define MZTJGBZLXH_DELTA 47500 // ĩ���Ƽ��ػ�ָ���ź�

// �ж�
#define GXZDXZXH_DELTA 2000   // �����Ƶ������źţ�2000msһ��
#define XGZDJZXH_DELTA 30000  // �ǹ��Ƶ�У׼�źţ��߾��ȣ���30000msһ��
#define DTMCJSXH_DELTA 130000 // ��ͷĸ�ս����ź�
#define YESFXH_DELTA 3000     // �ն��ͷ�ָ��

// ĩ��
#define ZRZTTZXH_DELTA 0     // ������̬�����ź�
#define MDZDXZXH_DELTA 7000 // ĩ���Ƶ������źţ��߾��ȣ�
#define YXBXJSXH_DELTA 9400 // ���ű��ս���ź�
#define YBZLXH_DELTA 11300   // ����ָ���ź�

// ��ʼ�������켣����
void init_trajectory_stepA(); /* ��ʼ���׶�A�������� */

void init_trajectory_stepB(); /* ��ʼ���׶�B�������� */

void init_trajectory_stepC(); /* ��ʼ���׶�C�������� */

void init_trajectory_stepD(); /* ��ʼ���׶�D�������� */

extern uint32_t current_step; /* ��ǰ���н׶α�ʶ��0δ���䣬1�����׶Σ�2�ж��Ƶ��׶Σ�3ĩ���Ƶ� */

/* ���µ���λ����Ϣ */
uint16_t update_missile_position(uint32_t current_time); // current_time: ��ǰʱ���(����)

#endif /* __MISSILE_CONTROL_H */
