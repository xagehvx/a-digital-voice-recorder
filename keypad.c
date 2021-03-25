/*
 * keypad.c
 *
 *  Created on: Dec 19, 2020
 *      Author: Mehmet Akif/171024027
 *      description:In this section, necessary pins of
 *      the keypad have been activated in order for the keypad
 *      buttons to receive data. Next, the interrupt was created
 *      for the buttons. Thanks to this interrupt, when the button
 *      is pressed, it is processed according to priority.
 */
#include "keypad.h"

/*to the reach delay func*/
extern void delay_ms(volatile unsigned int);
extern uint32_t k;
void keypad_init(void){

	   /* Enable GPIOB and GPIOA clock */
	    RCC->IOPENR |= (1U << 1);
	    RCC->IOPENR |= (1U << 0);


	    /* Setup PA8,PB9,PB5 and PB4 as output (rows)*/
	    GPIOA->MODER &= ~(3U << 2*8);
	    GPIOA->MODER |= (1U << 2*8);//PA8 is output

	    GPIOB->MODER &= ~(3U << 2*9);
	    GPIOB->MODER |= (1U << 2*9);//PB9 is output

	    GPIOB->MODER &= ~(3U << 2*5);
	    GPIOB->MODER |= (1U << 2*5);//PB5 is output

	    GPIOB->MODER &= ~(3U << 2*4);
	    GPIOB->MODER |= (1U << 2*4);//PB4 is output



	    /* Setup PA9,PB0,PB2 and PB8  as input(colums) */
	    GPIOA->MODER &= ~(3U << 2*9);// PA9 is input
	    GPIOA->PUPDR |= (2U << 2*9); // Pull-down mode

	    GPIOB->MODER &= ~(3U << 2*0);//PB0 is input
	    GPIOB->PUPDR |= (2U << 2*0); // Pull-down mode

	    GPIOB->MODER &= ~(3U << 2*2);//PB2 is input
	    GPIOB->PUPDR |= (2U << 2*2); // Pull-down mode

	    GPIOB->MODER &= ~(3U << 2*8);//PB8 is input
	    GPIOB->PUPDR |= (2U << 2*8); // Pull-down mode


	    /*setup interrupts for inputs*/
	    EXTI->EXTICR[2] |=(0U << 8*1);//PA9
	    EXTI->EXTICR[0] |=(1U << 0);//PB0
	    EXTI->EXTICR[0] |=(1U << 2*8);//PB2
	    EXTI->EXTICR[2] |=(1U << 0);//PB8


	    /*rising edge*/
	    EXTI->RTSR1 |= (1U << 9);// 9th pin
	    EXTI->RTSR1 |= (1U << 0);// 0th pin
	    EXTI->RTSR1 |= (1U << 2);// 2th pin
	    EXTI->RTSR1 |= (1U << 8);// 8th pin


	    /* MASK*/
	    EXTI->IMR1 |= (1U << 9);// 9th pin
	    EXTI->IMR1 |= (1U << 0);// 0th pin
	    EXTI->IMR1 |= (1U << 2);// 2th pin
	    EXTI->IMR1 |= (1U << 8);// 8th pin


	    /*NVIC*/
	    NVIC_SetPriority(EXTI0_1_IRQn,0);
	    NVIC_EnableIRQ(EXTI0_1_IRQn);

	    NVIC_SetPriority(EXTI2_3_IRQn,0);
	    NVIC_EnableIRQ(EXTI2_3_IRQn);

	    NVIC_SetPriority(EXTI4_15_IRQn,0);
	    NVIC_EnableIRQ(EXTI4_15_IRQn);

}
/* interrut for PB0*/
void EXTI0_1_IRQHandler(void){
	if (EXTI->RPR1 & (1U << 0)){// check if pending register equal 1

		clear_rows_keypad();
		/* make PA8 enable*/
		GPIOA->ODR ^=( 1U << 8);
		if ((GPIOB->IDR >> 0) & 1){//check if PB0 equal 1
			/* #=(F) character*/
			Keypad_data(15);

		}
		/*make PA8 disable*/
		GPIOA->ODR ^=( 1U << 8); // PA8

		/* make PB9 enable*/
		GPIOB->ODR ^=( 1U << 9); // PB9
		if ((GPIOB->IDR >> 0) & 1){
			/* 9 character*/
			Keypad_data(9);

		}
		/* make PB9 disable*/
		GPIOB->ODR ^=( 1U << 9); // PB9

		/* make PB5 enable*/
		GPIOB->ODR ^=( 1U << 5); // PB5
		if ((GPIOB->IDR >> 0) & 1){
			/* 6 character*/
			Keypad_data(6);

		}
		/* make PB5 disable*/
		GPIOB->ODR ^=( 1U << 5); // PB5

		/* make PB4 enable*/
		GPIOB->ODR ^=( 1U << 4); // PB4
		if ((GPIOB->IDR >> 0) & 1){
			/* 3 character*/
			Keypad_data(3);

		}
		/* make PB4 disable*/
		GPIOB->ODR ^=( 1U << 4); // PB4


		set_rows_keypad();
		/*clear interrupt for clear pending register */
		EXTI->RPR1 |= (1U << 0);
	}
}

