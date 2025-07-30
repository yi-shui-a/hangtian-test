#ifndef __TRAJECTORY_DATA_H
#define __TRAJECTORY_DATA_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct trajectory
{
    uint32_t time;
    double longitude;         /**< 经度（单位：度） */
    double latitude;          /**< 纬度（单位：度） */
    double altitude;          /**< 海拔高度（单位：米） */
    double accelerationX;     /**< X轴加速度（单位：米/秒2） */
    double accelerationY;     /**< Y轴加速度（单位：米/秒2） */
    double accelerationZ;     /**< Z轴加速度（单位：米/秒2） */
    double velocityX;         /**< X轴速度（单位：米/秒） */
    double velocityY;         /**< Y轴速度（单位：米/秒） */
    double velocityZ;         /**< Z轴速度（单位：米/秒） */
    double yawAngle;          /**< 偏航角度（单位：度） */
    double pitchAngle;        /**< 俯仰角度（单位：度） */
    double rollAngle;         /**< 横滚角度（单位：度） */
    double yawRate;           /**< 偏航角速度（单位：度/秒） */
    double pitchRate;         /**< 俯仰角速度（单位：度/秒） */
    double rollRate;          /**< 横滚角速度（单位：度/秒） */
    double yawAcceleration;   /**< 偏航角加速度（单位：度/秒2） */
    double pitchAcceleration; /**< 俯仰角加速度（单位：度/秒2） */
    double rollAcceleration;  /**< 横滚角加速度（单位：度/秒2） */
} TrajectoryData;

void trajectory_array_ptr(TrajectoryData *trajectory_ptr);

uint32_t getCurrentTime(uint32_t tick_counter); /* 锟斤拷取锟斤拷前时锟斤拷 */

uint8_t getCurrentStep(uint32_t tick_counter); /* 锟斤拷取锟斤拷前锟阶讹拷 锟斤拷锟斤拷前锟斤拷 5锟斤拷锟斤拷 */

TrajectoryData getTrajectoryData(uint32_t tick_counter);

TrajectoryData getTrajectoryDataWithIndex(uint32_t index);

#endif
