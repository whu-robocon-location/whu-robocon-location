#ifndef _TIME2_H
#define _TIME2_H

#include "stm32f4xx.h"
#include "filter.h"

#define P ((float)(1))							   //���ݰ�װ��б�ı궨ϵ��

extern u8 init_flag;


void time2_config(void);
//void exti_config(void);
#endif
