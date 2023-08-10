/*
 * Encoder.c
 *
 *  Created on: Jun 22, 2023
 *      Author: Lost
 */



#include "debug.h"                 // Device header
#include "Encoder.h"

void Encoder_Init(void)
{

/***************************************************************************************************/
    //Left_Back Motor
/***************************************************************************************/
    //配置频率时钟 频率对应Channel1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //选择打开时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); //打开TIM3端口对应的时钟

/*****************************************/
    //配置GPIO
    GPIO_InitTypeDef GPIO_InitStruture;

    GPIO_InitStruture.GPIO_Mode= GPIO_Mode_IN_FLOATING; //选择模式
    GPIO_InitStruture.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7; //选择引脚
    GPIO_InitStruture.GPIO_Speed=GPIO_Speed_50MHz; //选择GPIO的速度
    GPIO_Init(GPIOA,&GPIO_InitStruture);//开启GPIOA

/**********************************************/
    //配置计时器TIM3的计数单元

    TIM_TimeBaseInitTypeDef TimeBaseInit;

    TimeBaseInit.TIM_ClockDivision=TIM_CKD_DIV1; //确定采样频率，进行信号滤波
    TimeBaseInit.TIM_CounterMode= TIM_CounterMode_Up; //确定计数模式
    TimeBaseInit.TIM_Period=65536-1; //重装值
    TimeBaseInit.TIM_Prescaler=1-1; //预分频倍数
    TimeBaseInit.TIM_RepetitionCounter=0; //定义溢出多少次后会进行中断
    TIM_TimeBaseInit(TIM3,&TimeBaseInit);

/**********************************************/
    //配置输入捕获频率引脚部分
    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_ICStructInit(&TIM_ICInitStructure); //赋初始值
    TIM_ICInitStructure.TIM_Channel=TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICFilter=0xF; //滤波设置 只有N个点相同才会发生信号改变 因此可以过滤信号
    TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising; //高低电平极性不反转
    TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;//是否对采集的信号分频
    TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI; //选择是直连还是交叉连接
    TIM_ICInit(TIM3,&TIM_ICInitStructure);

    TIM_ICInitStructure.TIM_Channel=TIM_Channel_2;
    TIM_ICInitStructure.TIM_ICFilter=0xF; //滤波设置 只有N个点相同才会发生信号改变 因此可以过滤信号
    TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising; //高低电平极性不反转
    TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;//是否对采集的信号分频
    TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI; //选择是直连还是交叉连接
    TIM_ICInit(TIM3,&TIM_ICInitStructure);

/**********************************************/
    /*
        使用计时器的Encoder从模式 使用外部输入时钟
        根据AB信号的相对极性决定+-1
        TIM3 X4模式 两个信号都不反转
    */
    TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
    TIM_Cmd(TIM3,ENABLE);


/***************************************************************************************************/
        //Left_Front Motor
    /***************************************************************************************/
        //配置频率时钟 频率对应Channel1
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //选择打开时钟
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE); //打开TIM3端口对应的时钟

    /*****************************************/
        //配置GPIO

        GPIO_InitStruture.GPIO_Mode= GPIO_Mode_IN_FLOATING; //选择模式
        GPIO_InitStruture.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7; //选择引脚
        GPIO_InitStruture.GPIO_Speed=GPIO_Speed_50MHz; //选择GPIO的速度
        GPIO_Init(GPIOB,&GPIO_InitStruture);//开启GPIOA

    /**********************************************/
        //配置计时器TIM3的计数单元

        TimeBaseInit.TIM_ClockDivision=TIM_CKD_DIV1; //确定采样频率，进行信号滤波
        TimeBaseInit.TIM_CounterMode= TIM_CounterMode_Up; //确定计数模式
        TimeBaseInit.TIM_Period=65536-1; //重装值
        TimeBaseInit.TIM_Prescaler=1-1; //预分频倍数
        TimeBaseInit.TIM_RepetitionCounter=0; //定义溢出多少次后会进行中断
        TIM_TimeBaseInit(TIM4,&TimeBaseInit);

    /**********************************************/
        //配置输入捕获频率引脚部分

        TIM_ICStructInit(&TIM_ICInitStructure); //赋初始值
        TIM_ICInitStructure.TIM_Channel=TIM_Channel_1;
        TIM_ICInitStructure.TIM_ICFilter=0xF; //滤波设置 只有N个点相同才会发生信号改变 因此可以过滤信号
        TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising; //高低电平极性不反转
        TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;//是否对采集的信号分频
        TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI; //选择是直连还是交叉连接
        TIM_ICInit(TIM4,&TIM_ICInitStructure);

        TIM_ICInitStructure.TIM_Channel=TIM_Channel_2;
        TIM_ICInitStructure.TIM_ICFilter=0xF; //滤波设置 只有N个点相同才会发生信号改变 因此可以过滤信号
        TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising; //高低电平极性不反转
        TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;//是否对采集的信号分频
        TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI; //选择是直连还是交叉连接
        TIM_ICInit(TIM4,&TIM_ICInitStructure);


