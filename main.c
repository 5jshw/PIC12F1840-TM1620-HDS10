#include <xc.h>
#include "Dew_Sensor.h"

const unsigned char CODE[10]={0x3F,0x06,0x5b,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};		// ���������
unsigned int ADValue = 0;	// ADValue
unsigned char Thousandth = 0, Hundredth = 0, Tenth = 0, Unit = 0;
char ADSValue = 0;
unsigned int AD[5];

void main(void)
{
	PIC12F1840_Init();
	setup();				// ADת����ʼ����������
	//TM1620_Init();
	__delay_ms(500);
	while(1)
	{
		ADsensing();		// ��������, ADת��
		__delay_ms(20);
		Numerical_Partitioning(ADValue);
		__delay_ms(20);
		TM1620_Dis();
		__delay_ms(20);
	}
}

unsigned int getADCValue(unsigned char channel)		// ����ADת������
{
    ADCON0bits.CHS = channel;                               // ѡ��ADͨ��
    __delay_ms(5);                                          // �ı�ADͨ��������ʱ�ȶ�
    ADCON0bits.GO = 1;                                      // ��ʼADת��
    while (ADCON0bits.GO);                                  // ת�����ָʾ
    return (unsigned int)((ADRESH << 2) | (ADRESL >> 6));   // ���ظߵ�λ�ϲ����ADֵ
}

void ADsensing(void)		// ADת��������
{
	if(ADSValue < 5)
	{
		AD[ADSValue] = getADCValue(0x03);
		ADSValue++;
	}
	else
	{
		ADValue = (AD[0] + AD[1] + AD[2] + AD[3] + AD[4]) / 5;
		ADSValue = 0;
	}
}

void __interrupt() ISR(void)	// �жϴ�����
{
	if(PIR1bits.ADIF == 1)		// ���AD�Ƿ����ж�
	{
		PIE1bits.ADIE = 0;		// ��ֹ�жϷ���
		PIR1bits.ADIF = 0;		// ����жϱ�־

		PIE1bits.ADIE = 1;		// һ���ж�ִ����ϣ������жϼ�������
	}
}

void TM1620_Dis(void) //��������
{
	
	TM1620Sencmd(GRID6_SEG8);		// ������ʾģʽ��6λ8��ģʽ
	TM1620Sencmd(AddrAutoAdd);		// ��������������õ�ַ�Զ���1ģʽ 0X40
    TM1620Sencmd(Addr00H);			// ���õ�ַ��00H��ʼ
	__delay_us(5);
	
    TM1620Sendata(CODE[Thousandth]);		// ��00H��ʼ��ż����ַ����ʾ����
    TM1620Sendata(0x00);			// 01H
	TM1620Sendata(CODE[Hundredth]);			// ��00H��ʼ��ż����ַ����ʾ����
    TM1620Sendata(0x00);			// 03H
	TM1620Sendata(CODE[Tenth]);				// ��00H��ʼ��ż����ַ����ʾ����
    TM1620Sendata(0x00);			// 05H
	TM1620Sendata(CODE[Unit]);				// ��00H��ʼ��ż����ַ����ʾ����
    TM1620Sendata(0x00);			// 07H
	__delay_ms(5);
	
	STB = 1;				//��
	__delay_ms(1);
	STB = 0;				//��
	__delay_ms(1);
	TM1620Sencmd(0x8F);		//������ʾ�������ʾ������ռ�ձ�14/16.
	STB = 1;				//��
}

void TM1620Sendata(char TM1620Data)		//����һ���ֽ�
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

void TM1620Sencmd(char com)		//���Ϳ�������
 {
	STB = 1;				// ��
	__delay_ms(1);
	STB = 0;				// ��
	__delay_ms(1);
	TM1620Sendata(com);
 }

void Numerical_Partitioning(unsigned int ADCValue)
{
	Thousandth = ADCValue / 1000;
	Hundredth = ADCValue % 1000 / 100;
	Tenth = ADCValue % 100 / 10;
	Unit = ADCValue % 10;
}