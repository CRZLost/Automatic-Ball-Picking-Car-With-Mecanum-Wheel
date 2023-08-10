/*
 * GPIO_Init.h
 *
 *  Created on: Jun 21, 2023
 *      Author: Lost
 */

#ifndef GPIO_INIT
#define GPIO_INIT

void GPIOA_Init(uint16_t Pin,GPIOMode_TypeDef Mode);
void GPIOB_Init(uint16_t Pin,GPIOMode_TypeDef Mode);
void GPIOC_Init(uint16_t Pin,GPIOMode_TypeDef Mode);
void GPIOD_Init(uint16_t Pin,GPIOMode_TypeDef Mode);
void GPIOE_Init(uint16_t Pin,GPIOMode_TypeDef Mode);

#endif /* BLOCKS_DRIVER_HEADER_GPIO_INIT_H_ */
