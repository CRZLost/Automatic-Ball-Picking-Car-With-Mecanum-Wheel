/*
 * Filter.h
 *
 *  Created on: Jul 9, 2023
 *      Author: Lost
 */

#ifndef BLOCKS_DRIVER_HEADER_FILTER_H_
#define BLOCKS_DRIVER_HEADER_FILTER_H_

float High_Pass_Filter(float Real_Time_ms,float Real_Time_s,float Signal,float Cuttoff_Frequency);
float Low_Pass_Filter(float Real_Time_ms,float Real_Time_s,float Signal,float Cuttoff_Frequency);

#endif /* BLOCKS_DRIVER_HEADER_FILTER_H_ */
