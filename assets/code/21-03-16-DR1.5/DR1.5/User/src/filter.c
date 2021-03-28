#include "main.h"

k_filter kal_filter;
k_filter EXkal_filter;
second_order_struct second_order_flt;
comb_filter comb_flt;
IIR_struct IIR_flt;
static double exkalman_filte_b;
float kal_input;
float IIR_input;
float kal_output;
float sec_output;
float second_order_exkalman_output;
float cha = 0;
float point = 0;  ///////////////�����ԣ��Ժ����Ҫȥ��

int cmp(const void *a, const void *b) { return *(int *)a - *(int *)b; }
/*
 *
 * 		��ȥ�������Ȼ�󸴺��˲���ʵ�֣��ںϵ�ͨ�˲����޷��˲����޳����ֵ����Сֵ��ʣ��ֵ��ƽ��
 *
 */
// double combination_filter(comb_filter* comb_flt)
//{
//	int i=0;
//	long sum=0;
//	double n=MAX_NUM/2;
////��������ʱ��仯б��,MAX_NUM/2,ȥ�����¶������������ 	double k=0;
////ʱ�����Ư�������������ԣ�������û������
//
//	comb_flt->sum = 0;
//
//	for (i=0 ;i< MAX_NUM/2; i++)
//		sum += (comb_flt->data[i+(int)n]-comb_flt->data[i]);
//	k=(double)sum/(n*n);
//
//	for(i=0;i<MAX_NUM;i++)
//	{
//		comb_flt->data[i]=comb_flt->data[i]-k*(i+1)*0.0001;
//		comb_flt->sum+=comb_flt->data[i];
//	}
//
//	qsort(comb_flt->data,MAX_NUM,sizeof(int),cmp);
//	comb_flt->sum=comb_flt->sum-comb_flt->data[0]-comb_flt->data[MAX_NUM-1];
//	comb_flt->average = (float)(comb_flt->sum/(MAX_NUM-2));

//	comb_flt->comb_filter_flag = 1;
//	return 	comb_flt->average;
//}

double combination_filter(comb_filter *comb_flt)  //���� 44.67us������˲���
{
    int i = 0;

    comb_flt->sum = 0;
    comb_flt->max = comb_flt->data[0];
    comb_flt->min = comb_flt->data[0];
    for (i = 1; i < MAX_NUM; i++) {
        if (comb_flt->max < comb_flt->data[i]) {
            comb_flt->max = comb_flt->data[i];
        }
        if (comb_flt->min > comb_flt->data[i]) {
            comb_flt->min = comb_flt->data[i];
        }
    }
    for (i = 0; i < MAX_NUM; i++) {
        comb_flt->sum += comb_flt->data[i];
    }

    comb_flt->sum = comb_flt->sum - comb_flt->max - comb_flt->min;
    comb_flt->average = (float)(comb_flt->sum / (MAX_NUM - 2));
    comb_flt->sum = 0;
    comb_flt->comb_filter_flag = 1;

    return comb_flt->average;
}

/**
 * @brief �������˲�����ʼ��
 */
void kal_flt_init(k_filter *k_flt) {
    int i = 0;
    /* ϵͳ״̬ת�ƾ��� */
    k_flt->A = 1;
    /* �۲�����о��� */
    k_flt->H = 1;
    /* �ϴ�Ԥ�����Э������� C(k|k-1) */
    k_flt->C_last = 1;
    /* ��ȡ AD ��ֵ */
    for (i = 0; i < MAX_NUM; i++) comb_flt.data[i] = Read_AD_Value();
    /* ϵͳ״̬Ԥ������о��� */
    k_flt->X_last = combination_filter(&comb_flt);

    /* �۲����� */
    k_flt->R = 0.1;
    /* �������� */
    k_flt->Q = 0.00001;
    /* ��ʼ����ֵ, ��Z(k)Ϊ0 */
    k_flt->input = 0;
}

/**
 * @brief ��չ�������˲�����ʼ��
 */
