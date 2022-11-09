/*
 * button.h
 *
 *  Created on: Oct 7, 2022
 *      Author: DELL
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

#define NUM_OF_BTN 3
#define NORMAL_STATE 	1
#define PRESSED_STATE 0
#define TIMER_CYCLE 10
void button1_reading();
void button2_reading();
void button3_reading();

int button1_pressed();

int button2_pressed();
int button2_pressed_1s();

int button3_pressed();
#endif /* INC_BUTTON_H_ */
