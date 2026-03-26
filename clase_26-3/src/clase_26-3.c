#include "LPC17xx.h"
#include <stdio.h>
#include <stdlib.h>


void  conf_pcb(void);

uint8_t frecuencia = 50;

int main()
{

	conf_pcb();

	while(1)
	{

		__NOP();

	}

}

void EINT0_IRQHandler()
{

	if(frecuencia == 50)
	{

		frecuencia = 100;

	}
	else
	{

		frecuencia = 50;

	}

}


void SysTick_Handler ()
{

	static uint8_t ticks = 0;
	static uint8_t estado = 0;
	ticks++;

	if(ticks == frecuencia)
	{

		ticks = 0;

		switch(estado)                   //Azul Rojo verde
		{
		case 0:

		LPC_GPIO0->FIOSET = 0b01 << 22;  // Apago LED Rojo y Enciendo LED Verde
		LPC_GPIO3->FIOCLR = 0b01 << 25;
		estado++;

	    break;
		case 1:

		LPC_GPIO3->FIOSET = 0b01 << 25;  // Apago LED Verde y Enciendo LED Azul
		LPC_GPIO3->FIOCLR = 0b01 << 26;
		estado++;

		break;
		case 2:

		LPC_GPIO3->FIOSET = 0b01 << 26;  // Apago LED Azul y Enciendo LED Verde
		LPC_GPIO0->FIOCLR = 0b01 << 22;
		estado = 0;

		break;
		default:
		break;

		}



	}

}

void conf_pcb(void)
{

	// INT EXTERNA
	LPC_SC->EXTMODE  |= 0b01;               // la INT externa ya que puede generar interrupciones
	LPC_SC->EXTPOLAR &= ~(0b01);            // Ponemos que interrumpa en flanco descendente

	LPC_PINCON->PINSEL4 &= ~(0b10 << 20);   // Limpiamos el bit 21
	LPC_PINCON->PINSEL4 |=  (0b01 << 20);   // Ponemos bit 20 en 1, EINT0
	LPC_PINCON->PINMODE4 &= ~(0b00 << 20);  // Ponemos Pullup en el pin P2.10

	NVIC->ISER[0] |=   0b01 << 18;
	NVIC->IP[4]   &= ~(0b11111 << 19);      // Aseguramos un 0 en los bits para que quede el 5
	NVIC->IP[4]   |= 0b00101 << 19;         // Ponemos un 5 (101) en el apartado de prioridad del INTEXT0
		                                     // Prioridad 101 (5) a la int externa

	// LED ROJO
	LPC_PINCON->PINSEL1  &= ~(0b11 << 12);  // Pongo en GPIO (Borro con 11 ya que al negarlo se va a 0)
	LPC_PINCON->PINMODE1 &= ~(0b01 << 12);   // No pongo ni pullup ni pulldown
	LPC_PINCON->PINMODE1 |= 0b10 << 12;     // pongo 10 en 12:13
	LPC_GPIO0->FIODIR    |= 0b01 << 22;
	LPC_GPIO0->FIOSET    =  0b01 << 22;     // Pongo en 0 el bit 22 del puerto 0

	// LED VERDE
	LPC_PINCON->PINSEL7  &= ~(0b11 << 18);  // Lo pongo ne modo GPIO
	LPC_PINCON->PINMODE7 &= ~(0b01 << 18);  // No pongo ni pullup ni pulldown
	LPC_PINCON->PINMODE7 |= 0b10 << 18;     // pongo 10 en 18:19
	LPC_GPIO3->FIODIR    |= 0b01 << 25;     // Ponemos en 1 (salida) el bit 26


	// LED AZUL
	LPC_PINCON->PINSEL7  &= ~(0b11 << 20);  // Lo pongo ne modo GPIO
	LPC_PINCON->PINMODE7 &= ~(0b01 << 20);  // No pongo ni pullup ni pulldown
	LPC_PINCON->PINMODE7 |= 0b10 << 20;     // pongo 10 en 20:22
	LPC_GPIO3->FIODIR    |= 0b01 << 26;     // Ponemos en 1 (salida) Bit 25

	LPC_GPIO3->FIOSET    =  0b11 << 25;     // Limpio bit 25 y 26 del puerto 3


	// SysTick
	SysTick->CTRL = 0;                      // ctrl load val ctrl
	SysTick->LOAD = 999999;                 //En teoria 10ms
	SysTick->VAL  = 0;                      //
	SysTick->CTRL |= 0b111;                 // Pongo ENABLE 1, TICKINIT 1,  CLOCKSRC 1, clock de CPU, habilitado
	                                        // Y contando


}

