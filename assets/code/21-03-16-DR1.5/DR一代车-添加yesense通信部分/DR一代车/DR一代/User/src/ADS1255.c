#include "main.h"
u32 count6;
u8 status = 0, mux = 0, adcon = 0, drate = 0, io = 0;

u8 Read_Reg(u8 address)
{
    u8 data = 0;
    SPI2_WriteByte(RREG | address);
    SPI2_WriteByte(0x00);
    delay_us(20);
    data = SPI2_ReadByte(0x00);

    return    data;
}

void Write_Reg(u8 address, u8 data)
{
    SPI2_WriteByte(WREG | address);
    delay_us(5);
    SPI2_WriteByte(0x00);                 //д��һ���Ĵ���
    SPI2_WriteByte(data);
}

uint8_t ADS1256_ReadChipID(void)
{
    u8 data = 0, id = 0;
    data = Read_Reg(STATUS);
    id = (data >> 4);

    return id;
}

void Reg_Configuration(void)   //ADS1255�Ĵ������ó�ʼ��
{

//    for(count6 = 0; count6 < 10000; count6++)
//    {
        SPI2_WriteByte(WREG | STATUS);
        SPI2_WriteByte(0x04);                 //д��5���Ĵ���
        SPI2_WriteByte(0xF5);
        SPI2_WriteByte(0x01);
        SPI2_WriteByte(0x01);
        SPI2_WriteByte(0xE0);       //15K
        SPI2_WriteByte(0x00);
}
//	delay_ms(1);
void Reg_out(void)
{
        //�����Ĵ����ĸ���ֵ���Ƿ�д��


        SPI2_WriteByte(RREG | STATUS);
        SPI2_WriteByte(0x04);
        delay_us(12);
        SPI2_ReadByte(0x00);
        status = SPI2_ReadByte(0x00);
        mux = SPI2_ReadByte(0x00);
        adcon = SPI2_ReadByte(0x00);
        drate = SPI2_ReadByte(0x00);
        io = SPI2_ReadByte(0x00);
    //�Ĵ�����ʼ��ʧ��1s��һ�ε�
    while(((status & 0xf0) != 0x30) || (mux != 0x01) || (adcon != 0x01) || (drate != 0xE0) || (io != 0x00))
    {
        LED_RED_ON();
		  	LED_GREEN_OFF();
        delay_ms(500);
        LED_RED_OFF();
			  LED_GREEN_ON();
        delay_ms(500);
        //1hz
    }
}



//�������
void ADS1255_STANDBY(void)
{
    SPI2_WriteByte(STANDBY);
}

u8 ID = 0;
void ADS1255_config(void)
{

    ClrAD_CS;
    delay_us(1);
    while(Read_DRDY == 1);
    SPI2_WriteByte(Reset);  //��λ
    delay_ms(1);
    ID = ADS1256_ReadChipID();

    Reg_Configuration();   //�Ĵ�����ʼ��
    delay_ms(1);
	  Reg_out();

    SPI2_WriteByte(SYNC);        //ͬ��
    SPI2_WriteByte(WAKEUP);        //����
    delay_ms(10);

    SPI2_WriteByte(SELFCAL);//��У׼
    delay_ms(10);
    SetAD_CS;
}

u32 Read_AD_Value(void)	//��ȡ AD ��ֵ
{
    u32 adc_value = 0;
    u8 adc_h = 0, adc_m = 0, adc_l = 0;
    ClrAD_CS;

    while(Read_DRDY == 1);
    SPI2_WriteByte(RDATA);
    delay_us(7);                               //�����ӳ�Ҫ��ʱ��������������ݻ᲻��

    while(Read_DRDY == 1);
    SPI2_ReadByte(0x00);
    adc_h = SPI2_ReadByte(0x00);
    adc_m = SPI2_ReadByte(0x00);
    adc_l = SPI2_ReadByte(0x00);

    adc_value = (((u32)adc_h) << 16) | (((u32)adc_m) << 8) | ((u32)adc_l);

    SetAD_CS;
    adc_value = (adc_value ^ 0x800000);
    return adc_value;

}

