#ifndef __MISSILE_CONTROL_H
#define __MISSILE_CONTROL_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "trajectory_data.h"

// 考虑时间 大于等于 
#define SXGB_DELTA 0
#define YJDH_DELTA 5000
#define YJFL_DELTA 15000
#define EJDH_DELTA 25000
#define EJFL_DELTA 60000      /* 阶段A */

#define DYZK_DELTA  60000 
#define FDGR_DELTA  120000 
#define ZDJD_DELTA  190000     /* 阶段B */
 
#define DTFL_DELTA  0 
#define LDZD_DELTA  50000 
#define HWZD_DELTA  80000 
#define MBFP_DELTA  90000 
#define DJJD_DELTA  100000     /* 阶段C */

// 函数声明
void init_trajectory_stepA(); /* 插入数据 */

void init_trajectory_stepB(); /*  */

void init_trajectory_stepC();

extern uint32_t current_step;  /* 0未点火、  1代表上升阶段、  2代表中间阶段、 3代表末端  */

uint16_t update_missile_position(uint32_t current_time);

#endif /* __MISSILE_CONTROL_H */
    