#include "main.h"


/************************************UCOSII��������************************************/

/************************************START����************************************/
#define START_TASK_PRIO      			14 //��ʼ��������ȼ�����Ϊ���
#define START_STK_SIZE  				1024
OS_STK START_TASK_STK[START_STK_SIZE];                                                                 
void start_task(void *pdata);		   
/************************************Angle����************************************/
#define ANGLE_TASK_PRIO       			9
#define ANGLE_STK_SIZE  		    		1024
OS_STK ANGLE_TASK_STK[ANGLE_STK_SIZE];
void ANGLE_task(void *pdata);
unsigned short ANGLE_FLAG = 0;
/************************************POSI����************************************/
#define POSI_TASK_PRIO       			10 
#define POSI_STK_SIZE  		    		1024
OS_STK POSI_TASK_STK[POSI_STK_SIZE];
void POSI_task(void *pdata);
u16 RST_flag = 0;		//�����Ǹ�λ�ź�
/************************************TRANS����************************************/
#define TRANS_TASK_PRIO       			11 
#define TRANS_STK_SIZE  		    		1024
OS_STK TRANS_TASK_STK[TRANS_STK_SIZE];
void TRANS_task(void *pdata);
unsigned short TRANS_FLAG = 0;
/************************************LED����************************************/
#define LED_TASK_PRIO       			12
#define LED_STK_SIZE  		    		1024
OS_STK LED_TASK_STK[LED_STK_SIZE];
void LED_task(void *pdata);
unsigned short LED_FLAG = 0;
u8 CANTransSuccess_flag = 0;	//���ݷ��ͳɹ��ź�

int main(void) 
{
	SystemInit();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
	led_config();										//��ʼ�� LED ����
	usart1_init(); 										//��ʼ������1
	kal_flt_init(&kal_filter);							//�������˲����ṹ���ʼ��
	EXkal_flt_init(&EXkal_filter);
	IIR_init(&IIR_flt);									//��ͨ�˲���ʼ��
	second_order_init(&second_order_flt);				//���׵�ͨ�˲����ṹ���ʼ��
	QEPtime_config();									//tim3&tim5 for encoder��Ϊ�����õ�������ʱ����
	can_init();											//��ʼ�� CAN
	time2_config();
	kalman_init(&kalman_Vx);
	kalman_init(&kalman_Vy);
	kalman_init(&kalman_Vw);
	kalman_init(&kalman_Accelerate);
	
//	Position_Now.X = OO_distance * cos(Angle_OO);
//	Position_Now.Y = OO_distance * sin(Angle_OO);
	
	OSInit();   
 	OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO );//������ʼ����
	OSStart();	
	
  return 0;
}


void start_task(void *pdata)
{
    OS_CPU_SR cpu_sr=0;
	  pdata = pdata; 
	  OS_CPU_SysTickInit();
	
  	OS_ENTER_CRITICAL();			//�����ٽ���(�޷����жϴ��)  
  
    OSTaskCreate(ANGLE_task, NULL, (OS_STK*)&ANGLE_TASK_STK[ANGLE_STK_SIZE-1], ANGLE_TASK_PRIO);
    OSTaskCreate(POSI_task, NULL, (OS_STK*)&POSI_TASK_STK[POSI_STK_SIZE-1], POSI_TASK_PRIO);
	  OSTaskCreate(TRANS_task, NULL, (OS_STK*)&TRANS_TASK_STK[TRANS_STK_SIZE-1],TRANS_TASK_PRIO);
	  OSTaskCreate(LED_task, NULL, (OS_STK*)&LED_TASK_STK[LED_STK_SIZE-1], LED_TASK_PRIO); 				   
	  OSTaskSuspend(START_TASK_PRIO);	//������ʼ����.

	  OS_EXIT_CRITICAL();				//�˳��ٽ���(���Ա��жϴ��)
} 

void ANGLE_task(void *pdata){
	while(1)	
	{
		CountAngel();
		OSTimeDly(1);
	}

}

void POSI_task(void *pdata){
    while(1)
    {
        if(ANGLE_FLAG >= 1)
        {
            ANGLE_FLAG--;
            if(init_flag == 1)													//��λ��ʱ��init_flag==0
            {
                CountPosition();				//1ms����һ����������
				        CountSpeed();
				        TRANS_FLAG++;
                LED_FLAG++;
            }
            else																//��λ״̬(��λʱ�������ݾ�ֹ2.25s����)
            {
                if(RST_flag == 1)												//��λ�������ź�
                {
                    can_init();													//�������� CAN
                    RST_flag = 0;
                }
                TIM3->CNT = 0x7fff;
                TIM5->CNT = 0x7fff;
            }
        }
    	OSTimeDly(1);
	}
}

void LED_task(void *pdata){
    while(1)
    {
        if(LED_FLAG>= 5)						//LED��˸����(��ֵ) X 5ms
        {
            LED_FLAG = 0;
            if(CANTransSuccess_flag == 0)		   		 //CAN��������ɹ����̵���˸
            {
                LED_GREEN_TOGGLE();
                LED_RED_OFF();
            }
            else										//���ݷ���ʧ�ܣ������˸
            {
                LED_RED_TOGGLE();
                LED_GREEN_OFF();
				CAN_DeInit(CAN1);
				can_init();		
            }
        }
		OSTimeDly(1);
	}
}

void TRANS_task(void *pdata){
    while(1)
    {
        if(TRANS_FLAG >= 1)	//���� 229.76us
        {
            TRANS_FLAG--;					//�Դ˶�ʱ�����ƽ���ٶ�
			CANTransSuccess_flag = Position_Send(&Position);			//������������
            OSTimeDly(1);
            Speed_Send(&Speed_Now);			                     		//�����ٶ�����
		}
    	OSTimeDly(1);
	}
}
