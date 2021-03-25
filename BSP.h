/*
 * BSP.h
 *
 *  Created on: Jan 8, 2021
 *      Author:
 */

#ifndef BSP_H_
#define BSP_H_


#include "ADC.h"
#include "display.h"
#include "eeprom.h"


void BSP_init();

void TIM1_init();
void TIM3_init();
void soundfunc(uint8_t a, uint8_t *ARR);

uint8_t sound_buffer[100];

#endif /* BSP_H_ */
