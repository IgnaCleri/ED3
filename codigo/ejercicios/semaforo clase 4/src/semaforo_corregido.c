#ifdef __USE_CMSIS
#include "LPC17xx.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_uart.h"
#endif

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

int main(void) {
    cfg_pcb();
    cfg_systick();

    // Arranca mostrando verde.
    mostrar_estado(0);

    while (1) {
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

    // Todos apagados al inicio.
    apagar_todos();
}

void cfg_systick(void) {
    SysTick->CTRL = 0;
    SysTick->LOAD = 999999;
    SysTick->VAL  = 0;
    SysTick->CTRL = 7;
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
    static uint8_t ticks = 0;
    static uint8_t estado = 0;

    ticks++;

    if (ticks >= 50) {
        ticks = 0;

        estado++;
        if (estado > 2) {
            estado = 0;
        }

        mostrar_estado(estado);
    }
}