/**********************************************/
    /*
        使用计时器的Encoder从模式 使用外部输入时钟
        根据AB信号的相对极性决定+-1
        TIM3 X4模式 两个信号都不反转
    */
    TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
    TIM_Cmd(TIM4,ENABLE);



/***************************************************************************************************/
        //Right_Front Motor
    /***************************************************************************************/
        //配置频率时钟 频率对应Channel1
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); //选择打开时钟
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE); //打开TIM3端口对应的时钟

    /*****************************************/
        //配置GPIO

        GPIO_InitStruture.GPIO_Mode= GPIO_Mode_IN_FLOATING; //选择模式
        GPIO_InitStruture.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7; //选择引脚
        GPIO_InitStruture.GPIO_Speed=GPIO_Speed_50MHz; //选择GPIO的速度
        GPIO_Init(GPIOC,&GPIO_InitStruture);//开启GPIOA

    /**********************************************/
        //配置计时器TIM3的计数单元

        TimeBaseInit.TIM_ClockDivision=TIM_CKD_DIV1; //确定采样频率，进行信号滤波
        TimeBaseInit.TIM_CounterMode= TIM_CounterMode_Up; //确定计数模式
        TimeBaseInit.TIM_Period=65536-1; //重装值
        TimeBaseInit.TIM_Prescaler=1-1; //预分频倍数
        TimeBaseInit.TIM_RepetitionCounter=0; //定义溢出多少次后会进行中断
        TIM_TimeBaseInit(TIM8,&TimeBaseInit);

    /**********************************************/
        //配置输入捕获频率引脚部分

        TIM_ICStructInit(&TIM_ICInitStructure); //赋初始值
        TIM_ICInitStructure.TIM_Channel=TIM_Channel_1;
        TIM_ICInitStructure.TIM_ICFilter=0xF; //滤波设置 只有N个点相同才会发生信号改变 因此可以过滤信号
        TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising; //高低电平极性不反转
        TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;//是否对采集的信号分频
        TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI; //选择是直连还是交叉连接
        TIM_ICInit(TIM8,&TIM_ICInitStructure);

        TIM_ICInitStructure.TIM_Channel=TIM_Channel_2;
        TIM_ICInitStructure.TIM_ICFilter=0xF; //滤波设置 只有N个点相同才会发生信号改变 因此可以过滤信号
        TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising; //高低电平极性不反转
        TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;//是否对采集的信号分频
        TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI; //选择是直连还是交叉连接
        TIM_ICInit(TIM8,&TIM_ICInitStructure);

    /**********************************************/
        /*
            使用计时器的Encoder从模式 使用外部输入时钟
            根据AB信号的相对极性决定+-1
            TIM3 X4模式 两个信号都不反转
        */
        TIM_EncoderInterfaceConfig(TIM8,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
        TIM_Cmd(TIM8,ENABLE);


/***************************************************************************************************/
        //Right_Back Motor
    /***************************************************************************************/
        //配置频率时钟 频率对应Channel1
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE); //选择打开时钟
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_AFIO,ENABLE); //打开TIM3端口对应的时钟

    /*****************************************/
        //配置GPIO

        /*重映射TIM9的通道*/
        GPIO_PinRemapConfig(GPIO_FullRemap_TIM9,ENABLE);
        GPIO_InitStruture.GPIO_Mode= GPIO_Mode_IN_FLOATING; //选择模式
        GPIO_InitStruture.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_11; //选择引脚
        GPIO_InitStruture.GPIO_Speed=GPIO_Speed_50MHz; //选择GPIO的速度
        GPIO_Init(GPIOD,&GPIO_InitStruture);//开启GPIOA

    /**********************************************/
        //配置计时器TIM3的计数单元

        TimeBaseInit.TIM_ClockDivision=TIM_CKD_DIV1; //确定采样频率，进行信号滤波
        TimeBaseInit.TIM_CounterMode= TIM_CounterMode_Up; //确定计数模式
        TimeBaseInit.TIM_Period=65536-1; //重装值
        TimeBaseInit.TIM_Prescaler=1-1; //预分频倍数
        TimeBaseInit.TIM_RepetitionCounter=0; //定义溢出多少次后会进行中断
        TIM_TimeBaseInit(TIM9,&TimeBaseInit);

    /**********************************************/
        //配置输入捕获频率引脚部分

        TIM_ICStructInit(&TIM_ICInitStructure); //赋初始值
        TIM_ICInitStructure.TIM_Channel=TIM_Channel_1;
        TIM_ICInitStructure.TIM_ICFilter=0xF; //滤波设置 只有N个点相同才会发生信号改变 因此可以过滤信号
        TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising; //高低电平极性不反转
        TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;//是否对采集的信号分频
        TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI; //选择是直连还是交叉连接
        TIM_ICInit(TIM9,&TIM_ICInitStructure);

        TIM_ICInitStructure.TIM_Channel=TIM_Channel_2;
        TIM_ICInitStructure.TIM_ICFilter=0xF; //滤波设置 只有N个点相同才会发生信号改变 因此可以过滤信号
        TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising; //高低电平极性不反转
        TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;//是否对采集的信号分频
        TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI; //选择是直连还是交叉连接
        TIM_ICInit(TIM9,&TIM_ICInitStructure);

    /**********************************************/
        /*
            使用计时器的Encoder从模式 使用外部输入时钟
            根据AB信号的相对极性决定+-1
            TIM3 X4模式 两个信号都不反转
        */
        TIM_EncoderInterfaceConfig(TIM9,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
        TIM_Cmd(TIM9,ENABLE);



}