void EXkal_flt_init(k_filter *EXk_flt) {
    int i = 0;
    /* ϵͳ״̬ת�ƾ��� */
    EXk_flt->A = 1;
    /* �۲�����о��� */
    EXk_flt->H = 1;
    /* �ϴ�Ԥ�����Э������� C(k|k-1) */
    EXk_flt->C_last = 1;
    /* ��ȡ AD ��ֵ */
    for (i = 0; i < MAX_NUM; i++) comb_flt.data[i] = Read_AD_Value();
	
    /* ϵͳ״̬Ԥ������о��� */
    EXk_flt->X_last = combination_filter(&comb_flt);
    /* �۲����� */
    EXk_flt->R = 0.011;
    /* �������� */
    EXk_flt->Q = 0.00001;
    /* ��ʼ����ֵ, ��Z(k)Ϊ0 */
    EXk_flt->input = 0;
}

/**
 * @brief kalman filter ��ʵ��
 * �������˲�, ����һ���ͺ��˲� -- ���� 46.26us
 */
float kalman_filter(k_filter *k_flt, float input) {
    /* һ���ͺ��˲�����ò���ֵ, ����ͺ��ǿ��������� */
    // k_flt->input=IIR_filter(&IIR_flt,input);
    /* ���ⷽ�̵ĸ��£�3�鷽�� */
    k_flt->input = input;
    /* ���㿨�������� kg(k) = C(k|k-1)*H(ת��)/[H*C(k|k-1)*H(ת��)+R] */
    k_flt->kg = (k_flt->C_last) / (k_flt->C_last + k_flt->R);
    /* �õ�����״̬�����Ż�����ֵ X(k|k) = X(k|k-1)+kg(k)*[Z(k)-H*X(k|k-1)] */
    k_flt->X = k_flt->X_last + k_flt->kg * (k_flt->input - k_flt->X_last);
    /* ���� k ״̬�� X(k|k) ��Э���� C(k|k) = [I-kg(k)*H]*C(k|k-1) */
    k_flt->C = (1 - k_flt->kg) * (k_flt->C_last);
    /* ���ֵýǶ� */
    // k_flt->output = k_flt->output + k_flt->X*SAMP_TIME;
    /*ʱ����·��̣�2�鷽��*/
    /* ������һ״̬Ԥ����һ״̬�Ľ�� X(k+1|k) = A*X(k|k) û�п����� */
    k_flt->X_last = k_flt->X;
    /* ���� X(k|k-1) ��Э���� C(k+1|k) = A*C(k|k)*A(ת��)+B*Q*B(ת��) */
    k_flt->C_last = k_flt->C + k_flt->Q;

    /* ���ؿ������˲����ֵ */
    return k_flt->X;
}

/**
 * @brief ���׵�ͨ�˲�����ʼ��
 */
void second_order_init(second_order_struct *second_struct) {
    second_struct->fs = SAMP_RATE;
    second_struct->f0 = CUTOFF_RATE;
    second_struct->den =
        (second_struct->fs) * (second_struct->fs) +
        6 * pi * (second_struct->f0) * (second_struct->fs) +
        4 * pi * pi * (second_struct->f0) * (second_struct->f0);
    second_struct->a = 4 * pi * pi * (second_struct->f0) * (second_struct->f0) /
                       (second_struct->den);
    second_struct->b = (2 * (second_struct->fs) * (second_struct->fs) +
                        6 * pi * (second_struct->fs) * (second_struct->f0)) /
                       (second_struct->den);
    second_struct->c =
        (second_struct->fs) * (second_struct->fs) / (second_struct->den);

    //	second_struct->den_ac = (second_struct->fs)*(second_struct->fs) +
    // 6*pi*(second_struct->f0) +
    // 4*(second_struct->fs)*(second_struct->fs)*(second_struct->f0)*(second_struct->f0);
    //	second_struct->den_b = (second_struct->fs)*(second_struct->fs) +
    // 6*pi*(second_struct->f0)*(second_struct->fs) +
    // 4*(second_struct->fs)*(second_struct->fs)*(second_struct->f0)*(second_struct->f0);
    //	second_struct->a 	=
    // 4*pi*pi*(second_struct->f0)*(second_struct->f0)/(second_struct->den_ac);
    //	second_struct->b 	= (2*(second_struct->fs)*(second_struct->fs) +
    // 6*pi*(second_struct->fs)*(second_struct->f0))/(second_struct->den_b);
    //	second_struct->c 	=
    //(second_struct->fs)*(second_struct->fs)/(second_struct->den_ac);
}

