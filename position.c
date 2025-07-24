#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define YJDH 0X0000 // 一级点火
#define YJFL 0X0001 // 一级分离
#define EJDH 0X0002 // 二级点火
#define EJFL 0X0003 // 二级分离
#define DYZK 0X0004 // 弹翼展开
#define FDGR 0X0005 // 反弹干扰
#define ZDJD 0X0006 // 中段机动
#define DTFL 0X0007 // 弹头分离
#define LDZD 0X0008 // 雷达制导
#define HWZD 0X0009 // 红外制导
#define MBFP 0X000a // 目标分配
#define DJJD 0X000b // 打击角度




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
    
    double accelerationX;   /**< X轴加速度（单位：米/秒²） */
    double accelerationY;   /**< Y轴加速度（单位：米/秒²） */
    double accelerationZ;   /**< Z轴加速度（单位：米/秒²） */
    
    double velocityX;       /**< X轴速度（单位：米/秒） */
    double velocityY;       /**< Y轴速度（单位：米/秒） */
    double velocityZ;       /**< Z轴速度（单位：米/秒） */

    double yawAngle;        /**< 偏航角度（单位：度） */
    double pitchAngle;      /**< 俯仰角度（单位：度） */
    double rollAngle;       /**< 横滚角度（单位：度） */

    double yawRate;         /**< 偏航角速度（单位：度/秒） */
    double pitchRate;       /**< 俯仰角速度（单位：度/秒） */
    double rollRate;        /**< 横滚角速度（单位：度/秒） */

    double yawAcceleration;   /**< 偏航角加速度（单位：度/秒²） */
    double pitchAcceleration; /**< 俯仰角加速度（单位：度/秒²） */
    double rollAcceleration;  /**< 横滚角加速度（单位：度/秒²） */

} DiscretePoint;

// 生成[-0.5,0.5]米的随机扰动
double randomPerturbation() {
    return (rand() / (double)RAND_MAX - 0.5); 
}

/**
 * @brief 带扰动的导弹状态模拟
 * @param time 飞行时间（秒，0-400）
 * @return 对应时刻的导弹状态（含随机扰动）
 */
MissileState simulateMissileRealistic(double time) {
    srand((unsigned int)(time * 1000)); // 基于时间的随机种子
    
    MissileState state = {0};
    double perturbation = randomPerturbation();
    
    // 发射阶段（0-60秒）：螺旋上升
    if (time <= 60.0) {
        // 基础轨迹（螺旋上升）
        double t_norm = time/60;
        state.latitude = 39.9042 + 0.01 * sin(4*M_PI*t_norm) + perturbation*1e-5;
        state.longitude = 116.4074 + 0.01 * cos(4*M_PI*t_norm) + perturbation*1e-5;
        state.altitude = 1000.0 * pow(t_norm, 1.8) + perturbation;
        
        // 运动参数（三维复合运动）
        state.velocityX = 50.0 * sin(4*M_PI*t_norm) * (0.5 + 0.5*t_norm);
        state.velocityY = 50.0 * cos(4*M_PI*t_norm) * (0.5 + 0.5*t_norm);
        state.velocityZ = 80.0 * t_norm + perturbation*0.1;
        
        // 加速度（含随机抖动）
        state.accelerationX = 2.0 * cos(4*M_PI*t_norm) + perturbation*0.05;
        state.accelerationY = -2.0 * sin(4*M_PI*t_norm) + perturbation*0.05;
        state.accelerationZ = 30.0/(60-time+1) + perturbation*0.02;
    }
    // 巡航阶段（60-300秒）：蛇形机动
    else if (time <= 300.0) {
        double cruiseTime = time - 60;
        double phase = cruiseTime/30 * 2*M_PI;
        
        // 位置计算（蛇形路径）
        state.latitude = 39.9042 + 0.5*cruiseTime/240 
                       + 0.05*sin(phase) + perturbation*1e-5;
        state.longitude = 116.4074 + 0.8*cruiseTime/240 
                        + 0.03*cos(0.8*phase) + perturbation*1e-5;
        state.altitude = 10000.0 + 50*sin(0.5*phase) + perturbation;
        
        // 运动参数（带扰动的变速巡航）
        state.velocityX = 200.0 + 20*sin(0.2*phase) + perturbation*0.3;
        state.velocityY = 150.0 + 15*cos(0.3*phase) + perturbation*0.3;
        state.velocityZ = 10.0 * cos(phase) + perturbation*0.2;
        
        // 加速度（气动扰动）
        state.accelerationX = -0.5*sin(0.2*phase) + perturbation*0.01;
        state.accelerationY = 0.3*cos(0.3*phase) + perturbation*0.01;
        state.accelerationZ = -0.2*sin(phase) + perturbation*0.005;
    }
    // 攻击阶段（300-400秒）：螺旋俯冲
    else {
        double attackTime = time - 300;
        double t_norm = attackTime/100;
        double spiralPhase = 10*M_PI*t_norm;
        
        // 位置计算（螺旋下降）
        state.latitude = 40.4042 - 0.2*t_norm 
                       + 0.01*sin(spiralPhase) + perturbation*1e-5;
        state.longitude = 117.2074 - 0.1*t_norm 
                        + 0.01*cos(spiralPhase) + perturbation*1e-5;
        state.altitude = 10000.0*(1-pow(t_norm,1.2)) 
                       + 50*sin(2*spiralPhase) + perturbation;
        
        // 运动参数（三维加速俯冲）
        state.velocityX = -100.0*t_norm + 50*cos(spiralPhase) + perturbation*0.5;
        state.velocityY = -80.0*t_norm + 30*sin(spiralPhase) + perturbation*0.5;
        state.velocityZ = -500.0*pow(t_norm,0.8) + perturbation*0.3;
        
        // 加速度（末端机动）
        state.accelerationX = -1.0 + 2.0*sin(spiralPhase) + perturbation*0.02;
        state.accelerationY = -0.8 + 1.5*cos(spiralPhase) + perturbation*0.02;
        state.accelerationZ = -40.0*pow(t_norm,-0.2) + perturbation*0.01;
    }
    
    return state;
}

