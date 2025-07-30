#ifndef __EVENT_H
#define __EVENT_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// �¼�����
#define SXGB 0x0000 // ʱ��ر�
#define YJDH 0x0001 // һ�����  ������
#define YJFL 0x0002 // һ������
#define EJDH 0x0003 // �������
#define EJFL 0x0004 // ��������  /* �׶�A */

#define DYZK 0x0005 // ����չ��
#define FDGR 0x0006 // ��������
#define ZDJD 0x0007 // �жλ���  /* �׶�B */

#define DTFL 0x0008 // ��ͷ����
#define LDZD 0x0009 // �״��Ƶ�
#define HWZD 0x000a // �����Ƶ�
#define MBFP 0x000b // Ŀ�����
#define DJJD 0x000c // ����Ƕ�  /* �׶�C */

typedef struct
{
	uint32_t time;	/* ʱ�䣨��λ�����룩 */
	uint16_t event; /* �¼����� */
	uint8_t isNull; /* �Ƿ�� 0�� 1ռ�� */
} Event;

#define NUMBER 20

Event discrete_points[] = {
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0},
	{0, SXGB, 0}}; /* 20 ��� */

// ���������������
void insert_node(uint32_t time, uint16_t event, uint8_t isNull);

uint8_t array_index = 0;

uint8_t array_current = 0;

uint16_t get_current_node(uint32_t current_time);

#endif
