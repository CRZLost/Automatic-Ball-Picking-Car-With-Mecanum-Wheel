#include "debug.h"
#include "Serial.h"
#include "Data_Central_Process.h"

#define TX_Pin GPIO_Pin_10
#define RX_Pin GPIO_Pin_11

extern uint8_t Received_Data[8];
void Bluetooth_Init(void)
{

/***************************************************/
    //开启时钟模块
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);

/***************************************************/
    //配置GPIO
    GPIO_InitTypeDef GPIO_InitStruture;

    GPIO_InitStruture.GPIO_Mode=GPIO_Mode_AF_PP; //选择模式 复用推挽模式 串口模块接管引脚的高低电平 输出高低电平
    GPIO_InitStruture.GPIO_Pin=TX_Pin; //选择引脚
    GPIO_InitStruture.GPIO_Speed=GPIO_Speed_50MHz; //选择GPIO的速度
    GPIO_Init(GPIOB,&GPIO_InitStruture);//传递GPIOA的参数

    GPIO_InitStruture.GPIO_Mode=GPIO_Mode_IN_FLOATING; //选择模式 浮空输入模式 引脚控制权由对应串口的TX接管 注意TX RX引脚模式不同
    GPIO_InitStruture.GPIO_Pin=RX_Pin; //选择引脚
    GPIO_InitStruture.GPIO_Speed=GPIO_Speed_50MHz; //选择GPIO的速度
    GPIO_Init(GPIOB,&GPIO_InitStruture);//传递GPIOA的参数

/***************************************************/
    //配置串口模块

    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate=9600;  //波特率
    USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None; //数据流设置
    USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx; //串口模式设置 读或写
    USART_InitStructure.USART_Parity=USART_Parity_No; //校验位
    USART_InitStructure.USART_StopBits=USART_StopBits_1; //停止位的宽度
    USART_InitStructure.USART_WordLength=USART_WordLength_8b; //帧的宽度 8bits无校验位 9 bits有1位校验位
    USART_Init(USART3,&USART_InitStructure);

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


    DMA_DeInit(DMA1_Channel3);
    DMA_InitTypeDef DMA_InitStruct;
    //USART1->DR 转到USART1的DR寄存器 &取寄存器的地址
    DMA_InitStruct.DMA_PeripheralBaseAddr=(uint32_t)&USART3->DATAR; //外设首地址 读取寄存器地址
    DMA_InitStruct.DMA_PeripheralDataSize= DMA_PeripheralDataSize_Byte;//外设数据宽度
    DMA_InitStruct.DMA_PeripheralInc=DMA_PeripheralInc_Disable;//外设指针是否递增
    DMA_InitStruct.DMA_MemoryBaseAddr=(uint32_t)Received_Data; //内存地址
    DMA_InitStruct.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte; //内存数据宽度
    DMA_InitStruct.DMA_MemoryInc=DMA_MemoryInc_Enable ;//内存指针是否递增
    DMA_InitStruct.DMA_DIR=DMA_DIR_PeripheralSRC  ;//传输方向 SRC:外设作为源头 DIS外设作为目的地
    DMA_InitStruct.DMA_BufferSize=8; //传输计数器 传输n次 每次递减 到0停止
    DMA_InitStruct.DMA_Mode=DMA_Mode_Circular;//DMA模式 是否自动重装
    DMA_InitStruct.DMA_M2M=DMA_M2M_Disable;//软件触发还是硬件触发 1是软件触发
    DMA_InitStruct.DMA_Priority=DMA_Priority_Medium;//优先级


    DMA_Init(DMA1_Channel3,&DMA_InitStruct);//每个硬件触发都有自己对应的channel号

    USART_Cmd(USART3,ENABLE); //开启串口
    DMA_Cmd(DMA1_Channel3,ENABLE);
    USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE); //串口读取寄存器非空触发


}


void Plot(Serial_Election_t Election,float* Data,uint8_t ChannelNum)
{
    uint8_t Tem[4],i,j; //将浮点数字的4字节内存依次发送
    uint8_t EndCmd[4]={0x00,0x00,0x80,0x7f}; //协议终止符

    for(i=0;i<ChannelNum;i++)
    {
        for(j=0;j<4;j++)
        {
            Tem[j]=*((uint8_t*)Data+4*i+j); //Data浮点数指针转为字节型依次赋值发送
            Serial_SendByte(Election,Tem[j]);
        }

    }

    for(i=0;i<4;i++)
    {
        Serial_SendByte(Election,EndCmd[i]);
    }
}


void Vofa_Cmd_Analyze(char* Control_Mode)
{

   float Judge;
   uint8_t i;

   Judge=*((float*)Received_Data);
   if(Judge==1200||Judge==-1200)
   {
       if(*((float*)Received_Data)==-1200)
       {*Control_Mode='M';}
       if(*((float*)Received_Data)==1200)
       {*Control_Mode='A';}
      for(i=0;i<8;i++)
      {
          Received_Data[i]=0;
      }
   }
   if(Judge==1400)
   {
       *Control_Mode='S';//停止运行
       for(i=0;i<8;i++)
       {
          Received_Data[i]=0;
       }
   }

}





