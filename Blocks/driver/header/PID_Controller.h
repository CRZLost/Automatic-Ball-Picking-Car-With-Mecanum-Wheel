/*
 * PID_Controller.h
 *
 *  Created on: Jun 22, 2023
 *      Author: Lost
 */

#ifndef BLOCKS_DRIVER_HEADER_PID_CONTROLLER_H_
#define BLOCKS_DRIVER_HEADER_PID_CONTROLLER_H_

#include "debug.h"
typedef struct
{
    double Kp;
    double Ki;
    double Kd;
    float UpperLimit;
} PID_Parameter;

void Wheel_PID_Controller(PID_Parameter* Parameter,double (*Error)[3],double* Output,int32_t UpperLimit,int32_t LowerLimit);
void Rotate_PID_Controller(float* R_Theta,float Current_Orient,float* Angular_Reference,uint8_t Spin_Flag,uint8_t Rotate_Pause_Flag,float UpperLimit,float LowerLimit);
void Clear_Data(double* Data,uint8_t Size);

#endif /* BLOCKS_DRIVER_HEADER_PID_CONTROLLER_H_ */
