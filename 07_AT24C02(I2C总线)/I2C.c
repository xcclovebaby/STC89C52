#include <REGX52.H>
#include "Delay.h"

//根据原理图，定义SCL、SDA
sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;

//根据I2C时序结构
void I2C_Start() {
	//首先确保任何时候调用该函数SCL、SDA都处于一个预设状态
	//SCL建立在SDA之上改变，所以先设置SDA
	I2C_SDA = 1; //设置高电平为初始值
	I2C_SCL = 1; //SDA高电平后再设置SCL为高电平
	
	//起始条件:SCL高电平期间，SDA从高电平切换到低电平
	I2C_SDA = 0;
	I2C_SCL = 0; //SCL低电平期间，主机将数据位依次放到SDA线上（高位在前）
}

//终止条件：SCL高电平期间，SDA从低电平切换到高电平
void I2C_Stop() {
	//预设SDA为低电平
	I2C_SDA = 0;
	
	//根据时序结构，先拉高SCL然后再拉高SDA
	I2C_SCL = 1;
	I2C_SDA = 1;
}

//发送一字节数据
//SCL低电平期间，主机将数据位依次放到SDA线上（高位在前）
void I2C_SendByte(unsigned char byte) {
	unsigned char i;
	//依次循环上述过程8次，即可发送一个字节
	for(i = 0; i < 8; i++) {
		I2C_SDA = byte & (0x80 >> i); //从最高位依次取出数据放在SDA线上
		I2C_SCL = 1; //SCL低电平期间，才会取SDA线上数据，然后拉高SCL，从机将在SCL高电平期间读取数据位
		//延时1ms，延迟的时间根据单片机的交流电气特性，STC89C52这个单片机其实可以不延迟
		//延时为了保证读取数据
		Delay(1);
		I2C_SCL = 0; //SCL置为低电平，继续存放数据
	}
}

//接收一字节数据
unsigned char I2C_ReceiveByte() {
	unsigned char i, byte = 0x00;
	
	//主机在接收之前，需要释放SDA
	I2C_SDA = 1;
	
	//依次循环上述过程8次，即可接收一个字节
	for(i = 0; i < 8; i++) {
		//然后拉高SCL，主机将在SCL高电平期间读取数据位
		I2C_SCL = 1;
		Delay(1);
		//取出SDA线上的数据（高位在前）
		if(I2C_SDA) byte |= (0x80 >> i);
		//SCL低电平期间，从机将数据位依次放到SDA线上
		I2C_SCL = 0;
	}
	
	return byte;
}

//0为应答，1为非应答
//发送应答,SCL拉高读取SDA数据，再拉低SCL恢复
void I2C_SendAck(unsigned char ackBit) {
	I2C_SDA = ackBit;
	I2C_SCL = 1;
	Delay(1);
	I2C_SCL = 0;
}

//接收应答
unsigned char I2C_ReceiveAck() {
	unsigned char ackBit = 0;
	//主机在接收之前，需要释放SDA
	I2C_SDA = 1;
	Delay(1);
	I2C_SCL = 1;
	if(I2C_SDA) ackBit = 1;
	I2C_SCL = 0;
	
	return ackBit;
}