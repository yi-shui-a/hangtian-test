#ifndef __EVENT_H
#define __EVENT_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

//点火发射阶段
#define TLJCYQRXH 0x0000 // 推力监测与确认信号
#define FSTFLXH 0x0001 // 发射台分离信号

//助推段
#define YJFDJGBZLXH 0x0002 // 一级发动机关机指令信号
#define YJFLJGJSXH 0x0003 // 一级分离机构解锁信号
#define EJFDJDHXH 0x0004 // 二级发动机点火信号
#define ZLZFLXH 0x0005 // 整流罩分离信号
#define MZTJGBZLXH 0x0006 // 末助推级关机指令信号

//中段
#define GXZDXZXH 0x0007 // 惯性制导修正信号
#define XGZDJZXH 0x0008 // 星光制导校准信号（高精度）
#define DTMCJSXH 0x0009 // 弹头母舱解锁信号
#define YESFXH 0x000a // 诱饵释放指令

//末段
#define ZRZTTZXH 0x000b // 再入姿态调整信号
#define MDZDXZXH 0x000c // 末端制导修正信号（高精度）
#define YXBXJSXH 0x000d // 引信保险解除信号
#define YBZLXH 0x000e // 引爆指令信号

typedef struct
{
	uint32_t time;	
	uint16_t event; 
	uint8_t isNull; 
} Event;

void insert_node(uint32_t time, uint16_t event, uint8_t isNull);
uint16_t get_current_node(uint32_t current_time);

#endif /* __EVENT_H */