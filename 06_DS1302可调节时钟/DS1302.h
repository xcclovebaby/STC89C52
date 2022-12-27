#ifndef __DS1302_H__
#define __DS1302_H__

extern unsigned char time[];

//初始化
void DS1302_Init();
//写入
void DS1302_WriteByte(unsigned char Command, Data);
//读取
unsigned char DS1302_ReadByte(unsigned char Command);

void DES1302_SetTime();
void DES1302_ReadTime();

#endif