#include "usart1.h"
#include "analysis_data.h"


/*���ں������ڵ�����ʱʹ�ã��ڳ�����can��ͨ��*/



//UART_SEND 	u1_send;
u8 dbg_show_enable = 1;
uint8_t aTxBuffer[50] = {0};
QueueTypeDef TxBuffer;

u8 HEAD_FLAG = 0;
u8 RX_FLAG = 0;
short Data_len = 2;
u8 Data_Yesense[98] = {0x59, 0x53};
int res = 0;

void usart1_init(void)     //����1��ʼ������
{
	DMA_InitTypeDef   DMA_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);  //ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE); //ʹ��USART1ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);  //����PA9����ΪUSART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //����PA10����ΪUSART1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&GPIO_InitStructure);         // ��ʼ��PA9, PA10
	
	USART_InitStructure.USART_BaudRate = 115200;//460800;       //������115200
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;  //�ֳ�Ϊ8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;       //һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;          //����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;   //�շ�
	USART_Init(USART1, &USART_InitStructure);              //��ʼ������1
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);			//���������ж�
	
	DMA_DeInit(DMA2_Stream7);
	//* Configure DMA Initialization Structure 
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable ;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single ;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                         //DMA_MODE_NORMAL
	DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t)(&(USART1->DR)) ;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
	//Configure Tx DMA
	DMA_InitStructure.DMA_BufferSize = 0;
	DMA_InitStructure.DMA_Channel = DMA_Channel_4 ;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral ;
	DMA_InitStructure.DMA_Memory0BaseAddr =(uint32_t)aTxBuffer;
	DMA_Init(DMA2_Stream7,&DMA_InitStructure);
	
	DMA_ITConfig(DMA2_Stream7, DMA_IT_TC, ENABLE);  
	//����USARTΪDMA����
	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
	//����NVIC
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;          
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//2;  //��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//2;        //��Ӧ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //ʹ��IRQͨ��
	NVIC_Init(&NVIC_InitStructure);                           //����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream7_IRQn;          
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           
	NVIC_Init(&NVIC_InitStructure);   
	
	USART_Cmd(USART1, ENABLE);   //ʹ��USART
}


/**
 * @function    : 
 * @Description : ���ڷ��ʹ�����,�����������Ƿ���δ��������
**/
void USART_TxHandler(void)
{
	uint8_t i = 0,j = 0,data;
	j = GetQueueLength(&TxBuffer);
	if (j > 20) j = 20;
	else if (j == 0) return;
	for (i = 0; i < j; i++)
	{
			DeQueue(&TxBuffer,&data);
			aTxBuffer[i] = data;
	}
	DMA_SetCurrDataCounter(DMA2_Stream7,j);
	DMA_Cmd(DMA2_Stream7, ENABLE);  
}

void DMA2_Stream7_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA2_Stream7,DMA_IT_TCIF7) != RESET)
	{
		DMA_ClearITPendingBit(DMA2_Stream7,DMA_IT_TCIF7);
		USART_TxHandler();
	}
}


//���ڸĽ���printf()
void USART1_printf(const char *fmt, ...)
{	
	va_list ap;
	uint16_t len;
	uint8_t buf[128];
	va_start(ap, fmt);
	len = vsprintf((char *)buf, (char *)fmt, ap);
	va_end(ap);	/*�ÿɱ�����б�vsprintf������Ҫ������ַ�����ʽ����������ͻ�����*/
	while (len >= (50 - GetQueueLength(&TxBuffer)));/*���������������̫��Ļ���Ҫ��һ��*/
	USART1_sendData(buf,len);
}

void USART1_sendData(u8 *a,u8 count)
{
	uint8_t i = 0,j = 0,data;
	for (i = 0; i < count; i++)
	{
		EnQueue(&TxBuffer,a[i]);
	} 	
	if (DMA_GetCurrDataCounter(DMA2_Stream7) == 0)
	{
		j = GetQueueLength(&TxBuffer);
		if (j > 50) j = 50;
		for (i = 0; i < j; i++)
		{
			DeQueue(&TxBuffer,&data);
			aTxBuffer[i] = data;
		}
		DMA_SetCurrDataCounter(DMA2_Stream7,j);
		DMA_Cmd(DMA2_Stream7, ENABLE);  
	}
}

////��������
//u8 USART_RX_BUF[12] = {0};
//bool flag_rx_start = false;
//short rx_num = 0;
//double Angular_Velocity = 0.0;		//���ٶ�
//typedef unsigned int u32 ;
//int j = 0;
//u8 temp;	
//unsigned short sum = 0;
//int Cal_temp = 0;
//short s ;
//char *ps ;      
//char *pret ;
//int num_loss = 0;

