 /*
 * BSP.c
 *
 *  Created on: Jan 8, 2021
 *      Author:
 */

#include "BSP.h"
#include "string.h"
#include "stdlib.h"

uint32_t k=0;
int sayac;

void BSP_init(){

	__disable_irq();

//		SSD_init();
		init_ADC();
		TIM1_init();
		TIM3_init();
		I2C_init_();
		sayac = 0;
	__enable_irq();


}


void TIM1_init(){

	RCC->APBENR2 |= (1U<< 11);// enable time1 module clock

	TIM1->CR1=0;// zero out the control register just in case
	TIM1->CR1 |= (1<<7);	// ARPE
	TIM1->CNT=0;// zero out sayac

	/*0.1 ms interrupt	 */

	TIM1->PSC=10;
	TIM1->ARR=160;

	TIM1->DIER |= (1 << 0);// update interrupt enable
	TIM1->CR1 |= (1 << 0);// 	tım1 enable

	NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn, 3);
	NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);

}

void TIM1_BRK_UP_TRG_COM_IRQHandler(void)
{

	display_SSD();

	TIM1->SR &= ~(1U<<0); //clear update status register

}

void TIM3_init(void){

	RCC->IOPENR |= 7; /*??????????????????*/

	//setup PA6 as AF2
	GPIOA->MODER &= ~(3U << 2*6);
	GPIOA->MODER |= (2U << 2*6);

	// choose AF2 from mux
	GPIOA->AFR[0] &= ~(0xFU << 4*6);
	GPIOA->AFR[0] |= (1U << 4*6);

	////////////////
	RCC->APBENR1 |= (1U<< 1);// enable timer3 clock

	TIM3->CR1=0;// zero out the control register just in case
	TIM3->CR1 |= (1U << 7);	// ARPE
	TIM3->CNT=0;// zero out sayac

	//100us -> 0.10ms
	TIM3->PSC = 1;
	TIM3->ARR = 255;
	TIM3->DIER |= (1 << 0);// update interrupt enable

	/////////////

	//PWM FOR PA6 TIM3_CH1
	TIM3->CCMR1 |=(1 << 3); // output compare preload enable
	TIM3->CCMR1 &= ~(1U << 16); //0
	TIM3->CCMR1 &= ~(0xFU << 4);
	TIM3->CCMR1 |= (0x6U << 4); // mode 1 enable
	TIM3->CCER |= (1U << 0);

	TIM3->CCR1 = 8;

	TIM3->CR1 |= (1 << 0);// 	tim3 enable

	NVIC_SetPriority(TIM3_IRQn, 2);
	NVIC_EnableIRQ(TIM3_IRQn);

}

void TIM3_IRQHandler(void){

	TIM3->SR &= ~(1U << 0); //clear update status register

	ADC1->CR |= (1U << 2);//Bit 2 ADSTART: ADC start conversion command

	while(0 == (ADC1->ISR & (1U << 2)));


	uint8_t transporter;
	if(sayac == 10000){
		k = 1;
		sayac = 0;
	}
	switch(k){
	case 0:
		//ADC
		if(sayac < 10000){
			transporter = (uint8_t)ADC1->DR;

				transporter = (uint8_t)((transporter-127)*2);
				soundfunc(transporter, sound_buffer);

			if(!(sayac % 100)){
				write_ee((uint16_t)sayac, sound_buffer, 100);
			    for(int i = 0xFFFF; i>0; i--);
			}
			sayac++;
		}
		break;
	case 1:
		//PWM
		if(sayac<10000){

				read_ee((uint16_t)sayac, &transporter, 1);

				TIM3->CCR1 = (uint32_t)(transporter);


			sayac++;
		}
		break;
	case 3:
		//idle();
		break;

	}


}


void soundfunc(uint8_t a, uint8_t *ARR){
	static int i = 0;

		if (i<100){
			ARR[i] = a;
			i++;
		}
		else{
		i = 0;
		}



}

