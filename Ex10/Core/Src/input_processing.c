#include "main.h"
#include "button.h"
#include "input_processing.h"
#include "SoftwareTimer.h"
#include "7Seg_Led.h"
#define TRUE 1
#define FALSE 0
#define T_7SEGLED 250

int RED_DURATION;
int YELLOW_DURATION ;
int GREEN_DURATION;

int red_temp_dur, yellow_temp_dur, green_temp_dur;

enum State{INIT ,MODE1, MODE2, MODE3, MODE4, INCREASE, INCREASE_500MS, UPDATE_DURATION} ;
enum LED{RED,YELLOW,GREEN};
enum State state = INIT;

/* WAY1 TRAFFIC LIGHT VAR START */
enum LED current_led_way1;
int leds_way1_count[3];
/* WAY1 TRAFFIC LIGHT VAR END */

/* WAY2 TRAFFIC LIGHT VAR START */
enum LED current_led_way2;
int leds_way2_count[3];
/* WAY2 TRAFFIC LIGHT VAR END */

int button1_executed=0;
int button2_increase1=0;

enum LED LedToChange;

const int MAX_LED=2;
int index_7SEGLed=0;
int led_buffer1[2];
int led_buffer2[2];
void update_led_buffer1(int val);
void update_led_buffer2(int val);
void Switch7SEGLEDIndex();
void displayMode(int mode);
void update7SEG(int index);
void loadLedTempDuration(enum LED color);
void increaseTempDur(enum LED color);
void updateDuration(enum LED color);
void trafficLightCount(int*leds_count,enum LED*current_led);
void displaySingleLedsMode1();
void display7SEGMode1();
void turnOffSingleLed();
void ledBlinking(enum LED led_to_change);
/* 7SEG LED1s PARAMETERS START */
	GPIO_TypeDef*GPIO_Port_LED7SEG1[]={a1_GPIO_Port, b1_GPIO_Port, c1_GPIO_Port, d1_GPIO_Port,
			  e1_GPIO_Port, f1_GPIO_Port, g1_GPIO_Port};
	uint16_t GPIO_Pin_LED7SEG1[]={a1_Pin, b1_Pin, c1_Pin, d1_Pin, e1_Pin, f1_Pin, g1_Pin};
/* 7SEG LED1s PARAMETERS END */

/* 7SEG LED2s PARAMETERS START */
	GPIO_TypeDef*GPIO_Port_LED7SEG2[]={a2_GPIO_Port,b2_GPIO_Port,c2_GPIO_Port,d2_GPIO_Port,
				  e2_GPIO_Port, f2_GPIO_Port,g2_GPIO_Port};
	uint16_t GPIO_Pin_LED7SEG2[]={a2_Pin, b2_Pin, c2_Pin, d2_Pin, e2_Pin, f2_Pin, g2_Pin};