/**
 * @brief ���׵�ͨ�˲�����ʼ��
 * ���׵�ͨ�˲� -- ���� 44.58us
 */
double second_order_filter(second_order_struct *second_struct, double input) {
    second_struct->current_output =
        (second_struct->a) * input +
        (second_struct->b) * (second_struct->last_output) -
        (second_struct->c) *
            (second_struct->last_last_output);  //����������˲����
    /* �������ϴ���� */
    second_struct->last_last_output = second_struct->last_output;
    /* �����ϴ���� */
    second_struct->last_output = second_struct->current_output;
    /* ���ر����˲���� */
    return second_struct->current_output;
}

/**
 * @brief ��ͨ�˲���ʼ��
 */
void IIR_init(IIR_struct *IIR_flt) {
    IIR_flt->a = 0.99999;               //��ͨ�˲�ϵ��
    IIR_flt->last = kal_filter.X_last;  //��һʱ���˲����ֵ
}
double IIR_filter(IIR_struct *IIR_flt,
                  double input)  //һ���ͺ��ͨ�˲� -- ���� 45.21us
{
    IIR_flt->now = (1 - IIR_flt->a) * IIR_flt->last +
                   IIR_flt->a * input;  //��һʱ���˲����ֵ
    IIR_flt->last = IIR_flt->now;       //��һʱ���˲����ֵ

    return IIR_flt->now;
}

double second_order_exkalman_filter(k_filter *EXk_flt,
                                    second_order_struct *second_struct,
                                    double input) {
    second_struct->current_output =
        (second_struct->a) * input +
        (second_struct->b) * (second_struct->last_output) -
        (second_struct->c) *
            (second_struct->last_last_output);  //����������˲����
    second_struct->last_last_output =
        second_struct->last_output;  //�������ϴ����
    exkalman_filte_b =
        second_struct->current_output - second_struct->last_output;
    second_struct->last_output = second_struct->current_output;  //�����ϴ����

    //	k_flt->input=IIR_filter(&IIR_flt,input); //һ���ͺ��˲�����ò���ֵ,
    //����ͺ��ǿ���������
    /*���ⷽ�̵ĸ��£�3�鷽��*/
    EXk_flt->input = input;
    EXk_flt->kg = (EXk_flt->C_last) /
                  (EXk_flt->C_last +
                   EXk_flt->R); /*���㿨�������� kg(k) =
                                   C(k|k-1)*H(ת��)/[H*C(k|k-1)*H(ת��)+R] */
    EXk_flt->X =
        EXk_flt->X_last + exkalman_filte_b +
        EXk_flt->kg * (EXk_flt->input - EXk_flt->X_last -
                       exkalman_filte_b); /*�õ�����״̬�����Ż�����ֵ X(k|k) =
                                             X(k|k-1)+kg(k)*[Z(k)-H*X(k|k-1)]*/
    EXk_flt->C = (1 - EXk_flt->kg) *
                 (EXk_flt->C_last); /*���� k ״̬�� X(k|k) ��Э���� C(k|k) =
                                       [I-kg(k)*H]*C(k|k-1) */
    /*���ֵýǶ�*/
    //	k_flt->output = k_flt->output + k_flt->X*SAMP_TIME;
    /*ʱ����·��̣�2�鷽��*/
    EXk_flt->X_last = EXk_flt->X; /*������һ״̬Ԥ����һ״̬�Ľ�� X(k+1|k) =
                                     A*X(k|k) û�п�����*/
    EXk_flt->C_last =
        EXk_flt->C + EXk_flt->Q; /*���� X(k|k-1) ��Э���� C(k+1|k) =
                                    A*C(k|k)*A(ת��)+B*Q*B(ת��)*/

    return EXk_flt->X;  //���ؿ������˲����ֵ
}
