/*
 * DC_Motor.c
 *
 *  Created on: Jun 22, 2023
 *      Author: Lost
 */


#include "debug.h"                  // Device header
#include "PWM.h"
#include "GPIO_Init.h"
#include "DC_Motor.h"

void DCMotor_Init(void)
{
    PWM_Init();
    //初始化控制方向的IO
    GPIOD_Init(GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7,GPIO_Mode_Out_PP);
}


void SetMotor_Speed(Wheel_Speed_Typdef* Wheel_Speed)
{


    //左后轮控制
    if(Wheel_Speed->BL_Speed>0) //正转
    {
        GPIO_WriteBit(GPIOD, GPIO_Pin_0,SET);
        GPIO_WriteBit(GPIOD, GPIO_Pin_1,RESET);
    }
    else//反转
    {
        Wheel_Speed->BL_Speed=-Wheel_Speed->BL_Speed;
        GPIO_WriteBit(GPIOD, GPIO_Pin_0,RESET);
        GPIO_WriteBit(GPIOD, GPIO_Pin_1,SET);
    }



    //左前轮控制
    if(Wheel_Speed->FL_Speed>0) //正转
    {
        GPIO_WriteBit(GPIOD, GPIO_Pin_2,SET);
        GPIO_WriteBit(GPIOD, GPIO_Pin_3,RESET);
    }
    else//反转
    {
        Wheel_Speed->FL_Speed=-Wheel_Speed->FL_Speed;
        GPIO_WriteBit(GPIOD, GPIO_Pin_2,RESET);
        GPIO_WriteBit(GPIOD, GPIO_Pin_3,SET);
    }


    //右前轮控制
    if(Wheel_Speed->FR_Speed>0) //正转
    {
        GPIO_WriteBit(GPIOD, GPIO_Pin_4,SET);
        GPIO_WriteBit(GPIOD, GPIO_Pin_5,RESET);
    }
    else//反转
    {
        Wheel_Speed->FR_Speed=-Wheel_Speed->FR_Speed;
        GPIO_WriteBit(GPIOD, GPIO_Pin_4,RESET);
        GPIO_WriteBit(GPIOD, GPIO_Pin_5,SET);
    }


    //右前轮控制
   if(Wheel_Speed->BR_Speed>0) //正转
   {
       GPIO_WriteBit(GPIOD, GPIO_Pin_6,SET);
       GPIO_WriteBit(GPIOD, GPIO_Pin_7,RESET);
   }
   else//反转
   {
       Wheel_Speed->BR_Speed=-Wheel_Speed->BR_Speed;
       GPIO_WriteBit(GPIOD, GPIO_Pin_6,RESET);
       GPIO_WriteBit(GPIOD, GPIO_Pin_7,SET);
   }

  //控制PWM的占空比
   Wheel_t Wheel;

   Wheel=FR;
   Duty_Set(Wheel,Wheel_Speed);
   Wheel=FL;
   Duty_Set(Wheel,Wheel_Speed);
   Wheel=BL;
   Duty_Set(Wheel,Wheel_Speed);
   Wheel=BR;
   Duty_Set(Wheel,Wheel_Speed);

}
