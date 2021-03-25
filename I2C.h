/*
 *
 *
 *  Created on: Dec 29, 2020
 *      Author: MAKİF
 */

#ifndef I2C_H_
#define I2C_H_

#include "main.h"


void I2C_init_();
void read_general(uint8_t devAddr, uint8_t *data, uint32_t num);
void write_general(uint8_t devAddr, uint8_t *data, uint32_t num);


#endif /* I2C_H_ */