void Encoder_Get_CCR(Encoder_CCR_Typedef* Encoder_CCR)
{
    Encoder_CCR->BL_CCR=(uint16_t)TIM_GetCounter(TIM3);
    Encoder_CCR->FL_CCR=(uint16_t)TIM_GetCounter(TIM4);
    Encoder_CCR->FR_CCR=(uint16_t)TIM_GetCounter(TIM8);
    Encoder_CCR->BR_CCR=(uint16_t)TIM_GetCounter(TIM9);
}

void Clear_Encoder(void)
{
    TIM_SetCounter(TIM3,0);//重置Encoder 计数
    TIM_SetCounter(TIM4,0);//重置Encoder 计数
    TIM_SetCounter(TIM8,0);//重置Encoder 计数
    TIM_SetCounter(TIM9,0);//重置Encoder 计数
}

void Encoder_Get_Wheel_RPM(float* Measured_Wheel_RPM)
{
    uint16_t i,j;
    int16_t CCR_Sum=0;
    float CCR_Ave[4];
    static int16_t CCR[4][20]; //储存3行20列的CCR 每行代表一个轮子 BL=[0] FL=[1] FR=[2] BR=[3]
    static uint16_t flag=1;

    if(flag)
    {
        for(i=0;i<4;i++)
        {
            for(j=0;j<20;j++)
            {
                CCR[i][j]=0;
            }
            CCR_Ave[i]=0;
        }
        flag=0;
    }

    //储存20个CCR数值求和取平均去毛刺
    for(i=0;i<4;i++)
    {
        for(j=0;j<20;j++)
          {
              if(j<18)
              {
                  CCR[i][j]=CCR[i][j+1]; //储存CCR 数据前移
              }
              else
              {
                 switch (i) {
                    case 0:
                        CCR[i][j]=(int16_t)TIM_GetCounter(TIM3); //BL
                        break;
                    case 1:
                       CCR[i][j]=(int16_t)TIM_GetCounter(TIM4); //FL
                       break;
                    case 2:
                       CCR[i][j]=(int16_t)TIM_GetCounter(TIM8); //FR
                       break;
                    case 3:
                       CCR[i][j]=(int16_t)TIM_GetCounter(TIM9); //BR
                       break;
                    default:
                        break;
                }
              }
              CCR_Sum+=CCR[i][j];
          }
      CCR_Ave[i]=CCR_Sum*0.05;
      CCR_Sum=0;
    }

    for(i=0;i<4;i++)
    {
      *(Measured_Wheel_RPM+i)=(*(CCR_Ave+i))*7.69231; // 1/200:采样周期  60:一分钟60秒 4 X4模式 390 车轮一圈390个脉冲
    }
}

