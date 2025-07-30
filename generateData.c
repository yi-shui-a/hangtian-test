#include "generateData.h"

// 生成[-0.5,0.5]的随机扰动
double randomPerturbation() {
    return (rand() / (double)RAND_MAX - 0.5); 
}

/**
 * @brief 带事件触发的导弹状态模拟
 * @param time_ms 飞行时间（毫秒，0-400000）
 * @return 对应时刻的导弹状态（含事件标记）
 */
DiscretePoint simulateMissileEvent(uint32_t time_ms) {
    double time = time_ms / 1000.0; // 转换为秒
    DiscretePoint point = {0};
    point.time = time_ms;
    
    // 随机扰动生成（基于时间种子）
    srand((unsigned int)(time * 1000)); 
    double perturb = randomPerturbation();
		
    // 发射阶段（0-60秒）：多级动力飞行
    if (time_ms <= STEPA) {
        double t_norm = time/60;
        
        // 姿态动力学模型
        point.yawAngle = 5.0 * sin(2*M_PI*t_norm) + perturb*0.1;
        point.pitchAngle = 85.0*(1-t_norm/3) + 2.0*sin(4*M_PI*t_norm) + perturb*0.2;
        point.rollAngle = 15.0 * cos(3*M_PI*t_norm) + perturb*0.3;
        
        point.yawRate = 10.0 * cos(2*M_PI*t_norm) + perturb*0.5;
        point.pitchRate = -5.0 + 8.0*cos(4*M_PI*t_norm) + perturb*0.6;
        point.rollRate = -20.0 * sin(3*M_PI*t_norm) + perturb*0.4;
        
        point.yawAcceleration = -20.0*M_PI*sin(2*M_PI*t_norm) + perturb*0.02;
        point.pitchAcceleration = -32.0*M_PI*sin(4*M_PI*t_norm) + perturb*0.03;
        point.rollAcceleration = -60.0*M_PI*cos(3*M_PI*t_norm) + perturb*0.01;
        
        // 位置计算（螺旋上升）
        point.latitude = 39.9042 + 0.01*sin(4*M_PI*t_norm) + perturb*1e-5;
        point.longitude = 116.4074 + 0.01*cos(4*M_PI*t_norm) + perturb*1e-5;
        point.altitude = 10000.0*pow(t_norm,1.8)*(1+0.1*sin(6*M_PI*t_norm)) + perturb;
        
        // 速度计算（动力加速）
        double thrust_factor = (point.event==YJDH||point.event==EJDH) ? 1.5 : 1.0;
        point.velocityX = 50.0*sin(4*M_PI*t_norm)*thrust_factor + perturb*0.3;
        point.velocityY = 50.0*cos(4*M_PI*t_norm)*thrust_factor + perturb*0.3;
        point.velocityZ = 80.0*t_norm*thrust_factor + perturb*0.5;
        
        // 加速度（含级间分离冲击）
        if(point.event == YJFL || point.event == EJFL) {
            point.accelerationX = 5.0*sin(4*M_PI*t_norm) + perturb*0.5;
            point.accelerationY = 5.0*cos(4*M_PI*t_norm) + perturb*0.5;
            point.accelerationZ = -10.0 + 40.0*t_norm + perturb*0.8;
        } else {
            point.accelerationX = 2.0*cos(4*M_PI*t_norm) + perturb*0.1;
            point.accelerationY = -2.0*sin(4*M_PI*t_norm) + perturb*0.1;
            point.accelerationZ = 30.0/(60-time+1) + perturb*0.2;
        }
    }
    // 巡航阶段（60-300秒）：弹翼展开+机动
    else if (time_ms <= STEPB) {
        double cruiseTime = time - 60;
        double phase = cruiseTime/30 * 2*M_PI;
        
        // 姿态动力学（弹翼展开效应）
        double wingEffect = (point.event>=DYZK) ? 1.5 : 1.0;
        point.yawAngle = 8.0*sin(0.5*phase)*wingEffect + perturb*0.2;
        point.pitchAngle = 5.0*cos(0.3*phase) + perturb*0.3;
        point.rollAngle = 10.0*sin(0.7*phase)*wingEffect + perturb*0.4;
        
        point.yawRate = 4.0*cos(0.5*phase)*wingEffect + perturb*0.5;
        point.pitchRate = -1.5*sin(0.3*phase) + perturb*0.6;
        point.rollRate = 7.0*cos(0.7*phase)*wingEffect + perturb*0.4;
        
        point.yawAcceleration = -2.0*sin(0.5*phase)*wingEffect + perturb*0.02;
        point.pitchAcceleration = -0.45*cos(0.3*phase) + perturb*0.03;
        point.rollAcceleration = -4.9*sin(0.7*phase)*wingEffect + perturb*0.01;
        
        // 位置计算（蛇形机动）
        point.latitude = 39.9042 + 0.5*cruiseTime/240 
                       + 0.05*sin(phase)*(point.event==ZDJD?2.0:1.0) + perturb*1e-5;
        point.longitude = 116.4074 + 0.8*cruiseTime/240 
                        + 0.03*cos(0.8*phase)*(point.event==ZDJD?1.5:1.0) + perturb*1e-5;
        point.altitude = 10000.0 + 50*sin(0.5*phase) + perturb*0.8;
        
        // 速度计算（干扰弹效应）
        double jammerEffect = (point.event==FDGR) ? 1.2 : 1.0;
        point.velocityX = (200.0 + 20*sin(0.2*phase))*jammerEffect + perturb*0.5;
        point.velocityY = (150.0 + 15*cos(0.3*phase))*jammerEffect + perturb*0.5;
        point.velocityZ = 10.0*cos(phase)*jammerEffect + perturb*0.3;
        
        // 加速度（机动特性）
        point.accelerationX = -0.5*sin(0.2*phase)*jammerEffect + perturb*0.05;
        point.accelerationY = 0.3*cos(0.3*phase)*jammerEffect + perturb*0.05;
        point.accelerationZ = -0.2*sin(phase)*jammerEffect + perturb*0.03;
    }
    // 攻击阶段（300-400秒）：末端制导
    else {
        double attackTime = time - 300;
        double t_norm = attackTime/100;
        double spiralPhase = 10*M_PI*t_norm;
        
        // 姿态动力学（末端机动）
        point.yawAngle = 15.0*sin(spiralPhase)*(1+0.5*t_norm) + perturb*0.5;
        point.pitchAngle = -45.0*t_norm + 10.0*cos(2*spiralPhase) + perturb*0.6;
        point.rollAngle = 30.0*sin(1.5*spiralPhase) + perturb*0.7;
        
        point.yawRate = 150.0*cos(spiralPhase)*(1+t_norm) + perturb*2.0;
        point.pitchRate = -45.0 - 20.0*sin(2*spiralPhase) + perturb*3.0;
        point.rollRate = 45.0*cos(1.5*spiralPhase) + perturb*2.5;
        
        point.yawAcceleration = -1500.0*M_PI*sin(spiralPhase) + perturb*0.5;
        point.pitchAcceleration = -40.0*M_PI*cos(2*spiralPhase) + perturb*0.6;
        point.rollAcceleration = -67.5*M_PI*sin(1.5*spiralPhase) + perturb*0.3;
        
        // 位置计算（制导螺旋）
        point.latitude = 40.4042 - 0.2*t_norm 
                       + 0.02*sin(spiralPhase)*(point.event==LDZD?2.0:1.0) + perturb*1e-5;
        point.longitude = 117.2074 - 0.1*t_norm 
                        + 0.02*cos(spiralPhase)*(point.event==HWZD?1.5:1.0) + perturb*1e-5;
        point.altitude = 10000.0*(1-pow(t_norm,1.5)) 
                       + 100*sin(2*spiralPhase) + perturb*1.2;
        
        // 速度计算（末端加速）
        double guidanceEffect = (point.event>=LDZD) ? 1.8 : 1.0;
        point.velocityX = (-100.0*t_norm + 80*cos(spiralPhase))*guidanceEffect + perturb*1.0;
        point.velocityY = (-80.0*t_norm + 50*sin(spiralPhase))*guidanceEffect + perturb*1.0;
        point.velocityZ = (-800.0*pow(t_norm,0.7))*guidanceEffect + perturb*0.8;
        
        // 加速度（打击机动）
        point.accelerationX = (-1.0 + 3.0*sin(spiralPhase))*guidanceEffect + perturb*0.1;
        point.accelerationY = (-0.8 + 2.5*cos(spiralPhase))*guidanceEffect + perturb*0.1;
        point.accelerationZ = (-60.0*pow(t_norm,-0.3))*guidanceEffect + perturb*0.2;
    }
    
    return point;
}