/* 7SEG LED2s PARAMETERS END */
void fsm_for_input_processing(){
	switch(state){
	case INIT:
		/* INIT PORT OUTPUT START */
		turnOffSingleLed();
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 0);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 0);
		/* INIT PORT OUTPUT END */

		/* INITIALIZE TEMPORARY DURATION START */
		red_temp_dur=RED_DURATION;
		yellow_temp_dur=YELLOW_DURATION;
		green_temp_dur=GREEN_DURATION;
		/* INITIALIZE TEMPORARY DURATION END */

		/* INITIALIZE COUNT START */
		leds_way1_count[0]=RED_DURATION;
		leds_way1_count[1]=YELLOW_DURATION;
		leds_way1_count[2]=GREEN_DURATION;
		HAL_GPIO_WritePin(RED_LED1_GPIO_Port, RED_LED1_Pin, 0);
		current_led_way1=RED;
		leds_way2_count[0]=RED_DURATION;
		leds_way2_count[1]=YELLOW_DURATION;
		leds_way2_count[2]=GREEN_DURATION;
		HAL_GPIO_WritePin(YELLOW_LED2_GPIO_Port, YELLOW_LED2_Pin, 0);
		current_led_way2=YELLOW;
		/* INITIALIZE COUNT END */
		index_7SEGLed=0;
		state=MODE1;
		setTimer2(T_7SEGLED); //set timer2 for 7seg led traversal
		setTimer4(1000);  //SET TIMER4 FOR COUNT DOWN
		break;
	case MODE1:
		/* DISPLAY 7-SEG LED START */
		if(timer2_flag==1){
			setTimer2(T_7SEGLED);
			Switch7SEGLEDIndex();
			display7SEGMode1();
		}
		/* DISPLAY 7-SEG LED END */

		/* COUNT DOWN START */
		if(timer4_flag==1){
			setTimer4(1000);
			trafficLightCount(leds_way1_count,&current_led_way1);
			trafficLightCount(leds_way2_count,&current_led_way2);
			displaySingleLedsMode1();
		}
		/* COUNT DOWN END */

		/* DISPLAY 7-SEG LED START */
		if(timer2_flag==1){
			setTimer2(T_7SEGLED);
			Switch7SEGLEDIndex();
			display7SEGMode1();
		}
		/* DISPLAY 7-SEG LED END */

		/*EXECUTE INPUT BUTTON1 START */
		if(button1_executed==0){
			if(button1_pressed()==TRUE){
				state=MODE2;
				button1_executed=1;
				setTimer1(250);   //set timer for red led blinking
				/* INITIALIZE TEMP DURATION START */
				red_temp_dur=RED_DURATION;
				yellow_temp_dur=YELLOW_DURATION;
				green_temp_dur=GREEN_DURATION;
				/* INITIALIZE TEMP DURATION END */
				turnOffSingleLed();
			}
		}else if(button1_executed==1){
			if(button1_pressed()==FALSE){
				button1_executed=0;
			}
		}
		/*EXECUTE INPUT BUTTON1 END */

		break;
	case MODE2:
		loadLedTempDuration(RED);  //LOAD RED LED DURATION START

		/* BLINK SINGLE RED LED START */
		if(timer1_flag==1){
			setTimer1(250);
			HAL_GPIO_TogglePin(RED_LED1_GPIO_Port, RED_LED1_Pin);  //TOGGLE RED LEDS IN 2 WAY
			HAL_GPIO_TogglePin(RED_LED2_GPIO_Port, RED_LED2_Pin);
		}
		/* BLINK SINGLE RED LED END */

		/* DISPLAYING MODE START */
		if(timer2_flag==1){
			setTimer2(T_7SEGLED);
			Switch7SEGLEDIndex();
			displayMode(2);
			loadLedTempDuration(RED);  //LOAD RED LED TEMP DURATION START
		}
		/* DISPLAYING MODE END */

		/*EXECUTE INPUT BUTTON1 START */
		if(button1_executed==0){
			if(button1_pressed()==TRUE){
				state=MODE3;
				button1_executed=1;
				turnOffSingleLed();
			}
		}else if(button1_executed==1){
			if(button1_pressed()==FALSE){
				button1_executed=0;
			}
		}
		/*EXECUTE INPUT BUTTON1 END */

		/*EXECUTE INPUT BUTTON3 START */
		if(button3_pressed()==TRUE){
			state=UPDATE_DURATION;
			LedToChange=RED;
		}
		/*EXECUTE INPUT BUTTON3 END */

		/*EXECUTE INPUT BUTTON2 START */
		if(button2_pressed()==TRUE){
			state=INCREASE;
			LedToChange=RED;
			button2_increase1=0;
		}
		/*EXECUTE INPUT BUTTON2 END */
		//TO DO
		break;
	case MODE3:
		loadLedTempDuration(YELLOW);  //LOAD RED LED TEMPORARY DURATION START

		/* BLINK SINGLE YELLOW LED START */
		if(timer1_flag==1){
			setTimer1(250);
			HAL_GPIO_TogglePin(YELLOW_LED1_GPIO_Port, YELLOW_LED1_Pin);  //TOGGLE RED LEDS IN 2 WAY
			HAL_GPIO_TogglePin(YELLOW_LED2_GPIO_Port, YELLOW_LED2_Pin);
		}
		/* BLINK SINGLE YELLOW LED END */

		/* DISPLAYING MODE START */
		if(timer2_flag==1){
			setTimer2(T_7SEGLED);
			Switch7SEGLEDIndex();
			displayMode(3);
			loadLedTempDuration(YELLOW);  //LOAD RED LED TEMPORARY DURATION START
		}
		/* DISPLAYING MODE END */

		/*EXECUTE INPUT BUTTON1 START */
		if(button1_executed==0){
			if(button1_pressed()==TRUE){
				state=MODE4;
				button1_executed=1;
				turnOffSingleLed();
			}
		}else if(button1_executed==1){
			if(button1_pressed()==FALSE){
				button1_executed=0;
			}
		}
		/*EXECUTE INPUT BUTTON1 END */

		/*EXECUTE INPUT BUTTON3 START */
		if(button3_pressed()==TRUE){
			state=UPDATE_DURATION;
			LedToChange=YELLOW;
		}
		/*EXECUTE INPUT BUTTON3 END */

		/*EXECUTE INPUT BUTTON2 START */
		if(button2_pressed()==TRUE){
			state=INCREASE;
			LedToChange=YELLOW;
			button2_increase1=0;
		}
		/*EXECUTE INPUT BUTTON2 END */
		//TO DO
		break;
	case MODE4:
		loadLedTempDuration(GREEN);  //LOAD RED LED TEMPORARY DURATION START

		/* BLINK SINGLE GREEN LED START */
		if(timer1_flag==1){
			setTimer1(250);
			HAL_GPIO_TogglePin(GREEN_LED1_GPIO_Port, GREEN_LED1_Pin);  //TOGGLE RED LEDS IN 2 WAY
			HAL_GPIO_TogglePin(GREEN_LED2_GPIO_Port, GREEN_LED2_Pin);
		}
		/* BLINK SINGLE GREEN LED END */

		/* DISPLAYING MODE START */
		if(timer2_flag==1){
			setTimer2(T_7SEGLED);
			Switch7SEGLEDIndex();
			displayMode(4);
			loadLedTempDuration(GREEN);  //LOAD RED LED TEMPORARY DURATION START
		}
		/* DISPLAYING MODE END */

		/*EXECUTE INPUT BUTTON1 START */
		if(button1_executed==0){
			if(button1_pressed()==TRUE){
				state=INIT;
				button1_executed=1;
				setTimer1(0); //turn off or reset timer 1
				turnOffSingleLed();
			}
		}else if(button1_executed==1){
			if(button1_pressed()==FALSE){
				button1_executed=0;
			}
		}
		/*EXECUTE INPUT BUTTON1 END */

		/*EXECUTE INPUT BUTTON3 START */
		if(button3_pressed()==TRUE){
			state=UPDATE_DURATION;
			LedToChange=GREEN;
		}
		/*EXECUTE INPUT BUTTON3 END */

		/*EXECUTE INPUT BUTTON2 START */
		if(button2_pressed()==TRUE){
			state=INCREASE;
			LedToChange=GREEN;
			button2_increase1=0;
		}
		/*EXECUTE INPUT BUTTON2 END */
		//TO DO
		break;
	case INCREASE:
		/* BLINK SINGLE LED START */
		if(timer1_flag==1){
			setTimer1(250);
			ledBlinking(LedToChange);
		}
		/* BLINK SINGLE LED END */

		/* DISPLAYING MODE START */
		if(timer2_flag==1){
			setTimer2(T_7SEGLED);
			Switch7SEGLEDIndex();
			if(LedToChange==RED)
				displayMode(2);
			else if(LedToChange==YELLOW)
				displayMode(3);
			else if(LedToChange==GREEN)
				displayMode(4);

			loadLedTempDuration(LedToChange);
		}
		/* DISPLAYING MODE END */

		/* EXECUTE INPUT BUTTON2 START */
		if(button2_pressed_1s()==TRUE){
			state=INCREASE_500MS;
			setTimer3(500);
		}else if(button2_pressed()==FALSE){
			switch(LedToChange){
				case RED:
					state=MODE2;
					break;
				case YELLOW:
					state=MODE3;
					break;
				case GREEN:
					state=MODE4;
					break;
			}
		}
		/* EXECUTE INPUT BUTTON2 START */

		/* INCREASE DURATION START */
		if(button2_increase1==0){
			increaseTempDur(LedToChange);
			button2_increase1=1;
		}
		/* INCREASE DURATION END */
		//TO DO
		break;
	case INCREASE_500MS:
		/* BLINK SINGLE LED START */
		if(timer1_flag==1){
			setTimer1(250);
			ledBlinking(LedToChange);
		}
		/* BLINK SINGLE LED END */

		/* DISPLAYING MODE START */
		if(timer2_flag==1){
			setTimer2(T_7SEGLED);
			Switch7SEGLEDIndex();
			if(LedToChange==RED)
				displayMode(2);
			else if(LedToChange==YELLOW)
				displayMode(3);
			else if(LedToChange==GREEN)
				displayMode(4);
			loadLedTempDuration(LedToChange);  //LOAD RED LED DURATION START
		}
		/* DISPLAYING MODE END */

		/* EXECUTE INPUT BUTTON2 START */
		if(button2_pressed()==FALSE){
			switch(LedToChange){
				case RED:
					state=MODE2;
					break;
				case YELLOW:
					state=MODE3;
					break;
				case GREEN:
					state=MODE4;
					break;
			}
		}
		/* EXECUTE INPUT BUTTON2 START */

		/* INCREASE TEMP DURATION START */
		if(timer3_flag==1){
			setTimer3(500);
			increaseTempDur(LedToChange);
		}
		/* INCREASE TEMP DURATION END */
		//TO DO
		break;
	case UPDATE_DURATION:
		updateDuration(LedToChange);
		if(button3_pressed()==FALSE){
			switch(LedToChange){
				case RED:
					state=MODE2;
					break;
				case YELLOW:
					state=MODE3;
					break;
				case GREEN:
					state=MODE4;
					break;
			}
		}
		//TO DO
		break;
	}
}


