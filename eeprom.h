/*
 *
 *
 *  Created on: Dec 29, 2020
 *      Author: MAKİF
 */

#ifndef EEPROM_H_
#define EEPROM_H_

#include "main.h"
#include "I2C.h"

void read_ee(uint16_t regAddr, uint8_t *data, uint32_t num);
void write_ee(uint16_t regAddr, uint8_t *data, uint32_t num);

#endif /* EEPROM_H_ */

