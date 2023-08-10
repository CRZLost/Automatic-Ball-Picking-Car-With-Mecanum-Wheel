#include "debug.h"              // Device header

void Clock_Init()
{
/************************************************************/
    /*选择时钟信号源*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE); //开启APB1时钟

    TIM_InternalClockConfig(TIM1); //开启内部时钟2


/************************************************************/
    /*配置计时单元的基本参数*/
    TIM_TimeBaseInitTypeDef TimeBaseInit;

    TimeBaseInit.TIM_ClockDivision=TIM_CKD_DIV1; //确定采样频率，进行信号滤波
    TimeBaseInit.TIM_CounterMode= TIM_CounterMode_Up; //确定计数模式
    TimeBaseInit.TIM_Period=10-1; //重装值 ARR
    TimeBaseInit.TIM_Prescaler=7200-1; //预分频倍数 PSC
    TimeBaseInit.TIM_RepetitionCounter=0; //定义溢出多少次后会进行中断
    TIM_TimeBaseInit(TIM1,&TimeBaseInit);

/************************************************************/
    /*配置中断控制*/
    TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);

/************************************************************/
    /*配置NVIC*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel=TIM1_UP_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;

    NVIC_Init(&NVIC_InitStruct);

/************************************************************/
    /*启动定时器*/
    TIM_ClearFlag(TIM1, TIM_FLAG_Update);
    TIM_Cmd(TIM1,ENABLE);
}



