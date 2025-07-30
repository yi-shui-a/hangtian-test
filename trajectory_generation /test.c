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
    double yawAcceleration; /**< 偏航角加速度（单位：度/秒²） */
    double pitchAcceleration; /**< 俯仰角加速度（单位：度/秒²） */
    double rollAcceleration;  /**< 横滚角加速度（单位：度/秒²） */
} DiscretePoint;

/**
 * @brief 链表节点结构体
 */
typedef struct DiscretePointNode {
    DiscretePoint data;      /**< 导弹状态数据 */
    struct DiscretePointNode* next; /**< 指向下一个节点的指针 */
} DiscretePointNode;

/**
 * @brief 导弹状态链表管理结构体
 */
typedef struct {
    DiscretePointNode* head;      /**< 链表头节点 */
    DiscretePointNode* tail;      /**< 链表尾节点（优化尾插效率） */
    int count;              /**< 当前节点数量 */
} DiscretePointStateList;

/* 函数声明 */
void initDiscretePointList(DiscretePointStateList* list);
void insertDiscretePointData(
    DiscretePointStateList* list,
    double time, uint16_t event,
    double longitude, double latitude, double altitude,
    double accX, double accY, double accZ,
    double velX, double velY, double velZ,
    double yaw, double pitch, double roll,
    double yawRate, double pitchRate, double rollRate,
    double yawAcc, double pitchAcc, double rollAcc
);
void printDiscretePointList(const DiscretePointStateList* list);
DiscretePointNode* findDiscretePointByTime(const DiscretePointStateList* list, double time);
void deleteDiscretePointByTime(DiscretePointStateList* list, double time);
void clearDiscretePointList(DiscretePointStateList* list);

/**
 * @brief 初始化导弹状态链表
 */
void initDiscretePointList(DiscretePointStateList* list) {
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
}

/**
 * @brief 插入导弹状态数据（直接在函数内构造结构体）
 * @param list 链表指针
 * @param time 时间戳（毫秒）
 * @param event 事件索引
 * @param longitude 经度
 * @param latitude 纬度
 * @param altitude 高度
 * @param accX X轴加速度
 * @param accY Y轴加速度
 * @param accZ Z轴加速度
 * @param velX X轴速度
 * @param velY Y轴速度
 * @param velZ Z轴速度
 * @param yaw 偏航角
 * @param pitch 俯仰角
 * @param roll 横滚角
 * @param yawRate 偏航角速度
 * @param pitchRate 俯仰角速度
 * @param rollRate 横滚角速度
 * @param yawAcc 偏航角加速度
 * @param pitchAcc 俯仰角加速度
 * @param rollAcc 横滚角加速度
 */
void insertDiscretePointData(
    DiscretePointStateList* list,
    double time, uint16_t event,
    double longitude, double latitude, double altitude,
    double accX, double accY, double accZ,
    double velX, double velY, double velZ,
    double yaw, double pitch, double roll,
    double yawRate, double pitchRate, double rollRate,
    double yawAcc, double pitchAcc, double rollAcc
) {
    /* 创建新节点 */
    DiscretePointNode* newNode = (DiscretePointNode*)malloc(sizeof(DiscretePointNode));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed for new discretePoint data!\n");
        return;
    }

    /* 直接填充结构体数据 */
    newNode->data.time = time;
    newNode->data.event = event;
    newNode->data.longitude = longitude;
    newNode->data.latitude = latitude;
    newNode->data.altitude = altitude;
    newNode->data.accelerationX = accX;
    newNode->data.accelerationY = accY;
    newNode->data.accelerationZ = accZ;
    newNode->data.velocityX = velX;
    newNode->data.velocityY = velY;
    newNode->data.velocityZ = velZ;
    newNode->data.yawAngle = yaw;
    newNode->data.pitchAngle = pitch;
    newNode->data.rollAngle = roll;
    newNode->data.yawRate = yawRate;
    newNode->data.pitchRate = pitchRate;
    newNode->data.rollRate = rollRate;
    newNode->data.yawAcceleration = yawAcc;
    newNode->data.pitchAcceleration = pitchAcc;
    newNode->data.rollAcceleration = rollAcc;
    newNode->next = NULL;

    /* 插入链表 */
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->count++;
}

/**
 * @brief 打印导弹状态链表
 */
void printDiscretePointList(const DiscretePointStateList* list) {
    printf("===== DiscretePoint State List [Count: %d] =====\n", list->count);
    DiscretePointNode* current = list->head;
    while (current != NULL) {
        printf("[%.2fms] Event: %u\n", current->data.time, current->data.event);
        printf("  Position: (%.6f°, %.6f°, %.2fm)\n",
               current->data.longitude,
               current->data.latitude,
               current->data.altitude);
        printf("  Velocity: (%.2f, %.2f, %.2f) m/s\n",
               current->data.velocityX,
               current->data.velocityY,
               current->data.velocityZ);
        printf("  Angles: Yaw=%.2f°, Pitch=%.2f°, Roll=%.2f°\n",
               current->data.yawAngle,
               current->data.pitchAngle,
               current->data.rollAngle);
        printf("----------------------------------------\n");
        current = current->next;
    }
}

/**
 * @brief 根据时间查找导弹状态节点
 * @return 找到返回节点指针，未找到返回NULL
 */
