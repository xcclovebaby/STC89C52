#include <REGX52.H>
#include "OneWire.h"

#define DS18B20_SKIP_ROM 					0xCC //����ROM
#define DS18B20_CONVERT_T 				0x44 //��ʼ�¶ȱ任
#define DS18B20_READ_SCRATCHPAD 	0xBE //��ȡ�ݴ�������

/* �¶ȱ任
 * ��ʼ��������ROM ����ʼ�¶ȱ任
 */
void DS18B20_ConvertTemperature()
{
	OneWire_Init(); //��ʼ��
	OneWire_SendByte(DS18B20_SKIP_ROM); //����ROM
	OneWire_SendByte(DS18B20_CONVERT_T); //��ʼ�¶ȱ任
}

/* �¶ȶ�ȡ
 * ��ʼ��������ROM �����ݴ����������Ķ�����
 */
float DS18B20_ReadTemperature()
{
	unsigned char TLSB, TMSB;
	float T; //�¶�
	int Temp;
	OneWire_Init(); //��ʼ��
	OneWire_SendByte(DS18B20_SKIP_ROM); //����ROM
	OneWire_SendByte(DS18B20_READ_SCRATCHPAD); //���ݴ���
	//SCRATCHPAD�ݴ����ṹ �¶ȷ�Ϊ��TLSBΪ��λ TMSBΪ��λ
	TLSB = OneWire_ReceiveByte();
	TMSB = OneWire_ReceiveByte();
	//�����ڼ�������Բ�����ʽ��ţ�����������ϲ�Ϊ�з��ŵ�16λint
	// -0.5������ʽ:1000 0000 0000 1000 
	//����Temp����ƴ�Ӻõ�16���¶����ݣ�Ϊʲô��16������Ϊ�¶ȸ�ʽ��ÿһλ��ʵ�ʶ�����С16����
	Temp = (TMSB << 8) | TLSB;
	T = Temp / 16.0;
	return T;
}