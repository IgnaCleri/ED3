#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include <stdio.h>

#include <stdint.h>

#define BIT(x) (1U << (x))
#define BITS(l,x) (((1U << (l)) - 1U) << (x))

#define LED_ROJO_PIN   22U   // P0.22
#define LED_VERDE_PIN  25U   // P3.25
#define LED_AZUL_PIN   26U   // P3.26

void cfg_pcb(void);
void cfg_systick(void);
void apagar_todos(void);
void mostrar_estado(uint8_t estado);
void conf_ext_int(void);
void conf_isr_gpio(void);
volatile uint32_t frecuencia = 10;
volatile uint8_t print_pendiente = 0;

int main(void) {
    cfg_pcb();
    cfg_systick();
    //conf_ext_int();
    conf_isr_gpio();

    // Arranca mostrando verde.
    mostrar_estado(0);

    while (1) {
    	if (print_pendiente) {
    	            print_pendiente = 0;
    	            printf("frecuencia = %lu\r\n", frecuencia);
    	        }

        __WFI();
    }

    return 0;
}

void cfg_pcb(void) {
    // LEDs activos por bajo:
    // rojo  -> P0.22
    // verde -> P3.25
    // azul  -> P3.26

    // LED rojo - P0.22
    LPC_PINCON->PINSEL1 &= ~BITS(2, 12);
    LPC_PINCON->PINMODE1 |= BIT(12);
    LPC_PINCON->PINMODE1 &= ~BIT(13);
    LPC_GPIO0->FIODIR |= BIT(LED_ROJO_PIN);

    // LED verde - P3.25
    LPC_PINCON->PINSEL7 &= ~BITS(2, 18);
    LPC_PINCON->PINMODE7 |= BIT(18);
    LPC_PINCON->PINMODE7 &= ~BIT(19);
    LPC_GPIO3->FIODIR |= BIT(LED_VERDE_PIN);

    // LED azul - P3.26
    LPC_PINCON->PINSEL7 &= ~BITS(2, 20);
    LPC_PINCON->PINMODE7 |= BIT(20);
    LPC_PINCON->PINMODE7 &= ~BIT(21);
    LPC_GPIO3->FIODIR |= BIT(LED_AZUL_PIN);

    //Boton p2.10 entrada, con pull up, modo 01(eint0).
    //LPC_PINCON->PINSEL4 &= ~BITS(2, 20); //limpio el campo de funcion de P2.10
    //LPC_PINCON->PINSEL4 |= BIT(20); //P2.10 modo 01 = EINT0
    //LPC_PINCON->PINMODE4 &= ~BITS(2,20); //P2.10 pull up
    //LPC_GPIO2->FIODIR &= ~BIT(10); //P2.10 entrada

    //Boton p2.10 entrada, con pull up, modo 00(gpio).
    LPC_PINCON->PINSEL4 &= ~BITS(2, 20); //limpio el campo de funcion de P2.10
    LPC_PINCON->PINMODE4 &= ~BITS(2,20); //P2.10 pull up
    LPC_GPIO2->FIODIR &= ~BIT(10); //P2.10 entrada

    // Todos apagados al inicio.
    apagar_todos();
}

void cfg_systick(void) {
    SysTick->CTRL = 0;
    SysTick->LOAD = 999999;
    SysTick->VAL  = 0;
    SysTick->CTRL = 7;
}

// void conf_ext_int(void){
//     NVIC->ICER[0] |= BIT(EINT0_IRQn); //deshabilito EINT0 en NVIC mientras configuro

//     LPC_SC->EXTMODE |= BIT(0); //EINT0 sensible a flanco
//     LPC_SC->EXTPOLAR &= ~BIT(0); //EINT0 por flanco descendente
//     LPC_SC->EXTINT = BIT(0); //limpio el flag de EINT0 antes de habilitar

//     NVIC->ICPR[0] |= BIT(EINT0_IRQn); //limpio el pending de EINT0 en NVIC
//     NVIC->IP[EINT0_IRQn] = (10U << 3); //prioridad media para EINT0
//     NVIC->ISER[0] |= BIT(EINT0_IRQn); //habilito EINT0 en NVIC
// }

void conf_isr_gpio(void){
	NVIC->ICER[0] |= BIT(EINT3_IRQn); //deshabilito EINT3 en NVIC mientras configuro
	LPC_GPIOINT->IO2IntEnF |= BIT(10); // configuro ISR gpio flanco de bajada (si quiero isr por cambio de puerto debo habilitar ambos flancos)
	LPC_GPIOINT->IO2IntClr = BIT(10); // limpio bandera para P2.10
	NVIC->ISER[0] |= BIT(EINT3_IRQn); //habilito EINT3 en NVIC
}

void apagar_todos(void) {
    LPC_GPIO0->FIOSET = BIT(LED_ROJO_PIN);
    LPC_GPIO3->FIOSET = BIT(LED_VERDE_PIN) | BIT(LED_AZUL_PIN);
}

void mostrar_estado(uint8_t estado) {
    apagar_todos();

    switch (estado) {
        case 0: // VERDE
            LPC_GPIO3->FIOCLR = BIT(LED_VERDE_PIN);
            break;

        case 1: // AZUL
            LPC_GPIO3->FIOCLR = BIT(LED_AZUL_PIN);
            break;

        case 2: // ROJO
            LPC_GPIO0->FIOCLR = BIT(LED_ROJO_PIN);
            break;

        default:
            break;
    }
}

void SysTick_Handler(void) {
    static uint32_t ticks = 0;
    static uint32_t estado = 0;

    ticks++;

    if (ticks >= frecuencia) {
        ticks = 0;

        estado++;
        if (estado > 2) {
            estado = 0;
        }

        mostrar_estado(estado);
    }
}


// void EINT0_IRQHandler(void){
//     LPC_SC->EXTINT = BIT(0); //limpio la causa real de la interrupcion externa
//     if(frecuencia == 10){
//     	frecuencia = 25;
//     }
//     else if(frecuencia == 25){
//     	frecuencia = 50;
//     }
//     else if(frecuencia==50){
//     	frecuencia=100;
//     	//printf("f:500 \n");
//     }
//     else if(frecuencia == 100){
//     	frecuencia=200;
//     	//printf("f:50 \n");
//     }
//     else{
//     	frecuencia = 10;
//     }
//     print_pendiente = 1;
// }

void EINT3_IRQHandler(void){
    LPC_GPIOINT->IO2IntClr = BIT(10); //limpio la causa real de la interrupcion externa
    if(frecuencia == 10){
    	frecuencia = 25;
    }
    else if(frecuencia == 25){
    	frecuencia = 50;
    }
    else if(frecuencia==50){
    	frecuencia=100;
    	//printf("f:500 \n");
    }
    else if(frecuencia == 100){
    	frecuencia=200;
    	//printf("f:50 \n");
    }
    else{
    	frecuencia = 10;
    }
    print_pendiente = 1;
}
