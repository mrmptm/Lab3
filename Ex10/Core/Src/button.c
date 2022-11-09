/*
 * button.c
 *
 *  Created on: Oct 7, 2022
 *      Author: DELL
 */
#include "button.h"
/* 	BUTTON1 PARAMETER START */
int debounceButton1Buffer2=NORMAL_STATE;
int debounceButton1Buffer1=NORMAL_STATE;
int button1Buffer=NORMAL_STATE;
/* 	BUTTON1 PARAMETER END */
void button1_reading(){
	debounceButton1Buffer2 =debounceButton1Buffer1;
	debounceButton1Buffer1 = HAL_GPIO_ReadPin(Button1_GPIO_Port, Button1_Pin);
	if(debounceButton1Buffer1 == debounceButton1Buffer2)
		button1Buffer = debounceButton1Buffer1;
}

/* 	BUTTON2 PARAMETER START */
int debounceButton2Buffer2=NORMAL_STATE;
int debounceButton2Buffer1=NORMAL_STATE;
int button2Buffer=NORMAL_STATE;
int counterForButton2Press1s=1000;
int flagForButton2Press1s=0;
/* 	BUTTON2 PARAMETER END */
void button2_reading(){
	debounceButton2Buffer2 =debounceButton2Buffer1;
	debounceButton2Buffer1 = HAL_GPIO_ReadPin(Button2_GPIO_Port, Button2_Pin);
	if(debounceButton2Buffer1 == debounceButton2Buffer2)
		button2Buffer = debounceButton2Buffer1;

	if(button2Buffer == PRESSED_STATE){
	//if a button is pressed, we start counting
		if(counterForButton2Press1s >0){
			counterForButton2Press1s=counterForButton2Press1s-TIMER_CYCLE;
		} else {
		//the flag is turned on when 1 second has passed
		//since the button is pressed.
			flagForButton2Press1s = 1;
		}
	}else if(button2Buffer == NORMAL_STATE){
		counterForButton2Press1s = 1000;
		flagForButton2Press1s = 0;
	}
}

/* 	BUTTON3 PARAMETER START */
int debounceButton3Buffer2=NORMAL_STATE;
int debounceButton3Buffer1=NORMAL_STATE;
int button3Buffer=NORMAL_STATE;
/* 	BUTTON3 PARAMETER END */
void button3_reading(){
	debounceButton3Buffer2 =debounceButton3Buffer1;
	debounceButton3Buffer1 = HAL_GPIO_ReadPin(Button3_GPIO_Port, Button3_Pin);
	if(debounceButton3Buffer1 == debounceButton3Buffer2)
		button3Buffer = debounceButton3Buffer1;
}

int button1_pressed(){
	return (button1Buffer == PRESSED_STATE);
}

int button2_pressed(){
	return (button2Buffer == PRESSED_STATE);
}
int button2_pressed_1s(){
	return (flagForButton2Press1s == 1);
}

int button3_pressed(){
	return (button3Buffer == PRESSED_STATE);
}