// main函数，运行模拟
int main() {
    double current_time = 0.0;
    double timeStep = 0.5;
    double totalTime = 400.0;
    
    // 初始化随机数种子
    srand(time(NULL));

    //写入一个c文件，文件中定义一个导弹状态数组，数组中每个元素是一个代表当前时间的导弹状态结构体，
    //数组的长度是总时间除以时间步长，每个时间点的导弹状态结构体中包含导弹的经度、纬度、海拔高度、
    //X轴速度、Y轴速度、Z轴速度、X轴加速度、Y轴加速度、Z轴加速度
    FILE *file = fopen("missile_states.c", "w");
    if (file == NULL) {
        printf("Error: Could not open file for writing.\n");
        return 1;
    }
    // 添加结构体定义
    fprintf(file, "typedef struct {\n");
    fprintf(file, "    double longitude;       /* 经度（单位：度） */\n");
    fprintf(file, "    double latitude;        /* 纬度（单位：度） */\n");
    fprintf(file, "    double altitude;        /* 海拔高度（单位：米） */\n");
    fprintf(file, "    double accelerationX;   /* X轴加速度（单位：米/秒²） */\n");
    fprintf(file, "    double accelerationY;   /* Y轴加速度（单位：米/秒²） */\n");
    fprintf(file, "    double accelerationZ;   /* Z轴加速度（单位：米/秒²） */\n");
    fprintf(file, "    double velocityX;       /* X轴速度（单位：米/秒） */\n");
    fprintf(file, "    double velocityY;       /* Y轴速度（单位：米/秒） */\n");
    fprintf(file, "    double velocityZ;       /* Z轴速度（单位：米/秒） */\n");
    fprintf(file, "} MissileState;\n\n");
    // 生成数组定义
    fprintf(file, "MissileState missile_states[%d] = {\n", (int)(totalTime/timeStep));
while (current_time <= totalTime) {
        MissileState state = simulateMissileRealistic(current_time);
        fprintf(file, "    {%.6f, %.6f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f},\n",
               // 修正为结构体定义的成员顺序：经度、纬度、高度、加速度X/Y/Z、速度X/Y/Z
               state.longitude, state.latitude, state.altitude,
               state.accelerationX, state.accelerationY, state.accelerationZ,
               state.velocityX, state.velocityY, state.velocityZ);
        current_time += timeStep;
    }
    fprintf(file, "};\n");
    fclose(file);
    return 0;
}
    
