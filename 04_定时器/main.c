#include <REGX52.H>


void time_init(){
	//���ù�����ʽ�Ĵ���TMOD
	//TMOD = 0x01; //0000 0001��Ӧ16λ��ʱ����������ô��ֵ�޷�����������ʱ��
	TMOD = TMOD & 0xF0; //������λ����
	TMOD = TMOD | 0x01; //���õڰ�λΪ1
	//TF���λ����
	TF0 = 0;
	//T0���п���λ����
	TR0 = 1;
	//����16λ������TH0/TL0
	TH0 = 64535 / 256;
	TL0 = 64535 % 256;
	//T0�ж�ϵͳ����
	ET0 = 1;
	EA = 1;
	PT0 = 0;
}

unsigned int count = 0;

//T0�жϺ���
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
