/*
 * Encoder.h
 *
 *  Created on: Jun 22, 2023
 *      Author: Lost
 */

#ifndef BLOCKS_DRIVER_HEADER_ENCODER_H_
#define BLOCKS_DRIVER_HEADER_ENCODER_H_

typedef struct{uint16_t FL_CCR;uint16_t FR_CCR;uint16_t BR_CCR;uint16_t BL_CCR;} Encoder_CCR_Typedef;
extern Encoder_CCR_Typedef Encoder_CCR;

void Encoder_Init(void);
void Encoder_Get_CCR(Encoder_CCR_Typedef* Encoder_CCR);
void Clear_Encoder(void);
void Encoder_Get_Wheel_RPM(float* Measured_Wheel_RPM);

#endif /* BLOCKS_DRIVER_HEADER_ENCODER_H_ */

