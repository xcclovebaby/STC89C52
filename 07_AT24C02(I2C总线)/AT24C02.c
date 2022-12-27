#include <REGX52.H>
#include "I2C.h"

//AT24C02�Ĺ̶���ַΪ1010�������õ�ַ����������Ϊ000������SLAVE ADDRESS+WΪ0xA0��SLAVE ADDRESS+RΪ0xA1
#define AT24C02_ADDRESS 0xA0

//�ֽ�д����WORD ADDRESS��д������DATA:
void AT24C02_WriteByte(unsigned char Address, Data) {
	I2C_Start(); //��ʼ
	I2C_SendByte(AT24C02_ADDRESS); //I2Cд�����ݵĵ�ַ��AT24C02�ĵ�ַ��
	I2C_ReceiveAck();//��ȡӦ��
	I2C_SendByte(Address); //д�븱��ַ
	I2C_ReceiveAck();//��ȡӦ��
	I2C_SendByte(Data); //д������
	I2C_ReceiveAck();//��ȡӦ��
	I2C_Stop(); //����
}

//�������������WORD ADDRESS��������DATA
unsigned char AT24C02_ReadByte(unsigned char Address) {
	unsigned char Data = 0x00;
	I2C_Start(); //��ʼ
	I2C_SendByte(AT24C02_ADDRESS); //I2Cд�����ݵĵ�ַ��AT24C02�ĵ�ַ��
	I2C_ReceiveAck();//��ȡӦ��
	I2C_SendByte(Address); //д�븱��ַ
	I2C_ReceiveAck();//��ȡӦ��
	I2C_Start(); //��ʼ
	I2C_SendByte(AT24C02_ADDRESS | 0x01); //SLAVE ADDRESS+RΪ0xA1
	I2C_ReceiveAck();//��ȡӦ��
	Data = I2C_ReceiveByte(); //��ȡ����
	I2C_SendAck(1); //����Ӧ��
	I2C_Stop(); //����
	return Data;
}