//void USART1_IRQHandler(void)
//{	
//	int i = 0;
//	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)	
//	{
//		USART_ClearFlag (USART1,USART_FLAG_RXNE);			
//		USART_ClearITPendingBit(USART1,USART_IT_RXNE);	
//		
//		temp = USART_ReceiveData(USART1);
//	//	USART_SendData(USART2,temp);
//		if(!flag_rx_start)		
//		{
//			if(temp == 0xDD)
//				flag_rx_start = true;
//		}
//		else			//��ʼ����
//		{
//			USART_RX_BUF[rx_num] = temp;
//			rx_num++;
//			if(rx_num >= 7)
//			{
//				flag_rx_start = false;
//				rx_num = 0;
//				sum = 0;
//				for(i = 0; i < 3; i++)
//					sum+=USART_RX_BUF[i];
//				//if(((sum & 0xFF00)>>8)==USART_RX_BUF[5] && (sum & 0x00FF)==USART_RX_BUF[6])		//У��ͼ�����ȷ
//				if(sum == ((USART_RX_BUF[5] << 8) | USART_RX_BUF[6]))
//				{
//					
//					//���ٶ� USART_RX_BUF[1]�Ǹ�λ�ֽڣ�USART_RX_BUF[0]�ǵ�λ�ֽڣ�USART_RX_BUF[2]����λ�ֽ�
//					//��USART_RX_BUF[1]������չΪ�����ֽڣ���ps[1],ps[0]

//					signed char *cc = (signed char*)(&USART_RX_BUF[1]);
//					s = (short)cc[0];
//					ps = (char *)&s;
//					pret = (char *)&Cal_temp;
//										
//					pret[0] = USART_RX_BUF[0];
//					pret[1] = USART_RX_BUF[2];
//					pret[2] = ps[0];      
//					pret[3] = ps[1]; 
//					
//					Angular_Velocity = Cal_temp*2500.0/8388608.0;
//					
////					VS4Channal_Send((int16_t)(Angular_Velocity*1000),0,0,0);
////					VS4Channal_Send(0,0,0,0);
////					USART_SendData(USART2,(uint16_t)(Angular_Velocity*1000));
//				
//					if(j<MAX_NUM)	
//					{
//						comb_flt.data[j]= Angular_Velocity;
//						j++;
//					}
//					 if(j == MAX_NUM)
//					{
//						j = 0;
//				          comb_flt.comb_filter_flag = 2;
//					}
//			
//				}
//				else num_loss++;
//			}
//		}
//	}
//}

u8 USART_RX_BUF[32];     //���ջ���,���32���ֽ�.
//����״̬
//bit7��������ɱ�־
//bit6�����տ�ʼ��־
//bit5�����յ�0x0d
//bit4~0�����յ�����Ч�ֽ���Ŀ
u8 USART_RX_STA=0;       //����״̬���	
int flag1 = 0;
int flag2 = 0;
void USART1_IRQHandler(void)
{
	u8 temp;
	
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)	//���ռĴ����ǿ�
	{
		USART_ClearFlag (USART1,USART_IT_RXNE);			//����жϱ�־
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);	
				
		temp = USART_ReceiveData(USART1);
		
		if(RX_FLAG == 1)
		{
			Data_len++;
			Data_Yesense[Data_len-1] = temp;
			if(Data_len>97)					//������Χ
			{
				Data_len = 2;
				RX_FLAG = 0;
			}
		}
					
		if(HEAD_FLAG == 1)
		{
			if(temp == 0x53)				//֡ͷ2
			{
				Data_len-=2;
				res = analysis_data(Data_Yesense, Data_len);
				Data_len = 2;
				RX_FLAG = 1;
				HEAD_FLAG = 0;   
			}
			else if(temp != 0x59)			
				HEAD_FLAG = 0;
		}
		if(temp == 0x59)					//֡ͷ1
			HEAD_FLAG = 1;
			
			if((USART_RX_STA&0x40)!=0)//�����Ѿ���ʼ
			{			
				if((USART_RX_STA&0x80)==0)//����δ���
				{
					if(USART_RX_STA&0x20)//�ѽ��յ���0x0d
					{
						if(temp!=0x0a)
							USART_RX_STA=0;//���մ���,���¿�ʼ
						else 				
								USART_RX_STA|=0x80;	//���������														
					}
					else //��û�յ�0X0D
					{	
						if(temp==0x0d)
							USART_RX_STA|=0x20;
						else
						{
							USART_RX_BUF[USART_RX_STA&0X1F]=temp;
							USART_RX_STA++;
							if((USART_RX_STA&0X1F)>31)USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
						}		 
					}
				}  		
			}
			else if(temp=='#')		//���յ���ͷ
				USART_RX_STA|=0x40;	
			
			if((USART_RX_STA&0x80)!=0)			//�����Ѿ���ɣ���������ָ��
			{
			
				//flag1 = 1;
			}
	}
}








