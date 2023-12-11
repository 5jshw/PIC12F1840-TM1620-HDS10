#include <xc.h>
#include "Dew_Sensor.h"

const int CODE[10]={0x3F,0x06,0x5b,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};		// 共阴数码管
unsigned long currentResistance;		// NTC动态电阻值

void main(void)
{
	PIC12F1840_Init();
	TM1620_Init();
	setup();				// AD转换初始化函数调用
    __delay_ms(1000);		// 缓冲期
	while(1)
	{
		ADsensing();		// 函数调用, AD转换
		__delay_ms(100);	// 延时一定时间，减少AD采样频率
		TM1620_Dis();
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
	unsigned long voltageValue;			// NTC电压值
	unsigned long ADValue = 0;			// ad1 NTC
	ADValue = getADCValue(0x03);		// AN3
	ADValue = 1024 - ADValue;			// 由于NTC位于测温电路下端，所以温度升高时，电压下降，电阻上升。因此，将AD值反向
	voltageValue = ADValue * 500 / 1024;		// 转换成电压值
	currentResistance = (unsigned long)(500 - voltageValue) * 10000 / voltageValue;		// 计算NTC当前的动态电阻值
}

void __interrupt() ISR(void)	// 中断处理函数
{
	if(PIR1bits.ADIF == 1)		// 检查AD是否发生中断
	{
		PIE1bits.ADIE = 0;		// 禁止中断发生
		PIR1bits.ADIF = 0;		// 清除中断标志
		
		//中断程序
		
		PIE1bits.ADIE = 1;		// 一次中断执行完毕，允许中断继续发生
	}
}

