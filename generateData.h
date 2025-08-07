#ifndef __GENERATEDATE_H
#define __GENERATEDATE_H

#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>

// �¼�����
//�����׶�
#define YJDH  0x0000 // һ�����
#define YJFL  0x0001 // һ������
#define EJDH  0x0002 // �������
#define EJFL  0x0003 // ��������
#define DYZK  0x0004 // ����չ��
#define FDGR  0x0005 // ��������
#define ZDJD  0x0006 // �жλ���
#define DTFL  0x0007 // ��ͷ����
#define LDZD  0x0008 // �״��Ƶ�
#define HWZD  0x0009 // �����Ƶ�
#define MBFP  0x000a // Ŀ�����
#define DJJD  0x000b // ����Ƕ�
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

#define CURRENT_TIME 0   
#define TIME_STEP_MS 1000     // ��ǰʱ�䣨���룩
#define TOTAL_TIME_MS 40000   // ��ʱ�䣨400 000ms = 400�룩

#define STEPA 80000           // �����׶ν��� ʱ��60s 
#define STEPB 210000          // Ѳ���׶ν��� ʱ��300s
#define STEPC 400000          // �����׶ν��� ʱ��400s

#define TIME_BASE  100 

DiscretePoint simulateMissileEvent(uint32_t time_ms) ;

#endif
