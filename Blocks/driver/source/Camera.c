/*
 * Camera.c
 *
 *  Created on: Jun 28, 2023
 *      Author: Lost
 */
#include "debug.h"
#include "Camera.h"

extern char CameraData[12];//承接Openmv传来的数据流 由main函数统一声明

void Camera_Init(void)
{

/************************************************/
    //串口初始化
    /***************************************************/
        //开启时钟模块
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2,ENABLE);

    /***************************************************/
        //配置GPIO
        GPIO_InitTypeDef GPIO_InitStruture;

        GPIO_InitStruture.GPIO_Mode=GPIO_Mode_AF_PP; //选择模式 复用推挽模式 串口模块接管引脚的高低电平 输出高低电平
        GPIO_InitStruture.GPIO_Pin=GPIO_Pin_10; //选择引脚
        GPIO_InitStruture.GPIO_Speed=GPIO_Speed_50MHz; //选择GPIO的速度
        GPIO_Init(GPIOC,&GPIO_InitStruture);//传递GPIOA的参数

        GPIO_InitStruture.GPIO_Mode=GPIO_Mode_IN_FLOATING; //选择模式 浮空输入模式 引脚控制权由对应串口的TX接管 注意TX RX引脚模式不同
        GPIO_InitStruture.GPIO_Pin=GPIO_Pin_11; //选择引脚
        GPIO_InitStruture.GPIO_Speed=GPIO_Speed_50MHz; //选择GPIO的速度
        GPIO_Init(GPIOC,&GPIO_InitStruture);//传递GPIOA的参数

    /***************************************************/
        //配置串口模块

        USART_InitTypeDef USART_InitStructure;
        USART_InitStructure.USART_BaudRate=115200;  //波特率
        USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None; //数据流设置
        USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx; //串口模式设置 读或写
        USART_InitStructure.USART_Parity=USART_Parity_No; //校验位
        USART_InitStructure.USART_StopBits=USART_StopBits_1; //停止位的宽度
        USART_InitStructure.USART_WordLength=USART_WordLength_8b; //帧的宽度 8bits无校验位 9 bits有1位校验位
        USART_Init(UART4,&USART_InitStructure);

    /***************************************************/
        //配置NVIC和USART中断

    //  USART_ITConfig(USART1,USART_IT_RXNE,ENABLE); //开启串口的读取中断
    //  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //NVIC分组方式 全程序只能有一种分组方式
    //  NVIC_InitTypeDef NVIC_InitStructure;
    //  NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;//修改位 配置NVIC接收线
    //  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE; //使能
    //  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0; //配置抢占优先级
    //  NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;//配置响应优先级
    //  NVIC_Init(&NVIC_InitStructure);

    /***************************************************/
        //配置DMA


        DMA_DeInit(DMA2_Channel3);
        DMA_InitTypeDef DMA_InitStruct;
        //USART1->DR 转到USART1的DR寄存器 &取寄存器的地址
        DMA_InitStruct.DMA_PeripheralBaseAddr=(uint32_t)&UART4->DATAR; //外设首地址 读取寄存器地址
        DMA_InitStruct.DMA_PeripheralDataSize= DMA_PeripheralDataSize_Byte;//外设数据宽度
        DMA_InitStruct.DMA_PeripheralInc=DMA_PeripheralInc_Disable;//外设指针是否递增
        DMA_InitStruct.DMA_MemoryBaseAddr=(uint32_t)CameraData; //内存地址
        DMA_InitStruct.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte; //内存数据宽度
        DMA_InitStruct.DMA_MemoryInc=DMA_MemoryInc_Enable ;//内存指针是否递增
        DMA_InitStruct.DMA_DIR=DMA_DIR_PeripheralSRC  ;//传输方向 SRC:外设作为源头 DIS外设作为目的地
        DMA_InitStruct.DMA_BufferSize=12; //传输计数器 传输n次 每次递减 到0停止
        DMA_InitStruct.DMA_Mode=DMA_Mode_Circular;//DMA模式 是否自动重装
        DMA_InitStruct.DMA_M2M=DMA_M2M_Disable;//软件触发还是硬件触发 1是软件触发
        DMA_InitStruct.DMA_Priority=DMA_Priority_Medium;//优先级


        DMA_Init(DMA2_Channel3,&DMA_InitStruct);//每个硬件触发都有自己对应的channel号

        USART_Cmd(UART4,ENABLE); //开启串口
        DMA_Cmd(DMA2_Channel3,ENABLE);
        USART_DMACmd(UART4,USART_DMAReq_Rx,ENABLE); //串口读取寄存器非空触发
}


void CameraData_Process(Camera_DataSet_Typedef* Camera_DataSet)
{

    //!!!!!!!!!!!!!!!1注意这里变量的排序需要核对
    Camera_DataSet->Distance=*((float*)CameraData+0);
    Camera_DataSet->Phi=*((float*)CameraData+1);
    Camera_DataSet->Theta=*((float*)CameraData+2);
}



