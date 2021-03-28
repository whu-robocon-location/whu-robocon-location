#ifndef __ADS1255_H__
#define __ADS1255_H__

#ifndef _ADS1255_CONFIG_H
#define _ADS1255_CONFIG_H

#define u8 unsigned char
#define u16 unsigned short
#define u32 unsigned int
	
/*ADS1255 Register Address*/
#define  STATUS  0x00            	//״̬�Ĵ���
#define  MUX     0x01             //ģ���·ѡ��Ĵ���
#define  ADCON   0x02            //AD���ƼĴ���  
#define  DRATE   0x03             //AD�����ٶȼĴ���
#define  IO   	 0x04            	//I/O���ƼĴ���
#define  OFC0    0x05           	//
#define  OFC1    0x06
#define  OFC2    0x07
#define  FSC0    0x08
#define  FSC1    0x09
#define  FSC2    0x0A


/*Command Definition*/

#define WAKEUP    0x00
#define RDATA    	0x01            	//���ζ�ȡ����
#define RDATAC   	0x03            	//������ȡ����
#define SDATAC   	0x0f            	//ֹͣ������ȡ����
#define RREG     	0x10            	//�ӼĴ����ж�ȡ����  0x1x
#define WREG     	0x50             	//��Ĵ�����д������  0x5x
#define SELFCAL   0xf0             	//��������������У׼
#define SELFOCAL  0xf1             	//��������У׼
#define SELFGCAL  0xf2             	//��������У׼
#define SYSOCAL   0xf3             	//ϵͳ����У׼
#define SYSGCAL   0xf4             	//ϵͳ����У׼
#define SYNC      0xfc             	//ʹADת��ͬ��
#define STANDBY   0xfd             	//��������ģʽ
#define Reset     0xfe             	//��������ֵ
#define WAKEDOWN    0xff            //�������˳�����ģʽ

#define ClrAD_CS        GPIO_ResetBits(GPIOC,GPIO_Pin_6)             	//0 PC6��λ
#define ClrAD_DIN 			GPIO_ResetBits(GPIOB,GPIO_Pin_15)             //             
#define ClrAD_DOUT			GPIO_ResetBits(GPIOB,GPIO_Pin_14)             //
#define Read_DRDY			  GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_12)             //��DRDY�ܽ�״̬��Ϊ0ʱ����ת�����������Զ�����


#define SetAD_DIN 		  GPIO_SetBits(GPIOB,GPIO_Pin_15)             	//1             
#define SetAD_CS        GPIO_SetBits(GPIOC,GPIO_Pin_6)             		//                  
#define SetAD_DOUT			GPIO_SetBits(GPIOB,GPIO_Pin_14)            		//

#endif

void ADS1255_config(void);
u32 Read_AD_Value(void);
#endif
