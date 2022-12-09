#include <stdio.h>
#include <REGX52.H>
#include <INTRINS.H>

void Delay(int xms)		//@12.000MHz
{
	unsigned char i, j;
	
	while(--xms) {
		
		i = 195;
		j = 138;
		do
		{
			while (--j);
		} while (--i);
	}
}

void Delay1ms(int xms)		//@12.000MHz
{
	unsigned char i, j;
	while(--xms) {
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
	}
}

//LED��ˮ�ƺ���
void LED_Follow() {
		while(1) {
		P2 = 0xFE; //1111 1110
		Delay(200);
		P2 = 0xFD; //1111 1101
		Delay(200);
		P2 = 0xFB; //1111 1011
		Delay(200);
		P2 = 0xF7; //1111 0111
		Delay(200);
		P2 = 0xEF; //1110 1111
		Delay(200);
		P2 = 0xDF; //1101 1111
		Delay(200);
		P2 = 0xBF; //1011 1111
		Delay(200);
		P2 = 0x7F; //0111 1111
		Delay(200);
	}
}

//������������LED����
void contrl_LED() {
	//K1����ΪP31
	if(P3_1 == 0) {
		
		//����������ʱ20ms
		Delay1ms(20);
		//���밴��ƽ���ڵȴ�����,���ֺ����ѭ��
		while(P3_1 == 0);
		//����������ʱ20ms
		Delay1ms(20);
		
		//���һ��LED���ƣ�ֻ������0��1
		P2_0 = ~P2_0;	
	}
}

unsigned char LEDNum = 0; //λ����

//��������K2����LED����λ����
void contrl_bit_led() {
	if(P3_0 == 0) {
		Delay1ms(20);
		while(P3_0 == 0);
		Delay1ms(20);
		
		LEDNum++;
		
		if(LEDNum >= 8) LEDNum = 0;
		
		P2 = 0x01 << LEDNum;
	}
}

void main() {
//	LED_Follow();
	while(1) {
		contrl_LED();
		contrl_bit_led();
	}
}

