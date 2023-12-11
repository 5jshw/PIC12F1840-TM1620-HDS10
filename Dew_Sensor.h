#ifndef DEW_SENSOR_H
#define	DEW_SENSOR_H

// CONFIG1
#pragma config FOSC = INTOSC	// 指定使用内部振荡器 (INTOSC) 作为时钟源，而不是外部晶振。
#pragma config WDTE = OFF		// 禁用看门狗计时器，避免不必要的复位。
#pragma config PWRTE = OFF		// 禁用上电定时器，以确保在上电时不会有额外的延迟。
#pragma config MCLRE = ON		// 将 MCLR/VPP 引脚设置为 MCLR 功能，用作复位引脚。
#pragma config CP = OFF			// 禁用代码内存保护，允许在程序运行时修改程序存储器。
#pragma config CPD = OFF		// 禁用数据内存保护，允许在程序运行时修改数据存储器。
#pragma config BOREN = ON		// 禁用掉电复位功能，避免因电源波动而引起的复位。
#pragma config CLKOUTEN = OFF	// 禁用时钟输出功能，确保时钟输出引脚不用作其他目的。
#pragma config IESO = OFF		// 启用内部/外部切换功能，可以在运行时从内部时钟切换到外部时钟。
#pragma config FCMEN = ON		// 失效安全时钟监控使能（失效安全时钟监控已启用）

// CONFIG2
#pragma config WRT = OFF		// 禁用 Flash 存储器自写保护，允许在程序运行时对 Flash 存储器进行写入。
#pragma config PLLEN = ON		// 启用 4x PLL，将时钟频率提高到 4 倍。
#pragma config STVREN = ON		// 启用堆栈溢出/下溢复位功能，当堆栈溢出或下溢时将导致复位。
#pragma config BORV = LO		// 设置低电压触发点，用于探测电源的低电压情况。
#pragma config DEBUG = OFF		// 禁用在线调试模式，ICSPCLK 和 ICSPDAT 引脚将作为通用 I/O 引脚。
#pragma config LVP = OFF		// 启用低电压编程，以支持低电压编程模式。

#define _XTAL_FREQ 32000000

void TM1620Sendata(int TM1620Data);
void TM1620Sencmd(char com);
void TM1620_Dis(void);
void TM1620_Init(void);
void PIC12F1840_Init(void);
void setup(void);
unsigned int getADCValue(unsigned char channel);	// 单次AD转换
void __interrupt() ISR(void);						// 中断处理函数
void ADsensing(void);								// AD转换，主程序


#define AddrAutoAdd     0x40	// 写显示，自动累加地址 
#define Addr00H         0xC0	// 地址00H
#define GRID6_SEG8		0x02	// 6位8段数码管显示方式

#define STB			LATAbits.LATA0
#define T_STB		TRISAbits.TRISA0

#define CLK			LATAbits.LATA1
#define T_CLK		TRISAbits.TRISA1

#define DIN			LATAbits.LATA2
#define T_DIN		TRISAbits.TRISA2

#define JLS			LATAbits.LATA4
#define T_JLS		TRISAbits.TRISA4

#endif	/* DEW_SENSOR_H */

