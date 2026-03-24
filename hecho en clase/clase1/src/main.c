#include "LPC17xx.h"
#include <stdio.h>
#include <stdlib.h>

#define BIT(x) (1U << (x))//macro
#define PINMODE_MASK(pin) (3U << ((pin) * 2))
#define PINMODE_PULLUP(pin) (0U << ((pin) * 2))
#define PINMODE_PULLDOWN(pin) (3U << ((pin) * 2))
#define Y_LED 4
#define G_LED 5
#define R_LED 6
#define ROCK 0
#define PAPER 1
#define SCISSORS 2

void  conf_pcb(void);
void delay();
int ultimo_estado= 0;
int resultado[3][3]={
    {0,-1,1},
	{1,0,-1},
	{-1,1,0}
   };
void juego(int jugada);
int main(){
    conf_pcb();
    printf("Piedra Papel o Tijera:\n");
    while(1){
        int estado = LPC_GPIO2->FIOPIN & 7;
        if(estado!=ultimo_estado){
        	switch(estado){ //PRIMEROS 3 BITS
        	            case 0:
        	                ultimo_estado= estado;
        	                break;
        	            case 1:
        	                printf("Piedra");
        	                ultimo_estado= estado;
        	                juego(0);
        	                break;
        	            case 2:
        	                printf("Papel");
        	                ultimo_estado= estado;
        	                juego(1);
        	                break;
        	            case 4:
        	                printf("Tijeras");
        	                ultimo_estado= estado;
        	                juego(2);
        	                break;
        	            default:
        	                printf("No valido, 2 botones a la vez \n");
        	                ultimo_estado= estado;
        	                break;
        	        }

        }
    }
    return 0;
}

void juego(int jugada){
    int maquina = rand() %3;
    const char *jugadas[3] = {"Piedra", "Papel", "Tijera"};
	int salida = resultado[jugada][maquina];
	printf(" | CPU: %s", jugadas[maquina]);
	switch(salida){
	case 0:
		printf(" | Resultado : Empate \n");
		LPC_GPIO2->FIOSET = BIT(Y_LED);
		delay();
		LPC_GPIO2->FIOCLR = BIT(Y_LED);
		break;
	case 1:
		printf(" | Resultado : Gana el jugador \n");
		LPC_GPIO2->FIOSET = BIT(G_LED);
		delay();
		LPC_GPIO2->FIOCLR = BIT(G_LED);
		break;
	case -1:
		printf(" | Resultado : Gana el microcontrolador \n");
		LPC_GPIO2->FIOSET = BIT(R_LED);
		delay();
		LPC_GPIO2->FIOCLR = BIT(R_LED);
		break;
	}
}

void conf_pcb(void){
    LPC_PINCON->PINSEL4 &= ~PINMODE_MASK(G_LED);
    LPC_PINCON->PINMODE4 &= ~PINMODE_MASK(G_LED);
    LPC_PINCON->PINMODE4 |= PINMODE_PULLUP(G_LED);
    LPC_GPIO2->FIODIR |= BIT(G_LED);
    LPC_GPIO2->FIOCLR = BIT(G_LED);

    LPC_PINCON->PINSEL4 &= ~PINMODE_MASK(Y_LED);
    LPC_PINCON->PINMODE4 &= ~PINMODE_MASK(Y_LED);
    LPC_PINCON->PINMODE4 |= PINMODE_PULLUP(Y_LED);
    LPC_GPIO2->FIODIR |= BIT(Y_LED);
    LPC_GPIO2->FIOCLR = BIT(Y_LED);

    LPC_PINCON->PINSEL4 &= ~PINMODE_MASK(R_LED);
    LPC_PINCON->PINMODE4 &= ~PINMODE_MASK(R_LED);
    LPC_PINCON->PINMODE4 |= PINMODE_PULLUP(R_LED);
    LPC_GPIO2->FIODIR |= BIT(R_LED);
    LPC_GPIO2->FIOCLR = BIT(R_LED);

    LPC_PINCON->PINSEL4 &= ~PINMODE_MASK(ROCK);
    LPC_PINCON->PINMODE4 &= ~PINMODE_MASK(ROCK);
    LPC_PINCON->PINMODE4 |= PINMODE_PULLDOWN(ROCK);
    LPC_GPIO2->FIODIR &= ~BIT(ROCK);

    LPC_PINCON->PINSEL4 &= ~PINMODE_MASK(PAPER);
    LPC_PINCON->PINMODE4 &= ~PINMODE_MASK(PAPER);
    LPC_PINCON->PINMODE4 |= PINMODE_PULLDOWN(PAPER);
    LPC_GPIO2->FIODIR &= ~BIT(PAPER);

    LPC_PINCON->PINSEL4 &= ~PINMODE_MASK(SCISSORS);
    LPC_PINCON->PINMODE4 &= ~PINMODE_MASK(SCISSORS);
    LPC_PINCON->PINMODE4 |= PINMODE_PULLDOWN(SCISSORS);
    LPC_GPIO2->FIODIR &= ~BIT(SCISSORS);
}

void delay(){
	for(volatile int i=0; i<10000000; i++){
		__NOP();
	}
}
