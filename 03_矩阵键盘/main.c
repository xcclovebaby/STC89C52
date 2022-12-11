#include <REGX52.H>
#include "LCD1602.h"
#include "keyboard.h"

int password;
int count = 0;

/* 键盘密码锁
	S11确认
	S12取消
	S1-S10分别为1-0
*/
void pwd() {
	char num = keyboard();
	if(num != 0) {
		if(num <= 10) {
			if(count < 4){
				password *= 10;
				password += num % 10;
			}
			count++;
		}
		if(num == 11) {
			if(password == 1234){
				LCD_ShowString(1, 14, "OK ");
				goto init;
			}else {
				LCD_ShowString(1, 14, "ERR");
				goto init;
			}
		}
		if(num == 12) {
			init:
				password = 0;
				count = 0;
		}
	}
}

void main(){
	LCD_Init();
	LCD_ShowString(1, 1, "Password:");
	while(1) {
		pwd();
		LCD_ShowNum(2, 1, password, 4);
	}
	
}