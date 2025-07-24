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
    
    // 事件状态机（按时间顺序触发）
    if (time < 5.0)        point.event = YJDH;
    else if (time < 15.0)  point.event = YJFL;
    else if (time < 25.0)  point.event = EJDH;
    else if (time < 60.0)  point.event = EJFL;
    else if (time < 120.0) point.event = DYZK;
    else if (time < 180.0) point.event = FDGR;
    else if (time < 250.0) point.event = ZDJD;
    else if (time < 300.0) point.event = DTFL;
    else if (time < 350.0) point.event = LDZD;
    else if (time < 380.0) point.event = HWZD;
    else if (time < 390.0) point.event = MBFP;
    else                   point.event = DJJD;

    // 发射阶段（0-60秒）：多级动力飞行
    if (time <= 60.0) {
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
    else if (time <= 300.0) {
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

// main函数，生成离散点数组文件
int main() {
    uint32_t current_time_ms = 0;       // 当前时间（毫秒）
    uint32_t time_step_ms = 500;        // 时间步长（500ms = 0.5秒）
    uint32_t total_time_ms = 400000;    // 总时间（400000ms = 400秒）
    uint32_t point_count = total_time_ms / time_step_ms + 1; // 计算总点数

    // 初始化随机数种子
    srand(time(NULL));

    // 创建并打开输出文件
    FILE *file = fopen("python_test.c", "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file for writing.\n");
        return 1;
    }

    // 写入结构体定义
    fprintf(file, "#include <stdint.h>\n\n");

    // 写入事件宏定义
    fprintf(file, "// 事件定义\n");
    fprintf(file, "#define YJDH  0x0000 // 一级点火\n");
    fprintf(file, "#define YJFL  0x0001 // 一级分离\n");
    fprintf(file, "#define EJDH  0x0002 // 二级点火\n");
    fprintf(file, "#define EJFL  0x0003 // 二级分离\n");
    fprintf(file, "#define DYZK  0x0004 // 弹翼展开\n");
    fprintf(file, "#define FDGR  0x0005 // 反弹干扰\n");
    fprintf(file, "#define ZDJD  0x0006 // 中段机动\n");
    fprintf(file, "#define DTFL  0x0007 // 弹头分离\n");
    fprintf(file, "#define LDZD  0x0008 // 雷达制导\n");
    fprintf(file, "#define HWZD  0x0009 // 红外制导\n");
    fprintf(file, "#define MBFP  0x000a // 目标分配\n");
    fprintf(file, "#define DJJD  0x000b // 打击角度\n\n");

    fprintf(file, "typedef struct {\n");
    fprintf(file, "    double time;                  /* 时间（单位：毫秒） */\n");
    fprintf(file, "    uint16_t event;               /* 事件索引 */\n");
    fprintf(file, "    double longitude;             /* 经度（单位：度） */\n");
    fprintf(file, "    double latitude;              /* 纬度（单位：度） */\n");
    fprintf(file, "    double altitude;              /* 海拔高度（单位：米） */\n");
    fprintf(file, "    double accelerationX;         /* X轴加速度（单位：米/秒²） */\n");
    fprintf(file, "    double accelerationY;         /* Y轴加速度（单位：米/秒²） */\n");
    fprintf(file, "    double accelerationZ;         /* Z轴加速度（单位：米/秒²） */\n");
    fprintf(file, "    double velocityX;             /* X轴速度（单位：米/秒） */\n");
    fprintf(file, "    double velocityY;             /* Y轴速度（单位：米/秒） */\n");
    fprintf(file, "    double velocityZ;             /* Z轴速度（单位：米/秒） */\n");
    fprintf(file, "    double yawAngle;              /* 偏航角度（单位：度） */\n");
    fprintf(file, "    double pitchAngle;            /* 俯仰角度（单位：度） */\n");
    fprintf(file, "    double rollAngle;             /* 横滚角度（单位：度） */\n");
    fprintf(file, "    double yawRate;               /* 偏航角速度（单位：度/秒） */\n");
    fprintf(file, "    double pitchRate;             /* 俯仰角速度（单位：度/秒） */\n");
    fprintf(file, "    double rollRate;              /* 横滚角速度（单位：度/秒） */\n");
    fprintf(file, "    double yawAcceleration;       /* 偏航角加速度（单位：度/秒²） */\n");
    fprintf(file, "    double pitchAcceleration;     /* 俯仰角加速度（单位：度/秒²） */\n");
    fprintf(file, "    double rollAcceleration;      /* 横滚角加速度（单位：度/秒²） */\n");
    fprintf(file, "} DiscretePoint;\n\n");

    // 写入数组定义
    fprintf(file, "DiscretePoint discrete_points[%u] = {\n", point_count);

    // 事件名称映射表
    typedef struct { uint16_t code; const char* name; } EventMap;
    EventMap eventNames[] = {
        {0x0000, "YJDH"}, {0x0001, "YJFL"}, {0x0002, "EJDH"}, {0x0003, "EJFL"},
        {0x0004, "DYZK"}, {0x0005, "FDGR"}, {0x0006, "ZDJD"}, {0x0007, "DTFL"},
        {0x0008, "LDZD"}, {0x0009, "HWZD"}, {0x000a, "MBFP"}, {0x000b, "DJJD"}
    };
    int eventCount = sizeof(eventNames)/sizeof(EventMap);

    // 循环生成每个时间点的状态
    while (current_time_ms <= total_time_ms) {
        DiscretePoint point = simulateMissileEvent(current_time_ms);
        const char* eventName = "UNKNOWN_EVENT";
        
        // 查找事件宏名
        for (int i = 0; i < eventCount; i++) {
            if (eventNames[i].code == point.event) {
                eventName = eventNames[i].name;
                break;
            }
        }
        
        // 使用宏名初始化事件字段
        fprintf(file, "    {%.0f, %s, %.6f, %.6f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f},\n",
               point.time, eventName,
               point.longitude, point.latitude, point.altitude,
               point.accelerationX, point.accelerationY, point.accelerationZ,
               point.velocityX, point.velocityY, point.velocityZ,
               point.yawAngle, point.pitchAngle, point.rollAngle,
               point.yawRate, point.pitchRate, point.rollRate,
               point.yawAcceleration, point.pitchAcceleration, point.rollAcceleration);
        current_time_ms += time_step_ms;
    }

    fprintf(file, "};\n");
    fclose(file);
    return 0;
}