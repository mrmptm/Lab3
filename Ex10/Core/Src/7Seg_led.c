/*
 * 7Seg_led.c
 *
 *  Created on: Nov 4, 2022
 *      Author: DELL
 */
#include "7Seg_Led.h"
void display7SEG(GPIO_TypeDef**GPIO_Port,uint16_t*GPIO_Pin,int num){
	if(num==0){
		HAL_GPIO_WritePin(GPIO_Port[0],GPIO_Pin[0],0);
		HAL_GPIO_WritePin(GPIO_Port[1],GPIO_Pin[1],0);
		HAL_GPIO_WritePin(GPIO_Port[2],GPIO_Pin[2],0);
		HAL_GPIO_WritePin(GPIO_Port[3],GPIO_Pin[3],0);
		HAL_GPIO_WritePin(GPIO_Port[4],GPIO_Pin[4],0);
		HAL_GPIO_WritePin(GPIO_Port[5],GPIO_Pin[5],0);
		HAL_GPIO_WritePin(GPIO_Port[6],GPIO_Pin[6],1);
	}
	if(num==1){
		HAL_GPIO_WritePin(GPIO_Port[0],GPIO_Pin[0],1);
		HAL_GPIO_WritePin(GPIO_Port[1],GPIO_Pin[1],0);
		HAL_GPIO_WritePin(GPIO_Port[2],GPIO_Pin[2],0);
		HAL_GPIO_WritePin(GPIO_Port[3],GPIO_Pin[3],1);
		HAL_GPIO_WritePin(GPIO_Port[4],GPIO_Pin[4],1);
		HAL_GPIO_WritePin(GPIO_Port[5],GPIO_Pin[5],1);
		HAL_GPIO_WritePin(GPIO_Port[6],GPIO_Pin[6],1);
	}
	if(num==2){
		HAL_GPIO_WritePin(GPIO_Port[0],GPIO_Pin[0],0);
		HAL_GPIO_WritePin(GPIO_Port[1],GPIO_Pin[1],0);
		HAL_GPIO_WritePin(GPIO_Port[2],GPIO_Pin[2],1);
		HAL_GPIO_WritePin(GPIO_Port[3],GPIO_Pin[3],0);
		HAL_GPIO_WritePin(GPIO_Port[4],GPIO_Pin[4],0);
		HAL_GPIO_WritePin(GPIO_Port[5],GPIO_Pin[5],1);
		HAL_GPIO_WritePin(GPIO_Port[6],GPIO_Pin[6],0);
	}
	if(num==3){
		HAL_GPIO_WritePin(GPIO_Port[0],GPIO_Pin[0],0);
		HAL_GPIO_WritePin(GPIO_Port[1],GPIO_Pin[1],0);
		HAL_GPIO_WritePin(GPIO_Port[2],GPIO_Pin[2],0);
		HAL_GPIO_WritePin(GPIO_Port[3],GPIO_Pin[3],0);
		HAL_GPIO_WritePin(GPIO_Port[4],GPIO_Pin[4],1);
		HAL_GPIO_WritePin(GPIO_Port[5],GPIO_Pin[5],1);
		HAL_GPIO_WritePin(GPIO_Port[6],GPIO_Pin[6],0);
	}
	if(num==4){
		HAL_GPIO_WritePin(GPIO_Port[0],GPIO_Pin[0],1);
		HAL_GPIO_WritePin(GPIO_Port[1],GPIO_Pin[1],0);
		HAL_GPIO_WritePin(GPIO_Port[2],GPIO_Pin[2],0);
		HAL_GPIO_WritePin(GPIO_Port[3],GPIO_Pin[3],1);
		HAL_GPIO_WritePin(GPIO_Port[4],GPIO_Pin[4],1);
		HAL_GPIO_WritePin(GPIO_Port[5],GPIO_Pin[5],0);
		HAL_GPIO_WritePin(GPIO_Port[6],GPIO_Pin[6],0);
	}
	if(num==5){
		HAL_GPIO_WritePin(GPIO_Port[0],GPIO_Pin[0],0);
		HAL_GPIO_WritePin(GPIO_Port[1],GPIO_Pin[1],1);
		HAL_GPIO_WritePin(GPIO_Port[2],GPIO_Pin[2],0);
		HAL_GPIO_WritePin(GPIO_Port[3],GPIO_Pin[3],0);
		HAL_GPIO_WritePin(GPIO_Port[4],GPIO_Pin[4],1);
		HAL_GPIO_WritePin(GPIO_Port[5],GPIO_Pin[5],0);
		HAL_GPIO_WritePin(GPIO_Port[6],GPIO_Pin[6],0);
	}
	if(num==6){
		HAL_GPIO_WritePin(GPIO_Port[0],GPIO_Pin[0],0);
		HAL_GPIO_WritePin(GPIO_Port[1],GPIO_Pin[1],1);
		HAL_GPIO_WritePin(GPIO_Port[2],GPIO_Pin[2],0);
		HAL_GPIO_WritePin(GPIO_Port[3],GPIO_Pin[3],0);
		HAL_GPIO_WritePin(GPIO_Port[4],GPIO_Pin[4],0);
		HAL_GPIO_WritePin(GPIO_Port[5],GPIO_Pin[5],0);
		HAL_GPIO_WritePin(GPIO_Port[6],GPIO_Pin[6],0);
	}
	if(num==7){
		HAL_GPIO_WritePin(GPIO_Port[0],GPIO_Pin[0],0);
		HAL_GPIO_WritePin(GPIO_Port[1],GPIO_Pin[1],0);
		HAL_GPIO_WritePin(GPIO_Port[2],GPIO_Pin[2],0);
		HAL_GPIO_WritePin(GPIO_Port[3],GPIO_Pin[3],1);
		HAL_GPIO_WritePin(GPIO_Port[4],GPIO_Pin[4],1);
		HAL_GPIO_WritePin(GPIO_Port[5],GPIO_Pin[5],1);
		HAL_GPIO_WritePin(GPIO_Port[6],GPIO_Pin[6],1);
	}
	if(num==8){
		HAL_GPIO_WritePin(GPIO_Port[0],GPIO_Pin[0],0);
		HAL_GPIO_WritePin(GPIO_Port[1],GPIO_Pin[1],0);
		HAL_GPIO_WritePin(GPIO_Port[2],GPIO_Pin[2],0);
		HAL_GPIO_WritePin(GPIO_Port[3],GPIO_Pin[3],0);
		HAL_GPIO_WritePin(GPIO_Port[4],GPIO_Pin[4],0);
		HAL_GPIO_WritePin(GPIO_Port[5],GPIO_Pin[5],0);
		HAL_GPIO_WritePin(GPIO_Port[6],GPIO_Pin[6],0);
	}
	if(num==9){
		HAL_GPIO_WritePin(GPIO_Port[0],GPIO_Pin[0],0);
		HAL_GPIO_WritePin(GPIO_Port[1],GPIO_Pin[1],0);
		HAL_GPIO_WritePin(GPIO_Port[2],GPIO_Pin[2],0);
		HAL_GPIO_WritePin(GPIO_Port[3],GPIO_Pin[3],0);
		HAL_GPIO_WritePin(GPIO_Port[4],GPIO_Pin[4],1);
		HAL_GPIO_WritePin(GPIO_Port[5],GPIO_Pin[5],0);
		HAL_GPIO_WritePin(GPIO_Port[6],GPIO_Pin[6],0);
	}
}
