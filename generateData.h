#ifndef __GENERATEDATE_H
#define __GENERATEDATE_H

#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>

// 事件定义
#define YJDH  0x0000 // 一级点火
#define YJFL  0x0001 // 一级分离
#define EJDH  0x0002 // 二级点火
#define EJFL  0x0003 // 二级分离
#define DYZK  0x0004 // 弹翼展开
#define FDGR  0x0005 // 反弹干扰
#define ZDJD  0x0006 // 中段机动
#define DTFL  0x0007 // 弹头分离
#define LDZD  0x0008 // 雷达制导
#define HWZD  0x0009 // 红外制导
#define MBFP  0x000a // 目标分配
#define DJJD  0x000b // 打击角度

/**
 * @brief 导弹状态结构体
 * 用于描述导弹的实时运动状态和空间位置
 */
typedef struct {
    double time;            /**< 时间（单位：毫秒） */
    uint16_t event;         /**< 事件索引 */

    double longitude;       /**< 经度（单位：度） */
    double latitude;        /**< 纬度（单位：度） */
    double altitude;        /**< 海拔高度（单位：米） */
    
    double accelerationX;   /**< X轴加速度（单位：米/秒2） */
    double accelerationY;   /**< Y轴加速度（单位：米/秒2） */
    double accelerationZ;   /**< Z轴加速度（单位：米/秒2） */
    
    double velocityX;       /**< X轴速度（单位：米/秒） */
    double velocityY;       /**< Y轴速度（单位：米/秒） */
    double velocityZ;       /**< Z轴速度（单位：米/秒） */

    double yawAngle;        /**< 偏航角度（单位：度） */
    double pitchAngle;      /**< 俯仰角度（单位：度） */
    double rollAngle;       /**< 横滚角度（单位：度） */

    double yawRate;         /**< 偏航角速度（单位：度/秒） */
    double pitchRate;       /**< 俯仰角速度（单位：度/秒） */
    double rollRate;        /**< 横滚角速度（单位：度/秒） */

    double yawAcceleration;   /**< 偏航角加速度（单位：度/秒2） */
    double pitchAcceleration; /**< 俯仰角加速度（单位：度/秒2） */
    double rollAcceleration;  /**< 横滚角加速度（单位：度/秒2） */

} DiscretePoint;

// #define M_PI 3.14

#define CURRENT_TIME 0   
#define TIME_STEP_MS 1000     // 当前时间（毫秒）
#define TOTAL_TIME_MS 40000   // 总时间（400 000ms = 400秒）

#define STEPA 60000           // 上升阶段结束 时间60s 
#define STEPB 300000          // 巡航阶段结束 时间300s
#define STEPC 400000          // 攻击阶段结束 时间400s

#define TIME_BASE  100 

//uint32_t current_time_ms = 0;       
//uint32_t time_step_ms = 1000;        // 时间步长（1000ms = 1秒）
//uint32_t total_time_ms = 400000;    // 总时间（400 000ms = 400秒）
//uint32_t stepA = 60000;                 // 上升阶段结束 时间60s 
//uint32_t stepB = 300000;								// 平飞阶段结束 时间300s

DiscretePoint simulateMissileEvent(uint32_t time_ms) ;

#endif
