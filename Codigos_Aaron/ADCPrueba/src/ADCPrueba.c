#include "LPC17xx.h"

void conf_pines(void);
void conf_ADC(void);
void conf_MAT(void);

typedef enum
{
	NADA = 0,
	LED_ROJO,
	LED_AZUL,
	LED_VERDE
} estadoLEDs_t;

volatile uint16_t resultado;
volatile estadoLEDs_t estado = NADA;

int main()
{
	conf_pines();
	conf_MAT();
	conf_ADC();

	while (1)
	{
		switch(estado)
		{
			case NADA:
				LPC_GPIO3->FIOSET |= 1 << 26 | 1 << 25;
				LPC_GPIO0->FIOSET |= 1 << 22;
				break;

			case LED_ROJO:
				LPC_GPIO0->FIOCLR |= 1 << 22;
				LPC_GPIO3->FIOSET |= 1 << 25 | 1 << 26;
				break;

			case LED_VERDE:
				LPC_GPIO3->FIOCLR |= 1 << 25;
				LPC_GPIO3->FIOSET |= 1 << 26;
				LPC_GPIO0->FIOSET |= 1 << 22;
				break;

			case LED_AZUL:
				LPC_GPIO3->FIOCLR |= 1 << 26;
				LPC_GPIO3->FIOSET |= 1 << 25;
				LPC_GPIO0->FIOSET |= 1 << 22;
				break;
		}
	}
}

void ADC_IRQHandler()
{
	// Resultado de 12 bits en [15:4] del registro ADDR0
    resultado = (LPC_ADC->ADDR0 >> 4) & 0xFFF;

    if( (resultado > 1024) && (resultado <= 2048) )
    {

        estado = LED_ROJO;

    }
    else if( (resultado > 2048) && (resultado <= 3072))
    {

        estado = LED_VERDE;

    }
    else if(resultado > 3072)
    {

            estado = LED_AZUL;

    }
    else if (resultado < 1024)
    {

        estado = NADA;

    }
}

void conf_pines(void)
{
	// P0.22 → LED Rojo | P3.25 → LED Verde | P3.26 → LED Azul

	// GPIO sin pull-up ni pull-down
	LPC_PINCON->PINSEL1 &= ~(0b11 << 12);
	LPC_PINCON->PINSEL7 &= ~(0b11 << 18 | 0b11 << 20);
	LPC_PINCON->PINMODE1 |=  (1 << 12); LPC_PINCON->PINMODE1 &= ~(1 << 13);
	LPC_PINCON->PINMODE7 |=  (1 << 18) | (1 << 20);
	LPC_PINCON->PINMODE7 &= ~((1 << 19) | (1 << 21));

	// Salidas, iniciadas en alto (LEDs apagados, ánodo a VCC)
	LPC_GPIO0->FIODIR |= 1 << 22;
	LPC_GPIO3->FIODIR |= 1 << 25 | 1 << 26;
	LPC_GPIO0->FIOSET |= 1 << 22;
	LPC_GPIO3->FIOSET |= 1 << 25 | 1 << 26;
}

void conf_ADC(void)
{
	LPC_SC->PCONP    |= 1 << 12;          // Encender ADC
	LPC_SC->PCLKSEL0 &= ~(0b11 << 24);    // PCLK_ADC = CCLK/4 = 25 MHz

	// P0.23 como entrada analógica AD0 (canal 0)
	LPC_PINCON->PINSEL1  |=  (1 << 14); LPC_PINCON->PINSEL1  &= ~(1 << 15);
	LPC_PINCON->PINMODE1 |=  (1 << 14); LPC_PINCON->PINMODE1 &= ~(1 << 15);

	// Canal 0 | CLKDIV=8 | PDN=1 | Trigger por MAT0.1
	LPC_ADC->ADCR &= ~(0xFF | 1 << 16 | 0b111 << 24 | 1 << 27);
	LPC_ADC->ADCR |=  (1 | 1 << 8 | 1 << 21 | 0b100 << 24);

	LPC_ADC->ADINTEN  |= 1;        // Interrupción al finalizar canal 0
	NVIC->ISER[0]     |= 1 << 22;  // Habilitar IRQ del ADC en NVIC
}

void conf_MAT(void)
{
	LPC_SC->PCONP    |= 1 << 1;        // Encender Timer0
	LPC_SC->PCLKSEL0 &= ~(0b11 << 2); // PCLK_TIM0 = CCLK/4 = 25 MHz

	// PR=24 → tick cada 1µs | MR1=50000 → match cada 50ms (20 Hz)
	LPC_TIM0->PR  = 24;
	LPC_TIM0->MR1 = 50000;
	LPC_TIM0->MCR = 1 << 4;           // Reset del TC en cada match

	// Toggle de MAT0.1 cada dos match → dispara el ADC (ya que reacciona al flanco)
	LPC_TIM0->EMR &= ~(1 << 1);
	LPC_TIM0->EMR |=   0b11 << 6;

	// Reset y arranque del timer
	LPC_TIM0->TCR |=  0b10;
	LPC_TIM0->TCR &= ~(0b10);
	LPC_TIM0->TCR |=  1;
}


