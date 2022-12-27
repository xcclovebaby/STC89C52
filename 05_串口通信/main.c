#include <REGX52.H>
#include "delay.h"

void UartInit()		//4800bps@11.0592MHz
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xFA;		//设定定时初值
	TH1 = 0xFA;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	//配置中断
	EA = 1;
	ES = 1;
}

void UartSendByte(char byte) {
	SBUF = byte;
	while(TI == 0); //判断是否发送成功，发送成功后硬件会置位为1
	TI = 0; //软件复位
}

void UartRoutine() interrupt 4 {
	if(RI == 1) { //判断是否接收成功
		P2 = SBUF; //SBUF为接收数据
		UartSendByte(SBUF);
		RI = 0; //软件复位
	}
}

void main() {
	UartInit();
	UartSendByte(0x66);
	while(1){
	}
}
