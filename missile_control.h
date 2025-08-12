#ifndef __MISSILE_CONTROL_H
#define __MISSILE_CONTROL_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "trajectory_data.h"

// 事件定义
#define SXGB_DELTA 0
// 点火发射阶段
#define TLJCYQRXH_DELTA 60 // 推力监测与确认信号
#define FSTFLXH_DELTA 250  // 发射台分离信号

// 助推段
#define YJFDJGBZLXH_DELTA 18000 // 一级发动机关机指令信号
#define YJFLJGJSXH_DELTA 18200  // 一级分离机构解锁信号
#define EJFDJDHXH_DELTA 18400   // 二级发动机点火信号
#define ZLZFLXH_DELTA 38500    // 整流罩分离信号
#define MZTJGBZLXH_DELTA 47500 // 末助推级关机指令信号

// 中段
#define GXZDXZXH_DELTA 2000   // 惯性制导修正信号，2000ms一次
#define XGZDJZXH_DELTA 30000  // 星光制导校准信号（高精度），30000ms一次
#define DTMCJSXH_DELTA 130000 // 弹头母舱解锁信号
#define YESFXH_DELTA 3000     // 诱饵释放指令

// 末段
#define ZRZTTZXH_DELTA 0     // 再入姿态调整信号
#define MDZDXZXH_DELTA 7000 // 末端制导修正信号（高精度）
#define YXBXJSXH_DELTA 9400 // 引信保险解除信号
#define YBZLXH_DELTA 11300   // 引爆指令信号

// 初始化弹道轨迹函数
void init_trajectory_stepA(); /* 初始化阶段A弹道参数 */

void init_trajectory_stepB(); /* 初始化阶段B弹道参数 */

void init_trajectory_stepC(); /* 初始化阶段C弹道参数 */

void init_trajectory_stepD(); /* 初始化阶段D弹道参数 */

extern uint32_t current_step; /* 当前飞行阶段标识：0未发射，1点火发射阶段，2中段制导阶段，3末段制导 */

/* 更新导弹位置信息 */
uint16_t update_missile_position(uint32_t current_time); // current_time: 当前时间戳(毫秒)

#endif /* __MISSILE_CONTROL_H */
