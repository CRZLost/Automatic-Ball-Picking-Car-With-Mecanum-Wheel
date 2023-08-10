/*
 * GPIO_Init.c
 *
 *  Created on: Jun 21, 2023
 *      Author: Lost
 */

#include "debug.h"

void GPIOA_Init(uint16_t Pin,GPIOMode_TypeDef Mode) //区域 引脚 模式
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //选择打开时钟

    GPIO_InitTypeDef GPIO_InitStruture;

    GPIO_InitStruture.GPIO_Mode=Mode; //选择模式
    GPIO_InitStruture.GPIO_Pin=Pin; //选择引脚
    GPIO_InitStruture.GPIO_Speed=GPIO_Speed_50MHz; //选择GPIO的速度

    GPIO_Init(GPIOA,&GPIO_InitStruture);//开启GPIOA

}

void GPIOB_Init(uint16_t Pin,GPIOMode_TypeDef Mode)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //选择打开时钟

    GPIO_InitTypeDef GPIO_InitStruture;

    GPIO_InitStruture.GPIO_Mode=Mode; //选择模式
    GPIO_InitStruture.GPIO_Pin=Pin; //选择引脚
    GPIO_InitStruture.GPIO_Speed=GPIO_Speed_50MHz; //选择GPIO的速度

    GPIO_Init(GPIOB,&GPIO_InitStruture);//开启GPIOA
}

void GPIOC_Init(uint16_t Pin,GPIOMode_TypeDef Mode)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); //选择打开时钟

    GPIO_InitTypeDef GPIO_InitStruture;

    GPIO_InitStruture.GPIO_Mode=Mode; //选择模式
    GPIO_InitStruture.GPIO_Pin=Pin; //选择引脚
    GPIO_InitStruture.GPIO_Speed=GPIO_Speed_50MHz; //选择GPIO的速度

    GPIO_Init(GPIOC,&GPIO_InitStruture);//开启GPIOA
}


void GPIOD_Init(uint16_t Pin,GPIOMode_TypeDef Mode)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE); //选择打开时钟

    GPIO_InitTypeDef GPIO_InitStruture;

    GPIO_InitStruture.GPIO_Mode=Mode; //选择模式
    GPIO_InitStruture.GPIO_Pin=Pin; //选择引脚
    GPIO_InitStruture.GPIO_Speed=GPIO_Speed_50MHz; //选择GPIO的速度

    GPIO_Init(GPIOD,&GPIO_InitStruture);//开启GPIOA
}


void GPIOE_Init(uint16_t Pin,GPIOMode_TypeDef Mode)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE); //选择打开时钟

    GPIO_InitTypeDef GPIO_InitStruture;

    GPIO_InitStruture.GPIO_Mode=Mode; //选择模式
    GPIO_InitStruture.GPIO_Pin=Pin; //选择引脚
    GPIO_InitStruture.GPIO_Speed=GPIO_Speed_50MHz; //选择GPIO的速度

    GPIO_Init(GPIOE,&GPIO_InitStruture);//开启GPIOA
}
