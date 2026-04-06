#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <stdint.h>

#define BIT(x)                  (1UL << (x))
#define BITS(width, shift)      (((1UL << (width)) - 1UL) << (shift))

#define LED_ROJO_PIN            22U
#define LED_VERDE_PIN           25U
#define LED_AZUL_PIN            26U

#define PWM_LEVELS              32U
#define PWM_MAX                 (PWM_LEVELS - 1U)
#define BRIGHTNESS_LIMIT        12U
#define SYSTICK_HZ              8000U
#define COLOR_STEP_PRESCALER    130U

typedef struct
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} RgbColor;

static volatile RgbColor g_current_color = { PWM_MAX, 0U, 0U };

static const RgbColor g_palette[] =
{
    { PWM_MAX, 0U, 0U },
    { PWM_MAX, 4U, 0U },
    { PWM_MAX, 8U, 0U },
    { PWM_MAX, 12U, 0U },
    { PWM_MAX, 16U, 0U },
    { PWM_MAX, 18U, 0U },
    { PWM_MAX, 20U, 0U },
    { 28U, 24U, 0U },
    { 24U, PWM_MAX, 0U },
    { 16U, PWM_MAX, 0U },
    { 8U, PWM_MAX, 0U },
    { 0U, PWM_MAX, 0U },
    { 0U, PWM_MAX, 4U },
    { 0U, PWM_MAX, 8U },
    { 0U, PWM_MAX, 12U },
    { 0U, PWM_MAX, 16U },
    { 0U, 24U, 18U },
    { 0U, 20U, 20U },
    { 0U, 12U, 24U },
    { 0U, 8U, PWM_MAX },
    { 0U, 4U, PWM_MAX },
    { 0U, 0U, PWM_MAX },
    { 4U, 0U, PWM_MAX },
    { 8U, 0U, PWM_MAX },
    { 12U, 0U, PWM_MAX },
    { 16U, 0U, PWM_MAX },
    { 18U, 0U, 24U },
    { 20U, 0U, 20U },
    { 24U, 0U, 18U },
    { 28U, 0U, 12U },
    { PWM_MAX, 0U, 8U },
    { PWM_MAX, 0U, 4U },
    { PWM_MAX, 0U, 16U }
};

static void rgb_gpio_init(void);
static void rgb_all_off(void);
static void rgb_apply_pwm(RgbColor color, uint8_t phase);
static void rainbow_tick(void);
static uint8_t rgb_scale(uint8_t value);

int main(void)
{
    rgb_gpio_init();
    rgb_all_off();

    SysTick_Config(SystemCoreClock / SYSTICK_HZ);

    while (1)
    {
        __WFI();
    }
}

static void rgb_gpio_init(void)
{
    /* P0.22 -> GPIO */
    LPC_PINCON->PINSEL1 &= ~BITS(2U, 12U);
    LPC_PINCON->PINMODE1 &= ~BITS(2U, 12U);
    LPC_PINCON->PINMODE1 |= BIT(13U);
    LPC_GPIO0->FIODIR |= BIT(LED_ROJO_PIN);

    /* P3.25 -> GPIO */
    LPC_PINCON->PINSEL7 &= ~BITS(2U, 18U);
    LPC_PINCON->PINMODE7 &= ~BITS(2U, 18U);
    LPC_PINCON->PINMODE7 |= BIT(19U);
    LPC_GPIO3->FIODIR |= BIT(LED_VERDE_PIN);

    /* P3.26 -> GPIO */
    LPC_PINCON->PINSEL7 &= ~BITS(2U, 20U);
    LPC_PINCON->PINMODE7 &= ~BITS(2U, 20U);
    LPC_PINCON->PINMODE7 |= BIT(21U);
    LPC_GPIO3->FIODIR |= BIT(LED_AZUL_PIN);
}

static void rgb_all_off(void)
{
    /* Activo por bajo: SET apaga. */
    LPC_GPIO0->FIOSET = BIT(LED_ROJO_PIN);
    LPC_GPIO3->FIOSET = BIT(LED_VERDE_PIN) | BIT(LED_AZUL_PIN);
}

static void rgb_apply_pwm(RgbColor color, uint8_t phase)
{
    const uint8_t red = rgb_scale(color.red);
    const uint8_t green = rgb_scale(color.green);
    const uint8_t blue = rgb_scale(color.blue);

    rgb_all_off();

    if (red > phase)
    {
        LPC_GPIO0->FIOCLR = BIT(LED_ROJO_PIN);
    }

    if (green > phase)
    {
        LPC_GPIO3->FIOCLR = BIT(LED_VERDE_PIN);
    }

    if (blue > phase)
    {
        LPC_GPIO3->FIOCLR = BIT(LED_AZUL_PIN);
    }
}

static uint8_t rgb_scale(uint8_t value)
{
    return (uint8_t)(((uint32_t)value * BRIGHTNESS_LIMIT) / PWM_MAX);
}

static void rainbow_tick(void)
{
    static uint32_t prescaler = 0U;
    static uint8_t segment = 0U;
    static uint8_t step = 0U;
    const RgbColor start = g_palette[segment];
    const RgbColor end = g_palette[(segment + 1U) % (sizeof(g_palette) / sizeof(g_palette[0]))];

    prescaler++;
    if (prescaler < COLOR_STEP_PRESCALER)
    {
        return;
    }

    prescaler = 0U;

    g_current_color.red = (uint8_t)(start.red + (((int32_t)end.red - (int32_t)start.red) * (int32_t)step) / (int32_t)PWM_MAX);
    g_current_color.green = (uint8_t)(start.green + (((int32_t)end.green - (int32_t)start.green) * (int32_t)step) / (int32_t)PWM_MAX);
    g_current_color.blue = (uint8_t)(start.blue + (((int32_t)end.blue - (int32_t)start.blue) * (int32_t)step) / (int32_t)PWM_MAX);

    step++;
    if (step > PWM_MAX)
    {
        step = 0U;
        segment++;
        if (segment >= (sizeof(g_palette) / sizeof(g_palette[0])))
        {
            segment = 0U;
        }
    }
}

void SysTick_Handler(void)
{
    static uint8_t pwm_phase = 0U;

    rgb_apply_pwm(g_current_color, pwm_phase);

    pwm_phase++;
    if (pwm_phase >= PWM_LEVELS)
    {
        pwm_phase = 0U;
    }

    rainbow_tick();
}
