#include <REGX52.H>
#include "delay.h"

//ɨ��4*4�������
unsigned char keyboard() {
	unsigned char num = 0;
	
	//��4*4��������������Ϊ�ߵ�ƽ
	P1 = 0xFF; 
	
	//�жϵ�һ��,�ѵ�һ����Ϊ�͵�ƽ
	P1_3 = 0;
	//�����ж��ĸ�����������
	if(P1_7 == 0) {delay(20); while(P1_7 == 0); delay(20); num = 1;}
	if(P1_6 == 0) {delay(20); while(P1_6 == 0); delay(20); num = 5;}
	if(P1_5 == 0) {delay(20); while(P1_5 == 0); delay(20); num = 9;}
	if(P1_4 == 0) {delay(20); while(P1_4 == 0); delay(20); num = 13;}
	
	P1 = 0xFF; 
	//�жϵڶ��У��ѵڶ�����Ϊ�͵�ƽ
	P1_2 = 0;
	//�����ж��ĸ�����������
	if(P1_7 == 0) {delay(20); while(P1_7 == 0); delay(20); num = 2;}
	if(P1_6 == 0) {delay(20); while(P1_6 == 0); delay(20); num = 6;}
	if(P1_5 == 0) {delay(20); while(P1_5 == 0); delay(20); num = 10;}
	if(P1_4 == 0) {delay(20); while(P1_4 == 0); delay(20); num = 14;}
	
	P1 = 0xFF; 
	//�жϵ����У��ѵڶ�����Ϊ�͵�ƽ
	P1_1 = 0;
	//�����ж��ĸ�����������
	if(P1_7 == 0) {delay(20); while(P1_7 == 0); delay(20); num = 3;}
	if(P1_6 == 0) {delay(20); while(P1_6 == 0); delay(20); num = 7;}
	if(P1_5 == 0) {delay(20); while(P1_5 == 0); delay(20); num = 11;}
	if(P1_4 == 0) {delay(20); while(P1_4 == 0); delay(20); num = 15;}
	
	P1 = 0xFF; 
	//�жϵ����У��ѵڶ�����Ϊ�͵�ƽ
	P1_0 = 0;
	//�����ж��ĸ�����������
	if(P1_7 == 0) {delay(20); while(P1_7 == 0); delay(20); num = 4;}
	if(P1_6 == 0) {delay(20); while(P1_6 == 0); delay(20); num = 8;}
	if(P1_5 == 0) {delay(20); while(P1_5 == 0); delay(20); num = 12;}
	if(P1_4 == 0) {delay(20); while(P1_4 == 0); delay(20); num = 16;}
	
	return num;
}