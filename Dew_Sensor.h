#ifndef DEW_SENSOR_H
#define	DEW_SENSOR_H

// CONFIG1
#pragma config FOSC = INTOSC	// ָ��ʹ���ڲ����� (INTOSC) ��Ϊʱ��Դ���������ⲿ����
#pragma config WDTE = OFF		// ���ÿ��Ź���ʱ�������ⲻ��Ҫ�ĸ�λ��
#pragma config PWRTE = OFF		// �����ϵ綨ʱ������ȷ�����ϵ�ʱ�����ж�����ӳ١�
#pragma config MCLRE = ON		// �� MCLR/VPP ��������Ϊ MCLR ���ܣ�������λ���š�
#pragma config CP = OFF			// ���ô����ڴ汣���������ڳ�������ʱ�޸ĳ���洢����
#pragma config CPD = OFF		// ���������ڴ汣���������ڳ�������ʱ�޸����ݴ洢����
#pragma config BOREN = ON		// ���õ��縴λ���ܣ��������Դ����������ĸ�λ��
#pragma config CLKOUTEN = OFF	// ����ʱ��������ܣ�ȷ��ʱ��������Ų���������Ŀ�ġ�
#pragma config IESO = OFF		// �����ڲ�/�ⲿ�л����ܣ�����������ʱ���ڲ�ʱ���л����ⲿʱ�ӡ�
#pragma config FCMEN = ON		// ʧЧ��ȫʱ�Ӽ��ʹ�ܣ�ʧЧ��ȫʱ�Ӽ�������ã�

// CONFIG2
#pragma config WRT = OFF		// ���� Flash �洢����д�����������ڳ�������ʱ�� Flash �洢������д�롣
#pragma config PLLEN = ON		// ���� 4x PLL����ʱ��Ƶ����ߵ� 4 ����
#pragma config STVREN = ON		// ���ö�ջ���/���縴λ���ܣ�����ջ���������ʱ�����¸�λ��
#pragma config BORV = LO		// ���õ͵�ѹ�����㣬����̽���Դ�ĵ͵�ѹ�����
#pragma config DEBUG = OFF		// �������ߵ���ģʽ��ICSPCLK �� ICSPDAT ���Ž���Ϊͨ�� I/O ���š�
#pragma config LVP = OFF		// ���õ͵�ѹ��̣���֧�ֵ͵�ѹ���ģʽ��

#define _XTAL_FREQ 32000000

void TM1620Sendata(int TM1620Data);
void TM1620Sencmd(char com);
void TM1620_Dis(void);
void TM1620_Init(void);
void PIC12F1840_Init(void);
void setup(void);
unsigned int getADCValue(unsigned char channel);	// ����ADת��
void __interrupt() ISR(void);						// �жϴ�����
void ADsensing(void);								// ADת����������


#define AddrAutoAdd     0x40	// д��ʾ���Զ��ۼӵ�ַ 
#define Addr00H         0xC0	// ��ַ00H
#define GRID6_SEG8		0x02	// 6λ8���������ʾ��ʽ

#define STB			LATAbits.LATA0
#define T_STB		TRISAbits.TRISA0

#define CLK			LATAbits.LATA1
#define T_CLK		TRISAbits.TRISA1

#define DIN			LATAbits.LATA2
#define T_DIN		TRISAbits.TRISA2

#define JLS			LATAbits.LATA4
#define T_JLS		TRISAbits.TRISA4

#endif	/* DEW_SENSOR_H */

