#include <REGX52.H>
#include "delay.h"

void UartInit()		//4800bps@11.0592MHz
{
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����
	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
	TL1 = 0xFA;		//�趨��ʱ��ֵ
	TH1 = 0xFA;		//�趨��ʱ����װֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
	//�����ж�
	EA = 1;
	ES = 1;
}

void UartSendByte(char byte) {
	SBUF = byte;
	while(TI == 0); //�ж��Ƿ��ͳɹ������ͳɹ���Ӳ������λΪ1
	TI = 0; //�����λ
}

void UartRoutine() interrupt 4 {
	if(RI == 1) { //�ж��Ƿ���ճɹ�
		P2 = SBUF; //SBUFΪ��������
		UartSendByte(SBUF);
		RI = 0; //�����λ
	}
}

void main() {
	UartInit();
	UartSendByte(0x66);
	while(1){
	}
}