void update_led_buffer1(int val){
	led_buffer1[0]=val/10;
	led_buffer1[1]=val%10;
}

void update_led_buffer2(int val){
	led_buffer2[0]=val/10;
	led_buffer2[1]=val%10;
}
void Switch7SEGLEDIndex(){
	index_7SEGLed++;
	if(index_7SEGLed>=MAX_LED){
		index_7SEGLed=0;
	}
}

void update7SEG(int index){
	switch(index){
		case 0:
			//Display the first 7SEG with led_buffer[0]
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);	//TURN OFF PREVIOUS 7SEG
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 0);	//TURN ON THIS 7SEG
			display7SEG(GPIO_Port_LED7SEG1,GPIO_Pin_LED7SEG1,led_buffer1[0]);
			display7SEG(GPIO_Port_LED7SEG2,GPIO_Pin_LED7SEG2,led_buffer2[0]);
		break;
		case 1:
			//Display the second 7SEG with led_buffer[1]
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);	//TURN OFF PREVIOUS 7SEG
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 0);	//TURN ON THIS 7SEG
			display7SEG(GPIO_Port_LED7SEG1,GPIO_Pin_LED7SEG1,led_buffer1[1]);
			display7SEG(GPIO_Port_LED7SEG2,GPIO_Pin_LED7SEG2,led_buffer2[1]);
		break;
	}
}

