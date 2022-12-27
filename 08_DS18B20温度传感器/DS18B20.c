#include <REGX52.H>
#include "OneWire.h"

#define DS18B20_SKIP_ROM 					0xCC //跳过ROM
#define DS18B20_CONVERT_T 				0x44 //开始温度变换
#define DS18B20_READ_SCRATCHPAD 	0xBE //读取暂存器数据

/* 温度变换
 * 初始化→跳过ROM →开始温度变换
 */
void DS18B20_ConvertTemperature()
{
	OneWire_Init(); //初始化
	OneWire_SendByte(DS18B20_SKIP_ROM); //跳过ROM
	OneWire_SendByte(DS18B20_CONVERT_T); //开始温度变换
}

/* 温度读取
 * 初始化→跳过ROM →读暂存器→连续的读操作
 */
float DS18B20_ReadTemperature()
{
	unsigned char TLSB, TMSB;
	float T; //温度
	int Temp;
	OneWire_Init(); //初始化
	OneWire_SendByte(DS18B20_SKIP_ROM); //跳过ROM
	OneWire_SendByte(DS18B20_READ_SCRATCHPAD); //读暂存器
	//SCRATCHPAD暂存器结构 温度分为：TLSB为低位 TMSB为高位
	TLSB = OneWire_ReceiveByte();
	TMSB = OneWire_ReceiveByte();
	//负数在计算机中以补码形式存放，把两个补码合并为有符号的16位int
	// -0.5补码形式:1000 0000 0000 1000 
	//所以Temp就是拼接好的16倍温度数据（为什么是16倍，因为温度格式中每一位比实际二进制小16倍）
	Temp = (TMSB << 8) | TLSB;
	T = Temp / 16.0;
	return T;
}