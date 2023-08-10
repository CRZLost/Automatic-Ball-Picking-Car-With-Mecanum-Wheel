/*
 * Bluetooth.h
 *
 *  Created on: Jun 22, 2023
 *      Author: Lost
 */

#ifndef BLOCKS_DRIVER_HEADER_BLUETOOTH_H_
#define BLOCKS_DRIVER_HEADER_BLUETOOTH_H_

extern Serial_Election_t Election;
void Bluetooth_Init(void);
void Plot(Serial_Election_t Election,float* Data,uint8_t ChannelNum);
void Vofa_Cmd_Analyze(char* Control_Mode);

#endif /* BLOCKS_DRIVER_HEADER_BLUETOOTH_H_ */
