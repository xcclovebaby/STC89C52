#ifndef __DS1302_H__
#define __DS1302_H__

extern unsigned char time[];

//��ʼ��
void DS1302_Init();
//д��
void DS1302_WriteByte(unsigned char Command, Data);
//��ȡ
unsigned char DS1302_ReadByte(unsigned char Command);

void DES1302_SetTime();
void DES1302_ReadTime();

#endif