#ifndef __TRAJECTORY_DATA_H
#define __TRAJECTORY_DATA_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct trajectory
{
    uint32_t time;
    double longitude;         /* ���ȣ���λ���ȣ� */
    double latitude;          /* γ�ȣ���λ���ȣ� */
    double altitude;          /* ���θ߶ȣ���λ���ף� */
    double accelerationX;     /* X����ٶȣ���λ����/��2�� */
    double accelerationY;     /* Y����ٶȣ���λ����/��2�� */
    double accelerationZ;     /* Z����ٶȣ���λ����/��2�� */
    double velocityX;         /* X���ٶȣ���λ����/�룩 */
    double velocityY;         /* Y���ٶȣ���λ����/�룩 */
    double velocityZ;         /* Z���ٶȣ���λ����/�룩 */
    double yawAngle;          /* ƫ���Ƕȣ���λ���ȣ� */
    double pitchAngle;        /* �����Ƕȣ���λ���ȣ� */
    double rollAngle;         /* ����Ƕȣ���λ���ȣ� */
    double yawRate;           /* ƫ�����ٶȣ���λ����/�룩 */
    double pitchRate;         /* �������ٶȣ���λ����/�룩 */
    double rollRate;          /* ������ٶȣ���λ����/�룩 */
    double yawAcceleration;   /* ƫ���Ǽ��ٶȣ���λ����/��2�� */
    double pitchAcceleration; /* �����Ǽ��ٶȣ���λ����/��2�� */
    double rollAcceleration;  /* ����Ǽ��ٶȣ���λ����/��2�� */
} TrajectoryData;

#define ALTITUDE_DELTA 1000

uint32_t getCurrentTime(uint32_t tick_counter); /* ��ȡ��ǰʱ�� */

uint8_t getCurrentStep(uint32_t tick_counter, uint32_t index ); /* ��ȡ��ǰ�׶� ����ǰ�� 5���� */

#endif