/* interrut for PB2*/
void EXTI2_3_IRQHandler(void){

	if (EXTI->RPR1 & (1U << 2)){// check if pending register equal 1

		clear_rows_keypad();
		/*make PA8 enable*/
		GPIOA->ODR ^=( 1U << 8); // PA8
		if ((GPIOB ->IDR >> 2) & 1){//check if PB2 equal 1
			/* D character*/
			Keypad_data(13);

		}
		/*make PA8 disable*/
		GPIOA->ODR ^=( 1U << 8); // PA8

		/* make PB9 enable*/
		GPIOB->ODR ^=( 1U << 9); // PB9
		if ((GPIOB ->IDR >> 2) & 1){
			/* C character*/
			Keypad_data(12);

		}
		/* make PB9 disable*/
		GPIOB->ODR ^=( 1U << 9); // PB9

		/* make PB5 enable*/
		GPIOB->ODR ^=( 1U << 5); // PB5
		if ((GPIOB ->IDR >> 2) & 1){
			/* B character*/
			Keypad_data(11);

		}
		/* make PB5 disable*/
		GPIOB->ODR ^=( 1U << 5); // PB5

		/* make PB4 enable*/
		GPIOB->ODR ^=( 1U << 4); // PB4
		if ((GPIOB ->IDR >> 2) & 1){
			/* A character*/
			Keypad_data(10);

		}
		/* make PB4 disable*/
		GPIOB->ODR ^=( 1U << 4); // PB4


		set_rows_keypad();
		/*clear interrupt for clear pending register */
		EXTI->RPR1 |= (1U << 2);
	}
}

/* interrut for PB8 and PA9*/
void EXTI4_15_IRQHandler(void){

			/*interrut for PB8*/
		if (EXTI->RPR1 & (1U << 8)){// check if pending register equal 1
			clear_rows_keypad();
			/*make PA8 enable*/
			GPIOA->ODR ^=( 1U << 8); // PA8
			if ((GPIOB ->IDR >> 8) & 1){//check if PB8 equal 1
				/* *(E) character*/
				Keypad_data(14);

			}
			/*make PA8 disable*/
			GPIOA->ODR ^=( 1U << 8); // PA8

			/* make PB9 enable*/
			GPIOB->ODR ^=( 1U << 9); // PB9
			if ((GPIOB ->IDR >> 8) & 1){
				/* 7 character*/
				Keypad_data(7);

			}
			/* make PB9 disable*/
			GPIOB->ODR ^=( 1U << 9); // PB9

			/* make PB5 enable*/
			GPIOB->ODR ^=( 1U << 5); // PB5
			if ((GPIOB ->IDR >> 8) & 1){
				/* 4 character*/
				Keypad_data(4);

			}
			/* make PB5 disable*/
			GPIOB->ODR ^=( 1U << 5); // PB5

			/* make PB4 enable*/
			GPIOB->ODR ^=( 1U << 4); // PB4
			if ((GPIOB ->IDR >> 8) & 1){
				/* 1 character*/
				Keypad_data(1);

			}
			/* make PB4 disable*/
			GPIOB->ODR ^=( 1U << 4); // PB4


			set_rows_keypad();
			/*clear interrupt for clear pending register */
			EXTI->RPR1 |= (1U << 8);
		}

		/*interrut for PA9*/
		if (EXTI->RPR1 & (1U << 9)){// check if pending register equal 1
			clear_rows_keypad();
			/*make PA8 enable*/
			GPIOA->ODR ^=( 1U << 8); //check if PA8 equal 1
			if ((GPIOA ->IDR >> 9) & 1){
				/* 0 character*/
				Keypad_data(0);

			}
			/*make PA8 disable*/
			GPIOA->ODR ^=( 1U << 8); // PA8

			/* make PB9 enable*/
			GPIOB->ODR ^=( 1U << 9); // PB9
			if ((GPIOA ->IDR >> 9) & 1){
				/* 8 character*/
				Keypad_data(8);

			}
			/* make PB9 disable*/
			GPIOB->ODR ^=( 1U << 9); // PB9

			/* make PB5 enable*/
			GPIOB->ODR ^=( 1U << 5); // PB5
			if ((GPIOA ->IDR >> 9) & 1){
				/* 5 character*/
				Keypad_data(5);

			}
			/* make PB5 disable*/
			GPIOB->ODR ^=( 1U << 5); // PB5

			/* make PB4 enable*/
			GPIOB->ODR ^=( 1U << 4); // PB4
			if ((GPIOA ->IDR >> 9) & 1){
				/* 2 character*/
				Keypad_data(2);

			}
			/* make PB4 disable*/
			GPIOB->ODR ^=( 1U << 4); // PB4


			set_rows_keypad();

			/*clear interrupt for clear pending register */
			EXTI->RPR1 |= (1U << 9);
		}

}


void clear_rows_keypad(void){
		/*clearing the rows here*/
		GPIOA->ODR &= ~(1U << 8);//PA8
		GPIOB->ODR &= ~(1U << 9);//PB9
		GPIOB->ODR &= ~(1U << 5);//PB5
		GPIOB->ODR &= ~(1U << 4);//PB4
}

void set_rows_keypad(void){
		/*seting the rows here*/
		GPIOA->ODR |= (1U << 8);//PA8
		GPIOB->ODR |= (1U << 9);//PB9
		GPIOB->ODR |= (1U << 5);//PB5
		GPIOB->ODR |= (1U << 4);//PB4

}

void Keypad_data(uint8_t input){

	switch(input){

			case 0:
	//			delete_selected_track();

			break;

			case 1:
	//			play/resume(); //selected
				k=1;

				break;
			case 2:
	//			pause();
				k=3;

			case 10:
	//			record();
				k=0;

				break;

		}
}


