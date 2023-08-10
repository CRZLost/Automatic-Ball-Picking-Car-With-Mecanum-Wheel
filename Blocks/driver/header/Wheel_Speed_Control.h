/*
 * Wheel_Speeed_Control.h
 *
 *  Created on: Jun 24, 2023
 *      Author: Lost
 */

#ifndef BLOCKS_DRIVER_HEADER_WHEEL_SPEED_CONTROL_H_
#define BLOCKS_DRIVER_HEADER_WHEEL_SPEED_CONTROL_H_

typedef struct{float BL_RPM;float FL_RPM;float FR_RPM;float BR_RPM;}Wheel_Speed_Reference_Typedef;
void Wheel_Speed_Control(Wheel_Speed_Reference_Typedef* Wheel_Speed_Reference,float* Measured_Wheel_Speed);

#endif /* BLOCKS_DRIVER_HEADER_WHEEL_SPEED_CONTROL_H_ */
