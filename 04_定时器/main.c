#include <REGX52.H>


void time_init(){
	//配置工作方式寄存器TMOD
	//TMOD = 0x01; //0000 0001对应16位定时器，但是这么赋值无法配置两个定时器
	TMOD = TMOD & 0xF0; //给后四位置零
	TMOD = TMOD | 0x01; //设置第八位为1
	//TF溢出位置零
	TF0 = 0;
	//T0运行控制位启动
	TR0 = 1;
	//配置16位计数器TH0/TL0
	TH0 = 64535 / 256;
	TL0 = 64535 % 256;
	//T0中断系统配置
	ET0 = 1;
	EA = 1;
	PT0 = 0;
}

unsigned int count = 0;

//T0中断函数
void timer0() interrupt 1 {
	TH0 = 64535 / 256;
	TL0 = 64535 % 256;
	count++;
	if(count >= 1000) {
		P2_0 = ~P2_0;
		count = 0;
	}
}

void main(){
	time_init();
	while(1){
		
	}
}
