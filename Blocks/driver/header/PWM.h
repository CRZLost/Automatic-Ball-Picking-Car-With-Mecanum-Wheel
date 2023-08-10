/*
 * PWM.h
 *
 *  Created on: Jun 22, 2023
 *      Author: Lost
 */


#ifndef BLOCKS_DRIVER_HEADER_PWM_H_
#define BLOCKS_DRIVER_HEADER_PWM_H_

typedef enum{FL=1,FR=2,BR=3,BL=4} Wheel_t; //选择轮子
typedef struct{float FL_Speed;float FR_Speed;float BR_Speed;float BL_Speed;} Wheel_Speed_Typdef;
extern Wheel_t Wheel; //选择轮子
extern Wheel_Speed_Typdef Wheel_Speed;


void PWM_Init(void);
void Duty_Set(Wheel_t Wheel,Wheel_Speed_Typdef* Wheel_Speed);

#endif /* BLOCKS_DRIVER_HEADER_PWM_H_ */
