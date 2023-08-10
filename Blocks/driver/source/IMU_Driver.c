/*
 * IMU_Driver.c
 *
 *  Created on: Jun 22, 2023
 *      Author: Lost
 */


#include "debug.h"                // Device header
#include "Serial.h"

#define TX_Pin GPIO_Pin_9
#define RX_Pin GPIO_Pin_10

extern uint8_t IMU_ReceiveData[28]; //IMU传来的反馈数据 由main统一声明
//uint8_t IMU_ReceiveData[28];

typedef struct{
    float Angle_X;
    float Angle_Y;
    float Angle_Z;
    float Angular_Speed_X;
    float Angular_Speed_Y;
    float Angular_Speed_Z;
    float Accerelation_X;
    float Accerelation_Y;
    float Accerelation_Z;
}IMU_DataSetTypedef;


void IMU_Init(void)
{
/***************************************************/
    //开启时钟模块
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);

/***************************************************/
    //配置GPIO
    GPIO_InitTypeDef GPIO_InitStruture;

    GPIO_InitStruture.GPIO_Mode=GPIO_Mode_AF_PP; //选择模式 复用推挽模式 串口模块接管引脚的高低电平 输出高低电平
    GPIO_InitStruture.GPIO_Pin=TX_Pin; //选择引脚
    GPIO_InitStruture.GPIO_Speed=GPIO_Speed_50MHz; //选择GPIO的速度
    GPIO_Init(GPIOA,&GPIO_InitStruture);//传递GPIOA的参数

    GPIO_InitStruture.GPIO_Mode=GPIO_Mode_IN_FLOATING; //选择模式 浮空输入模式 引脚控制权由对应串口的TX接管 注意TX RX引脚模式不同
    GPIO_InitStruture.GPIO_Pin=RX_Pin; //选择引脚
    GPIO_InitStruture.GPIO_Speed=GPIO_Speed_50MHz; //选择GPIO的速度
    GPIO_Init(GPIOA,&GPIO_InitStruture);//传递GPIOA的参数

/***************************************************/
    //配置串口模块

    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate=115200;  //波特率
    USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None; //数据流设置
    USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx; //串口模式设置 读或写
    USART_InitStructure.USART_Parity=USART_Parity_No; //校验位
    USART_InitStructure.USART_StopBits=USART_StopBits_1; //停止位的宽度
    USART_InitStructure.USART_WordLength=USART_WordLength_8b; //帧的宽度 8bits无校验位 9 bits有1位校验位
    USART_Init(USART1,&USART_InitStructure);

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
    USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE); //串口读取寄存器非空触发

    DMA_InitTypeDef DMA_InitStruct;
    //USART1->DR 转到USART1的DR寄存器 &取寄存器的地址
    DMA_InitStruct.DMA_PeripheralBaseAddr=(uint32_t)(&USART1->DATAR); //外设首地址 读取寄存器地址
    DMA_InitStruct.DMA_PeripheralDataSize= DMA_PeripheralDataSize_Byte;//外设数据宽度
    DMA_InitStruct.DMA_PeripheralInc=DMA_PeripheralInc_Disable;//外设指针是否递增
    DMA_InitStruct.DMA_MemoryBaseAddr=(uint32_t)&IMU_ReceiveData; //内存地址
    DMA_InitStruct.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte; //内存数据宽度
    DMA_InitStruct.DMA_MemoryInc=DMA_MemoryInc_Enable ;//内存指针是否递增
    DMA_InitStruct.DMA_DIR=DMA_DIR_PeripheralSRC  ;//传输方向 SRC:外设作为源头 DIS外设作为目的地
    DMA_InitStruct.DMA_BufferSize=28; //传输计数器 传输n次 每次递减 到0停止
    DMA_InitStruct.DMA_Mode=DMA_Mode_Circular;//DMA模式 是否自动重装
    DMA_InitStruct.DMA_M2M=DMA_M2M_Disable;//软件触发还是硬件触发 1是软件触发
    DMA_InitStruct.DMA_Priority=DMA_Priority_Medium;//优先级


    DMA_Init(DMA1_Channel5,&DMA_InitStruct);//每个硬件触发都有自己对应的channel号
    DMA_Cmd(DMA1_Channel5,ENABLE);



    USART_Cmd(USART1,ENABLE); //开启串口
}


void Position_Process(IMU_DataSetTypedef* IMU_DataSet)
{
    uint8_t i;
    static float AcceX[20],AcceY[20],AngularZ[20],Accex_Sum,Accey_Sum,AngularZ_Sum;

    for(i=0;i<19;i++)
    {
        AcceX[i]=AcceX[i+1];
        AcceY[i]=AcceY[i+1];
        AngularZ[i]=AngularZ[i+1];
        Accex_Sum+=AcceX[i];
        Accey_Sum+=AcceY[i];
        AngularZ_Sum+=AngularZ[i];
    }

    AcceX[19]=(float)((int16_t)(IMU_ReceiveData[16]<<8|IMU_ReceiveData[15]))/32768*2*9.18;
    AcceY[19]=(float)((int16_t)(IMU_ReceiveData[18]<<8|IMU_ReceiveData[17]))/32768*2*9.18;
    AngularZ[19]=(float)((int16_t)(IMU_ReceiveData[9]<<8|IMU_ReceiveData[8]))/32768*180;

    IMU_DataSet->Accerelation_X=(Accex_Sum+AcceX[19])/20;
    IMU_DataSet->Accerelation_Y=(Accey_Sum+AcceY[19])/20;
    IMU_DataSet->Angle_Z=(AngularZ_Sum+AngularZ[19])/20;

    IMU_DataSet->Angle_X=(float)((int16_t)(IMU_ReceiveData[5]<<8|IMU_ReceiveData[4]))/32768*180;
    IMU_DataSet->Angle_Y=(float)((int16_t)(IMU_ReceiveData[7]<<8|IMU_ReceiveData[6]))/32768*180;
//    IMU_DataSet->Angle_Z=(float)((int16_t)(IMU_ReceiveData[9]<<8|IMU_ReceiveData[8]))/32768*180;

//    IMU_DataSet->Accerelation_X=(float)((int16_t)(IMU_ReceiveData[16]<<8|IMU_ReceiveData[15]))/32768*2*9.18;
//    IMU_DataSet->Accerelation_Y=(float)((int16_t)(IMU_ReceiveData[18]<<8|IMU_ReceiveData[17]))/32768*2*9.18;
    IMU_DataSet->Accerelation_Z=(float)((int16_t)(IMU_ReceiveData[20]<<8|IMU_ReceiveData[19]))/32768*2*9.18;

    IMU_DataSet->Angular_Speed_X=(float)((int16_t)(IMU_ReceiveData[22]<<8|IMU_ReceiveData[21]))/32768*250;
    IMU_DataSet->Angular_Speed_Y=(float)((int16_t)(IMU_ReceiveData[24]<<8|IMU_ReceiveData[23]))/32768*250;
    IMU_DataSet->Angular_Speed_Z=(float)((int16_t)(IMU_ReceiveData[26]<<8|IMU_ReceiveData[25]))/32768*250;

    Accex_Sum=0;
    Accey_Sum=0;
    AngularZ_Sum=0;
}






