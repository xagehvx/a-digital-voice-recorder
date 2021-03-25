/*
 *
 *
 *  Created on: Dec 29, 2020
 *      Author:MAKİF
 */

#include "eeprom.h"
#include "string.h"
#include "stdlib.h"

void read_ee(uint16_t regAddr, uint8_t *data, uint32_t num){
	uint8_t devAddr = 0x50;
	uint8_t arr[2];
	arr[0] = (uint8_t)(regAddr >> 8);
	arr[1] = (uint8_t)(regAddr & 0x00FF);
	write_general(devAddr, arr, 2);
	read_general(devAddr, data, num);
}

void write_ee(uint16_t regAddr, uint8_t *data, uint32_t num){
	uint8_t devAddr = 0x50;
	uint8_t arr[2];
	arr[0] = (uint8_t)(regAddr >> 8);
	arr[1] = (uint8_t)(regAddr & 0x00FF);
	uint8_t *ARR;
	ARR = (uint8_t*)malloc((num+2));
	memcpy(ARR, arr, 2);
	memcpy(ARR+2, data, num);
	write_general(devAddr, ARR, num+2);
	free(ARR);
}
