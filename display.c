/*
 * display.c
 *
 *  Created on: Dec 19, 2020
 *      Author: Mehmet Akif/171024027
 *
 */

#include "display.h"

void init_SSD(){
	GPIOB->MODER &= ~(3U << 2*1);
	GPIOB->MODER |= (1U << 2*1);//PB1 is output

	GPIOB->MODER &= ~(3U << 2*3);
	GPIOB->MODER |= (1U << 2*3);//PB3 is output

	GPIOB->MODER &= ~(3U << 2*6);
	GPIOB->MODER |= (1U << 2*6);//PB6 is output

	GPIOB->MODER &= ~(3U << 2*7);
	GPIOB->MODER |= (1U << 2*7);//PB7 is output

	GPIOA->MODER &= ~(3U << 2*0);
	GPIOA->MODER |= (1U << 2*0);//PA0 is output

	GPIOA->MODER &= ~(3U << 2*1);
	GPIOA->MODER |= (1U << 2*1);//PA1 is output

	GPIOA->MODER &= ~(3U << 2*4);
	GPIOA->MODER |= (1U << 2*4);//PA4 is output

	GPIOA->MODER &= ~(3U << 2*5);
	GPIOA->MODER |= (1U << 2*5);//PA5 is output

	GPIOA->MODER &= ~(3U << 2*6);
	GPIOA->MODER |= (1U << 2*6);//PA6 is output

	GPIOA->MODER &= ~(3U << 2*7);
	GPIOA->MODER |= (1U << 2*7);//PA7 is output

	GPIOA->MODER &= ~(3U << 2*11);
	GPIOA->MODER |= (1U << 2*11);//PA11 is output

	GPIOA->MODER &= ~(3U << 2*12);
	GPIOA->MODER |= (1U << 2*12);//PA12 is output


}

void display_SSD(){

	static int i = 0;

		if(i == 1){
			GPIOA->ODR |= (1U << 7); //PA7
			GPIOB->ODR &= ~(1U << 6); //PB6
			GPIOB->ODR &= ~(1U << 7); //PB7
			GPIOB->ODR &= ~(1U << 1); //PB1
			printDigit_SSD(Display.Digits[0]);
			GPIOA->ODR |= ( 1U << 6); // PA6

		}
		else if(i == 10){
			GPIOA->ODR &= ~(1U << 7); //PA7
			GPIOB->ODR |= (1U << 6); //PB6
			GPIOB->ODR &= ~(1U << 7); //PB7
			GPIOB->ODR &= ~(1U << 1); //PB1
			printDigit_SSD(Display.Digits[1]);
			GPIOA->ODR |= ( 1U << 6); // PA6

		}

		else if(i == 20){
			GPIOA->ODR &= ~(1U << 7); //PA7
			GPIOB->ODR &= ~(1U << 6); //PB6
			GPIOB->ODR |= (1U << 7); //PB7
			GPIOB->ODR &= ~(1U << 1); //PB1
			printDigit_SSD(Display.Digits[2]);
			GPIOA->ODR |= ( 1U << 6); // PA6

		}
		else if(i == 30){
			GPIOA->ODR &= ~(1U << 7); //PA7
			GPIOB->ODR &= ~(1U << 6); //PB6
			GPIOB->ODR &= ~(1U << 7); //PB7
			GPIOB->ODR |= (1U << 1); //PB1
			printDigit_SSD(Display.Digits[3]);
			GPIOA->ODR |= ( 1U << 6); // PA6

		}
		else if(i == 40) i = 0;

		i++;




}

