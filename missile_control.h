#ifndef __MISSILE_CONTROL_H
#define __MISSILE_CONTROL_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "trajectory_data.h"

// �¼�����
#define SXGB_DELTA 0
// �����׶�
#define TLJCYQRXH_DELTA 80 // ���������ȷ���ź�
#define FSTFLXH_DELTA 400  // ����̨�����ź�

// ���ƶ�
#define YJFDJGBZLXH_DELTA 29500 // һ���������ػ�ָ���ź�
#define YJFLJGJSXH_DELTA 29800 // һ��������������ź�
#define EJFDJDHXH_DELTA 29880 // ��������������ź�
#define ZLZFLXH_DELTA 59880    // �����ַ����ź�
#define MZTJGBZLXH_DELTA 79500 // ĩ���Ƽ��ػ�ָ���ź�

// �ж�
#define GXZDXZXH_DELTA 3000 // �����Ƶ������źţ�3000msһ��
#define XGZDJZXH_DELTA 50000 // �ǹ��Ƶ�У׼�źţ��߾��ȣ���50000msһ��
#define DTMCJSXH_DELTA 160000 // ��ͷĸ�ս����ź�
#define YESFXH_DELTA 5000 // �ն��ͷ�ָ��

// ĩ��
#define ZRZTTZXH_DELTA 0     // ������̬�����ź�
#define MDZDXZXH_DELTA 14000 // ĩ���Ƶ������źţ��߾��ȣ�
#define YXBXJSXH_DELTA 15400 // ���ű��ս���ź�
#define YBZLXH_DELTA 19000   // ����ָ���ź�

// ��ʼ�������켣����
void init_trajectory_stepA(); /* ��ʼ���׶�A�������� */

void init_trajectory_stepB(); /* ��ʼ���׶�B�������� */

void init_trajectory_stepC(); /* ��ʼ���׶�C�������� */

void init_trajectory_stepD(); /* ��ʼ���׶�D�������� */

extern uint32_t current_step; /* ��ǰ���н׶α�ʶ��0δ���䣬1�����׶Σ�2�ж��Ƶ��׶Σ�3ĩ���Ƶ� */

/* ���µ���λ����Ϣ */
uint16_t update_missile_position(uint32_t current_time); // current_time: ��ǰʱ���(����)

#endif /* __MISSILE_CONTROL_H */
