

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#define BIT(x) (1 << x)
#define BITS(l,x) (((1 << l)- 1) << x)

#include <stdio.h>

void cfg_pcb();
void cfg_systick();

int main(void) {
	cfg_pcb();
	cfg_systick();
	while(1){
		__WFI();
	}
    return 0 ;
}

void cfg_pcb(){
// usamos leds de la placa, rojo, azul, verde
// activos por bajo
// rojo: 0.22
// azul: 3.26
// verde: 3.25
// n pu, n pd, salida, modo gpio

// LED ROJO
LPC_PINCON->PINSEL1 &= ~BITS(2,12);
LPC_PINCON->PINMODE1 |= BIT(12);
LPC_PINCON->PINMODE1 &= ~BIT(13);
LPC_GPIO0->FIODIR |= BIT(22);
LPC_GPIO0->FIOCLR |= BIT(22);

// LED VERDE
LPC_PINCON->PINSEL7 &= ~BITS(2,20);
LPC_PINCON->PINMODE7 |= BIT(20);
LPC_PINCON->PINMODE7 &= ~BIT(21);
LPC_GPIO3->FIODIR |= BIT(26);
LPC_GPIO3->FIOCLR |= BIT(26);

// LED AZUL
LPC_PINCON->PINSEL7 &= ~BITS(2,18);
LPC_PINCON->PINMODE7 |= BIT(18);
LPC_PINCON->PINMODE7 &= ~BIT(19);
LPC_GPIO0->FIODIR |= BIT(25);
LPC_GPIO0->FIOCLR |= BIT(25);
}

void cfg_systick(){
	SysTick->CTRL = 0;
	SysTick->LOAD = 999999;
	SysTick->VAL = 0;
	SysTick->CTRL |= 7;
}

void SysTick_Handler(){
	static uint8_t ticks=0;
	static uint8_t estado=0;
	ticks++;
	if(ticks ==50){
		switch(estado){
		case 0: //VERDE
			LPC_GPIO0->FIOCLR |= BIT(22);
			LPC_GPIO3->FIOSET |= BIT(25);
		case 1: //AZUL
			LPC_GPIO3->FIOCLR |= BIT(25);
			LPC_GPIO3->FIOSET |= BIT(26);
		case 2://ROJO
			LPC_GPIO3->FIOCLR |= BIT(26);
			LPC_GPIO0->FIOSET |= BIT(22);
			estado = 0;
		}
		estado++;
	}
}
