#include <xc.h>
#include "Dew_Sensor.h"

const int CODE[10]={0x3F,0x06,0x5b,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};  //共阴数码管

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
	OSCCON = 0b11110000;  // 设置振荡器为8MHz, 使能PLL(倍频)
	// 配置 ADC
	ANSELAbits.ANSA4 = 1;   // 设置模拟输入引脚 A0
	ADCON1 = 0x50;          // 结果左对齐，FOSC/16，参考电压为VDD
	PIE1bits.ADIE = 1;      // 允许 ADC 中断
	PIR1bits.ADIF = 0;      // 清零 ADC 中断标志
	ADCON0bits.GO = 0;      // 初始化 AD 转换
	ADCON0bits.ADON = 1;    // 开启 AD 转换器
}

void TM1620_Init(void)				// 初始化
{
	TM1620Sencmd(GRID6_SEG8);		// 设置显示模式，6位8段模式
	TM1620Sencmd(AddrAutoAdd);		// 设置数据命令，采用地址自动加1模式 0X40
    TM1620Sencmd(Addr00H);			// 设置地址从00H开始
} 

void TM1620_Dis(void) //发送数据
{

    TM1620Sendata(CODE[0]);		// 从00H开始，偶数地址送显示数据
    TM1620Sendata(0x00);		// 01H
	TM1620Sendata(CODE[1]);		// 从00H开始，偶数地址送显示数据
    TM1620Sendata(0x00);		// 01H
	TM1620Sendata(CODE[2]);		// 从00H开始，偶数地址送显示数据
    TM1620Sendata(0x00);		// 01H
	TM1620Sendata(CODE[3]);		// 从00H开始，偶数地址送显示数据
    TM1620Sendata(0x00);		// 01H
	
	STB = 1;			//高
	__delay_ms(1);
	STB = 0;			//低
	__delay_ms(1);
	TM1620Sencmd(0x8F);				//设置显示命令，打开显示并设置占空比14/16.
	STB = 1;			//高
}

void TM1620Sendata(int TM1620Data) //发送一个字节
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

void TM1620Sencmd(char com) //发送控制命令
 {
	STB = 1;				// 高
	__delay_ms(1);
	STB = 0;				// 低
	__delay_ms(1);
	TM1620Sendata(com);
 }