#ifndef __EVENT_H
#define __EVENT_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "trajectory_data.h"

// �¼�����
#define SXGB 0x0000
//�����׶�
#define TLJCYQRXH 0x0001 // ���������ȷ���ź�
#define FSTFLXH 0x0002 // ����̨�����ź�

//���ƶ�
#define YJFDJGBZLXH 0x0003 // һ���������ػ�ָ���ź�
#define YJFLJGJSXH 0x0004 // һ��������������ź�
#define EJFDJDHXH 0x0005 // ��������������ź�
#define ZLZFLXH 0x0006 // �����ַ����ź�
#define MZTJGBZLXH 0x0007 // ĩ���Ƽ��ػ�ָ���ź�

//�ж�
#define GXZDXZXH 0x0008 // �����Ƶ������ź�
#define XGZDJZXH 0x0009 // �ǹ��Ƶ�У׼�źţ��߾��ȣ�
#define DTMCJSXH 0x000a // ��ͷĸ�ս����ź�
#define YESFXH 0x000b // �ն��ͷ�ָ��

//ĩ��
#define ZRZTTZXH 0x000c // ������̬�����ź�
#define MDZDXZXH 0x000d // ĩ���Ƶ������źţ��߾��ȣ�
#define YXBXJSXH 0x000e // ���ű��ս���ź�
#define YBZLXH 0x000f // ����ָ���ź�

typedef struct
{
    uint32_t time;    /* �¼�������ʱ�������λ�����룩 */
    uint16_t event;   /* �¼����� */
    uint8_t isNull;   /* �Ƿ�Ϊ���¼���0��ʾ�ǿգ�1��ʾ�� */
} Event;

/* �����¼��ڵ㵽�¼������� */
void insert_node(uint32_t time, uint16_t event, uint8_t isNull);

/* ��������Ƿ���������������ؼ���� */
int check(float trend, uint32_t alt_samples[], uint32_t current_step, uint16_t current_event);

/* ���ݵ�ǰʱ��Ͳ�����ȡ��ǰ�ڵ���¼����� */
uint16_t get_current_node(uint32_t current_time, uint32_t current_step);

#endif
