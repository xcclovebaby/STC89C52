#include <REGX52.H>

sbit OneWire_DQ = P3^7; //I/O����

//��ʼ����������������������480us��Ȼ���ͷ����ߣ��ȴ�15~60us��
//���ڵĴӻ�����������60~240us����Ӧ������֮��ӻ����ͷ�����
unsigned char OneWire_Init() {
	unsigned char i,Ack;
	OneWire_DQ = 1; //��ʼ��DQ����Ϊ�ߵ�ƽ
	OneWire_DQ = 0; //��������������
	i = 227; while (--i); //�ȴ�500us
	OneWire_DQ = 1; //�ͷ�����
	i = 29; while (--i); //�ȴ�70us
	Ack = OneWire_DQ; //Ӧ��
	i = 227; while (--i); //�ȴ�500us �ӻ��ͷ�����
	return Ack;
}

/* ����һλ��
 * ��������������60~120us��Ȼ���ͷ����ߣ���ʾ����0��
 * ��������������1~15us��Ȼ���ͷ����ߣ���ʾ����1��
 * �ӻ�������������30us�󣨵���ֵ����ȡ��ƽ������ʱ��ƬӦ����60us
 */
void OneWire_SendBit(unsigned char Bit)
{
	unsigned char i;
	OneWire_DQ = 0; //����������
	i = 3; while (--i); //������10us
	OneWire_DQ = Bit; //�����߸�ֵ
	i = 25; while (--i); //��ʱ60us
	OneWire_DQ = 1; //�ͷ�����
}

/* ����һλ
 * ��������������1~15us��Ȼ���ͷ����ߣ�
 * �������ͺ�15us�ڶ�ȡ���ߵ�ƽ����������15us��ĩβ����
 * ��ȡΪ�͵�ƽ��Ϊ����0����ȡΪ�ߵ�ƽ��Ϊ����1 ������ʱ��ƬӦ����60us
 */
unsigned char OneWire_ReceiveBit()
{
	unsigned char i, Data;
	OneWire_DQ = 0; //����������
	i = 1; while (--i); //�ȴ�5us
	OneWire_DQ = 1; //�ͷ�����
	i = 1; while (--i); //�ȴ�5us
	Data = OneWire_DQ; //��ȡ����
	i = 25; while (--i); //��ʱ60us
	return Data;
}

/* ����һ���ֽ�
 * ��������8�η���һλ��ʱ�����η���һ���ֽڵ�8λ����λ��ǰ��
 */
void OneWire_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i = 0; i < 8; i++) {
		OneWire_SendBit(Byte & (0x01 << i));
	}
}

/* ����һ���ֽ�
 * ��������8�ν���һλ��ʱ�����ν���һ���ֽڵ�8λ����λ��ǰ��
 */
unsigned char OneWire_ReceiveByte()
{
	unsigned char i, Byte = 0x00;
	for(i = 0; i < 8; i++) {
		if(OneWire_ReceiveBit()) Byte |= 0x01 << i;
	}
	return Byte;
}