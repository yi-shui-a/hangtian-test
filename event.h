#ifndef __EVENT_H
#define __EVENT_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// 事件定义
#define SXGB 0x0000 // 时序关闭
#define YJDH 0x0001 // 一级点火  ！！！
#define YJFL 0x0002 // 一级分离
#define EJDH 0x0003 // 二级点火
#define EJFL 0x0004 // 二级分离  /* 阶段A */

#define DYZK 0x0005 // 弹翼展开
#define FDGR 0x0006 // 反弹干扰
#define ZDJD 0x0007 // 中段机动  /* 阶段B */

#define DTFL 0x0008 // 弹头分离
#define LDZD 0x0009 // 雷达制导
#define HWZD 0x000a // 红外制导
#define MBFP 0x000b // 目标分配
#define DJJD 0x000c // 打击角度  /* 阶段C */

typedef struct
{
	uint32_t time;	/* 时间（单位：毫秒） */
	uint16_t event; /* 事件索引 */
	uint8_t isNull; /* 是否空 0空 1占用 */
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
	{0, SXGB, 0}}; /* 20 多个 */

// 数组操作函数声明
void insert_node(uint32_t time, uint16_t event, uint8_t isNull);

uint8_t array_index = 0;

uint8_t array_current = 0;

uint16_t get_current_node(uint32_t current_time);

#endif