void displayMode(int mode){
	update_led_buffer1(mode);
	update7SEG(index_7SEGLed);
}

void loadLedTempDuration(enum LED color){
	switch(color){
	case RED:
		update_led_buffer2(red_temp_dur);
		break;
	case YELLOW:
		update_led_buffer2(yellow_temp_dur);
		break;
	case GREEN:
		update_led_buffer2(green_temp_dur);
		break;
	}
	update7SEG(index_7SEGLed);
}
void increaseTempDur(enum LED color){
	switch(color){
		case RED:
			red_temp_dur++;
			if(red_temp_dur>99)
				red_temp_dur=1;
			break;
		case YELLOW:
			yellow_temp_dur++;
			if(yellow_temp_dur>99)
				yellow_temp_dur=1;
			break;
		case GREEN:
			green_temp_dur++;
			if(red_temp_dur>99)
				green_temp_dur=1;
			break;
	}
}

void updateDuration(enum LED color){
	switch(color){
		case RED:
			RED_DURATION=red_temp_dur;
			break;
		case YELLOW:
			YELLOW_DURATION=yellow_temp_dur;
			break;
		case GREEN:
			GREEN_DURATION=green_temp_dur;
			break;
	}
}

void display7SEGMode1(){
	switch(current_led_way1){
	case RED:
		update_led_buffer1(leds_way1_count[0]);
		break;
	case YELLOW:
		update_led_buffer1(leds_way1_count[1]);
		break;
	case GREEN:
		update_led_buffer1(leds_way1_count[2]);
		break;
	}

	switch(current_led_way2){
	case RED:
		update_led_buffer2(leds_way2_count[0]);
		break;
	case YELLOW:
		update_led_buffer2(leds_way2_count[1]);
		break;
	case GREEN:
		update_led_buffer2(leds_way2_count[2]);
		break;
	}
	update7SEG(index_7SEGLed);
}


