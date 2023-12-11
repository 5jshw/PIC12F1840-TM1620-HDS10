#include <xc.h>
#include "Dew_Sensor.h"

const int CODE[10]={0x3F,0x06,0x5b,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};		// ���������
unsigned long currentResistance;		// NTC��̬����ֵ

void main(void)
{
	PIC12F1840_Init();
	TM1620_Init();
	setup();				// ADת����ʼ����������
    __delay_ms(1000);		// ������
	while(1)
	{
		ADsensing();		// ��������, ADת��
		__delay_ms(100);	// ��ʱһ��ʱ�䣬����AD����Ƶ��
		TM1620_Dis();
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
	unsigned long voltageValue;			// NTC��ѹֵ
	unsigned long ADValue = 0;			// ad1 NTC
	ADValue = getADCValue(0x03);		// AN3
	ADValue = 1024 - ADValue;			// ����NTCλ�ڲ��µ�·�¶ˣ������¶�����ʱ����ѹ�½���������������ˣ���ADֵ����
	voltageValue = ADValue * 500 / 1024;		// ת���ɵ�ѹֵ
	currentResistance = (unsigned long)(500 - voltageValue) * 10000 / voltageValue;		// ����NTC��ǰ�Ķ�̬����ֵ
}

void __interrupt() ISR(void)	// �жϴ�����
{
	if(PIR1bits.ADIF == 1)		// ���AD�Ƿ����ж�
	{
		PIE1bits.ADIE = 0;		// ��ֹ�жϷ���
		PIR1bits.ADIF = 0;		// ����жϱ�־
		
		//�жϳ���
		
		PIE1bits.ADIE = 1;		// һ���ж�ִ����ϣ������жϼ�������
	}
}

