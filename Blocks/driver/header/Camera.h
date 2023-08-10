/*
 * Camera.h
 *
 *  Created on: Jun 28, 2023
 *      Author: Lost
 */

#ifndef BLOCKS_DRIVER_HEADER_CAMERA_H_
#define BLOCKS_DRIVER_HEADER_CAMERA_H_

#include "debug.h"

typedef struct{float Theta;float Phi; float Distance;} Camera_DataSet_Typedef;

void Camera_Init(void);
void CameraData_Process(Camera_DataSet_Typedef* Camera_DataSet);

#endif /* BLOCKS_DRIVER_HEADER_CAMERA_H_ */
