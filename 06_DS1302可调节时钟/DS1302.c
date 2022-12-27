#include <REGX52.H>

//����Ĵ�����ַ
#define DS1302_SECOND		0x80
#define DS1302_MINUTE		0x82
#define DS1302_HOUR			0x84
#define DS1302_DATE			0x86
#define DS1302_MONTH		0x88
#define DS1302_DAY			0x8A
#define DS1302_YEAR			0x8C
#define DS1302_WP				0x8E

//^λѡ����
sbit DS1302_SCLK = P3^6;
sbit DS1302_IO = P3^4;
sbit DS1302_CE = P3^5;

unsigned char time[] = {22, 12, 17, 19, 43, 03};

//��ʼ��
void DS1302_Init() {
	DS1302_CE = 0; //���ƿ��ظ��͵�ƽ
	DS1302_SCLK = 0; //ʱ�Ӹ��͵�ƽ
}

//д��
void DS1302_WriteByte(unsigned char Command, Data) {
	//�����ھֲ�������������Ҫ���ں����Ŀ�ͷ
	unsigned char i;
	
	DS1302_CE = 1;//���ƿ��ش�
	//Commandָ��
	for(i = 0; i < 8; i++) {
		//ȡ�����ݷŽ�IO��
		DS1302_IO = Command & (0x01 << i);
		DS1302_SCLK = 1; //ʱ�������أ�д������
		//delay(); ����STC89C52��Ƭ���������ʽ��������Բ�����ʱ
		DS1302_SCLK = 0; //ʱ���½���
	}
	
	//д�������Data
	for(i = 0; i < 8; i++) {
		//ȡ�����ݷŽ�IO��
		DS1302_IO = Data & (0x01 << i);
		DS1302_SCLK = 1; //ʱ�������أ�д������
		DS1302_SCLK = 0; //ʱ���½���
	}
	
	DS1302_CE = 0;
}

//��ȡ
unsigned char DS1302_ReadByte(unsigned char Command) {
	unsigned char i, Data = 0x00;	
	//0λ��1 ��ȡ����
	Command |= 0x01;
	DS1302_CE = 1;//���ƿ��ش�
	//Commandָ��
	for(i = 0; i < 8; i++) {
		//ȡ�����ݷŽ�IO��
		DS1302_IO = Command & (0x01 << i);
		DS1302_SCLK = 0; //ʱ���½���
		DS1302_SCLK = 1; //ʱ��������
	}
	
	for(i = 0; i < 8; i++) {
		//�ߵ���˳���
		DS1302_SCLK = 1;
		//Ҳ��Ӧ��ԭ��ͼ�ж�ȡ������Ҫʱ���½���
		DS1302_SCLK = 0;
		if(DS1302_IO) Data |= (0x01 << i); //��λ���λ��1 ��λ���λ��0
	}

	DS1302_CE = 0;
	//��IO�����㣬��ֹ��ȡ��������
	DS1302_IO = 0;
	//BCD��תʮ����
	return Data / 16 * 10 + Data % 16;
}

void DES1302_SetTime() {
	DS1302_WriteByte(DS1302_WP, 0x00); //�ر�д����
	DS1302_WriteByte(DS1302_YEAR, time[0] / 10 * 16 + time[0] % 10);
	DS1302_WriteByte(DS1302_MONTH, time[1] / 10 * 16 + time[1] % 10);
	DS1302_WriteByte(DS1302_DATE, time[2] / 10 * 16 + time[2] % 10);
	DS1302_WriteByte(DS1302_HOUR, time[3] / 10 * 16 + time[3] % 10);
	DS1302_WriteByte(DS1302_MINUTE, time[4] / 10 * 16 + time[4] % 10);
	DS1302_WriteByte(DS1302_SECOND, time[5] / 10 * 16 + time[5] % 10);
	DS1302_WriteByte(DS1302_WP, 0x80); //��д����
}

void DES1302_ReadTime() {
	time[0] = DS1302_ReadByte(DS1302_YEAR);
	time[1] = DS1302_ReadByte(DS1302_MONTH);
	time[2] = DS1302_ReadByte(DS1302_DATE);
	time[3] = DS1302_ReadByte(DS1302_HOUR);
	time[4] = DS1302_ReadByte(DS1302_MINUTE);
	time[5] = DS1302_ReadByte(DS1302_SECOND);
}

