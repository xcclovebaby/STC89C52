#include <REGX52.H>

//定义寄存器地址
#define DS1302_SECOND		0x80
#define DS1302_MINUTE		0x82
#define DS1302_HOUR			0x84
#define DS1302_DATE			0x86
#define DS1302_MONTH		0x88
#define DS1302_DAY			0x8A
#define DS1302_YEAR			0x8C
#define DS1302_WP				0x8E

//^位选符号
sbit DS1302_SCLK = P3^6;
sbit DS1302_IO = P3^4;
sbit DS1302_CE = P3^5;

unsigned char time[] = {22, 12, 17, 19, 43, 03};

//初始化
void DS1302_Init() {
	DS1302_CE = 0; //控制开关给低电平
	DS1302_SCLK = 0; //时钟给低电平
}

//写入
void DS1302_WriteByte(unsigned char Command, Data) {
	//函数内局部变量的声明，要放在函数的开头
	unsigned char i;
	
	DS1302_CE = 1;//控制开关打开
	//Command指令
	for(i = 0; i < 8; i++) {
		//取出数据放进IO口
		DS1302_IO = Command & (0x01 << i);
		DS1302_SCLK = 1; //时钟上升沿，写入数据
		//delay(); 由于STC89C52单片机运行速率较慢，可以不加延时
		DS1302_SCLK = 0; //时钟下降沿
	}
	
	//写入的数据Data
	for(i = 0; i < 8; i++) {
		//取出数据放进IO口
		DS1302_IO = Data & (0x01 << i);
		DS1302_SCLK = 1; //时钟上升沿，写入数据
		DS1302_SCLK = 0; //时钟下降沿
	}
	
	DS1302_CE = 0;
}

//读取
unsigned char DS1302_ReadByte(unsigned char Command) {
	unsigned char i, Data = 0x00;	
	//0位置1 读取数据
	Command |= 0x01;
	DS1302_CE = 1;//控制开关打开
	//Command指令
	for(i = 0; i < 8; i++) {
		//取出数据放进IO口
		DS1302_IO = Command & (0x01 << i);
		DS1302_SCLK = 0; //时钟下降沿
		DS1302_SCLK = 1; //时钟上升沿
	}
	
	for(i = 0; i < 8; i++) {
		//颠倒了顺序后
		DS1302_SCLK = 1;
		//也对应了原理图中读取数据需要时钟下降沿
		DS1302_SCLK = 0;
		if(DS1302_IO) Data |= (0x01 << i); //按位或把位置1 按位与把位置0
	}

	DS1302_CE = 0;
	//给IO口清零，防止读取错误数据
	DS1302_IO = 0;
	//BCD码转十进制
	return Data / 16 * 10 + Data % 16;
}

void DES1302_SetTime() {
	DS1302_WriteByte(DS1302_WP, 0x00); //关闭写保护
	DS1302_WriteByte(DS1302_YEAR, time[0] / 10 * 16 + time[0] % 10);
	DS1302_WriteByte(DS1302_MONTH, time[1] / 10 * 16 + time[1] % 10);
	DS1302_WriteByte(DS1302_DATE, time[2] / 10 * 16 + time[2] % 10);
	DS1302_WriteByte(DS1302_HOUR, time[3] / 10 * 16 + time[3] % 10);
	DS1302_WriteByte(DS1302_MINUTE, time[4] / 10 * 16 + time[4] % 10);
	DS1302_WriteByte(DS1302_SECOND, time[5] / 10 * 16 + time[5] % 10);
	DS1302_WriteByte(DS1302_WP, 0x80); //打开写保护
}

void DES1302_ReadTime() {
	time[0] = DS1302_ReadByte(DS1302_YEAR);
	time[1] = DS1302_ReadByte(DS1302_MONTH);
	time[2] = DS1302_ReadByte(DS1302_DATE);
	time[3] = DS1302_ReadByte(DS1302_HOUR);
	time[4] = DS1302_ReadByte(DS1302_MINUTE);
	time[5] = DS1302_ReadByte(DS1302_SECOND);
}

