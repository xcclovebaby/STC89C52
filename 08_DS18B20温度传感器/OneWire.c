#include <REGX52.H>

sbit OneWire_DQ = P3^7; //I/O总线

//初始化：主机将总线拉低至少480us，然后释放总线，等待15~60us后，
//存在的从机会拉低总线60~240us以响应主机，之后从机将释放总线
unsigned char OneWire_Init() {
	unsigned char i,Ack;
	OneWire_DQ = 1; //初始化DQ总线为高电平
	OneWire_DQ = 0; //主机将总线拉低
	i = 227; while (--i); //等待500us
	OneWire_DQ = 1; //释放总线
	i = 29; while (--i); //等待70us
	Ack = OneWire_DQ; //应答
	i = 227; while (--i); //等待500us 从机释放总线
	return Ack;
}

/* 发送一位：
 * 主机将总线拉低60~120us，然后释放总线，表示发送0；
 * 主机将总线拉低1~15us，然后释放总线，表示发送1。
 * 从机将在总线拉低30us后（典型值）读取电平，整个时间片应大于60us
 */
void OneWire_SendBit(unsigned char Bit)
{
	unsigned char i;
	OneWire_DQ = 0; //将总线拉低
	i = 3; while (--i); //先拉低10us
	OneWire_DQ = Bit; //给总线赋值
	i = 25; while (--i); //延时60us
	OneWire_DQ = 1; //释放总线
}

/* 接收一位
 * 主机将总线拉低1~15us，然后释放总线，
 * 并在拉低后15us内读取总线电平（尽量贴近15us的末尾），
 * 读取为低电平则为接收0，读取为高电平则为接收1 ，整个时间片应大于60us
 */
unsigned char OneWire_ReceiveBit()
{
	unsigned char i, Data;
	OneWire_DQ = 0; //将总线拉低
	i = 1; while (--i); //等待5us
	OneWire_DQ = 1; //释放总线
	i = 1; while (--i); //等待5us
	Data = OneWire_DQ; //读取数据
	i = 25; while (--i); //延时60us
	return Data;
}

/* 发送一个字节
 * 连续调用8次发送一位的时序，依次发送一个字节的8位（低位在前）
 */
void OneWire_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i = 0; i < 8; i++) {
		OneWire_SendBit(Byte & (0x01 << i));
	}
}

/* 接收一个字节
 * 连续调用8次接收一位的时序，依次接收一个字节的8位（低位在前）
 */
unsigned char OneWire_ReceiveByte()
{
	unsigned char i, Byte = 0x00;
	for(i = 0; i < 8; i++) {
		if(OneWire_ReceiveBit()) Byte |= 0x01 << i;
	}
	return Byte;
}