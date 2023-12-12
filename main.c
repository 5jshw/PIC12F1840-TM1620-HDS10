#include <xc.h>
#include "Dew_Sensor.h"

const unsigned char CODE[10]={0x3F,0x06,0x5b,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};		// 共阴数码管
unsigned int ADValue = 0;	// ADValue
unsigned char Thousandth = 0, Hundredth = 0, Tenth = 0, Unit = 0;
char ADSValue = 0;
unsigned int AD[5];

void main(void)
{
	PIC12F1840_Init();
	setup();				// AD转换初始化函数调用
	//TM1620_Init();
	__delay_ms(500);
	while(1)
	{
		ADsensing();		// 函数调用, AD转换
		__delay_ms(20);
		Numerical_Partitioning(ADValue);
		__delay_ms(20);
		TM1620_Dis();
		__delay_ms(20);
	}
}

unsigned int getADCValue(unsigned char channel)		// 单次AD转换函数
{
    ADCON0bits.CHS = channel;                               // 选择AD通道
    __delay_ms(5);                                          // 改变AD通道后，需延时稳定
    ADCON0bits.GO = 1;                                      // 开始AD转换
    while (ADCON0bits.GO);                                  // 转换完成指示
    return (unsigned int)((ADRESH << 2) | (ADRESL >> 6));   // 返回高低位合并后的AD值
}

void ADsensing(void)		// AD转换处理函数
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

void __interrupt() ISR(void)	// 中断处理函数
{
	if(PIR1bits.ADIF == 1)		// 检查AD是否发生中断
	{
		PIE1bits.ADIE = 0;		// 禁止中断发生
		PIR1bits.ADIF = 0;		// 清除中断标志

		PIE1bits.ADIE = 1;		// 一次中断执行完毕，允许中断继续发生
	}
}

void TM1620_Dis(void) //发送数据
{
	
	TM1620Sencmd(GRID6_SEG8);		// 设置显示模式，6位8段模式
	TM1620Sencmd(AddrAutoAdd);		// 设置数据命令，采用地址自动加1模式 0X40
    TM1620Sencmd(Addr00H);			// 设置地址从00H开始
	__delay_us(5);
	
    TM1620Sendata(CODE[Thousandth]);		// 从00H开始，偶数地址送显示数据
    TM1620Sendata(0x00);			// 01H
	TM1620Sendata(CODE[Hundredth]);			// 从00H开始，偶数地址送显示数据
    TM1620Sendata(0x00);			// 03H
	TM1620Sendata(CODE[Tenth]);				// 从00H开始，偶数地址送显示数据
    TM1620Sendata(0x00);			// 05H
	TM1620Sendata(CODE[Unit]);				// 从00H开始，偶数地址送显示数据
    TM1620Sendata(0x00);			// 07H
	__delay_ms(5);
	
	STB = 1;				//高
	__delay_ms(1);
	STB = 0;				//低
	__delay_ms(1);
	TM1620Sencmd(0x8F);		//设置显示命令，打开显示并设置占空比14/16.
	STB = 1;				//高
}

void TM1620Sendata(char TM1620Data)		//发送一个字节
{
	char i;
	for(i = 0; i < 8; i++)
	{
		CLK = 0;			// CLK低
		DIN = 1 & (TM1620Data >> i);
		CLK = 1;			// CLK高
		__delay_us(3);
	}
}

void TM1620Sencmd(char com)		//发送控制命令
 {
	STB = 1;				// 高
	__delay_ms(1);
	STB = 0;				// 低
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