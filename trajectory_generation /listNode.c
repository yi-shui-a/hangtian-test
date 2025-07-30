#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

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
typedef struct MissileNode {
    DiscretePoint data;      /**< 导弹状态数据 */
    struct MissileNode* next; /**< 指向下一个节点的指针 */
} MissileNode;

/**
 * @brief 导弹状态链表管理结构体
 */
typedef struct {
    MissileNode* head;      /**< 链表头节点 */
    MissileNode* tail;      /**< 链表尾节点（优化尾插效率） */
    int count;              /**< 当前节点数量 */
} MissileStateList;

/* 函数声明 */
void initMissileList(MissileStateList* list);
void insertMissileData(
    MissileStateList* list,
    double time, uint16_t event,
    double longitude, double latitude, double altitude,
    double accX, double accY, double accZ,
    double velX, double velY, double velZ,
    double yaw, double pitch, double roll,
    double yawRate, double pitchRate, double rollRate,
    double yawAcc, double pitchAcc, double rollAcc
);
void printMissileList(const MissileStateList* list);
MissileNode* findMissileByTime(const MissileStateList* list, double time);
void deleteMissileByTime(MissileStateList* list, double time);
void clearMissileList(MissileStateList* list);

/**
 * @brief 初始化导弹状态链表
 */
void initMissileList(MissileStateList* list) {
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
void insertMissileData(
    MissileStateList* list,
    double time, uint16_t event,
    double longitude, double latitude, double altitude,
    double accX, double accY, double accZ,
    double velX, double velY, double velZ,
    double yaw, double pitch, double roll,
    double yawRate, double pitchRate, double rollRate,
    double yawAcc, double pitchAcc, double rollAcc
) {
    /* 创建新节点 */
    MissileNode* newNode = (MissileNode*)malloc(sizeof(MissileNode));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed for new missile data!\n");
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
void printMissileList(const MissileStateList* list) {
    printf("===== Missile State List [Count: %d] =====\n", list->count);
    MissileNode* current = list->head;
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
MissileNode* findMissileByTime(const MissileStateList* list, double time) {
    MissileNode* current = list->head;
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
void deleteMissileByTime(MissileStateList* list, double time) {
    MissileNode *current = list->head, *prev = NULL;
    
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
    printf("No missile data found at time %.2fms\n", time);
}

/**
 * @brief 清空导弹状态链表
 */
void clearMissileList(MissileStateList* list) {
    MissileNode* current = list->head;
    while (current != NULL) {
        MissileNode* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
}