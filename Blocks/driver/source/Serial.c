#include "debug.h"
#include "_ansi.h"
#include <stdio.h>
#include <stdarg.h>
#include "Serial.h"



void Serial_SendByte(Serial_Election_t Election,uint8_t Data) //发送一个字节
{

    switch (Election) {
        case Serial1:
            USART_SendData(USART1,Data); //赋值给DR寄存器 传给发送移位寄存器逐位进行发送
            while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
            break;

        case Serial2:
            USART_SendData(USART2,Data); //赋值给DR寄存器 传给发送移位寄存器逐位进行发送
            while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
            break;

        case Serial3:
            USART_SendData(USART3,Data); //赋值给DR寄存器 传给发送移位寄存器逐位进行发送
            while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET);
            break;

        default:
            break;
    }

   /*
    检测TX寄存器空信号 如果非空 FLAG=RESET 说明存在TX未进入发送移位寄存器
    需要等待FlAG=SET 确保TX已经进入移位寄存器进行发送 防止数据在传输前就被覆盖
    当TX被写入后 FLAG=RESET 被硬件自动清位

    此处逻辑即 写入TX寄存器后等待其移位到移位寄存器进行发送 TXE=SET
    进而确保每次写入TX寄存器的时候里面都是空的 不会有数据被覆盖
    */
}

void Serial_SendArray(Serial_Election_t Election,uint8_t *Array_Address,uint16_t Length)
{
    uint16_t i;

    for(i=0;i<Length;i++)
    {
        Serial_SendByte(Election,*(Array_Address+i));
    }
}

void Serial_SendString(Serial_Election_t Election,char* String_Address) //传递一个字符类型指针 同时字符串自带截止位'\0'
{
    uint16_t i;

    for(i=0;String_Address[i]!='\0';i++)
    {
        Serial_SendByte(Election,*(String_Address+i));
    }

}

uint32_t Pow(uint32_t X,uint32_t Y)
{
    uint32_t Result=1;

    while(Y--)
    {
        Result=Result*X;
    }

    return Result;

}

void Serial_SendNum(Serial_Election_t Election,uint32_t Number,uint8_t Length)
{
    uint8_t i;

    for(i=0;i<Length;i++)
    {
        Serial_SendByte(Election,Number/Pow(10,Length-i-1)%10+'0');
    }
}

//int fputc(int ch,FILE* f)
//{
//    Serial_SendByte(ch); //将printf的方向重定位到串口进行输出
//    return ch;
//}


//void Serial_Printf(char *format,...) //可变参数的子函数定义
//{
//    char String[200];
//
//    va_list arg;
//    va_start(arg,format);
//    vsprintf(String,format,arg);
//    va_end(arg);
//    Serial_SendString(String);
//
//}

//中断函数
//void USART1_IRQHandler(void)__attribute__((intterrupt()));
//
//void USART1_IRQHandler(void)
//{
//  if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==SET)
//  {
//      ReceiveData=USART_ReceiveData(USART1);
//  }
//}




