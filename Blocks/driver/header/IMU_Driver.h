/*
 * IMU_Driver.h
 *
 *  Created on: Jun 22, 2023
 *      Author: Lost
 */

#ifndef BLOCKS_DRIVER_HEADER_IMU_DRIVER_H_
#define BLOCKS_DRIVER_HEADER_IMU_DRIVER_H_

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
void IMU_Init(void);
void Position_Process(IMU_DataSetTypedef* IMU_DataSet);


#endif /* BLOCKS_DRIVER_HEADER_IMU_DRIVER_H_ */
