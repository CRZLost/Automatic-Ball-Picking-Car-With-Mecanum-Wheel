/*
 * DC_Motor.h
 *
 *  Created on: Jun 22, 2023
 *      Author: Lost
 */



#ifndef BLOCKS_DRIVER_HEADER_DC_MOTOR_H_
#define BLOCKS_DRIVER_HEADER_DC_MOTOR_H_

//typedef enum{FL=1,FR=2,BR=3,BL=4} Wheel_t; //选择轮子
//Wheel_t Wheel;
//typedef struct{int32_t FL_Speed;int32_t FR_Speed;int32_t BR_Speed;int32_t BL_Speed;} Wheel_Speed_Typdef; //设置轮子速度包含正反
//Wheel_Speed_Typdef Wheel_Speed;
#include "PWM.h"
void DCMotor_Init(void);
void SetMotor_Speed(Wheel_Speed_Typdef* Wheel_Speed);

#endif /* BLOCKS_DRIVER_HEADER_DC_MOTOR_H_ */