DiscretePointNode* findDiscretePointByTime(const DiscretePointStateList* list, double time) {
    DiscretePointNode* current = list->head;
    while (current != NULL) {
        if (current->data.time == time) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

/**
 * @brief 根据时间删除导弹状态节点
 */
void deleteDiscretePointByTime(DiscretePointStateList* list, double time) {
    DiscretePointNode *current = list->head, *prev = NULL;
    
    while (current != NULL) {
        if (current->data.time == time) {
            if (prev == NULL) {
                /* 删除头节点 */
                list->head = current->next;
                if (list->tail == current) {
                    list->tail = NULL;
                }
            } else {
                prev->next = current->next;
                if (current == list->tail) {
                    list->tail = prev;
                }
            }
            free(current);
            list->count--;
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("No discretePoint data found at time %.2fms\n", time);
}

/**
 * @brief 清空导弹状态链表
 */
void clearDiscretePointList(DiscretePointStateList* list) {
    DiscretePointNode* current = list->head;
    while (current != NULL) {
        DiscretePointNode* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
}

DiscretePointStateList init(){
    DiscretePointStateList discretePointList;
    initDiscretePointList(&discretePointList);
    insertDiscretePointData(&discretePointList, 0, YJDH, 116.417403, 39.904203, 0.34, 2.03, 0.03, 0.56, 0.10, 75.10, 0.17, 0.03, 85.07, 15.10, 10.17, 3.20, 0.14, 0.01, 0.01, -188.49);
insertDiscretePointData(&discretePointList, 1000, YJDH, 116.417180, 39.906278, 0.51, 1.94, -0.43, 0.47, 15.55, 73.32, 1.93, 0.51, 84.91, 14.77, 9.87, 2.74, -3.19, -6.57, -20.91, -186.18);
insertDiscretePointData(&discretePointList, 2000, YJDH, 116.416533, 39.908265, 2.06, 1.80, -0.84, 0.46, 30.43, 68.44, 3.87, 1.01, 84.82, 14.19, 9.65, 2.15, -6.28, -13.07, -40.90, -179.27);
insertDiscretePointData(&discretePointList, 3000, YJDH, 116.415486, 39.910074, 4.54, 1.58, -1.21, 0.44, 43.97, 60.56, 5.81, 1.51, 84.68, 13.25, 9.32, 1.24, -9.23, -19.42, -59.10, -167.95);
insertDiscretePointData(&discretePointList, 4000, YJDH, 116.414096, 39.911636, 8.86, 1.39, -1.44, 0.63, 55.89, 50.33, 8.25, 2.08, 84.70, 12.28, 9.38, 0.65, -11.56, -25.55, -74.69, -152.49);
insertDiscretePointData(&discretePointList, 5000, YJFL, 116.412399, 39.912859, 12.44, 4.27, 2.44, -6.76, 43.27, 24.96, 6.61, 2.49, 84.35, 10.57, 8.60, -1.07, -14.19, -31.42, -87.07, -133.29);
insertDiscretePointData(&discretePointList, 6000, YJFL, 116.410488, 39.913708, 17.11, 4.63, 1.42, -6.19, 47.48, 15.38, 7.88, 2.91, 84.02, 8.74, 7.97, -2.67, -16.28, -36.94, -95.62, -110.80);
insertDiscretePointData(&discretePointList, 7000, YJFL, 116.408447, 39.914147, 22.75, 5.04, 0.59, -5.22, 49.77, 5.27, 9.40, 3.36, 83.71, 6.85, 7.50, -4.08, -17.76, -42.04, -99.98, -85.57);
insertDiscretePointData(&discretePointList, 8000, YJFL, 116.406350, 39.914140, 27.68, 4.73, -0.76, -5.05, 49.58, -5.37, 10.43, 3.67, 83.11, 4.49, 6.45, -6.13, -19.21, -46.70, -99.99, -58.25);
insertDiscretePointData(&discretePointList, 9000, YJFL, 116.404309, 39.913710, 33.79, 4.70, -1.60, -4.08, 47.52, -15.48, 11.95, 4.03, 82.63, 2.32, 5.83, -7.54, -19.80, -50.83, -95.61, -29.49);
insertDiscretePointData(&discretePointList, 10000, YJFL, 116.402398, 39.912858, 39.53, 4.22, -2.61, -3.51, 43.23, -25.07, 13.22, 4.31, 81.97, -0.07, 4.89, -9.13, -20.09, -54.42, -87.07, -0.00);
insertDiscretePointData(&discretePointList, 11000, YJFL, 116.400705, 39.911628, 45.39, 3.54, -3.52, -2.94, 37.05, -33.56, 14.50, 4.53, 81.22, -2.45, 3.90, -10.56, -19.89, -57.41, -74.72, 29.48);
insertDiscretePointData(&discretePointList, 12000, YJFL, 116.399305, 39.910073, 51.48, 2.71, -4.28, -2.37, 29.25, -40.59, 15.77, 4.71, 80.42, -4.77, 2.86, -11.75, -19.21, -59.77, -59.10, 58.24);
insertDiscretePointData(&discretePointList, 13000, YJFL, 116.398264, 39.908267, 58.50, 1.99, -4.61, -1.40, 20.31, -45.70, 17.29, 4.88, 79.66, -6.83, 2.04, -12.36, -17.85, -61.46, -40.89, 85.57);
insertDiscretePointData(&discretePointList, 14000, YJFL, 116.397621, 39.906282, 66.21, 1.19, -4.74, -0.43, 10.48, -48.82, 18.82, 5.00, 78.86, -8.73, 1.19, -12.65, -16.06, -62.48, -20.89, 110.80);
insertDiscretePointData(&discretePointList, 15000, EJDH, 116.397402, 39.904202, 74.40, -1.98, 0.02, 0.69, 0.05, -74.95, 30.09, 5.02, 77.95, -10.55, 0.09, -12.89, -14.07, -62.83, 0.01, 133.29);
insertDiscretePointData(&discretePointList, 16000, EJDH, 116.397619, 39.902121, 83.87, -1.95, 0.42, 0.68, -15.58, -73.34, 32.03, 4.98, 77.04, -12.12, -1.02, -12.79, -11.73, -62.49, 20.90, 152.50);
insertDiscretePointData(&discretePointList, 17000, EJDH, 116.398264, 39.900132, 94.89, -1.83, 0.81, 0.67, -30.52, -68.53, 33.97, 4.88, 76.15, -13.38, -2.11, -12.35, -9.10, -61.46, 40.89, 167.95);
insertDiscretePointData(&discretePointList, 18000, EJDH, 116.399308, 39.898320, 107.59, -1.64, 1.16, 0.66, -44.14, -60.73, 35.91, 4.74, 75.29, -14.32, -3.18, -11.58, -6.26, -59.76, 59.09, 179.27);
insertDiscretePointData(&discretePointList, 19000, EJDH, 116.400711, 39.896771, 122.50, -1.32, 1.51, 0.75, -55.68, -50.13, 38.10, 4.59, 74.58, -14.76, -3.97, -10.24, -3.05, -57.40, 74.71, 186.18);
insertDiscretePointData(&discretePointList, 20000, EJDH, 116.402396, 39.895536, 137.99, -1.04, 1.69, 0.65, -65.08, -37.63, 39.79, 4.29, 73.74, -15.13, -5.21, -9.25, -0.17, -54.42, 87.05, 188.49);
insertDiscretePointData(&discretePointList, 21000, EJDH, 116.404314, 39.894694, 156.25, -0.57, 1.95, 0.84, -71.19, -23.04, 42.23, 4.09, 73.27, -14.68, -5.65, -7.20, 3.31, -50.82, 95.62, 186.18);
insertDiscretePointData(&discretePointList, 22000, EJDH, 116.406358, 39.894258, 174.31, -0.18, 2.02, 0.84, -74.49, -7.74, 44.17, 3.75, 72.69, -14.16, -6.52, -5.63, 6.32, -46.69, 99.99, 179.27);
insertDiscretePointData(&discretePointList, 23000, EJDH, 116.408442, 39.894252, 192.12, 0.18, 1.96, 0.73, -74.68, 7.75, 45.86, 3.32, 72.09, -13.45, -7.57, -4.34, 8.97, -42.05, 99.97, 167.95);
insertDiscretePointData(&discretePointList, 24000, EJDH, 116.410486, 39.894685, 210.05, 0.58, 1.86, 0.73, -71.45, 23.05, 47.80, 2.90, 71.68, -12.26, -8.29, -2.77, 11.59, -36.94, 95.60, 152.49);
insertDiscretePointData(&discretePointList, 25000, EJFL, 116.412400, 39.895540, 227.49, -4.34, 2.49, 6.65, -43.31, 24.99, 33.32, 2.50, 71.46, -10.61, -8.67, -1.01, 14.13, -31.42, 87.06, 133.29);
insertDiscretePointData(&discretePointList, 26000, EJFL, 116.414090, 39.896767, 242.92, -3.79, 3.27, 7.21, -37.20, 33.41, 34.59, 2.02, 71.21, -8.86, -9.21, 0.26, 16.12, -25.56, 74.70, 110.79);
insertDiscretePointData(&discretePointList, 27000, EJFL, 116.415488, 39.898319, 256.52, -3.07, 3.91, 7.79, -29.47, 40.37, 35.87, 1.52, 71.02, -6.89, -9.64, 1.31, 17.71, -19.42, 59.08, 85.57);
insertDiscretePointData(&discretePointList, 28000, EJFL, 116.416537, 39.900134, 268.66, -1.98, 4.62, 8.76, -20.30, 45.71, 37.39, 1.05, 70.99, -4.60, -9.72, 2.38, 19.07, -13.06, 40.89, 58.25);
insertDiscretePointData(&discretePointList, 29000, EJFL, 116.417181, 39.902121, 278.52, -1.04, 4.89, 9.33, -10.40, 48.91, 38.66, 0.52, 70.89, -2.35, -9.95, 2.82, 19.75, -6.57, 20.90, 29.49);
insertDiscretePointData(&discretePointList, 30000, EJFL, 116.417404, 39.904204, 287.55, 0.19, 5.19, 10.30, 0.11, 50.11, 40.19, 0.04, 70.91, 0.11, -9.81, 3.22, 20.15, 0.01, 0.01, 0.00);
insertDiscretePointData(&discretePointList, 31000, EJFL, 116.417184, 39.906282, 295.47, 1.16, 5.01, 10.86, 10.47, 48.98, 41.46, -0.50, 70.83, 2.42, -9.82, 2.97, 19.85, 6.57, -20.89, -29.48);
insertDiscretePointData(&discretePointList, 32000, EJFL, 116.416537, 39.908269, 303.72, 2.10, 4.63, 11.44, 20.38, 45.72, 42.73, -1.03, 70.73, 4.67, -9.72, 2.39, 19.07, 13.07, -40.89, -58.25);
insertDiscretePointData(&discretePointList, 33000, EJFL, 116.415485, 39.910073, 312.85, 2.69, 3.80, 11.61, 29.24, 40.30, 43.75, -1.59, 70.49, 6.66, -9.76, 1.18, 17.62, 19.41, -59.11, -85.58);
insertDiscretePointData(&discretePointList, 34000, EJFL, 116.414090, 39.911630, 325.42, 3.66, 3.29, 12.58, 37.13, 33.42, 45.28, -2.04, 70.41, 8.78, -9.19, 0.29, 16.14, 25.55, -74.71, -110.80);
insertDiscretePointData(&discretePointList, 35000, EJFL, 116.412403, 39.912863, 341.38, 4.47, 2.64, 13.55, 43.38, 25.08, 46.80, -2.47, 70.26, 10.69, -8.52, -0.84, 14.25, 31.42, -87.05, -133.28);
insertDiscretePointData(&discretePointList, 36000, EJFL, 116.410487, 39.913707, 360.45, 4.58, 1.37, 13.72, 47.45, 15.35, 47.82, -2.97, 69.83, 12.03, -8.27, -2.74, 11.61, 36.92, -95.62, -152.50);
insertDiscretePointData(&discretePointList, 37000, EJFL, 116.408441, 39.914141, 384.52, 4.74, 0.29, 14.29, 49.58, 5.08, 49.10, -3.39, 69.42, 13.22, -7.67, -4.45, 8.89, 42.03, -99.99, -167.96);
insertDiscretePointData(&discretePointList, 38000, EJFL, 116.406359, 39.914149, 414.06, 5.18, -0.32, 15.66, 49.85, -5.10, 50.87, -3.67, 69.13, 14.39, -6.49, -5.59, 6.34, 46.70, -99.97, -179.27);
insertDiscretePointData(&discretePointList, 39000, EJFL, 116.404313, 39.913713, 446.57, 4.90, -1.40, 16.23, 47.64, -15.36, 52.14, -4.02, 68.54, 14.90, -5.73, -7.30, 3.24, 50.84, -95.60, -186.17);
insertDiscretePointData(&discretePointList, 40000, EJFL, 116.402402, 39.912862, 482.15, 4.41, -2.42, 16.80, 43.35, -24.95, 53.42, -4.31, 67.88, 15.05, -4.92, -8.90, 0.07, 54.42, -87.06, -188.49);
insertDiscretePointData(&discretePointList, 41000, EJFL, 116.400704, 39.911627, 519.01, 3.49, -3.57, 16.97, 37.02, -33.59, 54.44, -4.61, 67.03, 14.68, -4.29, -10.62, -3.31, 57.39, -74.72, -186.18);
insertDiscretePointData(&discretePointList, 42000, EJFL, 116.399309, 39.910077, 557.09, 2.91, -4.08, 17.95, 29.37, -40.47, 55.97, -4.76, 66.33, 14.25, -3.12, -11.51, -6.21, 59.76, -59.09, -179.27);
insertDiscretePointData(&discretePointList, 43000, EJFL, 116.398263, 39.908265, 593.22, 1.94, -4.66, 18.51, 20.28, -45.74, 57.24, -4.91, 65.47, 13.31, -2.18, -12.42, -9.16, 61.45, -40.90, -167.95);
insertDiscretePointData(&discretePointList, 44000, EJFL, 116.397615, 39.906276, 626.30, 0.88, -5.05, 19.08, 10.30, -49.00, 58.51, -5.00, 64.58, 12.04, -1.20, -13.01, -11.88, 62.48, -20.91, -152.50);
insertDiscretePointData(&discretePointList, 45000, EJFL, 116.397396, 39.904196, 654.96, -0.22, -5.22, 19.65, -0.13, -50.13, 59.78, -5.04, 63.66, 10.48, -0.22, -13.26, -14.31, 62.82, -0.01, -133.29);
insertDiscretePointData(&discretePointList, 46000, EJFL, 116.397618, 39.902120, 678.76, -1.07, -4.92, 20.62, -10.41, -48.92, 61.31, -4.98, 62.85, 8.80, 1.02, -12.86, -16.20, 62.49, 20.90, -110.80);
insertDiscretePointData(&discretePointList, 47000, EJFL, 116.398263, 39.900131, 696.28, -2.12, -4.65, 21.19, -20.39, -45.73, 62.58, -4.91, 61.96, 6.76, 1.99, -12.41, -17.89, 61.46, 40.88, -85.58);
insertDiscretePointData(&discretePointList, 48000, EJFL, 116.399307, 39.898319, 708.26, -3.08, -4.19, 21.77, -29.48, -40.54, 63.86, -4.78, 61.10, 4.55, 2.95, -11.65, -19.14, 59.75, 59.08, -58.25);
insertDiscretePointData(&discretePointList, 49000, EJFL, 116.400705, 39.896764, 715.56, -3.92, -3.55, 22.34, -37.28, -33.58, 65.13, -4.61, 60.29, 2.22, 3.86, -10.60, -19.92, 57.39, 74.70, -29.49);
insertDiscretePointData(&discretePointList, 50000, EJFL, 116.402405, 39.895544, 720.70, -4.10, -2.27, 23.71, -43.16, -24.86, 66.90, -4.28, 59.75, 0.14, 5.23, -8.72, -19.81, 54.42, 87.08, 0.00);
insertDiscretePointData(&discretePointList, 51000, EJFL, 116.404313, 39.894693, 723.65, -4.58, -1.37, 24.28, -47.45, -15.35, 68.17, -4.01, 59.08, -2.24, 6.05, -7.26, -19.62, 50.84, 95.62, 29.49);
insertDiscretePointData(&discretePointList, 52000, EJFL, 116.406357, 39.894257, 727.71, -4.86, -0.41, 24.85, -49.66, -5.16, 69.44, -3.69, 58.50, -4.57, 6.80, -5.70, -18.93, 46.70, 99.99, 58.25);
insertDiscretePointData(&discretePointList, 53000, EJFL, 116.408441, 39.894251, 734.77, -5.17, 0.33, 25.02, -49.84, 5.11, 70.47, -3.39, 57.90, -6.93, 7.23, -4.40, -17.98, 42.03, 99.97, 85.57);
insertDiscretePointData(&discretePointList, 54000, EJFL, 116.410490, 39.894689, 748.56, -4.76, 1.54, 25.99, -47.56, 15.45, 71.99, -2.94, 57.60, -8.82, 8.08, -2.54, -16.19, 36.93, 95.61, 110.79);
insertDiscretePointData(&discretePointList, 55000, EJFL, 116.412404, 39.895543, 769.89, -4.15, 2.68, 26.96, -43.19, 25.11, 73.52, -2.46, 57.37, -10.50, 8.84, -0.78, -14.00, 31.42, 87.07, 133.29);
insertDiscretePointData(&discretePointList, 56000, EJFL, 116.414089, 39.896766, 798.96, -3.84, 3.22, 27.13, -37.23, 33.38, 74.54, -2.06, 57.02, -12.21, 9.01, 0.20, -11.86, 25.55, 74.70, 152.49);
insertDiscretePointData(&discretePointList, 57000, EJFL, 116.415491, 39.898323, 838.16, -2.88, 4.11, 28.10, -29.35, 40.49, 76.06, -1.53, 56.93, -13.33, 9.57, 1.54, -9.03, 19.42, 59.09, 167.95);
insertDiscretePointData(&discretePointList, 58000, EJFL, 116.416536, 39.900133, 885.51, -2.03, 4.57, 28.67, -20.34, 45.68, 77.34, -1.04, 56.80, -14.26, 9.78, 2.31, -6.18, 13.06, 40.89, 179.27);
insertDiscretePointData(&discretePointList, 59000, EJFL, 116.417180, 39.902120, 940.10, -1.10, 4.83, 29.24, -10.43, 48.87, 78.61, -0.53, 56.70, -14.85, 9.89, 2.75, -3.18, 6.57, 20.90, 186.17);
insertDiscretePointData(&discretePointList, 60000, DYZK, 116.417403, 39.904203, 1000.26, 2.03, 0.03, 30.05, 0.08, 50.08, 80.13, 0.03, 56.72, -14.92, 10.13, 3.16, 0.10, 0.01, 0.01, 188.50);
insertDiscretePointData(&discretePointList, 61000, DYZK, 116.440315, 39.916680, 10005.34, -0.01, 0.31, -0.04, 200.91, 165.04, 9.82, 1.28, 5.03, 2.25, 6.04, -0.01, 10.44, -0.31, -0.44, -1.07);
insertDiscretePointData(&discretePointList, 62000, DYZK, 116.442398, 39.928704, 10010.41, -0.04, 0.30, -0.08, 201.68, 164.89, 9.14, 2.50, 4.97, 4.34, 5.88, -0.18, 10.06, -0.62, -0.45, -2.12);
insertDiscretePointData(&discretePointList, 63000, DYZK, 116.443693, 39.939843, 10015.77, -0.04, 0.31, -0.11, 202.71, 164.93, 8.21, 3.79, 5.03, 6.55, 5.91, -0.04, 9.66, -0.92, -0.43, -3.13);
insertDiscretePointData(&discretePointList, 64000, DYZK, 116.444247, 39.949693, 10020.56, -0.07, 0.30, -0.14, 203.47, 164.67, 6.77, 4.94, 4.93, 8.41, 5.62, -0.21, 8.86, -1.21, -0.43, -4.06);
insertDiscretePointData(&discretePointList, 65000, DYZK, 116.444142, 39.957920, 10025.13, -0.10, 0.29, -0.17, 204.24, 164.35, 5.05, 6.03, 4.80, 10.10, 5.28, -0.37, 7.87, -1.50, -0.42, -4.92);
insertDiscretePointData(&discretePointList, 66000, DYZK, 116.443470, 39.964248, 10029.02, -0.15, 0.26, -0.20, 204.74, 163.72, 2.95, 6.96, 4.51, 11.37, 4.62, -0.83, 6.51, -1.77, -0.43, -5.67);
insertDiscretePointData(&discretePointList, 67000, DYZK, 116.442358, 39.968509, 10033.39, -0.15, 0.27, -0.20, 205.74, 163.53, 1.02, 8.01, 4.50, 12.80, 4.42, -0.69, 5.41, -2.01, -0.41, -6.29);
insertDiscretePointData(&discretePointList, 68000, DYZK, 116.440915, 39.970591, 10037.00, -0.17, 0.25, -0.20, 206.48, 163.05, -1.10, 8.88, 4.32, 13.75, 3.92, -0.84, 3.99, -2.23, -0.40, -6.78);
insertDiscretePointData(&discretePointList, 69000, DYZK, 116.439286, 39.970505, 10040.59, -0.18, 0.26, -0.18, 207.45, 162.75, -3.04, 9.74, 4.28, 14.60, 3.62, -0.70, 2.68, -2.42, -0.37, -7.12);
insertDiscretePointData(&discretePointList, 70000, DYZK, 116.437593, 39.968330, 10042.95, -0.23, 0.22, -0.19, 207.92, 161.92, -5.13, 10.30, 3.91, 14.74, 2.78, -1.14, 0.92, -2.61, -0.38, -7.31);
insertDiscretePointData(&discretePointList, 71000, DYZK, 116.436003, 39.964278, 10046.03, -0.20, 0.25, -0.14, 209.11, 161.78, -6.56, 11.05, 3.98, 15.16, 2.66, -0.69, -0.26, -2.73, -0.33, -7.34);
insertDiscretePointData(&discretePointList, 72000, DYZK, 116.434625, 39.958587, 10047.41, -0.25, 0.21, -0.12, 209.54, 160.84, -8.14, 11.38, 3.59, 14.66, 1.76, -1.14, -2.04, -2.86, -0.33, -7.22);
insertDiscretePointData(&discretePointList, 73000, DYZK, 116.433609, 39.951617, 10048.67, -0.27, 0.19, -0.09, 210.21, 160.12, -9.22, 11.68, 3.33, 14.05, 1.10, -1.27, -3.57, -2.94, -0.32, -6.94);
insertDiscretePointData(&discretePointList, 74000, DYZK, 116.433078, 39.943763, 10049.79, -0.27, 0.20, -0.04, 211.11, 159.60, -9.76, 11.95, 3.21, 13.32, 0.67, -1.11, -4.83, -2.98, -0.28, -6.51);
insertDiscretePointData(&discretePointList, 75000, DYZK, 116.433129, 39.935450, 10049.96, -0.30, 0.17, -0.00, 211.73, 158.79, -10.01, 11.99, 2.93, 12.12, -0.02, -1.24, -6.19, -3.00, -0.27, -5.95);
insertDiscretePointData(&discretePointList, 76000, DYZK, 116.433860, 39.927136, 10049.60, -0.32, 0.15, 0.04, 212.34, 157.96, -9.83, 11.90, 2.63, 10.65, -0.71, -1.36, -7.41, -2.99, -0.25, -5.25);
insertDiscretePointData(&discretePointList, 77000, DYZK, 116.435349, 39.919282, 10049.08, -0.32, 0.16, 0.09, 213.18, 157.34, -9.07, 11.78, 2.47, 9.16, -1.14, -1.18, -8.28, -2.93, -0.21, -4.44);
insertDiscretePointData(&discretePointList, 78000, DYZK, 116.437633, 39.912307, 10047.23, -0.36, 0.11, 0.11, 213.49, 156.19, -8.21, 11.33, 2.01, 7.07, -2.06, -1.60, -9.36, -2.86, -0.20, -3.54);
insertDiscretePointData(&discretePointList, 79000, DYZK, 116.440764, 39.906631, 10046.06, -0.33, 0.13, 0.16, 214.53, 155.76, -6.55, 11.06, 1.98, 5.42, -2.20, -1.11, -9.65, -2.73, -0.15, -2.56);
insertDiscretePointData(&discretePointList, 80000, DYZK, 116.444721, 39.902564, 10043.19, -0.38, 0.09, 0.17, 214.79, 154.56, -5.04, 10.36, 1.50, 3.06, -3.07, -1.51, -10.33, -2.60, -0.14, -1.53);
insertDiscretePointData(&discretePointList, 81000, DYZK, 116.449504, 39.900395, 10040.24, -0.40, 0.06, 0.18, 215.28, 153.60, -3.17, 9.66, 1.17, 0.84, -3.66, -1.61, -10.58, -2.43, -0.12, -0.46);
insertDiscretePointData(&discretePointList, 82000, DYZK, 116.455074, 39.900308, 10037.25, -0.39, 0.06, 0.20, 215.99, 152.87, -1.01, 8.94, 0.97, -1.21, -3.96, -1.40, -10.42, -2.23, -0.08, 0.62);
insertDiscretePointData(&discretePointList, 83000, DYZK, 116.461362, 39.902396, 10033.85, -0.39, 0.06, 0.21, 216.67, 152.13, 1.19, 8.13, 0.77, -3.23, -4.21, -1.19, -10.02, -2.00, -0.04, 1.68);
insertDiscretePointData(&discretePointList, 84000, DYZK, 116.468281, 39.906651, 10029.69, -0.40, 0.04, 0.20, 217.07, 151.13, 3.20, 7.13, 0.43, -5.37, -4.67, -1.27, -9.61, -1.76, -0.02, 2.71);
insertDiscretePointData(&discretePointList, 85000, DYZK, 116.475731, 39.912980, 10024.81, -0.45, -0.01, 0.17, 217.20, 149.88, 4.93, 5.95, -0.07, -7.60, -5.32, -1.65, -9.19, -1.50, -0.01, 3.67);
insertDiscretePointData(&discretePointList, 86000, DYZK, 116.483611, 39.921211, 10020.44, -0.44, -0.01, 0.15, 217.79, 149.13, 6.73, 4.91, -0.27, -9.26, -5.41, -1.42, -8.18, -1.22, 0.03, 4.57);
insertDiscretePointData(&discretePointList, 87000, DYZK, 116.491774, 39.931056, 10015.06, -0.48, -0.06, 0.10, 217.85, 147.87, 7.94, 3.61, -0.77, -11.13, -5.95, -1.78, -7.38, -0.94, 0.04, 5.35);
insertDiscretePointData(&discretePointList, 88000, DYZK, 116.500109, 39.942200, 10010.71, -0.44, -0.04, 0.09, 218.63, 147.39, 9.25, 2.57, -0.82, -12.16, -5.67, -1.24, -5.84, -0.62, 0.10, 6.04);
insertDiscretePointData(&discretePointList, 89000, DYZK, 116.508447, 39.954219, 10005.04, -0.48, -0.09, 0.03, 218.63, 146.15, 9.71, 1.21, -1.31, -13.53, -6.08, -1.59, -4.76, -0.32, 0.10, 6.58);
insertDiscretePointData(&discretePointList, 90000, DYZK, 116.516672, 39.966702, 10000.12, -0.47, -0.08, 0.00, 219.10, 145.44, 10.05, 0.03, -1.50, -14.20, -5.92, -1.33, -3.18, 0.00, 0.14, 6.99);
insertDiscretePointData(&discretePointList, 91000, DYZK, 116.524628, 39.979174, 9994.40, -0.50, -0.13, -0.06, 219.03, 144.24, 9.64, -1.35, -1.98, -14.98, -6.20, -1.67, -1.94, 0.30, 0.15, 7.24);
insertDiscretePointData(&discretePointList, 92000, DYZK, 116.532209, 39.991208, 9989.93, -0.47, -0.11, -0.07, 219.68, 143.82, 9.26, -2.41, -2.01, -14.83, -5.66, -1.11, -0.05, 0.63, 0.20, 7.35);
insertDiscretePointData(&discretePointList, 93000, DYZK, 116.539267, 40.002337, 9984.38, -0.50, -0.15, -0.12, 219.54, 142.67, 8.03, -3.75, -2.47, -14.96, -5.81, -1.44, 1.23, 0.92, 0.21, 7.29);
insertDiscretePointData(&discretePointList, 94000, DYZK, 116.545718, 40.012187, 9979.40, -0.51, -0.18, -0.16, 219.62, 141.80, 6.59, -4.95, -2.78, -14.58, -5.64, -1.46, 2.69, 1.21, 0.23, 7.08);
insertDiscretePointData(&discretePointList, 95000, DYZK, 116.551474, 40.020418, 9975.04, -0.49, -0.17, -0.17, 219.92, 141.21, 5.02, -5.99, -2.92, -13.68, -5.17, -1.18, 4.29, 1.50, 0.27, 6.72);
insertDiscretePointData(&discretePointList, 96000, DYZK, 116.556457, 40.026752, 9970.56, -0.50, -0.19, -0.19, 219.93, 140.41, 3.07, -7.07, -3.21, -12.69, -4.89, -1.20, 5.60, 1.76, 0.28, 6.21);
insertDiscretePointData(&discretePointList, 97000, DYZK, 116.560631, 40.031013, 9966.79, -0.48, -0.19, -0.19, 220.15, 139.89, 1.14, -7.97, -3.33, -11.23, -4.30, -0.91, 6.99, 2.01, 0.32, 5.57);
insertDiscretePointData(&discretePointList, 98000, DYZK, 116.563963, 40.033095, 9963.00, -0.49, -0.21, -0.19, 220.09, 139.16, -0.99, -8.88, -3.59, -9.72, -3.92, -0.91, 8.03, 2.23, 0.33, 4.80);
insertDiscretePointData(&discretePointList, 99000, DYZK, 116.566453, 40.032999, 9959.20, -0.52, -0.25, -0.20, 219.74, 138.23, -3.22, -9.79, -3.98, -8.21, -3.74, -1.22, 8.69, 2.42, 0.33, 3.93);
insertDiscretePointData(&discretePointList, 100000, DYZK, 116.568139, 40.030834, 9956.66, -0.50, -0.25, -0.17, 219.87, 137.84, -5.02, -10.40, -4.06, -6.12, -3.03, -0.91, 9.57, 2.60, 0.36, 2.99);
insertDiscretePointData(&discretePointList, 101000, DYZK, 116.569058, 40.026777, 9954.59, -0.48, -0.24, -0.14, 219.95, 137.50, -6.59, -10.90, -4.12, -3.90, -2.28, -0.61, 10.24, 2.75, 0.39, 1.98);
insertDiscretePointData(&discretePointList, 102000, DYZK, 116.569271, 40.021091, 9952.61, -0.48, -0.25, -0.11, 219.75, 136.96, -8.03, -11.37, -4.32, -1.80, -1.75, -0.60, 10.50, 2.86, 0.40, 0.92);
insertDiscretePointData(&discretePointList, 103000, DYZK, 116.568872, 40.014121, 9951.16, -0.48, -0.27, -0.08, 219.52, 136.47, -9.11, -11.72, -4.50, 0.35, -1.20, -0.59, 10.53, 2.94, 0.41, -0.15);
insertDiscretePointData(&discretePointList, 104000, DYZK, 116.567970, 40.006267, 9950.65, -0.46, -0.26, -0.03, 219.50, 136.29, -9.64, -11.84, -4.51, 2.69, -0.39, -0.27, 10.54, 2.99, 0.43, -1.22);
insertDiscretePointData(&discretePointList, 105000, DYZK, 116.566669, 39.997948, 9949.88, -0.48, -0.29, -0.00, 218.95, 135.66, -10.05, -12.03, -4.80, 4.57, -0.08, -0.55, 9.93, 3.00, 0.42, -2.27);
insertDiscretePointData(&discretePointList, 106000, DYZK, 116.565113, 39.989635, 9950.06, -0.48, -0.30, 0.03, 218.61, 135.34, -9.86, -11.99, -4.92, 6.56, 0.49, -0.54, 9.30, 2.98, 0.43, -3.27);
insertDiscretePointData(&discretePointList, 107000, DYZK, 116.563434, 39.981776, 9950.78, -0.48, -0.31, 0.07, 218.24, 135.07, -9.25, -11.82, -5.03, 8.40, 1.05, -0.52, 8.46, 2.93, 0.43, -4.20);
insertDiscretePointData(&discretePointList, 108000, DYZK, 116.561783, 39.974816, 9952.84, -0.43, -0.27, 0.13, 218.34, 135.36, -7.94, -11.32, -4.81, 10.46, 2.10, 0.10, 7.85, 2.86, 0.46, -5.03);
insertDiscretePointData(&discretePointList, 109000, DYZK, 116.560275, 39.969125, 9954.22, -0.45, -0.31, 0.14, 217.66, 134.96, -6.73, -10.99, -5.03, 11.70, 2.37, -0.17, 6.47, 2.74, 0.45, -5.76);
insertDiscretePointData(&discretePointList, 110000, DYZK, 116.559069, 39.965068, 9956.90, -0.42, -0.29, 0.18, 217.44, 135.12, -4.93, -10.34, -4.93, 13.09, 3.12, 0.15, 5.35, 2.60, 0.46, -6.36);
insertDiscretePointData(&discretePointList, 111000, DYZK, 116.558274, 39.962893, 9959.25, -0.44, -0.32, 0.18, 216.70, 134.84, -3.20, -9.78, -5.10, 13.80, 3.34, -0.13, 3.72, 2.42, 0.44, -6.84);
insertDiscretePointData(&discretePointList, 112000, DYZK, 116.558019, 39.962802, 9962.45, -0.44, -0.32, 0.18, 216.17, 134.87, -1.19, -9.02, -5.11, 14.41, 3.77, -0.11, 2.20, 2.22, 0.43, -7.16);
insertDiscretePointData(&discretePointList, 113000, DYZK, 116.558410, 39.964894, 9966.85, -0.38, -0.28, 0.21, 216.12, 135.46, 1.16, -7.95, -4.80, 15.10, 4.65, 0.51, 1.03, 2.02, 0.45, -7.32);
insertDiscretePointData(&discretePointList, 114000, DYZK, 116.559509, 39.969150, 9970.83, -0.37, -0.28, 0.20, 215.54, 135.61, 3.17, -7.00, -4.76, 15.08, 4.99, 0.53, -0.55, 1.77, 0.44, -7.33);
insertDiscretePointData(&discretePointList, 115000, DYZK, 116.561385, 39.975479, 9974.72, -0.39, -0.30, 0.16, 214.69, 135.56, 4.89, -6.07, -4.86, 14.53, 5.02, 0.25, -2.33, 1.49, 0.42, -7.19);
insertDiscretePointData(&discretePointList, 116000, DYZK, 116.564093, 39.983710, 9979.68, -0.36, -0.28, 0.15, 214.30, 136.07, 6.70, -4.88, -4.64, 14.07, 5.49, 0.57, -3.65, 1.22, 0.42, -6.89);
insertDiscretePointData(&discretePointList, 117000, DYZK, 116.567636, 39.993560, 9984.47, -0.35, -0.28, 0.11, 213.64, 136.38, 8.06, -3.73, -4.55, 13.11, 5.66, 0.58, -5.10, 0.93, 0.40, -6.44);
insertDiscretePointData(&discretePointList, 118000, DYZK, 116.572012, 40.004694, 9989.43, -0.34, -0.27, 0.07, 212.96, 136.75, 9.07, -2.54, -4.45, 11.86, 5.76, 0.59, -6.43, 0.62, 0.39, -5.86);
insertDiscretePointData(&discretePointList, 119000, DYZK, 116.577192, 40.016718, 9994.51, -0.33, -0.27, 0.03, 212.26, 137.17, 9.68, -1.32, -4.32, 10.36, 5.80, 0.60, -7.64, 0.31, 0.37, -5.15);
insertDiscretePointData(&discretePointList, 120000, FDGR, 116.583125, 40.029195, 9999.64, -0.38, -0.31, -0.01, 253.88, 165.21, 11.86, -0.09, -4.18, 8.64, 5.77, 0.61, -8.68, -0.01, 0.35, -4.32);
insertDiscretePointData(&discretePointList, 121000, FDGR, 116.589748, 40.041683, 10005.56, -0.31, -0.26, -0.04, 253.49, 166.34, 11.86, 1.34, -3.73, 7.12, 6.18, 1.21, -9.14, -0.31, 0.36, -3.40);
insertDiscretePointData(&discretePointList, 122000, FDGR, 116.596948, 40.053707, 10010.64, -0.30, -0.25, -0.09, 252.58, 167.03, 11.05, 2.56, -3.55, 5.05, 6.02, 1.21, -9.79, -0.62, 0.34, -2.41);
insertDiscretePointData(&discretePointList, 123000, FDGR, 116.604623, 40.064836, 10015.20, -0.30, -0.26, -0.15, 251.40, 167.52, 9.61, 3.64, -3.52, 2.68, 5.55, 0.90, -10.44, -0.93, 0.30, -1.38);
insertDiscretePointData(&discretePointList, 124000, FDGR, 116.612666, 40.074691, 10020.38, -0.26, -0.23, -0.18, 250.70, 168.56, 8.05, 4.89, -3.17, 0.65, 5.51, 1.19, -10.47, -1.22, 0.29, -0.31);
insertDiscretePointData(&discretePointList, 125000, FDGR, 116.620930, 40.082917, 10024.95, -0.25, -0.21, -0.21, 249.73, 169.39, 5.98, 5.99, -2.96, -1.59, 5.17, 1.18, -10.47, -1.50, 0.26, 0.77);
insertDiscretePointData(&discretePointList, 126000, FDGR, 116.629282, 40.089251, 10029.25, -0.23, -0.20, -0.23, 248.75, 170.27, 3.65, 7.02, -2.73, -3.80, 4.76, 1.16, -10.24, -1.77, 0.24, 1.83);
insertDiscretePointData(&discretePointList, 127000, FDGR, 116.637581, 40.093506, 10033.21, -0.21, -0.19, -0.25, 247.74, 171.18, 1.16, 7.97, -2.50, -5.93, 4.31, 1.13, -9.80, -2.01, 0.21, 2.85);
insertDiscretePointData(&discretePointList, 128000, FDGR, 116.645688, 40.095589, 10036.82, -0.19, -0.17, -0.25, 246.73, 172.13, -1.38, 8.83, -2.25, -7.94, 3.81, 1.11, -9.15, -2.24, 0.18, 3.80);
insertDiscretePointData(&discretePointList, 129000, FDGR, 116.653474, 40.095502, 10040.42, -0.15, -0.13, -0.23, 245.95, 173.35, -3.72, 9.70, -1.85, -9.58, 3.51, 1.37, -8.11, -2.43, 0.16, 4.68);
insertDiscretePointData(&discretePointList, 130000, FDGR, 116.660811, 40.093338, 10043.58, -0.11, -0.09, -0.20, 245.16, 174.61, -5.90, 10.46, -1.44, -11.01, 3.17, 1.63, -6.89, -2.59, 0.15, 5.47);
insertDiscretePointData(&discretePointList, 131000, FDGR, 116.667580, 40.089276, 10045.85, -0.09, -0.08, -0.17, 244.11, 175.63, -7.96, 11.01, -1.18, -12.41, 2.55, 1.59, -5.72, -2.74, 0.12, 6.12);
insertDiscretePointData(&discretePointList, 132000, FDGR, 116.673690, 40.083590, 10047.63, -0.07, -0.06, -0.14, 243.06, 176.68, -9.68, 11.43, -0.91, -13.53, 1.90, 1.53, -4.43, -2.85, 0.09, 6.65);
insertDiscretePointData(&discretePointList, 133000, FDGR, 116.679064, 40.076620, 10048.90, -0.05, -0.05, -0.10, 242.00, 177.74, -10.97, 11.73, -0.63, -14.37, 1.24, 1.48, -3.04, -2.93, 0.06, 7.04);
insertDiscretePointData(&discretePointList, 134000, FDGR, 116.683650, 40.068766, 10050.01, -0.01, -0.00, -0.04, 241.19, 179.05, -11.63, 12.01, -0.21, -14.69, 0.81, 1.71, -1.39, -2.98, 0.04, 7.27);
insertDiscretePointData(&discretePointList, 135000, FDGR, 116.687397, 40.060447, 10049.79, -0.01, -0.01, -0.01, 239.87, 179.87, -12.08, 11.95, -0.08, -15.10, -0.13, 1.35, -0.10, -3.01, -0.01, 7.35);
insertDiscretePointData(&discretePointList, 136000, FDGR, 116.690314, 40.052139, 10049.83, 0.03, 0.03, 0.05, 239.06, 181.19, -11.70, 11.96, 0.35, -14.79, -0.56, 1.57, 1.58, -2.98, -0.02, 7.27);
insertDiscretePointData(&discretePointList, 137000, FDGR, 116.692398, 40.044280, 10048.91, 0.05, 0.05, 0.10, 237.99, 182.26, -10.96, 11.74, 0.63, -14.36, -1.25, 1.49, 3.03, -2.93, -0.06, 7.04);
insertDiscretePointData(&discretePointList, 138000, FDGR, 116.693693, 40.037315, 10047.86, 0.09, 0.09, 0.15, 237.18, 183.56, -9.59, 11.49, 1.05, -13.42, -1.66, 1.70, 4.62, -2.85, -0.07, 6.65);
insertDiscretePointData(&discretePointList, 139000, FDGR, 116.694247, 40.031629, 10045.89, 0.11, 0.10, 0.19, 236.13, 184.61, -7.95, 11.02, 1.32, -12.39, -2.31, 1.61, 5.92, -2.74, -0.10, 6.12);
insertDiscretePointData(&discretePointList, 140000, FDGR, 116.694142, 40.027567, 10043.42, 0.13, 0.12, 0.21, 235.08, 185.64, -5.96, 10.42, 1.59, -11.09, -2.93, 1.51, 7.08, -2.60, -0.13, 5.46);
insertDiscretePointData(&discretePointList, 141000, FDGR, 116.693470, 40.025392, 10040.07, 0.13, 0.11, 0.21, 233.79, 186.39, -3.85, 9.61, 1.70, -9.75, -3.77, 1.11, 7.90, -2.44, -0.18, 4.68);
insertDiscretePointData(&discretePointList, 142000, FDGR, 116.692358, 40.025306, 10037.08, 0.17, 0.15, 0.24, 233.01, 187.62, -1.28, 8.90, 2.10, -7.81, -4.06, 1.30, 8.94, -2.23, -0.19, 3.81);
insertDiscretePointData(&discretePointList, 143000, FDGR, 116.690920, 40.027393, 10033.68, 0.21, 0.19, 0.25, 232.25, 188.81, 1.34, 8.09, 2.49, -5.70, -4.32, 1.48, 9.79, -2.00, -0.21, 2.85);
insertDiscretePointData(&discretePointList, 144000, FDGR, 116.689280, 40.031644, 10029.12, 0.20, 0.18, 0.22, 230.99, 189.47, 3.61, 6.99, 2.58, -3.87, -5.02, 1.06, 10.03, -1.77, -0.25, 1.82);
insertDiscretePointData(&discretePointList, 145000, FDGR, 116.687598, 40.037982, 10025.03, 0.25, 0.21, 0.21, 230.26, 190.60, 6.01, 6.01, 2.95, -1.55, -5.18, 1.24, 10.46, -1.50, -0.26, 0.77);
insertDiscretePointData(&discretePointList, 146000, FDGR, 116.686003, 40.046214, 10020.67, 0.29, 0.25, 0.19, 229.54, 191.68, 8.15, 4.96, 3.31, 0.80, -5.27, 1.41, 10.66, -1.21, -0.27, -0.30);
insertDiscretePointData(&discretePointList, 147000, FDGR, 116.684625, 40.056059, 10015.29, 0.28, 0.24, 0.13, 228.34, 192.22, 9.65, 3.67, 3.36, 2.73, -5.81, 0.97, 10.23, -0.93, -0.31, -1.38);
insertDiscretePointData(&discretePointList, 148000, FDGR, 116.683614, 40.067198, 10010.54, 0.32, 0.27, 0.10, 227.65, 193.21, 11.01, 2.53, 3.70, 5.00, -5.78, 1.13, 9.99, -0.62, -0.32, -2.42);
insertDiscretePointData(&discretePointList, 149000, FDGR, 116.683077, 40.079222, 10005.27, 0.33, 0.28, 0.05, 226.75, 193.90, 11.76, 1.27, 3.87, 6.97, -5.94, 0.99, 9.33, -0.31, -0.34, -3.40);
insertDiscretePointData(&discretePointList, 150000, FDGR, 116.683129, 40.091699, 9999.95, 0.35, 0.29, -0.00, 225.86, 194.53, 11.98, -0.01, 4.03, 8.79, -6.03, 0.84, 8.47, -0.00, -0.37, -4.32);
insertDiscretePointData(&discretePointList, 151000, FDGR, 116.683865, 40.104182, 9995.02, 0.39, 0.32, -0.04, 225.25, 195.35, 11.83, -1.19, 4.32, 10.62, -5.81, 0.99, 7.63, 0.32, -0.37, -5.14);
insertDiscretePointData(&discretePointList, 152000, FDGR, 116.685349, 40.116205, 9989.76, 0.40, 0.33, -0.09, 224.42, 195.87, 11.02, -2.46, 4.44, 12.03, -5.77, 0.84, 6.43, 0.63, -0.39, -5.85);
insertDiscretePointData(&discretePointList, 153000, FDGR, 116.687637, 40.127340, 9984.61, 0.41, 0.33, -0.14, 223.61, 196.32, 9.73, -3.69, 4.55, 13.17, -5.67, 0.68, 5.09, 0.93, -0.40, -6.44);
insertDiscretePointData(&discretePointList, 154000, FDGR, 116.690759, 40.137190, 9979.63, 0.43, 0.33, -0.18, 222.83, 196.71, 8.02, -4.89, 4.64, 14.04, -5.50, 0.53, 3.64, 1.22, -0.42, -6.89);
insertDiscretePointData(&discretePointList, 155000, FDGR, 116.694721, 40.145416, 9974.86, 0.44, 0.33, -0.21, 222.08, 197.03, 5.95, -6.03, 4.70, 14.60, -5.28, 0.36, 2.12, 1.50, -0.43, -7.19);
insertDiscretePointData(&discretePointList, 156000, FDGR, 116.699504, 40.151750, 9970.38, 0.45, 0.33, -0.24, 221.36, 197.29, 3.62, -7.11, 4.76, 14.86, -5.00, 0.20, 0.54, 1.76, -0.44, -7.34);
insertDiscretePointData(&discretePointList, 157000, FDGR, 116.705068, 40.156005, 9966.22, 0.46, 0.33, -0.25, 220.68, 197.48, 1.13, -8.11, 4.79, 14.79, -4.66, 0.04, -1.04, 2.00, -0.45, -7.33);
insertDiscretePointData(&discretePointList, 158000, FDGR, 116.711362, 40.158097, 9963.22, 0.52, 0.38, -0.22, 220.53, 198.09, -1.11, -8.82, 5.10, 14.79, -3.78, 0.47, -2.21, 2.24, -0.43, -7.15);
insertDiscretePointData(&discretePointList, 159000, FDGR, 116.718276, 40.158001, 9959.44, 0.50, 0.35, -0.23, 219.67, 197.89, -3.75, -9.74, 4.95, 13.89, -3.60, 0.01, -3.92, 2.42, -0.45, -6.84);
insertDiscretePointData(&discretePointList, 160000, FDGR, 116.725731, 40.155832, 9956.49, 0.51, 0.35, -0.22, 219.08, 197.87, -6.08, -10.45, 4.92, 12.88, -3.13, -0.16, -5.36, 2.59, -0.46, -6.37);
insertDiscretePointData(&discretePointList, 161000, FDGR, 116.733606, 40.151770, 9954.01, 0.51, 0.34, -0.19, 218.54, 197.77, -8.15, -11.04, 4.87, 11.60, -2.63, -0.33, -6.68, 2.73, -0.46, -5.76);
insertDiscretePointData(&discretePointList, 162000, FDGR, 116.741774, 40.146084, 9952.05, 0.52, 0.33, -0.16, 218.03, 197.61, -9.86, -11.51, 4.81, 10.07, -2.10, -0.49, -7.85, 2.84, -0.46, -5.04);
insertDiscretePointData(&discretePointList, 163000, FDGR, 116.750109, 40.139124, 9951.39, 0.57, 0.37, -0.09, 218.06, 197.87, -10.85, -11.66, 5.02, 8.71, -1.06, -0.06, -8.47, 2.94, -0.43, -4.19);
insertDiscretePointData(&discretePointList, 164000, FDGR, 116.758447, 40.131260, 9950.08, 0.55, 0.34, -0.06, 217.38, 197.31, -11.81, -11.98, 4.77, 6.57, -0.75, -0.52, -9.50, 2.98, -0.44, -3.27);
insertDiscretePointData(&discretePointList, 165000, FDGR, 116.766672, 40.122951, 9950.11, 0.58, 0.35, 0.00, 217.24, 197.19, -11.96, -11.97, 4.79, 4.69, 0.07, -0.38, -9.93, 3.00, -0.42, -2.27);
insertDiscretePointData(&discretePointList, 166000, FDGR, 116.774627, 40.114633, 9949.89, 0.55, 0.31, 0.04, 216.64, 196.49, -11.88, -12.03, 4.50, 2.31, 0.38, -0.84, -10.55, 2.97, -0.43, -1.23);
insertDiscretePointData(&discretePointList, 167000, FDGR, 116.782209, 40.106784, 9951.41, 0.60, 0.35, 0.11, 216.83, 196.48, -10.84, -11.66, 4.64, 0.47, 1.44, -0.40, -10.34, 2.94, -0.40, -0.15);
insertDiscretePointData(&discretePointList, 168000, FDGR, 116.789267, 40.099808, 9952.27, 0.58, 0.30, 0.13, 216.31, 195.66, -9.78, -11.46, 4.31, -1.97, 1.74, -0.86, -10.51, 2.85, -0.40, 0.92);
insertDiscretePointData(&discretePointList, 169000, FDGR, 116.795723, 40.094128, 9954.45, 0.60, 0.31, 0.18, 216.33, 195.28, -7.98, -10.93, 4.27, -3.97, 2.52, -0.71, -10.05, 2.74, -0.38, 1.98);
insertDiscretePointData(&discretePointList, 170000, FDGR, 116.801473, 40.090066, 9956.73, 0.60, 0.29, 0.21, 216.15, 194.58, -5.99, -10.39, 4.06, -6.09, 3.02, -0.86, -9.58, 2.60, -0.36, 2.99);
insertDiscretePointData(&discretePointList, 171000, FDGR, 116.806462, 40.087901, 9959.88, 0.62, 0.30, 0.24, 216.25, 194.08, -3.58, -9.63, 3.98, -7.87, 3.73, -0.71, -8.70, 2.44, -0.33, 3.94);
insertDiscretePointData(&discretePointList, 172000, FDGR, 116.810631, 40.087810, 9963.07, 0.61, 0.28, 0.25, 216.15, 193.27, -1.17, -8.86, 3.73, -9.69, 4.16, -0.85, -7.83, 2.24, -0.32, 4.81);
insertDiscretePointData(&discretePointList, 173000, FDGR, 116.813958, 40.089887, 9966.28, 0.58, 0.23, 0.23, 215.84, 192.15, 1.15, -8.10, 3.32, -11.49, 4.29, -1.29, -6.99, 2.00, -0.32, 5.56);
insertDiscretePointData(&discretePointList, 174000, FDGR, 116.816458, 40.094148, 9970.65, 0.60, 0.23, 0.23, 216.07, 191.50, 3.72, -7.04, 3.20, -12.65, 4.88, -1.13, -5.61, 1.76, -0.29, 6.21);
insertDiscretePointData(&discretePointList, 175000, FDGR, 116.818139, 40.100481, 9974.94, 0.59, 0.21, 0.21, 216.09, 190.54, 5.98, -6.01, 2.92, -13.73, 5.16, -1.26, -4.30, 1.50, -0.27, 6.71);
insertDiscretePointData(&discretePointList, 176000, FDGR, 116.819052, 40.108708, 9979.51, 0.58, 0.18, 0.17, 216.16, 189.55, 7.97, -4.92, 2.62, -14.52, 5.39, -1.38, -2.90, 1.22, -0.25, 7.08);
insertDiscretePointData(&discretePointList, 177000, FDGR, 116.819271, 40.118563, 9984.70, 0.60, 0.18, 0.15, 216.52, 188.77, 9.76, -3.67, 2.47, -14.81, 5.80, -1.20, -1.24, 0.93, -0.21, 7.29);
insertDiscretePointData(&discretePointList, 178000, FDGR, 116.818872, 40.129697, 9989.65, 0.59, 0.16, 0.10, 216.67, 187.70, 10.98, -2.48, 2.15, -14.97, 5.90, -1.32, 0.24, 0.62, -0.19, 7.35);
insertDiscretePointData(&discretePointList, 179000, FDGR, 116.817965, 40.141721, 9994.73, 0.58, 0.13, 0.05, 216.86, 186.60, 11.72, -1.26, 1.82, -14.81, 5.94, -1.43, 1.73, 0.31, -0.17, 7.25);
insertDiscretePointData(&discretePointList, 180000, ZDJD, 116.821304, 40.154198, 9999.86, 0.47, 0.08, -0.01, 180.89, 154.55, 9.95, -0.03, 1.49, -14.33, 5.91, -1.53, 3.18, -0.00, -0.14, 6.99);
insertDiscretePointData(&discretePointList, 181000, ZDJD, 116.817309, 40.177077, 10005.39, 0.48, 0.08, -0.04, 181.36, 153.83, 9.84, 1.30, 1.31, -13.35, 6.07, -1.33, 4.75, -0.31, -0.11, 6.59);
insertDiscretePointData(&discretePointList, 182000, ZDJD, 116.813120, 40.199036, 10010.07, 0.44, 0.04, -0.09, 181.36, 152.61, 9.01, 2.41, 0.81, -12.48, 5.66, -1.72, 5.83, -0.63, -0.10, 6.03);
insertDiscretePointData(&discretePointList, 183000, ZDJD, 116.808972, 40.219233, 10015.82, 0.48, 0.06, -0.10, 182.14, 152.11, 8.23, 3.80, 0.77, -10.75, 5.94, -1.21, 7.37, -0.92, -0.04, 5.36);
insertDiscretePointData(&discretePointList, 184000, ZDJD, 116.805046, 40.236846, 10020.21, 0.44, 0.01, -0.15, 182.20, 150.87, 6.65, 4.85, 0.27, -9.38, 5.40, -1.59, 8.17, -1.22, -0.03, 4.56);
insertDiscretePointData(&discretePointList, 185000, ZDJD, 116.801564, 40.251216, 10024.78, 0.42, -0.01, -0.18, 182.54, 149.86, 4.92, 5.94, -0.08, -7.61, 5.06, -1.67, 8.98, -1.51, -0.01, 3.67);
insertDiscretePointData(&discretePointList, 186000, ZDJD, 116.798717, 40.261807, 10029.47, 0.43, -0.01, -0.19, 183.17, 149.11, 3.12, 7.07, -0.28, -5.48, 4.91, -1.43, 9.80, -1.76, 0.03, 2.71);
insertDiscretePointData(&discretePointList, 187000, ZDJD, 116.796673, 40.268240, 10033.84, 0.43, -0.01, -0.18, 183.82, 148.36, 1.19, 8.13, -0.48, -3.23, 4.70, -1.20, 10.42, -2.00, 0.07, 1.68);
insertDiscretePointData(&discretePointList, 188000, ZDJD, 116.795579, 40.270323, 10037.45, 0.42, -0.04, -0.19, 184.25, 147.37, -0.93, 8.99, -0.83, -1.11, 4.20, -1.25, 10.61, -2.22, 0.10, 0.62);
insertDiscretePointData(&discretePointList, 189000, ZDJD, 116.795558, 40.268053, 10040.25, 0.37, -0.09, -0.20, 184.46, 146.14, -3.17, 9.66, -1.32, 0.84, 3.40, -1.61, 10.38, -2.43, 0.10, -0.46);
insertDiscretePointData(&discretePointList, 190000, ZDJD, 116.796713, 40.261632, 10043.00, 0.35, -0.11, -0.18, 184.95, 145.18, -5.11, 10.32, -1.66, 2.97, 2.81, -1.65, 10.12, -2.61, 0.13, -1.53);
insertDiscretePointData(&discretePointList, 191000, ZDJD, 116.799101, 40.251426, 10045.28, 0.33, -0.14, -0.16, 185.46, 144.23, -6.84, 10.86, -1.99, 5.03, 2.19, -1.69, 9.64, -2.75, 0.15, -2.57);
insertDiscretePointData(&discretePointList, 192000, ZDJD, 116.802754, 40.237977, 10047.46, 0.34, -0.13, -0.12, 186.25, 143.56, -8.12, 11.39, -2.16, 7.18, 1.80, -1.43, 9.16, -2.86, 0.19, -3.54);
insertDiscretePointData(&discretePointList, 193000, ZDJD, 116.807652, 40.221955, 10048.72, 0.31, -0.16, -0.09, 186.81, 142.66, -9.21, 11.69, -2.48, 8.97, 1.13, -1.46, 8.27, -2.94, 0.21, -4.45);
insertDiscretePointData(&discretePointList, 194000, ZDJD, 116.813761, 40.204159, 10049.84, 0.32, -0.15, -0.04, 187.65, 142.03, -9.74, 11.96, -2.64, 10.77, 0.70, -1.18, 7.40, -2.98, 0.25, -5.25);
insertDiscretePointData(&discretePointList, 195000, ZDJD, 116.820995, 40.185450, 10050.02, 0.30, -0.18, 0.00, 188.26, 141.20, -9.99, 12.01, -2.93, 12.15, 0.01, -1.20, 6.18, -3.00, 0.27, -5.95);
insertDiscretePointData(&discretePointList, 196000, ZDJD, 116.829253, 40.166746, 10050.05, 0.30, -0.17, 0.05, 189.14, 140.64, -9.66, 12.02, -3.07, 13.46, -0.42, -0.91, 5.03, -2.98, 0.30, -6.51);
insertDiscretePointData(&discretePointList, 197000, ZDJD, 116.838387, 40.148946, 10049.13, 0.27, -0.19, 0.09, 189.78, 139.87, -9.05, 11.79, -3.34, 14.28, -1.11, -0.92, 3.57, -2.93, 0.32, -6.94);
insertDiscretePointData(&discretePointList, 198000, ZDJD, 116.848237, 40.132918, 10047.28, 0.22, -0.24, 0.11, 190.19, 138.90, -8.19, 11.34, -3.75, 14.60, -2.02, -1.23, 1.83, -2.86, 0.32, -7.22);
insertDiscretePointData(&discretePointList, 199000, ZDJD, 116.858632, 40.119469, 10045.71, 0.22, -0.23, 0.15, 191.13, 138.46, -6.68, 10.97, -3.84, 15.00, -2.42, -0.93, 0.45, -2.74, 0.35, -7.34);
insertDiscretePointData(&discretePointList, 200000, ZDJD, 116.869362, 40.109263, 10043.24, 0.20, -0.25, 0.17, 191.83, 137.83, -5.02, 10.38, -4.07, 14.89, -3.04, -0.93, -1.13, -2.60, 0.36, -7.31);
insertDiscretePointData(&discretePointList, 201000, ZDJD, 116.880224, 40.102842, 10040.29, 0.17, -0.26, 0.18, 192.54, 137.23, -3.15, 9.67, -4.28, 14.45, -3.63, -0.92, -2.69, -2.43, 0.37, -7.12);
insertDiscretePointData(&discretePointList, 202000, ZDJD, 116.891006, 40.100578, 10036.90, 0.15, -0.28, 0.19, 193.26, 136.70, -1.14, 8.85, -4.48, 13.70, -4.17, -0.91, -4.20, -2.24, 0.38, -6.78);
insertDiscretePointData(&discretePointList, 203000, ZDJD, 116.901500, 40.102660, 10033.10, 0.12, -0.29, 0.19, 194.00, 136.21, 0.91, 7.94, -4.66, 12.65, -4.68, -0.90, -5.62, -2.02, 0.39, -6.29);
insertDiscretePointData(&discretePointList, 204000, ZDJD, 116.911512, 40.109094, 10029.34, 0.12, -0.28, 0.19, 195.00, 136.02, 3.07, 7.04, -4.67, 11.53, -4.88, -0.59, -6.72, -1.76, 0.42, -5.66);
insertDiscretePointData(&discretePointList, 205000, ZDJD, 116.920842, 40.119679, 10024.86, 0.10, -0.29, 0.17, 195.75, 135.65, 4.95, 5.96, -4.81, 9.97, -5.28, -0.57, -7.87, -1.50, 0.42, -4.92);
insertDiscretePointData(&discretePointList, 206000, ZDJD, 116.929330, 40.134049, 10020.10, 0.07, -0.31, 0.14, 196.51, 135.32, 6.60, 4.82, -4.93, 8.18, -5.63, -0.55, -8.87, -1.23, 0.43, -4.07);
insertDiscretePointData(&discretePointList, 207000, ZDJD, 116.936830, 40.151667, 10015.11, 0.04, -0.32, 0.10, 197.28, 135.06, 7.96, 3.62, -5.04, 6.22, -5.92, -0.53, -9.67, -0.94, 0.43, -3.13);
insertDiscretePointData(&discretePointList, 208000, ZDJD, 116.943230, 40.171859, 10010.36, 0.04, -0.30, 0.08, 198.31, 135.10, 9.12, 2.49, -4.97, 4.32, -5.89, -0.21, -10.07, -0.62, 0.45, -2.12);
insertDiscretePointData(&discretePointList, 209000, ZDJD, 116.948435, 40.193824, 10005.10, 0.01, -0.31, 0.04, 199.08, 134.95, 9.73, 1.22, -5.04, 2.13, -6.05, -0.19, -10.45, -0.32, 0.44, -1.08);
insertDiscretePointData(&discretePointList, 210000, ZDJD, 116.952397, 40.216697, 9999.78, -0.01, -0.31, -0.01, 199.86, 134.86, 9.92, -0.06, -5.08, -0.11, -6.14, -0.17, -10.61, -0.01, 0.44, -0.00);
insertDiscretePointData(&discretePointList, 211000, ZDJD, 116.955099, 40.239570, 9994.45, -0.04, -0.32, -0.05, 200.64, 134.83, 9.66, -1.33, -5.11, -2.35, -6.17, -0.15, -10.55, 0.31, 0.44, 1.07);
insertDiscretePointData(&discretePointList, 212000, ZDJD, 116.956568, 40.261545, 9989.99, -0.02, -0.27, -0.07, 201.91, 135.36, 9.28, -2.40, -4.82, -4.14, -5.63, 0.47, -9.86, 0.63, 0.46, 2.13);
insertDiscretePointData(&discretePointList, 213000, ZDJD, 116.956832, 40.281727, 9984.43, -0.07, -0.30, -0.12, 202.43, 135.19, 8.05, -3.74, -4.95, -6.44, -5.78, 0.19, -9.56, 0.92, 0.44, 3.13);
insertDiscretePointData(&discretePointList, 214000, ZDJD, 116.956002, 40.299350, 9979.85, -0.07, -0.28, -0.14, 203.46, 135.59, 6.76, -4.83, -4.77, -8.21, -5.36, 0.52, -8.65, 1.22, 0.44, 4.07);
insertDiscretePointData(&discretePointList, 215000, ZDJD, 116.954179, 40.313720, 9975.09, -0.10, -0.28, -0.17, 204.22, 135.79, 5.03, -5.98, -4.72, -9.99, -5.14, 0.53, -7.76, 1.50, 0.43, 4.92);
insertDiscretePointData(&discretePointList, 216000, ZDJD, 116.951512, 40.324306, 9970.61, -0.12, -0.28, -0.19, 204.97, 136.05, 3.09, -7.05, -4.65, -11.56, -4.86, 0.55, -6.69, 1.76, 0.42, 5.66);
insertDiscretePointData(&discretePointList, 217000, ZDJD, 116.948175, 40.330739, 9966.85, -0.13, -0.25, -0.19, 205.97, 136.62, 1.16, -7.95, -4.41, -12.68, -4.27, 0.87, -5.29, 2.01, 0.42, 6.29);
insertDiscretePointData(&discretePointList, 218000, ZDJD, 116.944345, 40.332821, 9963.05, -0.15, -0.25, -0.19, 206.70, 136.98, -0.97, -8.87, -4.31, -13.73, -3.89, 0.88, -3.97, 2.23, 0.40, 6.78);
insertDiscretePointData(&discretePointList, 219000, ZDJD, 116.940222, 40.330552, 9959.26, -0.20, -0.27, -0.20, 207.18, 137.15, -3.20, -9.78, -4.33, -14.67, -3.71, 0.59, -2.76, 2.42, 0.37, 7.12);
insertDiscretePointData(&discretePointList, 220000, ZDJD, 116.936030, 40.324136, 9956.71, -0.20, -0.24, -0.17, 208.14, 137.87, -4.99, -10.39, -4.04, -14.91, -2.99, 0.89, -1.09, 2.60, 0.36, 7.31);
insertDiscretePointData(&discretePointList, 221000, ZDJD, 116.931969, 40.313935, 9954.64, -0.20, -0.21, -0.14, 209.09, 138.64, -6.57, -10.88, -3.73, -14.83, -2.24, 1.19, 0.60, 2.75, 0.36, 7.35);
insertDiscretePointData(&discretePointList, 222000, ZDJD, 116.928238, 40.300476, 9952.27, -0.25, -0.23, -0.12, 209.52, 138.95, -8.16, -11.46, -3.71, -14.83, -1.97, 0.89, 1.88, 2.85, 0.32, 7.22);
insertDiscretePointData(&discretePointList, 223000, ZDJD, 116.925048, 40.284453, 9950.81, -0.28, -0.22, -0.09, 210.18, 139.56, -9.24, -11.81, -3.53, -14.31, -1.42, 0.88, 3.31, 2.93, 0.30, 6.94);
insertDiscretePointData(&discretePointList, 224000, ZDJD, 116.922577, 40.266653, 9949.90, -0.30, -0.21, -0.06, 210.83, 140.20, -9.92, -12.03, -3.33, -13.48, -0.86, 0.88, 4.68, 2.97, 0.27, 6.51);
insertDiscretePointData(&discretePointList, 225000, ZDJD, 116.920998, 40.247954, 9950.33, -0.27, -0.16, 0.01, 211.96, 141.39, -9.88, -11.92, -2.81, -11.97, 0.21, 1.46, 6.34, 3.01, 0.28, 5.95);
insertDiscretePointData(&discretePointList, 226000, ZDJD, 116.920424, 40.229240, 9950.11, -0.32, -0.17, 0.04, 212.32, 141.86, -9.84, -11.98, -2.74, -10.80, 0.52, 1.14, 7.26, 2.98, 0.23, 5.25);
insertDiscretePointData(&discretePointList, 227000, ZDJD, 116.920989, 40.211445, 9951.23, -0.32, -0.14, 0.09, 213.16, 142.86, -9.08, -11.70, -2.36, -9.00, 1.33, 1.42, 8.43, 2.94, 0.22, 4.45);
insertDiscretePointData(&discretePointList, 228000, ZDJD, 116.922755, 40.195422, 9952.49, -0.34, -0.13, 0.12, 213.72, 143.64, -8.07, -11.40, -2.11, -7.20, 1.88, 1.39, 9.22, 2.85, 0.19, 3.54);
insertDiscretePointData(&discretePointList, 229000, ZDJD, 116.925777, 40.181973, 9954.67, -0.34, -0.09, 0.16, 214.51, 144.69, -6.56, -10.88, -1.71, -5.06, 2.66, 1.65, 10.01, 2.75, 0.18, 2.57);
insertDiscretePointData(&discretePointList, 230000, ZDJD, 116.930048, 40.171762, 9956.55, -0.38, -0.10, 0.17, 214.77, 145.27, -5.06, -10.43, -1.60, -3.19, 2.91, 1.31, 10.20, 2.59, 0.13, 1.53);
insertDiscretePointData(&discretePointList, 231000, ZDJD, 116.935557, 40.165341, 9959.30, -0.40, -0.09, 0.18, 215.26, 146.12, -3.18, -9.77, -1.34, -1.06, 3.37, 1.27, 10.36, 2.42, 0.10, 0.46);
insertDiscretePointData(&discretePointList, 232000, ZDJD, 116.942243, 40.163082, 9962.90, -0.39, -0.05, 0.20, 215.96, 147.22, -1.02, -8.90, -0.92, 1.28, 4.05, 1.51, 10.49, 2.23, 0.09, -0.61);
insertDiscretePointData(&discretePointList, 233000, ZDJD, 116.950006, 40.165169, 9966.91, -0.39, -0.01, 0.21, 216.65, 148.35, 1.18, -7.94, -0.49, 3.61, 4.69, 1.76, 10.40, 2.02, 0.07, -1.67);
insertDiscretePointData(&discretePointList, 234000, ZDJD, 116.958719, 40.171598, 9970.88, -0.41, -0.00, 0.20, 217.05, 149.22, 3.19, -6.99, -0.21, 5.65, 5.02, 1.70, 9.90, 1.77, 0.04, -2.70);
insertDiscretePointData(&discretePointList, 235000, ZDJD, 116.968230, 40.182178, 9974.77, -0.45, -0.01, 0.16, 217.18, 149.85, 4.91, -6.06, -0.09, 7.38, 5.05, 1.33, 8.98, 1.49, -0.01, -3.68);
insertDiscretePointData(&discretePointList, 236000, ZDJD, 116.978382, 40.196553, 9979.73, -0.44, 0.02, 0.15, 217.77, 150.99, 6.72, -4.86, 0.34, 9.35, 5.53, 1.55, 8.26, 1.22, -0.03, -4.56);
insertDiscretePointData(&discretePointList, 237000, ZDJD, 116.988968, 40.214171, 9984.53, -0.45, 0.04, 0.12, 218.08, 151.87, 8.08, -3.71, 0.62, 10.92, 5.69, 1.47, 7.18, 0.93, -0.06, -5.36);
insertDiscretePointData(&discretePointList, 238000, ZDJD, 116.999794, 40.234363, 9989.88, -0.44, 0.07, 0.09, 218.61, 152.98, 9.24, -2.43, 1.04, 12.46, 6.04, 1.68, 6.13, 0.63, -0.07, -6.03);
insertDiscretePointData(&discretePointList, 239000, ZDJD, 117.010643, 40.256328, 9994.96, -0.46, 0.09, 0.05, 218.86, 153.84, 9.85, -1.21, 1.31, 13.53, 6.08, 1.59, 4.76, 0.32, -0.11, -6.58);
insertDiscretePointData(&discretePointList, 240000, ZDJD, 117.021302, 40.279196, 9999.69, -0.49, 0.07, -0.01, 218.83, 154.44, 9.88, -0.08, 1.43, 14.11, 5.81, 1.19, 3.09, -0.01, -0.15, -6.99);
insertDiscretePointData(&discretePointList, 241000, ZDJD, 117.031582, 40.302074, 10005.22, -0.48, 0.11, -0.04, 219.26, 155.52, 9.78, 1.25, 1.84, 14.78, 5.96, 1.39, 1.75, -0.31, -0.17, -7.25);
insertDiscretePointData(&discretePointList, 242000, ZDJD, 117.041277, 40.324044, 10010.69, -0.47, 0.15, -0.07, 219.66, 156.57, 9.25, 2.57, 2.24, 15.14, 6.05, 1.58, 0.37, -0.62, -0.18, -7.34);
insertDiscretePointData(&discretePointList, 243000, ZDJD, 117.050201, 40.344226, 10015.25, -0.50, 0.13, -0.12, 219.52, 157.10, 8.02, 3.66, 2.33, 14.78, 5.58, 1.17, -1.41, -0.93, -0.22, -7.29);
insertDiscretePointData(&discretePointList, 244000, ZDJD, 117.058216, 40.361849, 10020.44, -0.49, 0.17, -0.14, 219.85, 158.10, 6.73, 4.91, 2.72, 14.50, 5.55, 1.34, -2.77, -1.22, -0.24, -7.08);
insertDiscretePointData(&discretePointList, 245000, ZDJD, 117.065171, 40.376214, 10024.61, -0.52, 0.15, -0.19, 219.64, 158.57, 4.85, 5.90, 2.79, 13.51, 4.95, 0.92, -4.47, -1.51, -0.28, -6.72);
insertDiscretePointData(&discretePointList, 246000, ZDJD, 117.070985, 40.386804, 10029.30, -0.50, 0.19, -0.19, 219.90, 159.50, 3.06, 7.03, 3.15, 12.62, 4.80, 1.09, -5.67, -1.77, -0.29, -6.21);
insertDiscretePointData(&discretePointList, 247000, ZDJD, 117.075578, 40.393238, 10033.67, -0.49, 0.22, -0.19, 220.13, 160.40, 1.13, 8.08, 3.50, 11.46, 4.59, 1.25, -6.75, -2.00, -0.30, -5.56);
insertDiscretePointData(&discretePointList, 248000, ZDJD, 117.078910, 40.395320, 10037.28, -0.49, 0.23, -0.19, 220.07, 161.01, -1.00, 8.95, 3.69, 9.86, 4.09, 1.12, -7.89, -2.23, -0.32, -4.80);
insertDiscretePointData(&discretePointList, 249000, ZDJD, 117.080986, 40.393056, 10040.47, -0.50, 0.23, -0.19, 219.97, 161.57, -3.08, 9.71, 3.86, 8.05, 3.54, 0.97, -8.86, -2.43, -0.35, -3.94);
insertDiscretePointData(&discretePointList, 250000, DTFL, 117.068139, 40.343334, 10043.23, -0.50, 0.24, -0.18, 219.85, 162.09, -5.03, 10.37, 4.02, 6.07, 2.96, 0.83, -9.63, -2.60, -0.37, -2.99);
insertDiscretePointData(&discretePointList, 251000, DTFL, 117.069057, 40.339277, 10045.90, -0.48, 0.27, -0.14, 219.93, 162.81, -6.61, 11.02, 4.31, 4.15, 2.58, 0.97, -10.00, -2.73, -0.37, -1.97);
insertDiscretePointData(&discretePointList, 252000, DTFL, 117.069271, 40.333591, 10047.68, -0.48, 0.27, -0.11, 219.73, 163.23, -8.04, 11.45, 4.43, 1.95, 1.94, 0.82, -10.35, -2.85, -0.39, -0.92);
insertDiscretePointData(&discretePointList, 253000, DTFL, 117.068867, 40.326616, 10048.55, -0.51, 0.25, -0.09, 219.25, 163.35, -9.27, 11.65, 4.39, -0.49, 1.02, 0.37, -10.68, -2.94, -0.42, 0.15);
insertDiscretePointData(&discretePointList, 254000, DTFL, 117.067970, 40.318766, 10050.06, -0.46, 0.30, -0.03, 219.47, 164.16, -9.65, 12.02, 4.78, -2.33, 0.84, 0.81, -10.18, -2.98, -0.41, 1.23);
insertDiscretePointData(&discretePointList, 255000, DTFL, 117.066674, 40.310453, 10050.24, -0.46, 0.30, 0.01, 219.17, 164.42, -9.91, 12.06, 4.85, -4.51, 0.15, 0.65, -9.86, -2.99, -0.42, 2.27);
insertDiscretePointData(&discretePointList, 256000, DTFL, 117.065118, 40.302140, 10049.88, -0.46, 0.30, 0.05, 218.84, 164.62, -9.73, 11.97, 4.90, -6.60, -0.53, 0.48, -9.33, -2.98, -0.43, 3.27);
insertDiscretePointData(&discretePointList, 257000, DTFL, 117.063439, 40.294281, 10048.96, -0.46, 0.30, 0.08, 218.47, 164.77, -9.11, 11.75, 4.93, -8.53, -1.21, 0.32, -8.59, -2.93, -0.44, 4.20);
insertDiscretePointData(&discretePointList, 258000, DTFL, 117.061783, 40.287315, 10047.91, -0.43, 0.32, 0.13, 218.32, 165.11, -7.96, 11.50, 5.09, -10.09, -1.63, 0.46, -7.47, -2.84, -0.43, 5.04);
insertDiscretePointData(&discretePointList, 259000, DTFL, 117.060279, 40.281629, 10045.94, -0.43, 0.32, 0.16, 217.89, 165.13, -6.59, 11.03, 5.09, -11.63, -2.28, 0.29, -6.39, -2.73, -0.44, 5.76);
insertDiscretePointData(&discretePointList, 260000, DTFL, 117.059069, 40.277567, 10043.47, -0.42, 0.31, 0.18, 217.42, 165.10, -4.94, 10.43, 5.06, -12.91, -2.90, 0.12, -5.17, -2.59, -0.44, 6.37);
insertDiscretePointData(&discretePointList, 261000, DTFL, 117.058278, 40.275398, 10040.52, -0.42, 0.30, 0.19, 216.93, 165.01, -3.07, 9.72, 5.01, -13.91, -3.49, -0.05, -3.83, -2.43, -0.45, 6.83);
insertDiscretePointData(&discretePointList, 262000, DTFL, 117.058028, 40.275312, 10037.53, -0.39, 0.32, 0.21, 216.65, 165.11, -0.91, 9.01, 5.10, -14.42, -3.78, 0.09, -2.21, -2.22, -0.43, 7.16);
insertDiscretePointData(&discretePointList, 263000, DTFL, 117.058404, 40.277389, 10033.33, -0.41, 0.29, 0.19, 215.85, 164.66, 1.00, 8.00, 4.86, -15.01, -4.54, -0.37, -0.94, -2.01, -0.45, 7.32);
insertDiscretePointData(&discretePointList, 264000, DTFL, 117.059504, 40.281644, 10029.17, -0.40, 0.28, 0.18, 215.27, 164.39, 3.01, 7.00, 4.76, -15.08, -4.99, -0.54, 0.55, -1.77, -0.44, 7.33);
insertDiscretePointData(&discretePointList, 265000, DTFL, 117.061385, 40.287978, 10024.69, -0.39, 0.27, 0.16, 214.67, 164.07, 4.88, 5.92, 4.64, -14.83, -5.39, -0.70, 2.03, -1.51, -0.44, 7.19);
insertDiscretePointData(&discretePointList, 266000, DTFL, 117.064098, 40.296214, 10020.73, -0.33, 0.30, 0.16, 214.53, 164.19, 6.84, 4.98, 4.79, -13.86, -5.24, -0.26, 3.85, -1.21, -0.40, 6.89);
insertDiscretePointData(&discretePointList, 267000, DTFL, 117.067635, 40.306059, 10015.34, -0.35, 0.26, 0.11, 213.62, 163.50, 8.05, 3.68, 4.48, -13.20, -5.78, -0.72, 5.00, -0.93, -0.41, 6.44);
insertDiscretePointData(&discretePointList, 268000, DTFL, 117.072016, 40.317199, 10010.59, -0.31, 0.28, 0.09, 213.19, 163.27, 9.21, 2.54, 4.45, -11.85, -5.75, -0.58, 6.45, -0.62, -0.39, 5.86);
insertDiscretePointData(&discretePointList, 269000, DTFL, 117.077197, 40.329222, 10005.32, -0.30, 0.26, 0.05, 212.48, 162.73, 9.82, 1.28, 4.26, -10.45, -5.91, -0.73, 7.55, -0.31, -0.38, 5.14);
insertDiscretePointData(&discretePointList, 270000, DTFL, 117.083130, 40.341700, 10000.01, -0.29, 0.24, 0.00, 211.76, 162.14, 10.00, 0.00, 4.05, -8.81, -6.00, -0.88, 8.50, 0.00, -0.36, 4.32);
insertDiscretePointData(&discretePointList, 271000, DTFL, 117.089747, 40.354183, 9995.08, -0.26, 0.25, -0.03, 211.26, 161.75, 9.90, -1.18, 3.97, -6.80, -5.78, -0.73, 9.46, 0.32, -0.34, 3.41);
insertDiscretePointData(&discretePointList, 272000, DTFL, 117.096948, 40.366206, 9989.81, -0.25, 0.23, -0.07, 210.49, 161.07, 9.21, -2.44, 3.72, -4.83, -5.74, -0.87, 10.02, 0.63, -0.32, 2.42);
insertDiscretePointData(&discretePointList, 273000, DTFL, 117.104628, 40.377341, 9984.66, -0.23, 0.21, -0.11, 209.71, 160.34, 8.13, -3.68, 3.47, -2.75, -5.64, -1.01, 10.37, 0.93, -0.30, 1.38);
insertDiscretePointData(&discretePointList, 274000, DTFL, 117.112661, 40.387186, 9979.28, -0.25, 0.17, -0.16, 208.65, 159.32, 6.55, -4.98, 3.04, -0.82, -5.72, -1.44, 10.30, 1.21, -0.30, 0.30);
insertDiscretePointData(&discretePointList, 275000, DTFL, 117.120930, 40.395417, 9974.92, -0.21, 0.17, -0.18, 208.08, 158.77, 4.97, -6.02, 2.91, 1.53, -5.25, -1.27, 10.40, 1.50, -0.27, -0.77);
insertDiscretePointData(&discretePointList, 276000, DTFL, 117.129287, 40.401756, 9970.84, -0.17, 0.17, -0.18, 207.50, 158.18, 3.17, -7.00, 2.76, 3.84, -4.71, -1.10, 10.28, 1.77, -0.23, -1.83);
insertDiscretePointData(&discretePointList, 277000, DTFL, 117.137580, 40.406006, 9966.27, -0.18, 0.13, -0.21, 206.41, 157.06, 0.94, -8.10, 2.31, 5.68, -4.63, -1.52, 9.54, 2.00, -0.23, -2.85);
insertDiscretePointData(&discretePointList, 278000, DTFL, 117.145693, 40.408093, 9962.88, -0.14, 0.13, -0.20, 205.80, 156.41, -1.03, -8.91, 2.14, 7.79, -3.99, -1.33, 9.00, 2.23, -0.19, -3.81);
insertDiscretePointData(&discretePointList, 279000, DTFL, 117.153479, 40.408007, 9959.89, -0.10, 0.13, -0.18, 205.18, 155.73, -2.96, -9.62, 1.97, 9.73, -3.32, -1.14, 8.26, 2.44, -0.15, -4.68);
insertDiscretePointData(&discretePointList, 280000, DTFL, 117.160805, 40.405833, 9956.54, -0.11, 0.08, -0.18, 204.06, 154.54, -5.06, -10.43, 1.49, 11.07, -3.10, -1.55, 6.95, 2.59, -0.14, -5.46);
insertDiscretePointData(&discretePointList, 281000, DTFL, 117.167574, 40.401771, 9954.07, -0.10, 0.06, -0.16, 203.18, 153.57, -6.79, -11.03, 1.15, 12.37, -2.60, -1.64, 5.68, 2.73, -0.12, -6.13);
insertDiscretePointData(&discretePointList, 282000, DTFL, 117.173690, 40.396090, 9952.50, -0.06, 0.06, -0.12, 202.54, 152.84, -8.07, -11.40, 0.95, 13.60, -1.82, -1.44, 4.49, 2.85, -0.08, -6.65);
insertDiscretePointData(&discretePointList, 283000, DTFL, 117.179069, 40.389125, 9951.44, -0.02, 0.06, -0.07, 201.89, 152.10, -9.00, -11.65, 0.76, 14.54, -1.03, -1.22, 3.21, 2.94, -0.04, -7.03);
insertDiscretePointData(&discretePointList, 284000, DTFL, 117.183645, 40.381260, 9950.13, -0.03, 0.01, -0.05, 200.75, 150.85, -9.84, -11.97, 0.26, 14.77, -0.72, -1.61, 1.46, 2.98, -0.03, -7.27);
insertDiscretePointData(&discretePointList, 285000, DTFL, 117.187397, 40.372947, 9949.76, -0.02, -0.02, -0.01, 199.85, 149.85, -10.09, -12.06, -0.09, 14.88, -0.15, -1.68, -0.12, 2.99, -0.01, -7.35);
insertDiscretePointData(&discretePointList, 286000, DTFL, 117.190309, 40.364634, 9949.94, -0.00, -0.04, 0.03, 198.95, 148.85, -9.91, -12.02, -0.44, 14.67, 0.42, -1.75, -1.70, 2.98, 0.02, -7.28);
insertDiscretePointData(&discretePointList, 287000, DTFL, 117.192398, 40.356779, 9951.06, 0.04, -0.04, 0.08, 198.31, 148.10, -9.15, -11.75, -0.64, 14.34, 1.23, -1.51, -3.05, 2.93, 0.06, -7.04);
insertDiscretePointData(&discretePointList, 288000, DTFL, 117.193688, 40.349809, 9952.32, 0.05, -0.06, 0.11, 197.41, 147.11, -8.14, -11.45, -0.99, 13.51, 1.77, -1.57, -4.54, 2.85, 0.08, -6.65);
insertDiscretePointData(&discretePointList, 289000, DTFL, 117.194241, 40.344123, 9954.09, 0.07, -0.09, 0.14, 196.52, 146.13, -6.78, -11.02, -1.33, 12.38, 2.30, -1.62, -5.92, 2.73, 0.10, -6.12);
insertDiscretePointData(&discretePointList, 290000, DTFL, 117.194137, 40.340061, 9956.37, 0.08, -0.11, 0.16, 195.64, 145.16, -5.12, -10.47, -1.67, 10.98, 2.80, -1.67, -7.19, 2.59, 0.13, -5.47);
insertDiscretePointData(&discretePointList, 291000, DTFL, 117.193475, 40.337897, 9959.53, 0.12, -0.11, 0.19, 195.02, 144.47, -3.10, -9.71, -1.85, 9.55, 3.52, -1.41, -8.10, 2.43, 0.17, -4.69);
insertDiscretePointData(&discretePointList, 292000, DTFL, 117.192357, 40.337806, 9962.73, 0.14, -0.13, 0.19, 194.15, 143.54, -1.09, -8.95, -2.17, 7.71, 3.94, -1.44, -9.04, 2.23, 0.19, -3.81);
insertDiscretePointData(&discretePointList, 293000, DTFL, 117.190915, 40.339888, 9966.33, 0.15, -0.16, 0.19, 193.29, 142.64, 0.97, -8.08, -2.49, 5.71, 4.33, -1.47, -9.78, 2.00, 0.21, -2.85);
insertDiscretePointData(&discretePointList, 294000, DTFL, 117.189280, 40.344143, 9970.31, 0.16, -0.18, 0.18, 192.45, 141.77, 2.98, -7.13, -2.79, 3.58, 4.66, -1.50, -10.32, 1.76, 0.23, -1.83);
insertDiscretePointData(&discretePointList, 295000, DTFL, 117.187602, 40.350487, 9975.39, 0.23, -0.15, 0.19, 192.11, 141.43, 5.15, -5.90, -2.79, 1.77, 5.44, -0.92, -10.25, 1.51, 0.28, -0.76);
insertDiscretePointData(&discretePointList, 296000, DTFL, 117.186003, 40.358713, 9979.96, 0.24, -0.17, 0.16, 191.30, 140.63, 6.80, -4.81, -3.07, -0.48, 5.67, -0.93, -10.34, 1.23, 0.30, 0.31);
insertDiscretePointData(&discretePointList, 297000, DTFL, 117.184624, 40.368558, 9984.35, 0.23, -0.22, 0.11, 190.24, 139.61, 8.02, -3.76, -3.50, -2.91, 5.58, -1.24, -10.41, 0.92, 0.30, 1.37);
insertDiscretePointData(&discretePointList, 298000, DTFL, 117.183608, 40.379693, 9989.31, 0.24, -0.24, 0.07, 189.46, 138.88, 9.03, -2.57, -3.75, -5.08, 5.69, -1.25, -10.06, 0.62, 0.32, 2.41);
insertDiscretePointData(&discretePointList, 299000, DTFL, 117.183077, 40.391721, 9994.78, 0.28, -0.23, 0.04, 188.94, 138.45, 9.79, -1.25, -3.85, -6.94, 5.97, -0.95, -9.30, 0.31, 0.35, 3.41);
insertDiscretePointData(&discretePointList, 300000, LDZD, 117.183128, 40.404199, 9999.91, 0.29, -0.25, -0.00, 188.19, 137.81, 9.97, -0.02, -4.08, -8.86, 5.95, -0.95, -8.54, -0.00, 0.36, 4.32);
insertDiscretePointData(&discretePointList, 301000, LDZD, 117.225419, 40.414558, 10048.51, -0.15, 2.82, -430.00, 134.92, 26.14, -57.51, 4.54, 7.50, 13.46, 143.63, -57.44, 39.53, -1456.32, -101.80, -96.34);
insertDiscretePointData(&discretePointList, 302000, LDZD, 117.221582, 40.423713, 10067.00, 1.39, 2.22, -349.20, 113.05, 50.17, -93.01, 8.98, 2.28, 24.38, 124.08, -63.57, 26.83, -2769.80, -38.74, -171.51);
insertDiscretePointData(&discretePointList, 303000, LDZD, 117.216156, 40.430561, 10043.18, 2.57, 1.21, -309.23, 79.27, 68.52, -123.67, 12.33, -4.42, 29.65, 90.87, -63.93, 7.12, -3812.39, 38.85, -209.44);
insertDiscretePointData(&discretePointList, 304000, LDZD, 117.209579, 40.434241, 9978.67, 3.33, -0.06, -283.68, 37.21, 79.75, -151.36, 14.51, -9.94, 28.47, 48.03, -57.02, -14.13, -4481.79, 101.61, -201.71);
insertDiscretePointData(&discretePointList, 305000, LDZD, 117.202398, 40.434198, 9887.95, 3.58, -1.46, -265.34, -9.21, 82.59, -177.03, 15.27, -12.37, 21.07, -0.42, -45.62, -32.34, -4712.49, 125.54, -150.01);
insertDiscretePointData(&discretePointList, 306000, LDZD, 117.195216, 40.430239, 9793.86, 3.30, -2.86, -251.24, -55.63, 76.63, -201.20, 14.53, -10.99, 9.04, -49.79, -34.23, -43.62, -4481.91, 101.47, -65.63);
insertDiscretePointData(&discretePointList, 307000, LDZD, 117.188640, 40.422556, 9719.15, 2.52, -4.13, -239.92, -97.69, 62.28, -224.20, 12.33, -6.51, -5.01, -95.24, -27.33, -45.57, -3812.63, 38.56, 33.04);
insertDiscretePointData(&discretePointList, 308000, LDZD, 117.183224, 40.411716, 9679.14, 1.42, -5.04, -230.32, -130.46, 41.82, -245.42, 9.39, -0.25, -17.33, -130.19, -24.68, -35.32, -2769.66, -38.57, 124.77);
insertDiscretePointData(&discretePointList, 309000, LDZD, 117.179382, 40.398564, 9671.60, -0.10, -5.69, -222.35, -152.84, 15.16, -266.64, 5.00, 4.23, -26.51, -154.87, -32.31, -19.65, -1456.05, -101.48, 189.04);
insertDiscretePointData(&discretePointList, 310000, LDZD, 117.177402, 40.384202, 9684.00, -1.78, -5.92, -215.45, -161.81, -14.21, -287.17, 0.09, 5.61, -29.87, -164.62, -44.43, 0.47, 0.09, -125.55, 212.11);
insertDiscretePointData(&discretePointList, 311000, LDZD, 117.177375, 40.369835, 9693.44, -3.51, -5.76, -209.50, -157.18, -44.08, -307.48, -5.10, 2.88, -27.03, -159.21, -58.04, 19.36, 1455.99, -101.92, 188.82);
insertDiscretePointData(&discretePointList, 312000, LDZD, 117.179219, 40.356688, 9679.35, -4.98, -5.09, -204.03, -138.15, -70.23, -326.47, -9.37, -2.34, -17.67, -136.02, -64.18, 36.27, 2769.85, -38.86, 124.63);
insertDiscretePointData(&discretePointList, 313000, LDZD, 117.182648, 40.345843, 9626.78, -6.14, -4.05, -199.11, -107.71, -91.20, -344.98, -12.76, -8.74, -4.46, -98.97, -63.03, 45.27, 3812.57, 39.03, 33.27);
insertDiscretePointData(&discretePointList, 314000, LDZD, 117.187217, 40.338155, 9534.60, -6.96, -2.86, -194.86, -69.99, -106.04, -363.86, -15.41, -14.56, 9.07, -53.42, -57.62, 42.07, 4481.60, 101.49, -65.62);
insertDiscretePointData(&discretePointList, 315000, LDZD, 117.192396, 40.334196, 9418.56, -7.24, -1.48, -190.89, -27.41, -112.01, -381.94, -16.33, -17.00, 20.93, -0.82, -46.23, 30.80, 4712.18, 125.42, -150.07);
insertDiscretePointData(&discretePointList, 316000, LDZD, 117.197580, 40.334157, 9301.18, -6.94, -0.05, -187.16, 15.67, -108.67, -399.28, -15.42, -15.31, 28.51, 53.71, -33.34, 13.83, 4481.73, 101.65, -201.69);
insertDiscretePointData(&discretePointList, 317000, LDZD, 117.202159, 40.337843, 9204.38, -6.13, 1.24, -183.71, 54.39, -96.94, -416.28, -12.99, -10.53, 29.87, 103.85, -24.93, -6.17, 3812.58, 39.04, -209.34);
insertDiscretePointData(&discretePointList, 318000, LDZD, 117.205583, 40.344691, 9141.49, -4.95, 2.22, -180.61, 84.33, -78.59, -433.38, -9.50, -4.87, 24.43, 143.65, -25.29, -25.88, 2769.99, -38.70, -171.49);
insertDiscretePointData(&discretePointList, 319000, LDZD, 117.207422, 40.353840, 9113.16, -3.46, 2.85, -177.72, 102.86, -55.06, -450.20, -5.02, -0.40, 13.70, 169.98, -32.92, -39.83, 1456.26, -101.60, -96.24);
insertDiscretePointData(&discretePointList, 320000, LDZD, 117.207405, 40.364205, 9106.16, -1.75, 3.11, -174.93, 108.49, -28.31, -466.36, 0.24, 1.29, 0.34, 180.97, -43.54, -43.78, 0.24, -125.37, 0.15);
insertDiscretePointData(&discretePointList, 321000, LDZD, 117.205420, 40.374559, 9096.28, -0.14, 2.83, -172.51, 99.02, -2.56, -483.07, 5.06, -1.44, -13.71, 172.35, -57.16, -40.43, -1456.27, -101.74, 96.23);
insertDiscretePointData(&discretePointList, 322000, LDZD, 117.201583, 40.383714, 9063.51, 1.40, 2.23, -170.05, 77.14, 21.47, -498.75, 9.91, -6.66, -24.10, 148.54, -63.28, -25.83, -2769.75, -38.68, 171.63);
insertDiscretePointData(&discretePointList, 323000, LDZD, 117.196157, 40.390562, 8992.21, 2.58, 1.22, -167.82, 43.36, 39.81, -514.62, 13.59, -13.37, -29.55, 108.69, -63.66, -6.73, -3812.34, 38.91, 209.48);
insertDiscretePointData(&discretePointList, 324000, LDZD, 117.189580, 40.394242, 8883.03, 3.34, -0.05, -165.71, 1.30, 51.04, -530.28, 15.98, -18.89, -28.53, 57.49, -56.74, 13.92, -4481.75, 101.67, 201.68);
insertDiscretePointData(&discretePointList, 325000, LDZD, 117.182399, 40.394199, 8749.86, 3.59, -1.45, -163.72, -45.11, 53.89, -545.75, 16.82, -21.32, -21.29, -0.23, -45.34, 31.53, -4712.45, 125.60, 149.91);
insertDiscretePointData(&discretePointList, 326000, LDZD, 117.175222, 40.390245, 8615.79, 3.36, -2.80, -161.73, -91.04, 48.42, -560.64, 16.25, -19.63, -9.09, -57.88, -32.46, 43.45, -4481.62, 101.82, 65.61);
insertDiscretePointData(&discretePointList, 327000, LDZD, 117.168646, 40.382562, 8502.10, 2.58, -4.07, -159.93, -133.10, 34.07, -575.75, 13.84, -15.16, 4.79, -111.70, -25.56, 44.79, -3812.33, 38.92, -33.13);
insertDiscretePointData(&discretePointList, 328000, LDZD, 117.163215, 40.371707, 8422.70, 1.33, -5.13, -158.32, -167.37, 12.11, -591.09, 9.81, -9.79, 17.30, -156.28, -27.40, 35.22, -2770.11, -39.12, -124.79);
insertDiscretePointData(&discretePointList, 329000, LDZD, 117.159383, 40.358565, 8380.00, -0.09, -5.68, -156.49, -188.75, -13.55, -605.08, 5.51, -4.72, 27.01, -183.23, -32.04, 21.43, -1456.01, -101.42, -188.82);
insertDiscretePointData(&discretePointList, 330000, LDZD, 117.157403, 40.344203, 8357.17, -1.77, -5.91, -154.93, -197.72, -42.92, -619.71, 0.14, -3.33, 30.20, -194.43, -44.15, 0.71, 0.14, -125.49, -211.97);
insertDiscretePointData(&discretePointList, 331000, LDZD, 117.157376, 40.329836, 8332.37, -3.50, -5.75, -153.53, -193.09, -72.79, -634.60, -5.52, -6.06, 26.50, -187.55, -57.76, -21.27, 1456.04, -101.86, -189.04);
insertDiscretePointData(&discretePointList, 332000, LDZD, 117.159220, 40.316689, 8284.96, -4.97, -5.08, -152.00, -174.06, -98.94, -648.55, -10.21, -11.29, 17.66, -160.10, -63.90, -36.30, 2769.89, -38.81, -124.63);
insertDiscretePointData(&discretePointList, 333000, LDZD, 117.162649, 40.305844, 8199.91, -6.13, -4.04, -150.53, -143.62, -119.91, -662.37, -13.93, -17.69, 4.99, -116.42, -62.75, -43.39, 3812.61, 39.09, -33.05);
insertDiscretePointData(&discretePointList, 334000, LDZD, 117.167223, 40.298161, 8076.62, -6.91, -2.80, -149.21, -105.39, -134.25, -676.46, -16.54, -23.21, -9.06, -61.50, -55.84, -42.04, 4481.90, 101.85, 65.62);
insertDiscretePointData(&discretePointList, 335000, LDZD, 117.172402, 40.294202, 7929.59, -7.18, -1.42, -147.94, -62.82, -140.22, -690.43, -17.53, -25.64, -21.09, 0.36, -44.45, -31.36, 4712.48, 125.77, 150.00);
insertDiscretePointData(&discretePointList, 336000, LDZD, 117.177581, 40.294158, 7781.29, -6.93, -0.04, -146.72, -20.24, -137.37, -704.28, -16.80, -24.25, -28.49, 63.16, -33.06, -13.75, 4481.78, 101.70, 201.70);
insertDiscretePointData(&discretePointList, 337000, LDZD, 117.182160, 40.297844, 7654.80, -6.12, 1.25, -145.44, 18.48, -125.65, -717.61, -14.16, -19.47, -29.32, 121.68, -24.65, 8.15, 3812.62, 39.10, 209.58);
insertDiscretePointData(&discretePointList, 338000, LDZD, 117.185584, 40.304692, 7562.81, -4.94, 2.23, -144.31, 48.42, -107.30, -731.24, -10.33, -13.82, -24.04, 168.11, -25.01, 27.26, 2770.03, -38.64, 171.66);
insertDiscretePointData(&discretePointList, 339000, LDZD, 117.187418, 40.313836, 7505.32, -3.50, 2.81, -143.31, 66.46, -84.27, -745.15, -5.69, -9.64, -13.83, 197.70, -34.13, 39.36, 1456.06, -101.84, 96.18);
insertDiscretePointData(&discretePointList, 340000, LDZD, 117.187401, 40.324201, 7470.28, -1.79, 3.07, -142.15, 72.08, -57.52, -758.17, 0.04, -7.95, 0.06, 210.16, -44.75, 45.20, 0.04, -125.61, 0.02);
insertDiscretePointData(&discretePointList, 341000, LDZD, 117.185421, 40.334560, 7433.45, -0.14, 2.84, -141.13, 63.11, -31.27, -771.49, 5.57, -10.38, 13.59, 201.07, -56.87, 40.00, -1456.23, -101.69, -96.28);
insertDiscretePointData(&discretePointList, 342000, LDZD, 117.181584, 40.343715, 7373.61, 1.41, 2.23, -140.03, 41.24, -7.24, -784.30, 10.84, -15.60, 24.51, 173.01, -62.99, 27.31, -2769.70, -38.63, -171.45);
insertDiscretePointData(&discretePointList, 343000, LDZD, 117.176153, 40.350558, 7275.07, 2.54, 1.18, -139.17, 6.96, 10.61, -797.83, 14.60, -22.61, 29.44, 125.52, -64.86, 6.34, -3812.54, 38.66, -209.53);
insertDiscretePointData(&discretePointList, 344000, LDZD, 117.169581, 40.354243, 7140.26, 3.35, -0.04, -138.14, -34.61, 22.33, -810.47, 17.45, -27.83, 28.60, 66.94, -56.47, -13.67, -4481.70, 101.72, -201.65);
insertDiscretePointData(&discretePointList, 345000, LDZD, 117.162405, 40.354205, 6981.88, 3.65, -1.39, -137.14, -80.52, 25.68, -823.02, 18.61, -29.96, 21.55, 0.96, -43.56, -30.62, -4712.15, 125.95, -149.80);
insertDiscretePointData(&discretePointList, 346000, LDZD, 117.155218, 40.350241, 6821.18, 3.32, -2.84, -136.36, -127.44, 19.21, -836.28, 17.48, -28.88, 9.17, -67.96, -33.67, -43.15, -4481.82, 101.58, -65.57);
insertDiscretePointData(&discretePointList, 347000, LDZD, 117.148642, 40.342558, 6682.42, 2.54, -4.11, -135.51, -169.50, 4.87, -849.06, 14.86, -24.40, -4.88, -130.13, -26.76, -45.10, -3812.53, 38.68, 33.09);
insertDiscretePointData(&discretePointList, 348000, LDZD, 117.143221, 40.331713, 6579.50, 1.39, -5.07, -134.58, -202.78, -16.10, -861.36, 10.99, -18.44, -17.55, -179.37, -25.63, -36.12, -2769.81, -38.76, 124.68);
insertDiscretePointData(&discretePointList, 349000, LDZD, 117.139384, 40.318566, 6511.82, -0.08, -5.67, -133.67, -224.66, -42.25, -873.58, 6.02, -13.66, -26.38, -211.57, -31.76, -19.19, -1455.96, -101.37, 189.09);
insertDiscretePointData(&discretePointList, 350000, HWZD, 117.127404, 40.304204, 6464.92, -1.76, -5.90, -132.89, -233.62, -71.62, -886.12, 0.19, -12.27, -29.74, -224.25, -43.87, 0.94, 0.19, -125.44, 212.17);
insertDiscretePointData(&discretePointList, 351000, HWZD, 117.127866, 40.296017, 6416.36, -3.49, -5.74, -132.22, -228.99, -101.49, -898.99, -5.94, -15.00, -26.90, -215.90, -57.48, 19.83, 1456.09, -101.81, 188.87);
insertDiscretePointData(&discretePointList, 352000, HWZD, 117.131131, 40.288446, 6345.50, -4.96, -5.07, -131.38, -209.96, -127.64, -910.99, -11.04, -20.23, -17.54, -184.18, -63.61, 36.75, 2769.94, -38.75, 124.69);
insertDiscretePointData(&discretePointList, 353000, HWZD, 117.136762, 40.282015, 6236.06, -6.22, -4.13, -130.76, -180.53, -149.62, -923.72, -15.60, -27.23, -5.03, -135.87, -65.49, 43.23, 3812.16, 38.54, 33.03);
insertDiscretePointData(&discretePointList, 354000, HWZD, 117.144128, 40.277178, 6090.48, -6.95, -2.84, -129.95, -141.80, -163.46, -935.57, -18.17, -32.45, 9.20, -71.59, -57.06, 42.54, 4481.70, 101.60, -65.56);
insertDiscretePointData(&discretePointList, 355000, HWZD, 117.152403, 40.274203, 5921.42, -7.17, -1.41, -129.16, -98.73, -168.93, -947.36, -18.99, -34.59, 21.40, 0.54, -44.19, 32.50, 4712.52, 125.83, -149.87);
insertDiscretePointData(&discretePointList, 356000, HWZD, 117.160672, 40.273180, 5750.75, -6.92, -0.03, -128.49, -56.15, -166.08, -959.48, -18.18, -33.20, 28.64, 72.62, -32.78, 14.30, 4481.83, 101.76, -201.63);
insertDiscretePointData(&discretePointList, 357000, HWZD, 117.168029, 40.274015, 5600.93, -6.22, 1.16, -127.93, -18.43, -155.36, -971.94, -15.83, -29.02, 29.30, 137.49, -27.38, -8.20, 3812.17, 38.55, -209.59);
insertDiscretePointData(&discretePointList, 358000, HWZD, 117.173670, 40.276443, 5487.64, -4.98, 2.19, -127.19, 12.01, -136.51, -983.54, -11.42, -23.06, 24.21, 191.56, -26.24, -26.67, 2769.83, -38.88, -171.58);
insertDiscretePointData(&discretePointList, 359000, HWZD, 117.176935, 40.280023, 5409.70, -3.44, 2.87, -126.46, 31.05, -112.47, -995.07, -5.85, -18.28, 13.83, 227.42, -32.35, -39.35, 1456.36, -101.49, -96.18);
insertDiscretePointData(&discretePointList, 360000, HWZD, 117.177402, 40.284202, 5352.63, -1.78, 3.08, -125.85, 36.18, -86.22, -1006.95, 0.09, -16.89, 0.12, 240.35, -44.47, -44.56, 0.09, -125.56, 0.05);
insertDiscretePointData(&discretePointList, 361000, HWZD, 117.174927, 40.288376, 5294.00, -0.18, 2.80, -125.35, 26.71, -60.47, -1019.16, 5.83, -19.63, -13.93, 228.80, -58.08, -41.20, -1456.43, -101.93, 96.14);
insertDiscretePointData(&discretePointList, 362000, HWZD, 117.169670, 40.291955, 5213.14, 1.37, 2.19, -124.67, 4.83, -36.44, -1030.52, 11.52, -24.85, -24.31, 196.46, -64.21, -26.61, -2769.90, -38.87, 171.54);
insertDiscretePointData(&discretePointList, 363000, HWZD, 117.162037, 40.294383, 5095.01, 2.60, 1.24, -123.99, -28.44, -17.59, -1041.83, 16.11, -31.25, -29.41, 144.34, -63.08, -6.25, -3812.25, 39.02, 209.54);
insertDiscretePointData(&discretePointList, 364000, HWZD, 117.152672, 40.295223, 4939.01, 3.36, -0.03, -123.43, -70.51, -6.37, -1053.47, 18.93, -36.77, -28.40, 76.41, -56.17, 14.39, -4481.65, 101.78, 201.74);
insertDiscretePointData(&discretePointList, 365000, HWZD, 117.142396, 40.294196, 4759.02, 3.56, -1.48, -122.98, -117.43, -4.03, -1065.47, 19.66, -39.51, -21.51, -0.85, -46.28, 30.75, -4712.60, 125.41, 149.82);
insertDiscretePointData(&discretePointList, 366000, HWZD, 117.132129, 40.291221, 4579.30, 3.33, -2.84, -122.35, -163.35, -9.49, -1076.61, 18.95, -37.82, -9.30, -77.04, -33.39, 42.68, -4481.77, 101.64, 65.51);
insertDiscretePointData(&discretePointList, 367000, HWZD, 117.122770, 40.286384, 4421.11, 2.60, -4.05, -121.72, -204.91, -23.33, -1087.70, 16.37, -33.04, 4.93, -146.57, -24.97, 45.28, -3812.24, 39.03, -33.07);
insertDiscretePointData(&discretePointList, 368000, HWZD, 117.115132, 40.279958, 4297.72, 1.39, -5.06, -121.21, -238.69, -44.81, -1099.14, 11.92, -27.38, 17.78, -203.45, -25.35, 36.93, -2769.77, -38.71, -124.58);
insertDiscretePointData(&discretePointList, 369000, HWZD, 117.109864, 40.272376, 4209.16, -0.17, -5.76, -120.80, -261.56, -71.95, -1110.92, 6.03, -23.20, 26.45, -241.90, -34.46, 19.41, -1456.41, -101.91, -189.07);
insertDiscretePointData(&discretePointList, 370000, HWZD, 117.107405, 40.264205, 4143.94, -1.75, -5.89, -120.10, -269.53, -100.33, -1121.47, 0.23, -21.22, 30.33, -254.07, -43.60, 1.17, 0.23, -125.38, -211.92);
insertDiscretePointData(&discretePointList, 371000, HWZD, 117.107872, 40.256023, 4076.63, -3.43, -5.68, -119.62, -264.40, -129.70, -1132.75, -6.11, -23.65, 26.98, -243.24, -55.70, -19.55, 1456.38, -101.45, -188.84);
insertDiscretePointData(&discretePointList, 372000, HWZD, 117.111127, 40.248442, 3985.38, -5.00, -5.11, -119.24, -246.37, -156.85, -1144.40, -12.13, -29.47, 17.44, -209.27, -64.83, -37.08, 2769.74, -38.99, -124.73);
insertDiscretePointData(&discretePointList, 373000, HWZD, 117.116763, 40.242016, 3857.52, -6.21, -4.12, -118.77, -216.43, -178.32, -1155.59, -16.76, -36.17, 4.42, -153.31, -65.18, -45.42, 3812.21, 38.60, -33.29);
insertDiscretePointData(&discretePointList, 374000, HWZD, 117.124129, 40.237179, 3693.04, -6.94, -2.83, -118.21, -177.71, -192.17, -1166.35, -19.55, -41.40, -9.28, -80.68, -56.79, -42.83, 4481.74, 101.66, 65.53);
insertDiscretePointData(&discretePointList, 375000, HWZD, 117.132404, 40.234204, 3505.25, -7.16, -1.40, -117.66, -134.63, -197.63, -1177.06, -20.44, -43.53, -20.96, 0.73, -43.90, -30.90, 4712.57, 125.88, 150.06);
insertDiscretePointData(&discretePointList, 376000, HWZD, 117.140673, 40.233181, 3315.99, -6.91, -0.02, -117.22, -92.05, -194.79, -1188.12, -19.56, -42.14, -28.36, 82.08, -32.50, -13.28, 4481.87, 101.81, 201.75);
insertDiscretePointData(&discretePointList, 377000, HWZD, 117.148030, 40.234016, 3147.73, -6.21, 1.17, -116.88, -54.33, -184.06, -1199.54, -16.99, -37.96, -29.89, 155.31, -27.09, 6.11, 3812.22, 38.61, 209.34);
insertDiscretePointData(&discretePointList, 378000, HWZD, 117.153666, 40.236439, 3015.53, -5.02, 2.15, -116.46, -24.39, -165.71, -1210.51, -12.50, -32.31, -24.62, 215.02, -27.46, 25.22, 2769.63, -39.13, 171.41);
insertDiscretePointData(&discretePointList, 379000, HWZD, 117.156931, 40.240019, 2919.41, -3.48, 2.83, -115.94, -5.36, -141.69, -1221.05, -6.52, -27.53, -13.70, 255.13, -33.59, 39.81, 1456.15, -101.73, 96.24);
insertDiscretePointData(&discretePointList, 380000, MBFP, 117.147403, 40.244203, 2844.91, -1.77, 3.09, -115.42, 0.27, -114.93, -1231.54, 0.14, -25.84, 0.19, 270.54, -44.19, 45.68, 0.14, -125.50, 0.08);
insertDiscretePointData(&discretePointList, 381000, MBFP, 117.145423, 40.248382, 2768.95, -0.12, 2.85, -115.02, -8.71, -88.69, -1242.40, 6.58, -28.27, 13.72, 258.50, -56.33, 40.45, -1456.14, -101.58, -96.23);
insertDiscretePointData(&discretePointList, 382000, MBFP, 117.141581, 40.251956, 2669.73, 1.38, 2.20, -114.62, -31.07, -65.15, -1253.21, 12.45, -33.79, 24.29, 220.92, -63.93, 26.53, -2769.86, -38.81, -171.55);
insertDiscretePointData(&discretePointList, 383000, MBFP, 117.136160, 40.254384, 2533.94, 2.61, 1.25, -114.13, -64.35, -46.30, -1263.59, 17.38, -40.20, 29.92, 162.16, -62.80, 8.06, -3812.20, 39.08, -209.32);
insertDiscretePointData(&discretePointList, 384000, MBFP, 117.129583, 40.255224, 2360.40, 3.36, -0.02, -113.74, -106.41, -35.07, -1274.32, 20.40, -45.72, 28.73, 85.87, -55.88, -13.18, -4481.60, 101.84, -201.59);
insertDiscretePointData(&discretePointList, 385000, MBFP, 117.122402, 40.254202, 2163.60, 3.62, -1.42, -113.36, -152.82, -32.22, -1285.02, 21.46, -48.14, 21.34, 0.35, -44.47, -31.38, -4712.30, 125.77, -149.89);
insertDiscretePointData(&discretePointList, 386000, MBFP, 117.115215, 40.251217, 1965.37, 3.29, -2.88, -113.09, -199.75, -38.70, -1296.08, 20.17, -47.06, 8.95, -87.12, -34.60, -43.93, -4481.97, 101.39, -65.66);
insertDiscretePointData(&discretePointList, 387000, MBFP, 117.108649, 40.246385, 1790.59, 2.61, -4.04, -112.52, -240.81, -52.04, -1305.90, 17.63, -41.98, -4.39, -164.01, -24.69, -43.37, -3812.19, 39.09, 33.30);
insertDiscretePointData(&discretePointList, 388000, MBFP, 117.103218, 40.239954, 1649.53, 1.35, -5.10, -112.26, -275.09, -74.01, -1316.90, 12.60, -36.63, -17.77, -228.53, -26.56, -36.89, -2769.97, -38.95, 124.59);
insertDiscretePointData(&discretePointList, 389000, MBFP, 117.099376, 40.232377, 1544.61, -0.16, -5.75, -111.90, -297.46, -100.66, -1327.45, 6.54, -32.15, -26.95, -270.25, -34.18, -21.21, -1456.36, -101.85, 188.85);
insertDiscretePointData(&discretePointList, 390000, DJJD, 117.097396, 40.224196, 1461.34, -1.84, -5.98, -111.55, -306.43, -130.03, -1337.96, -0.21, -30.76, -30.30, -285.85, -46.28, -1.06, -0.21, -125.92, 211.93);
insertDiscretePointData(&discretePointList, 391000, DJJD, 117.097378, 40.216019, 1377.87, -3.47, -5.72, -111.11, -300.80, -158.90, -1348.05, -6.77, -32.89, -26.77, -272.58, -56.91, 20.30, 1456.18, -101.70, 188.93);
insertDiscretePointData(&discretePointList, 392000, DJJD, 117.099223, 40.208448, 1271.17, -4.94, -5.05, -110.67, -281.77, -185.05, -1358.10, -12.71, -38.11, -17.40, -232.34, -63.04, 37.22, 2770.04, -38.64, 124.74);
insertDiscretePointData(&discretePointList, 393000, DJJD, 117.102641, 40.202017, 1126.16, -6.20, -4.11, -110.44, -252.34, -207.03, -1368.91, -17.93, -45.12, -4.90, -170.75, -64.91, 43.71, 3812.26, 38.66, 33.08);
insertDiscretePointData(&discretePointList, 394000, DJJD, 117.107216, 40.197175, 944.64, -6.98, -2.87, -110.11, -214.11, -221.37, -1379.29, -21.18, -50.64, 8.98, -90.75, -58.00, 41.76, 4481.54, 101.42, -65.65);
insertDiscretePointData(&discretePointList, 395000, DJJD, 117.112400, 40.194200, 740.51, -7.20, -1.44, -109.68, -171.03, -226.83, -1389.24, -22.14, -52.77, 21.19, -0.07, -45.10, 31.74, 4712.37, 125.64, -149.96);
insertDiscretePointData(&discretePointList, 396000, DJJD, 117.117584, 40.193182, 535.59, -6.90, -0.02, -109.26, -127.96, -223.49, -1399.16, -20.94, -51.08, 28.77, 91.54, -32.22, 14.76, 4481.92, 101.87, -201.58);
insertDiscretePointData(&discretePointList, 397000, DJJD, 117.122153, 40.194017, 351.18, -6.20, 1.18, -109.05, -90.23, -212.76, -1409.84, -18.16, -46.90, 29.44, 173.15, -26.79, -7.72, 3812.27, 38.67, -209.53);
insertDiscretePointData(&discretePointList, 398000, DJJD, 117.125576, 40.196440, 202.91, -5.01, 2.16, -108.74, -60.30, -194.42, -1420.10, -13.34, -41.25, 23.99, 239.48, -27.18, -27.45, 2769.67, -39.07, -171.68);
insertDiscretePointData(&discretePointList, 399000, DJJD, 117.127421, 40.200020, 90.83, -3.47, 2.84, -108.33, -41.26, -170.38, -1429.91, -6.94, -36.47, 13.61, 283.87, -33.28, -40.13, 1456.20, -101.67, -96.28);
insertDiscretePointData(&discretePointList, 400000, DJJD, 117.127404, 40.204204, 0.44, -1.76, 3.10, -107.93, -35.63, -143.63, -1439.71, 0.18, -34.78, 0.26, 300.73, -43.90, -44.08, 0.18, -125.44, 0.11);

    return discretePointList;
}

int main(){
    DiscretePointStateList msl = init();
    printDiscretePointList(&msl);
    return 0;
}