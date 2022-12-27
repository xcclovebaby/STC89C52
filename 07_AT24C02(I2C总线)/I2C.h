#ifndef __I2C_H__
#define __I2C_H__

void I2C_Start();
void I2C_Stop();
void I2C_SendByte(unsigned char byte);
unsigned char I2C_ReceiveByte();
void I2C_SendAck(unsigned char ackBit);
unsigned char I2C_ReceiveAck();

#endif