/////******�����ø�������************/
////void usart1_sendU16(u16 data)		
////{
////	u16 temp =  data;
////	int i;
////	u8 temp1[7]={'\n','\r',0,0,0,0,0};
////	for(i=0;i<5;i++)
////	{
////		temp1[i+2]=temp%10+0x30;
////		temp = temp/10;
////	}
////	for(i=6;i>=0;i--)
////	{
////		
////	}
////}

//////��ȷ��С�����1λ���������ֲ�����4λ
//void usart1_sendFloatX10(float data)		
//{
////	s16 temp =  data*10;
//	s16 temp =  data;
//	int i;
//	u8 temp1[9]={0,0,0,0,0,0,0,' ',' '};

//	for(i=6;i>=0;i--)
//	{
//		temp1[i]=temp%10+0x30;
//		temp = temp/10;
//	}
//	USART1_sendData(temp1,9);		
//}

//int fputc(int ch,FILE*f)
//{
//	USART_SendData(USART1,(unsigned char) ch);
//	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
//	return(ch);
//}
void USART2_MyInit()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��USART2ʱ��
//	USART_DeInit(USART1);	//���ڸ�λ
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //PA2 ����Ϊ USART2
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA2 �� GPIOA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //�ٶ� 50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ�� PA2��PA3
	
	//���ڲ�����ʼ��	
	USART_InitStruct.USART_BaudRate=115200;	//����������
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;	//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStruct.USART_StopBits=USART_StopBits_1;	//һ��ֹͣλ
	USART_InitStruct.USART_Parity=USART_Parity_No;	//��żУ��λ
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;	//��Ӳ������������
	USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;	//�շ�ģʽ
	USART_Init( USART2,&USART_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=3 ; 	//��ռ���ȼ� 3
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 4; 	//�����ȼ� 3
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE; 	//IRQ ͨ��ʹ��
	NVIC_Init(&NVIC_InitStruct); 	//�ж����ȼ���ʼ��
	
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//�����ռĴ����ǿ�ʱ�������ж�read register not empty(һ�����ݾͿ��жϣ�yi)
	USART_Cmd(USART2,ENABLE);
	
}

/*�����յ��ӵ��Է����������ݣ��ѽ��յ������ݱ����� USART_RX_BUF ��
ͬʱ�ڽ���״̬�Ĵ�����USART_RX_STA���м������յ�����Ч���ݸ���*/

u8 USART_RX_STA2=0;	//�����ڽ���״̬�Ĵ�����1~6λ��������7λ��1��ʾ���յ���#������8λ��1��ʾ
u8 USART_RX_BUF[32];//��������
u16 len;

/*�涨����������#��ʼ���س�����*/

void USART2_IRQHandler()	//���� 1 ���ж���Ӧ����
{
	u8 temp;
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)//���ռĴ����ǿ�read register not empty
	{
		USART_ClearFlag(USART2,USART_IT_RXNE);
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
		
		temp=USART_ReceiveData(USART2);//��ȡ���յ�������
		
 /*2*/	if((USART_RX_STA2 & 0x40) != 0) //����7λΪ1�������յ���#����
        {
 /*5*/      if((USART_RX_STA2 & 0x80) == 0)	//USART_RX_STA��ʾ����δ���
            {
 /*4*/          if(temp == 0x0d)//�س�ASCII�룬���յ��س�
                    USART_RX_STA2 |=0x80; //������ݽ��գ���USART1_RX_STA��bit[15]��1
 /*3*/          else 
                {
                    USART_RX_BUF[USART_RX_STA2 & 0X3F] = temp;
                    USART_RX_STA2++;
					len++;
                    if((USART_RX_STA2 & 0X3F) > 31)	//ע��USART_RX_STA����λΪ���λ��������Ч����Ϊ��6λ
                        USART_RX_STA2 = 0; 
                }
            }
        }
 /*1*/  else if(temp == '#') 
        {
		int i;
		USART_RX_STA2 |= 0x40;	//���USART1_RX_STA��7λ��1
		for(i = 0; i < 32; i++)	//�������		
		USART_RX_BUF[i] = 0x00;
         }
 				
 /*6*/	 if((USART_RX_STA&0x80)!=0)		//��������ȫ���͵���������������ת�ʹ���		VS4Channal_Send(0,0,0,0);	
		{		
			int i;
			for(i=0;i<len;i++)
			{
				USART_SendData(USART2,USART_RX_BUF[i]);
				while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);
				
			}
			USART_RX_STA2=0;//������
			len = 0;
		} 
		}
	
}
