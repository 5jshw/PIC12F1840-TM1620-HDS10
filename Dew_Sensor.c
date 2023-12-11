#include <xc.h>
#include "Dew_Sensor.h"

const int CODE[10]={0x3F,0x06,0x5b,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};  //���������

void PIC12F1840_Init(void)
{
	STB = 1;
	T_STB = 0;
	CLK = 1;
	T_CLK = 0;
	DIN = 1;
	T_DIN = 0;
	JLS = 0;
	T_JLS = 0;
}

void setup(void)
{
	OSCCON = 0b11110000;  // ��������Ϊ8MHz, ʹ��PLL(��Ƶ)
	// ���� ADC
	ANSELAbits.ANSA4 = 1;   // ����ģ���������� A0
	ADCON1 = 0x50;          // �������룬FOSC/16���ο���ѹΪVDD
	PIE1bits.ADIE = 1;      // ���� ADC �ж�
	PIR1bits.ADIF = 0;      // ���� ADC �жϱ�־
	ADCON0bits.GO = 0;      // ��ʼ�� AD ת��
	ADCON0bits.ADON = 1;    // ���� AD ת����
}

void TM1620_Init(void)				// ��ʼ��
{
	TM1620Sencmd(GRID6_SEG8);		// ������ʾģʽ��6λ8��ģʽ
	TM1620Sencmd(AddrAutoAdd);		// ��������������õ�ַ�Զ���1ģʽ 0X40
    TM1620Sencmd(Addr00H);			// ���õ�ַ��00H��ʼ
} 

void TM1620_Dis(void) //��������
{

    TM1620Sendata(CODE[0]);		// ��00H��ʼ��ż����ַ����ʾ����
    TM1620Sendata(0x00);		// 01H
	TM1620Sendata(CODE[1]);		// ��00H��ʼ��ż����ַ����ʾ����
    TM1620Sendata(0x00);		// 01H
	TM1620Sendata(CODE[2]);		// ��00H��ʼ��ż����ַ����ʾ����
    TM1620Sendata(0x00);		// 01H
	TM1620Sendata(CODE[3]);		// ��00H��ʼ��ż����ַ����ʾ����
    TM1620Sendata(0x00);		// 01H
	
	STB = 1;			//��
	__delay_ms(1);
	STB = 0;			//��
	__delay_ms(1);
	TM1620Sencmd(0x8F);				//������ʾ�������ʾ������ռ�ձ�14/16.
	STB = 1;			//��
}

void TM1620Sendata(int TM1620Data) //����һ���ֽ�
{
	char i;
	for(i = 0; i < 8; i++)
	{
		CLK = 0;			// CLK��
		DIN = 1 & (TM1620Data >> i);
		CLK = 1;			// CLK��
		__delay_us(3);
	}
}

void TM1620Sencmd(char com) //���Ϳ�������
 {
	STB = 1;				// ��
	__delay_ms(1);
	STB = 0;				// ��
	__delay_ms(1);
	TM1620Sendata(com);
 }