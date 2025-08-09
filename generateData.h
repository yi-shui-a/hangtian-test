#ifndef __GENERATEDATE_H
#define __GENERATEDATE_H

#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>

// 事件定义
#define SXGB 0x0000
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

#define STEP_A 500           // 上升阶段结束 时间0.5s 
#define STEP_B 80000           // 上升阶段结束 时间80s 
#define STEP_C 380000          // 巡航阶段结束 时间380s
#define STEP_D 400000          // 攻击阶段结束 时间400s

#define TIME_BASE  100 

//uint32_t current_time_ms = 0;       
//uint32_t time_step_ms = 1000;        // 时间步长（1000ms = 1秒）
//uint32_t total_time_ms = 400000;    // 总时间（400 000ms = 400秒）
//uint32_t stepA = 60000;                 // 上升阶段结束 时间60s 
//uint32_t stepB = 300000;								// 平飞阶段结束 时间300s

DiscretePoint simulateMissileEvent(uint32_t time_ms) ;

#endif
