#ifndef _POSITIONCOUNT_H
#define _POSITIONCOUNT_H

#include "MyMath.h"
#include "filter.h"
#include "stm32f4xx.h"
#include "math.h"
#include "kalman.h"
#include "time2.h"
#include "QEPtime.h"
#include "led.h"
#include "ucos_ii.h"

extern float DeltaCntEncoder10, DeltaCntEncoder20;
extern float DeltaCntEncoder11, DeltaCntEncoder22;

//����ṹ����������
typedef struct pot {
    float X;  //��������������ϵԭ���ڳ�������ϵ�е�X���꣬cm
    float Y;  //��������������ϵԭ���ڳ�������ϵ�е�Y���꣬cm
    float
        AngleDeg;  //�����˵���̬��(��������ϵX��ת����������ϵX��)���Ƕ��ƣ�˳������
    float Sum_Encoder1;  //����1�߹���·��
    float Sum_Encoder2;  //����2�߹���·��
    float Sum_Distance;  //�������߹�����·��

} POSITION;

typedef struct spd {
    float Vx;  //�������ڳ�������ϵX�᷽��ķ��ٶȣ�cm/s
    float Vy;  //�������ڳ�������ϵY�᷽��ķ��ٶȣ�cm/s
    float Vw;  //�����˽��ٶȣ���/s,˳������
    float V;   //�����˵ĺ��ٶ�
} SPEED;

typedef struct correct {
    float real_x;
    float dt_del_x;
    float real_y;
    float dt_del_y;
} CORRECT;

extern float CM_PER_CNT_1;  // 2*pi*Radius_Wheel_1/(4*����������) //��λϵͳX��
extern float CM_PER_CNT_2;  // 2*pi*Radius_Wheel_2/(4*����������) //��λϵͳY��

// extern float CM_PER_CNT_11;		//2*pi*Radius_Wheel_1/(4*����������)
// //��λϵͳX�� extern float CM_PER_CNT_22;
// //2*pi*Radius_Wheel_2/(4*����������) //��λϵͳY��

//����Ĳ���ȡ�������̵İ�װλ��
extern float OO_distance;  //��������ϵԭ���붨λϵͳ����ϵԭ��ľ��룬��λcm
extern float
    Angle_XX;  //��������ϵx��ת��λϵͳ����ϵx��ĽǶȣ������ƣ�˳������
extern float
    Angle_OO;  //��������ϵX��ת����������ϵԭ��ָ��λϵͳ����ϵԭ�����ߵĽǶȣ������ƣ�˳������

//������λ�����ٶ�����
extern POSITION Position_Now;
extern POSITION Position;
extern SPEED Speed_Now;

extern float Gyro_angle_delta;  //���ݽǶ��������Ƕ���
extern float speed_V, speedv;
extern float time;
extern float Accelerated_Speed;

void Position_init(void);
void CountPosition(void);
void CountSpeed(void);
void CountAngel(void);
void GYRO_Reset(void);


#endif