void printDigit_SSD(uint8_t x){

		switch(x){
		case 0:		//0

			GPIOB->ODR &= ~( 1U << 3); // PB3
			GPIOA->ODR &= ~( 1U << 0); // PA0
			GPIOA->ODR &= ~( 1U << 1); // PA1
			GPIOA->ODR &= ~( 1U << 4); // PA4
			GPIOA->ODR &= ~( 1U << 5); // PA5
			GPIOA->ODR &= ~( 1U << 12); // PA12
			GPIOA->ODR |=  ( 1U << 11); // PA11

			break;

		case 1:		//1
			GPIOB->ODR |= ( 1U << 3); // PB3
			GPIOA->ODR &= ~( 1U << 0); // PA0
			GPIOA->ODR &= ~( 1U << 1); // PA1
			GPIOA->ODR |= ( 1U << 4); // PA4
			GPIOA->ODR |= ( 1U << 5); // PA5
			GPIOA->ODR |= ( 1U << 12); // PA12
			GPIOA->ODR |= ( 1U << 11); // PA11

			break;

		case 2:		//2
			GPIOB->ODR &= ~( 1U << 3); // PB3
			GPIOA->ODR &= ~( 1U << 0); // PA0
			GPIOA->ODR |=  ( 1U << 1); // PA1
			GPIOA->ODR &= ~( 1U << 4); // PA4
			GPIOA->ODR &= ~( 1U << 5); // PA5
			GPIOA->ODR |=  ( 1U << 12); // PA12
			GPIOA->ODR &= ~( 1U << 11); // PA11

			break;

		case 3:		//3

			GPIOB->ODR &= ~( 1U << 3); // PB3
			GPIOA->ODR &= ~( 1U << 0); // PA0
			GPIOA->ODR &= ~( 1U << 1); // PA1
			GPIOA->ODR &= ~( 1U << 4); // PA4
			GPIOA->ODR |=  ( 1U << 5); // PA5
			GPIOA->ODR |=  ( 1U << 12); // PA12
			GPIOA->ODR &= ~( 1U << 11); // PA11

			break;

		case 4:		//4
			GPIOB->ODR |=  ( 1U << 3); // PB3
			GPIOA->ODR &= ~( 1U << 0); // PA0
			GPIOA->ODR &= ~( 1U << 1); // PA1
			GPIOA->ODR |=  ( 1U << 4); // PA4
			GPIOA->ODR |=  ( 1U << 5); // PA5
			GPIOA->ODR &= ~( 1U << 12); // PA12
			GPIOA->ODR &= ~( 1U << 11); // PA11

			break;

		case 5:		//5

			GPIOB->ODR &= ~( 1U << 3); // PB3
			GPIOA->ODR |=  ( 1U << 0); // PA0
			GPIOA->ODR &= ~( 1U << 1); // PA1
			GPIOA->ODR &= ~( 1U << 4); // PA4
			GPIOA->ODR |=  ( 1U << 5); // PA5
			GPIOA->ODR &= ~( 1U << 12); // PA12
			GPIOA->ODR &= ~( 1U << 11); // PA11

			break;

		case 6:		//6
			GPIOB->ODR &= ~( 1U << 3); // PB3
			GPIOA->ODR |=  ( 1U << 0); // PA0
			GPIOA->ODR &= ~( 1U << 1); // PA1
			GPIOA->ODR &= ~( 1U << 4); // PA4
			GPIOA->ODR &= ~( 1U << 5); // PA5
			GPIOA->ODR &= ~( 1U << 12); // PA12
			GPIOA->ODR &= ~( 1U << 11); // PA11

			break;

		case 7:		//7

			GPIOB->ODR &= ~( 1U << 3); // PB3
			GPIOA->ODR &= ~( 1U << 0); // PA0
			GPIOA->ODR &= ~( 1U << 1); // PA1
			GPIOA->ODR |=  ( 1U << 4); // PA4
			GPIOA->ODR |=  ( 1U << 5); // PA5
			GPIOA->ODR |=  ( 1U << 12); // PA12
			GPIOA->ODR |=  ( 1U << 11); // PA11

			break;

		case 8:		//8

			GPIOB->ODR &= ~( 1U << 3); // PB3
			GPIOA->ODR &= ~( 1U << 0); // PA0
			GPIOA->ODR &= ~( 1U << 1); // PA1
			GPIOA->ODR &= ~( 1U << 4); // PA4
			GPIOA->ODR &= ~( 1U << 5); // PA5
			GPIOA->ODR &= ~( 1U << 12); // PA12
			GPIOA->ODR &= ~( 1U << 11); // PA11

			break;

		case 9:		//9
			GPIOB->ODR &= ~( 1U << 3); // PB3
			GPIOA->ODR &= ~( 1U << 0); // PA0
			GPIOA->ODR &= ~( 1U << 1); // PA1
			GPIOA->ODR &= ~( 1U << 4); // PA4
			GPIOA->ODR |=  ( 1U << 5); // PA5
			GPIOA->ODR &= ~( 1U << 12); // PA12
			GPIOA->ODR &= ~( 1U << 11); // PA11

			break;

		case 10://A

			GPIOB->ODR &= ~( 1U << 3); // PB3
			GPIOA->ODR &= ~( 1U << 0); // PA0
			GPIOA->ODR &= ~( 1U << 1); // PA1
			GPIOA->ODR &= ~( 1U << 4); // PA4
			GPIOA->ODR &= ~( 1U << 5); // PA5
			GPIOA->ODR |=  ( 1U << 12); // PA12
			GPIOA->ODR &= ~( 1U << 11); // PA11



			break;

		case 11://B

			GPIOB->ODR |=  ( 1U << 3); // PB3
			GPIOA->ODR |=  ( 1U << 0); // PA0
			GPIOA->ODR &= ~( 1U << 1); // PA1
			GPIOA->ODR &= ~( 1U << 4); // PA4
			GPIOA->ODR &= ~( 1U << 5); // PA5
			GPIOA->ODR &= ~( 1U << 12); // PA12
			GPIOA->ODR &= ~( 1U << 11); // PA11


			break;

		case 12://C
			GPIOB->ODR &= ~( 1U << 3); // PB3
			GPIOA->ODR |=  ( 1U << 0); // PA0
			GPIOA->ODR |=  ( 1U << 1); // PA1
			GPIOA->ODR &= ~( 1U << 4); // PA4
			GPIOA->ODR &= ~( 1U << 5); // PA5
			GPIOA->ODR &= ~( 1U << 12); // PA12
			GPIOA->ODR |=  ( 1U << 11); // PA11

			break;

		case 13://D
			GPIOB->ODR |=  ( 1U << 3); // PB3
			GPIOA->ODR &= ~( 1U << 0); // PA0
			GPIOA->ODR &= ~( 1U << 1); // PA1
			GPIOA->ODR &= ~( 1U << 4); // PA4
			GPIOA->ODR &= ~( 1U << 5); // PA5
			GPIOA->ODR |=  ( 1U << 12); // PA12
			GPIOA->ODR &= ~( 1U << 11); // PA11

			break;

		case 14://E
			GPIOB->ODR &= ~( 1U << 3); // PB3
			GPIOA->ODR |=  ( 1U << 0); // PA0
			GPIOA->ODR |=  ( 1U << 1); // PA1
			GPIOA->ODR &= ~( 1U << 4); // PA4
			GPIOA->ODR &= ~( 1U << 5); // PA5
			GPIOA->ODR &= ~( 1U << 12); // PA12
			GPIOA->ODR &= ~( 1U << 11); // PA11


			break;

		case 15: //F
			GPIOB->ODR &= ~( 1U << 3); // PB3
			GPIOA->ODR |=  ( 1U << 0); // PA0
			GPIOA->ODR |=  ( 1U << 1); // PA1
			GPIOA->ODR |=  ( 1U << 4); // PA4
			GPIOA->ODR &= ~( 1U << 5); // PA5
			GPIOA->ODR &= ~( 1U << 12); // PA12
			GPIOA->ODR &= ~( 1U << 11); // PA11
			break;


		case 30: //u
			GPIOB->ODR |=  ( 1U << 3); // PB3
			GPIOA->ODR |=  ( 1U << 0); // PA0
			GPIOA->ODR &= ~( 1U << 1); // PA1
			GPIOA->ODR &= ~( 1U << 4); // PA4
			GPIOA->ODR &= ~( 1U << 5); // PA5
			GPIOA->ODR |=  ( 1U << 12); // PA12
			GPIOA->ODR |=  ( 1U << 11); // PA11
			break;

		case 31: //L
			GPIOB->ODR |=  ( 1U << 3); // PB3
			GPIOA->ODR |=  ( 1U << 0); // PA0
			GPIOA->ODR |=  ( 1U << 1); // PA1
			GPIOA->ODR &= ~( 1U << 4); // PA4
			GPIOA->ODR &= ~( 1U << 5); // PA5
			GPIOA->ODR &= ~( 1U << 12); // PA12
			GPIOA->ODR |=  ( 1U << 11); // PA11
			break;

		case 32: //n
			GPIOB->ODR |=  ( 1U << 3); // PB3
			GPIOA->ODR |=  ( 1U << 0); // PA0
			GPIOA->ODR &= ~( 1U << 1); // PA1
			GPIOA->ODR |=  ( 1U << 4); // PA4
			GPIOA->ODR &= ~( 1U << 5); // PA5
			GPIOA->ODR |=  ( 1U << 12); // PA12
			GPIOA->ODR &= ~( 1U << 11); // PA11
			break;

		case 33: //D
			GPIOB->ODR |=  ( 1U << 3); // PB3
			GPIOA->ODR &= ~( 1U << 0); // PA0
			GPIOA->ODR &= ~( 1U << 1); // PA1
			GPIOA->ODR &= ~( 1U << 4); // PA4
			GPIOA->ODR &= ~( 1U << 5); // PA5
			GPIOA->ODR |=  ( 1U << 12); // PA12
			GPIOA->ODR &= ~( 1U << 11); // PA11
			break;

		case 34: // negative sign
			GPIOB->ODR |= ( 1U << 3); // PB3
			GPIOA->ODR |= ( 1U << 0); // PA0
			GPIOA->ODR |= ( 1U << 1); // PA1
			GPIOA->ODR |= ( 1U << 4); // PA4
			GPIOA->ODR |= ( 1U << 5); // PA5
			GPIOA->ODR |= ( 1U << 12); // PA12
			GPIOA->ODR &= ~( 1U << 11); // PA11
			break;

		case 35: // space
			GPIOB->ODR |= ( 1U << 3); // PB3
			GPIOA->ODR |= ( 1U << 0); // PA0
			GPIOA->ODR |= ( 1U << 1); // PA1
			GPIOA->ODR |= ( 1U << 4); // PA4
			GPIOA->ODR |= ( 1U << 5); // PA5
			GPIOA->ODR |= ( 1U << 12); // PA12
			GPIOA->ODR |= ( 1U << 11); // PA11
			break;
		}
}




void utility_SSD(float var){

	int number = (int)var;

	float i = 0.0;



	number = (int)(var * i);

	int temp = number / 10;
	Display.Digits[0] = (uint8_t)(number - (temp*10));

	temp = number / 100;
	Display.Digits[1] = (uint8_t)((number - (temp * 100)) / 10);

	temp = number / 1000;
	Display.Digits[2] = (uint8_t)((number - (temp * 1000)) / 100);

	temp = number / 10000;
	Display.Digits[3] = (uint8_t)((number - (temp * 10000)) / 1000);



}

