#include <REGX52.H>

//数字对应的数码管十六进制
unsigned char table[] = 
{
		0x3F, //0011 1111 => 0
		0x06, //0000 0110 => 1
		0x5B, //0101 1011 => 2
		0x4F, //0100 1111 => 3
		0x66, //0110 0110 => 4
		0x6D, //0110 1101 => 5
		0x7D, //0111 1101 => 6
		0x07, //0000 0111 => 7
		0x7F, //0111 1111 => 8
		0x6F //0110 1111 =>9
};

void Delay1ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
}

void static_led(const unsigned char location, char number){
	
	switch(location) {
		case 1:
			P2_4 = 0; P2_3 = 0; P2_2 = 0;
			break;
		case 2:
			P2_4 = 0; P2_3 = 0; P2_2 = 1;
			break;
		case 3:
			P2_4 = 0; P2_3 = 1; P2_2 = 0;
			break;
		case 4:
			P2_4 = 0; P2_3 = 1; P2_2 = 1;
			break;
		case 5:
			P2_4 = 1; P2_3 = 0; P2_2 = 0;
			break;
		case 6:
			P2_4 = 1; P2_3 = 0; P2_2 = 1;
			break;
		case 7:
			P2_4 = 1; P2_3 = 1; P2_2 = 0;
			break;
		case 8:
			P2_4 = 1; P2_3 = 1; P2_2 = 1;
			break;
	}
	P0 = table[number];
	
	//延时1ms避免LED灯变暗
	Delay1ms();
	
	//清零操作
	P0 = 0x00;
}

void main() {
	while(1) {
		static_led(8, 1);
		static_led(7, 2);
		static_led(6, 3);
	}
}