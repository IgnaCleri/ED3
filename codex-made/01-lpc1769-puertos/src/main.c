#include <stdint.h>
#include "LPC17xx.h"

/*
 * Ajusta estos pines segun tu placa real.
 * Formato: puerto y bit dentro del puerto.
 */
#define LED_BLINK_PORT   1U
#define LED_BLINK_PIN    18U

#define LED_INPUT_PORT   1U
#define LED_INPUT_PIN    20U

#define INPUT_PORT       0U
#define INPUT_PIN        15U

#define BIT(pin)         (1UL << (pin))

static void delay(volatile uint32_t count)
{
    while (count--)
    {
        __NOP();
    }
}

static void gpio_set_as_gpio(void)
{
    /* P1.18 y P1.20 -> GPIO (PINSEL3, 2 bits por pin) */
    LPC_PINCON->PINSEL3 &= ~((3UL << 4U) | (3UL << 8U));

    /* P0.15 -> GPIO (PINSEL0, bits 31:30) */
    LPC_PINCON->PINSEL0 &= ~(3UL << 30U);
}

static void gpio_config_direction(void)
{
    /* Salidas */
    LPC_GPIO1->FIODIR |= BIT(LED_BLINK_PIN);
    LPC_GPIO1->FIODIR |= BIT(LED_INPUT_PIN);

    /* Entrada */
    LPC_GPIO0->FIODIR &= ~BIT(INPUT_PIN);
}

int main(void)
{
    gpio_set_as_gpio();
    gpio_config_direction();

    while (1)
    {
        /* Blink del LED principal */
        LPC_GPIO1->FIOSET = BIT(LED_BLINK_PIN);
        delay(300000U);
        LPC_GPIO1->FIOCLR = BIT(LED_BLINK_PIN);
        delay(300000U);

        /* Refleja entrada en LED de estado */
        if (LPC_GPIO0->FIOPIN & BIT(INPUT_PIN))
        {
            LPC_GPIO1->FIOSET = BIT(LED_INPUT_PIN);
        }
        else
        {
            LPC_GPIO1->FIOCLR = BIT(LED_INPUT_PIN);
        }
    }
}
