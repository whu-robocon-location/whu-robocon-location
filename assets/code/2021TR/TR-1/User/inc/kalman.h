#ifndef __KALMAN_H__
#define __KALMAN_H__

typedef struct KALMAN
{
    double Q;       //����������Э����
    double R;       //�۲�������Э����
    
    double x_last;  //�ϴε�����ֵ�����β���ֵ����������ֵ
    double p_last;  //�ϴ�Э�������Ԥ��Э�������Э����
    
    double kg;      //kalman����
    
    double A;       //ϵͳת�ƾ���
    double H;       //�۲�ת�ƾ���   
		
    double best;

}KALMAN_filter;


extern KALMAN_filter   kalman_Encoder1;
extern KALMAN_filter   kalman_Encoder2;
extern KALMAN_filter   kalman_Vx;
extern KALMAN_filter   kalman_Vy;
extern KALMAN_filter   kalman_Vw;
extern KALMAN_filter   kalman_Accelerate;
extern KALMAN_filter   kalmanVx;
extern KALMAN_filter   kalmanVy;
extern KALMAN_filter   kalmanVw;
extern KALMAN_filter   kalmanAccelerate;

void  kalman_init(KALMAN_filter* kalman);
double KAL_filter(KALMAN_filter *kalman,double input);

#endif

