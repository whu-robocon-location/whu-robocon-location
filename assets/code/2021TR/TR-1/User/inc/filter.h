#ifndef FILTER_H_
#define FILTER_H_

#include "stm32f4xx.h"

#define SAMP_RATE 1000  // 1200 //����Ƶ��(Hz)
#define CUTOFF_RATE \
    50                     // 50
                           // //��ֹƵ��,ʵ�ʽ�ֹƵ��Ϊ100Hz
#define pi 3.14159265359   //Բ����
#define SAMP_TIME 0.0001005 /*��������(s)*/
#define SCALE 0.0127       /*(1000*5)/(65535*6)*(N-ZERO_POinT)*/
#define MAX_NUM 5 /*ð�����������ݵ���Ŀ*/
#define MAX_ZP_SAMPLE 2000
#define ZERO_THREDHOLD  (float)(44.788452)
//(float)(315.406) /*���ǰ�����β����ľ���ֵС����ֵ�����ô����ݸ������*/
//#define			THETA			0.65
///*һ�׵�ͨ�˲�ϵ��*/

/*�����˲��ṹ�嶨��,ȥ����ֵ��ƽ��*/

/*�����˲��ṹ�嶨��*/
typedef struct tag_comb_filter4 {
    u32 max;
    u32 min;
    double average;
    double sum;
    unsigned char comb_filter_flag;
    u32 data[MAX_NUM];
} comb_filter;

/*�ݹ��˲���*/
typedef struct IIR {
    float last;  //��һʱ���˲����ֵ
    float now;   //��һʱ���˲����ֵ
    float a;     //��ͨ�˲�ϵ��
} IIR_struct;

typedef struct tag_k_filter {
    int32_t A; /*ϵͳ״̬ת�ƾ���*/
               //	float B;						/*������������о���*/
    int32_t H; /*�۲�����о���*/
    /*ǰ��������Ϊϵͳ�Ĳ������󣬼�������Ѿ�������ֱ�Ӵ��룬����������̲��ô˾��󣬽�����¼��*/

    float C;      /*Ԥ�����Э�������     C(k|k)  */
    float C_last; /*�ϴ�Ԥ�����Э������� C(k|k-1)*/
    float Q;      /*��������*/
    float R;      /*�۲�����*/

    float X;          /*ϵͳ״̬�˲���������о���*/
    float X_last;     /*ϵͳ״̬Ԥ������о���*/
    float kg;         /*���������棬�о���*/
    float zero_point; /*kalman filter zero_point*/
    float input;      /*����ֵ����Z(k)*/
} k_filter;

/*���׵�ͨ�˲����ṹ��*/
typedef struct tag_second_order {
    unsigned int fs;  //����Ƶ��(Hz)
    unsigned int f0;  //��ֹƵ��,ע��Ҫ��2����ʵ�ʵĽ�ֹƵ(Hz)
    float den;
    float den_ac;
    float den_b;
    float a;                 // x[n]ϵ��
    float b;                 // y[n-1]ϵ��
    float c;                 // y[n-2]ϵ��
    float current_output;    // y[n]
    float last_output;       // y[n-1]
    float last_last_output;  // y[n-2]
} second_order_struct;

extern float kal_input;
extern float IIR_input;
extern float kal_output;
extern float sec_output;
extern float second_order_exkalman_output;
extern float cha;
extern float point;  ///////////////�����ԣ��Ժ����Ҫȥ��

extern k_filter kal_filter;
extern k_filter EXkal_filter;
extern second_order_struct second_order_flt;
extern comb_filter comb_flt;
extern IIR_struct IIR_flt;
static double exkalman_filte_b;

void IIR_init(IIR_struct* IIR_flt);
double IIR_filter(IIR_struct* IIR_flt, double input);
/*
 * 		kalman�˲�����ʼ��
 *		k1_flt: һ��kalmanָ��
 */
extern void kal_flt_init(k_filter* k_flt);
/*
 * 		kalman�˲�����ʼ��
 *		k1_flt: һ��kalmanָ��
 */
extern float kalman_filter(k_filter* k_flt, float input);
void second_order_init(second_order_struct* second_struct);
double second_order_filter(second_order_struct* second_struct, double input);
double second_order_exkalman_filter(k_filter* k_flt,
                                    second_order_struct* second_struct,
                                    double input);
void EXkal_flt_init(k_filter* EXk_flt);
/*
 * 		����˲���
 *		comb_flt: comb_filter ָ��
 */
double combination_filter(comb_filter* comb_flt);

#endif
