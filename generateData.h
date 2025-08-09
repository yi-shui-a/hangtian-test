#ifndef __GENERATEDATE_H
#define __GENERATEDATE_H

#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>

// �¼�����
#define SXGB 0x0000
//�����׶�
#define TLJCYQRXH 0x0000 // ���������ȷ���ź�
#define FSTFLXH 0x0001 // ����̨�����ź�

//���ƶ�
#define YJFDJGBZLXH 0x0002 // һ���������ػ�ָ���ź�
#define YJFLJGJSXH 0x0003 // һ��������������ź�
#define EJFDJDHXH 0x0004 // ��������������ź�
#define ZLZFLXH 0x0005 // �����ַ����ź�
#define MZTJGBZLXH 0x0006 // ĩ���Ƽ��ػ�ָ���ź�

//�ж�
#define GXZDXZXH 0x0007 // �����Ƶ������ź�
#define XGZDJZXH 0x0008 // �ǹ��Ƶ�У׼�źţ��߾��ȣ�
#define DTMCJSXH 0x0009 // ��ͷĸ�ս����ź�
#define YESFXH 0x000a // �ն��ͷ�ָ��

//ĩ��
#define ZRZTTZXH 0x000b // ������̬�����ź�
#define MDZDXZXH 0x000c // ĩ���Ƶ������źţ��߾��ȣ�
#define YXBXJSXH 0x000d // ���ű��ս���ź�
#define YBZLXH 0x000e // ����ָ���ź�

/**
 * @brief ����״̬�ṹ��
 * ��������������ʵʱ�˶�״̬�Ϳռ�λ��
 */
typedef struct {
    double time;            /**< ʱ�䣨��λ�����룩 */
    uint16_t event;         /**< �¼����� */

    double longitude;       /**< ���ȣ���λ���ȣ� */
    double latitude;        /**< γ�ȣ���λ���ȣ� */
    double altitude;        /**< ���θ߶ȣ���λ���ף� */
    
    double accelerationX;   /**< X����ٶȣ���λ����/��2�� */
    double accelerationY;   /**< Y����ٶȣ���λ����/��2�� */
    double accelerationZ;   /**< Z����ٶȣ���λ����/��2�� */
    
    double velocityX;       /**< X���ٶȣ���λ����/�룩 */
    double velocityY;       /**< Y���ٶȣ���λ����/�룩 */
    double velocityZ;       /**< Z���ٶȣ���λ����/�룩 */

    double yawAngle;        /**< ƫ���Ƕȣ���λ���ȣ� */
    double pitchAngle;      /**< �����Ƕȣ���λ���ȣ� */
    double rollAngle;       /**< ����Ƕȣ���λ���ȣ� */

    double yawRate;         /**< ƫ�����ٶȣ���λ����/�룩 */
    double pitchRate;       /**< �������ٶȣ���λ����/�룩 */
    double rollRate;        /**< ������ٶȣ���λ����/�룩 */

    double yawAcceleration;   /**< ƫ���Ǽ��ٶȣ���λ����/��2�� */
    double pitchAcceleration; /**< �����Ǽ��ٶȣ���λ����/��2�� */
    double rollAcceleration;  /**< ����Ǽ��ٶȣ���λ����/��2�� */

} DiscretePoint;

// #define M_PI 3.14

#define CURRENT_TIME 0   
#define TIME_STEP_MS 1000     // ��ǰʱ�䣨���룩
#define TOTAL_TIME_MS 40000   // ��ʱ�䣨400 000ms = 400�룩

#define STEP_A 500           // �����׶ν��� ʱ��0.5s 
#define STEP_B 80000           // �����׶ν��� ʱ��80s 
#define STEP_C 380000          // Ѳ���׶ν��� ʱ��380s
#define STEP_D 400000          // �����׶ν��� ʱ��400s

#define TIME_BASE  100 

//uint32_t current_time_ms = 0;       
//uint32_t time_step_ms = 1000;        // ʱ�䲽����1000ms = 1�룩
//uint32_t total_time_ms = 400000;    // ��ʱ�䣨400 000ms = 400�룩
//uint32_t stepA = 60000;                 // �����׶ν��� ʱ��60s 
//uint32_t stepB = 300000;								// ƽ�ɽ׶ν��� ʱ��300s

DiscretePoint simulateMissileEvent(uint32_t time_ms) ;

#endif
