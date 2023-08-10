/*
 * Serial.h
 *
 *  Created on: Jun 22, 2023
 *      Author: Lost
 */


#ifndef BLOCKS_DRIVER_HEADER_SERIAL_H_
#define BLOCKS_DRIVER_HEADER_SERIAL_H_

typedef enum{Serial1=1,Serial2=2,Serial3=3} Serial_Election_t;
extern Serial_Election_t Serial_Election;

void Serial_SendByte(Serial_Election_t Election,uint8_t Data);
void Serial_SendArray(Serial_Election_t Election,uint8_t *Array_Address,uint16_t Length);
void Serial_SendString(Serial_Election_t Election,char* String_Address);
uint32_t Pow(uint32_t X,uint32_t Y);
void Serial_SendNum(Serial_Election_t Election,uint32_t Number,uint8_t Length);
//void Serial_Printf(char *format,...);

#endif /* BLOCKS_DRIVER_HEADER_SERIAL_H_ */
