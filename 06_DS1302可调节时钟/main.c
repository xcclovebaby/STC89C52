#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Key.h"
#include "Delay.h"
#include "Time.h"

unsigned char num, mode = 0,select = 0, flag = 0;

//时间显示
void Time_Show() {
	DES1302_ReadTime();
	LCD_ShowNum(1, 1, time[0], 2);
	LCD_ShowNum(1, 4, time[1], 2);
	LCD_ShowNum(1, 7, time[2], 2);
	LCD_ShowNum(2, 1, time[3], 2);
	LCD_ShowNum(2, 4, time[4], 2);
	LCD_ShowNum(2, 7, time[5], 2);
}

//日期判断
void change() {
	if(time[1] > 12) time[1] = 1;
	if(time[1] < 1) time[1] = 12;
	if((time[1] == 4 || time[1] == 6 || time[1] == 9 || time[1] == 11) && time[2] > 30) time[2] = 1;
	if((time[1] == 1 || time[1] == 3 || time[1] == 5 || time[1] == 7 || time[1] == 8 || time[1] == 10 || time[1] == 12) && time[2] > 31) time[2] = 1;
	if(time[1] == 2) {
		if(time[0] % 4 == 0 && time[2] > 29) time[2] = 1;
		else if(time[2] > 28) time[2] = 1;
	}
	if(time[3] > 23) time[3] = 0;
	if(time[4] > 59) time[4] = 0;
	if(time[5] > 59) time[5] = 0;
}

void Time_Set() {
	if(num == 2) {
		select++;
		select %= 6;
	}
	if(num == 3) {
		time[select]++;
		change();
	}
	if(num == 4) {
		time[select]--;
		change();
	}
	
	//LCD_ShowNum(2, 10, select, 2);
	//LCD_ShowNum(2, 13, flag, 2);
	
	if(select == 0 && flag == 1) {LCD_ShowString(1, 1, "  ");}
	else{LCD_ShowNum(1, 1, time[0], 2);}
	
	if(select == 1 && flag == 1) {LCD_ShowString(1, 4, "  ");}
	else{LCD_ShowNum(1, 4, time[1], 2);}
	
	if(select == 2 && flag == 1) {LCD_ShowString(1, 7, "  ");}
	else{LCD_ShowNum(1, 7, time[2], 2);}
	
	if(select == 3 && flag == 1) {LCD_ShowString(2, 1, "  ");}
	else{LCD_ShowNum(2, 1, time[3], 2);}
	
	if(select == 4 && flag == 1) {LCD_ShowString(2, 4, "  ");}
	else {LCD_ShowNum(2, 4, time[4], 2);}
	
	if(select == 5 && flag == 1) {LCD_ShowString(2, 7, "  ");}
	else {LCD_ShowNum(2, 7, time[5], 2);}
}

void main() {
	LCD_Init(); //LCD初始化
	DS1302_Init(); //DS1302初始化
	time_init(); //定时器0初始化
	
	LCD_ShowString(1, 1, "  -  -  ");
	LCD_ShowString(2, 1, "  :  :  ");
	
	DES1302_SetTime();
	
	while(1){
		num = Key_Num();
		//按键判断，用于切换显示时间、设置时间两种模式
		if(num == 1) {
			if(mode == 0) mode = 1;
			else if(mode == 1) {
				mode = 0;
				DES1302_SetTime();
			}
		}
		switch(mode) {
			case 0:
				Time_Show();
				break;
			case 1:
				Time_Set();
				break;
		}
	}
}

//T0中断函数
void Timer0_Routine() interrupt 1 {
	static unsigned int count;
	TL0 = 0x16;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	count++;
    if(count >= 500) {
		flag = !flag;
        count = 0;
    }
}