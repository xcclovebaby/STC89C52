#include <REGX52.H>
#include "Key.h"
#include "LCD1602.h"
#include "Delay.h"
#include "AT24C02.h"

unsigned char Data;

void main() {
	LCD_Init();
	LCD_ShowString(1,1,"Hello");
	AT24C02_WriteByte(1,66);
	Delay(5); //单片机写周期为5ms
	Data = AT24C02_ReadByte(1);
	LCD_ShowNum(2, 1, Data, 2);
	while(1){
		
	}
}