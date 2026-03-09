#include <stdint.h>
#include "LPC17xx.h"

/*
 * Demo GPIO LPC1769:
 * - Salida push-pull
 * - Salida open-drain
 * - Entrada pull-up
 * - Entrada pull-down
 * - Entrada repeater
 * - Entrada sin pull-up/pull-down (tristate)
 *
 * Ajusta los pines segun tu placa real.
 */
#define LED_BLINK_PIN              18U    /* P1.18, salida push-pull */
#define LED_STATUS_PIN             20U    /* P1.20, salida push-pull */
#define OPEN_DRAIN_OUT_PIN         19U    /* P1.19, salida open-drain */

#define INPUT_PULLUP_PIN           15U    /* P0.15 */
#define INPUT_PULLDOWN_PIN         16U    /* P0.16 */
#define INPUT_REPEATER_PIN         17U    /* P0.17 */
#define INPUT_TRISTATE_PIN         18U    /* P0.18 */

#define BIT(pin)         (1UL << (pin))

typedef enum
{
    GPIO_MODE_PULLUP = 0U,
    GPIO_MODE_REPEATER = 1U,
    GPIO_MODE_TRISTATE = 2U,
    GPIO_MODE_PULLDOWN = 3U
} GpioPinMode;

static void delay(volatile uint32_t count)
{
    while (count--)
    {
        __NOP();
    }
}

static void gpio_set_function_as_gpio(void)
{
    /* P1.18, P1.19 y P1.20 -> GPIO (PINSEL3) */
    LPC_PINCON->PINSEL3 &= ~((3UL << 4U) | (3UL << 6U) | (3UL << 8U));

    /* P0.15 -> GPIO (PINSEL0, bits 31:30) */
    LPC_PINCON->PINSEL0 &= ~(3UL << 30U);

    /* P0.16, P0.17 y P0.18 -> GPIO (PINSEL1) */
    LPC_PINCON->PINSEL1 &= ~((3UL << 0U) | (3UL << 2U) | (3UL << 4U));
}

static void gpio_set_pin_mode_p0(uint32_t pin, GpioPinMode mode)
{
    uint32_t shift;

    if (pin <= 15U)
    {
        shift = pin * 2U;
        LPC_PINCON->PINMODE0 = (LPC_PINCON->PINMODE0 & ~(3UL << shift)) | ((uint32_t)mode << shift);
    }
    else
    {
        shift = (pin - 16U) * 2U;
        LPC_PINCON->PINMODE1 = (LPC_PINCON->PINMODE1 & ~(3UL << shift)) | ((uint32_t)mode << shift);
    }
}

static void gpio_config_input_modes(void)
{
    gpio_set_pin_mode_p0(INPUT_PULLUP_PIN, GPIO_MODE_PULLUP);
    gpio_set_pin_mode_p0(INPUT_PULLDOWN_PIN, GPIO_MODE_PULLDOWN);
    gpio_set_pin_mode_p0(INPUT_REPEATER_PIN, GPIO_MODE_REPEATER);
    gpio_set_pin_mode_p0(INPUT_TRISTATE_PIN, GPIO_MODE_TRISTATE);
}

static void gpio_config_open_drain(void)
{
    /* Habilita open-drain en P1.19 */
    LPC_PINCON->PINMODE_OD1 |= BIT(OPEN_DRAIN_OUT_PIN);
}

static void gpio_config_direction(void)
{
    /* Salidas en Puerto 1 */
    LPC_GPIO1->FIODIR |= BIT(LED_BLINK_PIN) | BIT(LED_STATUS_PIN) | BIT(OPEN_DRAIN_OUT_PIN);

    /* Entradas en Puerto 0 */
    LPC_GPIO0->FIODIR &= ~(BIT(INPUT_PULLUP_PIN) |
                           BIT(INPUT_PULLDOWN_PIN) |
                           BIT(INPUT_REPEATER_PIN) |
                           BIT(INPUT_TRISTATE_PIN));
}

int main(void)
{
    uint32_t input_sample;

    gpio_set_function_as_gpio();
    gpio_config_input_modes();
    gpio_config_open_drain();
    gpio_config_direction();

    while (1)
    {
        /* Salida push-pull */
        LPC_GPIO1->FIOSET = BIT(LED_BLINK_PIN);
        /* En open-drain: escribir 0 fuerza LOW */
        LPC_GPIO1->FIOCLR = BIT(OPEN_DRAIN_OUT_PIN);
        delay(250000U);

        LPC_GPIO1->FIOCLR = BIT(LED_BLINK_PIN);
        /* En open-drain: escribir 1 libera la linea (HIGH-Z) */
        LPC_GPIO1->FIOSET = BIT(OPEN_DRAIN_OUT_PIN);
        delay(250000U);

        /*
         * Lee entradas con distintos modos:
         * - pull-up (P0.15)
         * - pull-down (P0.16)
         * - repeater (P0.17)
         * - sin resistor interno (P0.18)
         */
        input_sample = LPC_GPIO0->FIOPIN &
                       (BIT(INPUT_PULLUP_PIN) |
                        BIT(INPUT_PULLDOWN_PIN) |
                        BIT(INPUT_REPEATER_PIN) |
                        BIT(INPUT_TRISTATE_PIN));

        /* Estado consolidado en LED_STATUS */
        if (input_sample != 0U)
        {
            LPC_GPIO1->FIOSET = BIT(LED_STATUS_PIN);
        }
        else
        {
            LPC_GPIO1->FIOCLR = BIT(LED_STATUS_PIN);
        }
    }
}
