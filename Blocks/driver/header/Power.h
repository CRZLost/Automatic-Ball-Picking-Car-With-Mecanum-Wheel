/*
 * Power.h
 *
 *  Created on: Jun 28, 2023
 *      Author: Lost
 */

#ifndef BLOCKS_DRIVER_HEADER_POWER_H_
#define BLOCKS_DRIVER_HEADER_POWER_H_

#include "debug.h"
typedef enum{Power_Wheel=1,Power_Motor=2} Power_Manage_Typedef;
void Power_Manage(Power_Manage_Typedef Select,uint8_t Action);
void Power_Manage_Init(void);

#endif /* BLOCKS_DRIVER_HEADER_POWER_H_ */
