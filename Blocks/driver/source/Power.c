/*
 * Power.c
 *
 *  Created on: Jun 28, 2023
 *      Author: Lost
 */

#include "Power.h"
#include "debug.h"

#define Wheel_Control GPIO_Pin_0
#define Motor_Control GPIO_Pin_2


void Power_Manage_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = Wheel_Control;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin =Motor_Control ;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

}

void Power_Manage(Power_Manage_Typedef Select,uint8_t Action)
{
    switch (Select)
    {
        case Power_Wheel:

            if (Action)
            {
                GPIO_WriteBit(GPIOC, Wheel_Control,SET);
            }
            else
            {
                GPIO_WriteBit(GPIOC, Wheel_Control,RESET);
            }

            break;

        case Power_Motor:
            if (Action)
              {
                  GPIO_WriteBit(GPIOC,Motor_Control,SET);
              }
              else
              {
                  GPIO_WriteBit(GPIOC,Motor_Control,RESET);
              }

            break;
        default:
            break;
    }
}
