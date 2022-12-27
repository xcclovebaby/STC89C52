#include <REGX52.H>
#include "LCD1602.h"
#include "DS18B20.h"

//温度显示
void ShowTemperature()
{
	float T;
	DS18B20_ConvertTemperature();
	T = DS18B20_ReadTemperature();
	if(T < 0) {
		LCD_ShowChar(2, 1, '-');
		T = -T; //置为正数
	}else {
		LCD_ShowChar(2, 1, '+');
	}
	LCD_ShowNum(2,2, T, 3);
	LCD_ShowChar(2, 5, '.');
	LCD_ShowNum(2,6, (unsigned long)(T*10000) % 10000, 4);
	LCD_ShowChar(2, 10, 0xDF);
	LCD_ShowChar(2, 11, 'C');
}

void main() {
	LCD_Init();
	LCD_ShowString(1, 1, "Temperature:");
	while(1){
		ShowTemperature();
	}
}