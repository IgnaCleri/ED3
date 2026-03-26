

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
		__WFI(); // ERROR A TENER EN CUENTA: esto depende de que las interrupciones estén funcionando bien.
		         // Si SysTick no queda correctamente configurado, el programa “duerme” y parece que no hace nada.
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
LPC_GPIO0->FIOCLR |= BIT(22); // ERROR CONCEPTUAL POSIBLE: si los LEDs son activos por bajo, limpiar el bit los enciende.
                             // Así, al arrancar este LED queda prendido y no necesariamente en un “estado inicial apagado”.

// LED VERDE
LPC_PINCON->PINSEL7 &= ~BITS(2,20);
LPC_PINCON->PINMODE7 |= BIT(20);
LPC_PINCON->PINMODE7 &= ~BIT(21);
LPC_GPIO3->FIODIR |= BIT(26);
LPC_GPIO3->FIOCLR |= BIT(26); // MISMA OBSERVACIÓN: con lógica activa por bajo, esto enciende el LED verde al inicio.

// LED AZUL
LPC_PINCON->PINSEL7 &= ~BITS(2,18);
LPC_PINCON->PINMODE7 |= BIT(18);
LPC_PINCON->PINMODE7 &= ~BIT(19);
LPC_GPIO0->FIODIR |= BIT(25); // ERROR GRAVE: el LED azul es P3.25 según tu comentario de arriba,
                              // pero acá se configura P0.25. El puerto no coincide con el pin real.
LPC_GPIO0->FIOCLR |= BIT(25); // ERROR DERIVADO: también se está intentando manejar el azul desde GPIO0.
                              // Debería ser GPIO3 para P3.25.
}

void cfg_systick(){
	SysTick->CTRL = 0;
	SysTick->LOAD = 999999; // OBSERVACIÓN: este valor define el período, pero solo será correcto si el clock del core es el esperado.
	SysTick->VAL = 0;
	SysTick->CTRL |= 7;     // Habilita contador, interrupción y clock interno.
}

void SysTick_Handler(){
	static uint8_t ticks=0;   // ERROR DE COMPILACIÓN: se usa uint8_t pero no se incluyó <stdint.h>.
	static uint8_t estado=0;  // Sin ese include, esto puede no compilar.
	ticks++;
	if(ticks ==50){           // ERROR LÓGICO: nunca se reinicia ticks a 0, así que esta condición se cumple una sola vez.
		switch(estado){
		case 0: //VERDE
			LPC_GPIO0->FIOCLR |= BIT(22);
			LPC_GPIO3->FIOSET |= BIT(25); // ERROR DE PUERTO: otra vez se usa P3.25/P0.22 mezclado con una lógica inconsistente.
			                            // Además, no coincide con la configuración hecha arriba para el azul.
		case 1: //AZUL
			LPC_GPIO3->FIOCLR |= BIT(25); // ERROR DE PUERTO: el azul está siendo tratado como P3.25 acá,
			                            // pero en cfg_pcb fue configurado como P0.25.
			LPC_GPIO3->FIOSET |= BIT(26);
		case 2://ROJO
			LPC_GPIO3->FIOCLR |= BIT(26);
			LPC_GPIO0->FIOSET |= BIT(22);
			estado = 0;
		}
		estado++; // ERROR LÓGICO: aunque en case 2 hacés estado = 0, acá inmediatamente pasa a 1.
		         // O sea, nunca vuelve realmente al estado 0 como esperás.
		         // Además, faltan break en todos los case, así que hay fall-through y se ejecutan varios casos seguidos.
	}
}
