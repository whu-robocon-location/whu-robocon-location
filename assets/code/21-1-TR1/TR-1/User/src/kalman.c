#include "kalman.h"
#include "main.h"

KALMAN_filter   kalman_Encoder1;
KALMAN_filter   kalman_Encoder2;
KALMAN_filter   kalman_Vx;
KALMAN_filter   kalman_Vy;
KALMAN_filter   kalman_Vw;
KALMAN_filter   kalman_Accelerate;
KALMAN_filter   kalmanVx;
KALMAN_filter   kalmanVy;
KALMAN_filter   kalmanVw;
KALMAN_filter   kalmanAccelerate;

void kalman_init(KALMAN_filter* kalman)
{
    kalman->x_last=1;
    kalman->p_last=5;     //��������ֵ��ʼ������ν����P��ҪΪ0
    
    kalman->Q=0.0001;     //��������
    kalman->R=0.01; 	  //�۲�����,��ԭʼ�ٶ����ݵķ��������
    kalman->A=1;          //�򻯵�ģ��
    kalman->H=1;
}

double KAL_filter(KALMAN_filter *kalman,double input)
{
    kalman->x_last=kalman->A*kalman->x_last;                //������һ�ε�ֵԤ�Ȿ�ε�ֵ    
    kalman->p_last=kalman->p_last+kalman->Q;                //������һ�ε�Э������㱾�ε�Э����    
    kalman->kg=kalman->p_last/(kalman->p_last+kalman->R);   //���ݱ��ε�Э�������kalman����    
    kalman->x_last=kalman->x_last+kalman->kg*(input-kalman->H*kalman->x_last);//������ε�����ֵ    
    kalman->p_last=(1-kalman->kg)*kalman->p_last;           //������ε�Э����	
	kalman->best=kalman->x_last;    
    return kalman->best;
}

