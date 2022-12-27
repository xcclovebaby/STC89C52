#include <REGX52.H>
#include "Delay.h"

//����ԭ��ͼ������SCL��SDA
sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;

//����I2Cʱ��ṹ
void I2C_Start() {
	//����ȷ���κ�ʱ����øú���SCL��SDA������һ��Ԥ��״̬
	//SCL������SDA֮�ϸı䣬����������SDA
	I2C_SDA = 1; //���øߵ�ƽΪ��ʼֵ
	I2C_SCL = 1; //SDA�ߵ�ƽ��������SCLΪ�ߵ�ƽ
	
	//��ʼ����:SCL�ߵ�ƽ�ڼ䣬SDA�Ӹߵ�ƽ�л����͵�ƽ
	I2C_SDA = 0;
	I2C_SCL = 0; //SCL�͵�ƽ�ڼ䣬����������λ���ηŵ�SDA���ϣ���λ��ǰ��
}

//��ֹ������SCL�ߵ�ƽ�ڼ䣬SDA�ӵ͵�ƽ�л����ߵ�ƽ
void I2C_Stop() {
	//Ԥ��SDAΪ�͵�ƽ
	I2C_SDA = 0;
	
	//����ʱ��ṹ��������SCLȻ��������SDA
	I2C_SCL = 1;
	I2C_SDA = 1;
}

//����һ�ֽ�����
//SCL�͵�ƽ�ڼ䣬����������λ���ηŵ�SDA���ϣ���λ��ǰ��
void I2C_SendByte(unsigned char byte) {
	unsigned char i;
	//����ѭ����������8�Σ����ɷ���һ���ֽ�
	for(i = 0; i < 8; i++) {
		I2C_SDA = byte & (0x80 >> i); //�����λ����ȡ�����ݷ���SDA����
		I2C_SCL = 1; //SCL�͵�ƽ�ڼ䣬�Ż�ȡSDA�������ݣ�Ȼ������SCL���ӻ�����SCL�ߵ�ƽ�ڼ��ȡ����λ
		//��ʱ1ms���ӳٵ�ʱ����ݵ�Ƭ���Ľ����������ԣ�STC89C52�����Ƭ����ʵ���Բ��ӳ�
		//��ʱΪ�˱�֤��ȡ����
		Delay(1);
		I2C_SCL = 0; //SCL��Ϊ�͵�ƽ�������������
	}
}

//����һ�ֽ�����
unsigned char I2C_ReceiveByte() {
	unsigned char i, byte = 0x00;
	
	//�����ڽ���֮ǰ����Ҫ�ͷ�SDA
	I2C_SDA = 1;
	
	//����ѭ����������8�Σ����ɽ���һ���ֽ�
	for(i = 0; i < 8; i++) {
		//Ȼ������SCL����������SCL�ߵ�ƽ�ڼ��ȡ����λ
		I2C_SCL = 1;
		Delay(1);
		//ȡ��SDA���ϵ����ݣ���λ��ǰ��
		if(I2C_SDA) byte |= (0x80 >> i);
		//SCL�͵�ƽ�ڼ䣬�ӻ�������λ���ηŵ�SDA����
		I2C_SCL = 0;
	}
	
	return byte;
}

//0ΪӦ��1Ϊ��Ӧ��
//����Ӧ��,SCL���߶�ȡSDA���ݣ�������SCL�ָ�
void I2C_SendAck(unsigned char ackBit) {
	I2C_SDA = ackBit;
	I2C_SCL = 1;
	Delay(1);
	I2C_SCL = 0;
}

//����Ӧ��
unsigned char I2C_ReceiveAck() {
	unsigned char ackBit = 0;
	//�����ڽ���֮ǰ����Ҫ�ͷ�SDA
	I2C_SDA = 1;
	Delay(1);
	I2C_SCL = 1;
	if(I2C_SDA) ackBit = 1;
	I2C_SCL = 0;
	
	return ackBit;
}