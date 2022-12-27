#include <REGX52.H>

void time_init(){ //1毫秒@11.0592MHz
    //配置工作方式寄存器TMOD
    TMOD &= 0xF0;		//设置定时器模式
		TMOD |= 0x01;		//设置定时器模式
    TL0 = 0x16;		//设置定时初值
		TH0 = 0xFC;		//设置定时初值
		TF0 = 0;		//清除TF0标志
		TR0 = 1;		//定时器0开始计时
    //T0中断系统配置
    ET0 = 1;
    EA = 1;
    PT0 = 0;
}