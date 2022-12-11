#include <REGX52.H>
#include "delay.h"

//扫描4*4矩阵键盘
unsigned char keyboard() {
	unsigned char num = 0;
	
	//把4*4矩阵所有引脚置为高电平
	P1 = 0xFF; 
	
	//判断第一列,把第一列置为低电平
	P1_3 = 0;
	//逐行判断哪个按键被按下
	if(P1_7 == 0) {delay(20); while(P1_7 == 0); delay(20); num = 1;}
	if(P1_6 == 0) {delay(20); while(P1_6 == 0); delay(20); num = 5;}
	if(P1_5 == 0) {delay(20); while(P1_5 == 0); delay(20); num = 9;}
	if(P1_4 == 0) {delay(20); while(P1_4 == 0); delay(20); num = 13;}
	
	P1 = 0xFF; 
	//判断第二列，把第二列置为低电平
	P1_2 = 0;
	//逐行判断哪个按键被按下
	if(P1_7 == 0) {delay(20); while(P1_7 == 0); delay(20); num = 2;}
	if(P1_6 == 0) {delay(20); while(P1_6 == 0); delay(20); num = 6;}
	if(P1_5 == 0) {delay(20); while(P1_5 == 0); delay(20); num = 10;}
	if(P1_4 == 0) {delay(20); while(P1_4 == 0); delay(20); num = 14;}
	
	P1 = 0xFF; 
	//判断第三列，把第二列置为低电平
	P1_1 = 0;
	//逐行判断哪个按键被按下
	if(P1_7 == 0) {delay(20); while(P1_7 == 0); delay(20); num = 3;}
	if(P1_6 == 0) {delay(20); while(P1_6 == 0); delay(20); num = 7;}
	if(P1_5 == 0) {delay(20); while(P1_5 == 0); delay(20); num = 11;}
	if(P1_4 == 0) {delay(20); while(P1_4 == 0); delay(20); num = 15;}
	
	P1 = 0xFF; 
	//判断第四列，把第二列置为低电平
	P1_0 = 0;
	//逐行判断哪个按键被按下
	if(P1_7 == 0) {delay(20); while(P1_7 == 0); delay(20); num = 4;}
	if(P1_6 == 0) {delay(20); while(P1_6 == 0); delay(20); num = 8;}
	if(P1_5 == 0) {delay(20); while(P1_5 == 0); delay(20); num = 12;}
	if(P1_4 == 0) {delay(20); while(P1_4 == 0); delay(20); num = 16;}
	
	return num;
}