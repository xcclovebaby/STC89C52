#include <REGX52.H>
#include "I2C.h"

//AT24C02的固定地址为1010，可配置地址本开发板上为000，所以SLAVE ADDRESS+W为0xA0，SLAVE ADDRESS+R为0xA1
#define AT24C02_ADDRESS 0xA0

//字节写：在WORD ADDRESS处写入数据DATA:
void AT24C02_WriteByte(unsigned char Address, Data) {
	I2C_Start(); //初始
	I2C_SendByte(AT24C02_ADDRESS); //I2C写入数据的地址（AT24C02的地址）
	I2C_ReceiveAck();//读取应答
	I2C_SendByte(Address); //写入副地址
	I2C_ReceiveAck();//读取应答
	I2C_SendByte(Data); //写入数据
	I2C_ReceiveAck();//读取应答
	I2C_Stop(); //结束
}

//随机读：读出在WORD ADDRESS处的数据DATA
unsigned char AT24C02_ReadByte(unsigned char Address) {
	unsigned char Data = 0x00;
	I2C_Start(); //初始
	I2C_SendByte(AT24C02_ADDRESS); //I2C写入数据的地址（AT24C02的地址）
	I2C_ReceiveAck();//读取应答
	I2C_SendByte(Address); //写入副地址
	I2C_ReceiveAck();//读取应答
	I2C_Start(); //初始
	I2C_SendByte(AT24C02_ADDRESS | 0x01); //SLAVE ADDRESS+R为0xA1
	I2C_ReceiveAck();//读取应答
	Data = I2C_ReceiveByte(); //读取数据
	I2C_SendAck(1); //发送应答
	I2C_Stop(); //结束
	return Data;
}