void displaySingleLedsMode1(){
	if(current_led_way1==RED){
		HAL_GPIO_WritePin(RED_LED1_GPIO_Port, RED_LED1_Pin, 0);  // TURN ON RED LED
		HAL_GPIO_WritePin(GREEN_LED1_GPIO_Port, GREEN_LED1_Pin, 1);  // TURN OFF GREEN LED

	}
	if(current_led_way1==YELLOW){
		HAL_GPIO_WritePin(YELLOW_LED1_GPIO_Port, YELLOW_LED1_Pin, 0);  // TURN ON YELLOW LED
		HAL_GPIO_WritePin(RED_LED1_GPIO_Port, RED_LED1_Pin, 1);  // TURN OFF RED LED

	}
	if(current_led_way1==GREEN){
		HAL_GPIO_WritePin(GREEN_LED1_GPIO_Port, GREEN_LED1_Pin, 0);  // TURN ON GREEN LED
		HAL_GPIO_WritePin(YELLOW_LED1_GPIO_Port, YELLOW_LED1_Pin, 1);  // TURN OFF YELLOW LED

	}

	if(current_led_way2==RED){
		HAL_GPIO_WritePin(RED_LED2_GPIO_Port, RED_LED2_Pin, 0);  // TURN ON RED LED
		HAL_GPIO_WritePin(GREEN_LED2_GPIO_Port, GREEN_LED2_Pin, 1);  // TURN OFF GREEN LED

	}
	if(current_led_way2==YELLOW){
		HAL_GPIO_WritePin(YELLOW_LED2_GPIO_Port, YELLOW_LED2_Pin, 0);  // TURN ON YELLOW LED
		HAL_GPIO_WritePin(RED_LED2_GPIO_Port, RED_LED2_Pin, 1);  // TURN OFF RED LED

	}
	if(current_led_way2==GREEN){
		HAL_GPIO_WritePin(GREEN_LED2_GPIO_Port, GREEN_LED2_Pin, 0);  // TURN ON GREEN LED
		HAL_GPIO_WritePin(YELLOW_LED2_GPIO_Port, YELLOW_LED2_Pin, 1);  // TURN OFF YELLOW LED

	}


}

void trafficLightCount(int*leds_count,enum LED*current_led){
	if(*current_led==RED){
		leds_count[0]--;
		if(leds_count[0]<=0){
			leds_count[0]=RED_DURATION;
			*current_led=YELLOW;
		}
	}
	else if(*current_led==YELLOW){
		leds_count[1]--;
		if(leds_count[1]<=0){
			leds_count[1]=YELLOW_DURATION;
			*current_led=GREEN;
		}
	}
	else if(*current_led==GREEN){
		leds_count[2]--;
		if(leds_count[2]<=0){
			leds_count[2]=GREEN_DURATION;
			*current_led=RED;
		}
	}
}

void turnOffSingleLed(){
	  HAL_GPIO_WritePin(RED_LED1_GPIO_Port, RED_LED1_Pin, 1);
	  HAL_GPIO_WritePin(YELLOW_LED1_GPIO_Port, YELLOW_LED1_Pin, 1);
	  HAL_GPIO_WritePin(GREEN_LED1_GPIO_Port, GREEN_LED1_Pin, 1);

	  HAL_GPIO_WritePin(RED_LED2_GPIO_Port, RED_LED2_Pin, 1);
	  HAL_GPIO_WritePin(YELLOW_LED2_GPIO_Port, YELLOW_LED2_Pin, 1);
	  HAL_GPIO_WritePin(GREEN_LED2_GPIO_Port, GREEN_LED2_Pin, 1);
}

void ledBlinking(enum LED led_to_change){
	switch(led_to_change){
	case RED:
		HAL_GPIO_TogglePin(RED_LED1_GPIO_Port, RED_LED1_Pin);  //TOGGLE RED LEDS IN 2 WAY
		HAL_GPIO_TogglePin(RED_LED2_GPIO_Port, RED_LED2_Pin);
		break;
	case YELLOW:
		HAL_GPIO_TogglePin(YELLOW_LED1_GPIO_Port, YELLOW_LED1_Pin);  //TOGGLE RED LEDS IN 2 WAY
		HAL_GPIO_TogglePin(YELLOW_LED2_GPIO_Port, YELLOW_LED2_Pin);
		break;
	case GREEN:
		HAL_GPIO_TogglePin(GREEN_LED1_GPIO_Port, GREEN_LED1_Pin);  //TOGGLE RED LEDS IN 2 WAY
		HAL_GPIO_TogglePin(GREEN_LED2_GPIO_Port, GREEN_LED2_Pin);
		break;
	}
}

