#ifndef __EVENT_H
#define __EVENT_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "trajectory_data.h"

// 事件定义
#define SXGB 0x0000
//点火发射阶段
#define TLJCYQRXH 0x0001 // 推力监测与确认信号
#define FSTFLXH 0x0002 // 发射台分离信号

//助推段
#define YJFDJGBZLXH 0x0003 // 一级发动机关机指令信号
#define YJFLJGJSXH 0x0004 // 一级分离机构解锁信号
#define EJFDJDHXH 0x0005 // 二级发动机点火信号
#define ZLZFLXH 0x0006 // 整流罩分离信号
#define MZTJGBZLXH 0x0007 // 末助推级关机指令信号

//中段
#define GXZDXZXH 0x0008 // 惯性制导修正信号
#define XGZDJZXH 0x0009 // 星光制导校准信号（高精度）
#define DTMCJSXH 0x000a // 弹头母舱解锁信号
#define YESFXH 0x000b // 诱饵释放指令

//末段
#define ZRZTTZXH 0x000c // 再入姿态调整信号
#define MDZDXZXH 0x000d // 末端制导修正信号（高精度）
#define YXBXJSXH 0x000e // 引信保险解除信号
#define YBZLXH 0x000f // 引爆指令信号

typedef struct
{
    uint32_t time;    /* 事件发生的时间戳（单位：毫秒） */
    uint16_t event;   /* 事件类型 */
    uint8_t isNull;   /* 是否为空事件：0表示非空，1表示空 */
} Event;

/* 插入事件节点到事件链表中 */
void insert_node(uint32_t time, uint16_t event, uint8_t isNull);

/* 检查趋势是否符合条件，并返回检查结果 */
int check(float trend, uint32_t alt_samples[], uint32_t current_step, uint16_t current_event);

/* 根据当前时间和步长获取当前节点的事件类型 */
uint16_t get_current_node(uint32_t current_time, uint32_t current_step);

#endif
