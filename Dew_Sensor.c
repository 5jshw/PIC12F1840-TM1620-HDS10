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
	OSCCON = 0b11110000;	// 设置振荡器为8MHz, 使能PLL(倍频)
	// 配置 ADC
	ANSELAbits.ANSA4 = 1;	// 设置模拟输入引脚 A0
	ADCON1 = 0x50;			// 结果左对齐，FOSC/16，参考电压为VDD
	INTCONbits.GIE = 1;		//开总中断
	INTCONbits.PEIE = 1;	//开外设中断
	PIE1bits.ADIE = 1;		// 允许 ADC 中断
	PIR1bits.ADIF = 0;		// 清零 ADC 中断标志
	ADCON0bits.GO = 0;		// 初始化 AD 转换
	ADCON0bits.ADON = 1;	// 开启 AD 转换器
}

void TM1620_Init(void)				// 初始化
{
	TM1620Sencmd(GRID6_SEG8);		// 设置显示模式，6位8段模式
	TM1620Sencmd(AddrAutoAdd);		// 设置数据命令，采用地址自动加1模式 0X40
    TM1620Sencmd(Addr00H);			// 设置地址从00H开始
	__delay_us(5);
} 

