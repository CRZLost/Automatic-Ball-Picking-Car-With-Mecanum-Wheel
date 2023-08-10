/*
 * PWM.c
 *
 *  Created on: Jun 22, 2023
 *      Author: Lost
 */


#include "debug.h"                  // Device header
#include "GPIO_Init.h"
#include "PWM.h"

/*
    TIM2用来发出PWM波形控制速度的同时
    每次更新触发中断读取TIM3中的CNT的值
    利用v=N/T 算出速度
*/
void PWM_Init(void)
{
/**************************************************/
    //配置计时器TIM2
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); //打开TIM2端口对应的时钟

    TIM_InternalClockConfig(TIM2); //TIM2以内部时钟为时钟源

    TIM_TimeBaseInitTypeDef TimeBaseInit;

    TimeBaseInit.TIM_ClockDivision=TIM_CKD_DIV1; //确定采样频率，进行信号滤波
    TimeBaseInit.TIM_CounterMode= TIM_CounterMode_Up; //确定计数模式
    TimeBaseInit.TIM_Period=400-1; //重装值 ARR 直流电机有100档
    TimeBaseInit.TIM_Prescaler=900-1; //预分频倍数
    TimeBaseInit.TIM_RepetitionCounter=0; //定义溢出多少次后会进行中断
    TIM_TimeBaseInit(TIM2,&TimeBaseInit);

/**************************************************/
    //配置输出比较信号

    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
    TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
    TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);//使能TIM在CCR上的预装载寄存器
    TIM_OCInitTypeDef TIM_OCInitStruct;
    TIM_OCStructInit(&TIM_OCInitStruct); //先赋予默认值，再改关键参数
    TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1; //PWM1模式
    TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High; //reference有效时输出高电平
    TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable; //开启对外输出
    TIM_OCInitStruct.TIM_Pulse=0;
    TIM_OC1Init(TIM2,&TIM_OCInitStruct);
    TIM_OC2Init(TIM2,&TIM_OCInitStruct);
    TIM_OC3Init(TIM2,&TIM_OCInitStruct);
    TIM_OC4Init(TIM2,&TIM_OCInitStruct);

/**************************************************/
    //配置GPIO引脚
    GPIOA_Init(GPIO_Pin_0,GPIO_Mode_AF_PP);
    GPIOA_Init(GPIO_Pin_1,GPIO_Mode_AF_PP);
    GPIOA_Init(GPIO_Pin_2,GPIO_Mode_AF_PP);
    GPIOA_Init(GPIO_Pin_3,GPIO_Mode_AF_PP);
    /*
        AF_PP复用引脚输出 Pin的控制权在外设端 由复用外设进行控制
        GPIOA1对应Output Compare Channel 1 对应关系定死
        但可以开其AFIO对引脚进行重映射
    */

    /************************************************************/
    /*配置时钟的中断模式*/
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //更新重置中断

/************************************************************/
    /*配置NVIC*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel=TIM2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;

    NVIC_Init(&NVIC_InitStruct);

    TIM_Cmd(TIM2,ENABLE);//开启TIM2
}

//满档400
void Duty_Set(Wheel_t Wheel,Wheel_Speed_Typdef* Wheel_Speed)
{
     TIM_OCInitTypeDef TIM_OCInitStruct;
     TIM_OCStructInit(&TIM_OCInitStruct); //先赋予默认值，再改关键参数
     TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1; //PWM1模式
     TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High; //reference有效时输出高电平
     TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable; //开启对外输出

     //根据Wheel 选择改变哪个轮子的转速
    switch (Wheel) {

        case FL:
            TIM_OCInitStruct.TIM_Pulse=(uint32_t)(Wheel_Speed->FL_Speed);
            TIM_OC1Init(TIM2,&TIM_OCInitStruct);
            break;

        case FR:
            TIM_OCInitStruct.TIM_Pulse=(uint32_t)(Wheel_Speed->FR_Speed);
            TIM_OC2Init(TIM2,&TIM_OCInitStruct);
            break;

        case BR:
             TIM_OCInitStruct.TIM_Pulse=(uint32_t)(Wheel_Speed->BR_Speed);
             TIM_OC3Init(TIM2,&TIM_OCInitStruct);
             break;

        case BL:
           TIM_OCInitStruct.TIM_Pulse=(uint32_t)(Wheel_Speed->BL_Speed);
           TIM_OC4Init(TIM2,&TIM_OCInitStruct);
           break;

        default:
            break;
    }

}




