#include <REGX52.H>
#include "Delay.h"

unsigned char Key_Num() {
	unsigned char num = 0;
	if(P3_1 == 0) {
		Delay(20);
		while(P3_1 == 0);
		Delay(20);
		num = 1;
	}
	if(P3_0 == 0) {
		Delay(20);
		while(P3_0 == 0);
		Delay(20);
		num = 2;
	}
	if(P3_2 == 0) {
		Delay(20);
		while(P3_2 == 0);
		Delay(20);
		num = 3;
	}
	if(P3_3 == 0) {
		Delay(20);
		while(P3_3 == 0);
		Delay(20);
		num = 4;
	}
	return num;
}