#include <xc.h>
#include "Dew_Sensor.h"

void PIC12F1840_Init(void)
{
	STB = 1;
	T_STB = 0;
	CLK = 1;
	T_CLK = 0;
	DIN = 1;
	T_DIN = 0;
}

void setup(void)
{
	OSCCON = 0b11110000;	// ��������Ϊ8MHz, ʹ��PLL(��Ƶ)
	// ���� ADC
	ANSELAbits.ANSA4 = 1;	// ����ģ���������� A0
	ADCON1 = 0x50;			// �������룬FOSC/16���ο���ѹΪVDD
	INTCONbits.GIE = 1;		//�����ж�
	INTCONbits.PEIE = 1;	//�������ж�
	PIE1bits.ADIE = 1;		// ���� ADC �ж�
	PIR1bits.ADIF = 0;		// ���� ADC �жϱ�־
	ADCON0bits.GO = 0;		// ��ʼ�� AD ת��
	ADCON0bits.ADON = 1;	// ���� AD ת����
}

void TM1620_Init(void)				// ��ʼ��
{
	TM1620Sencmd(GRID6_SEG8);		// ������ʾģʽ��6λ8��ģʽ
	TM1620Sencmd(AddrAutoAdd);		// ��������������õ�ַ�Զ���1ģʽ 0X40
    TM1620Sencmd(Addr00H);			// ���õ�ַ��00H��ʼ
	__delay_us(5);
} 

