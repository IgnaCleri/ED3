#include "LPC17xx.h"

// Idea del proyecto: realizar un contador de 0 a 99 usando dos displays de 7 segmentos.
// Los dos displays deben multiplexarse para que la visualizacion sea correcta.
// El conteo debe avanzar cada medio segundo.
// Los delays y la base de tiempos deben gestionarse con SysTick.
// Ademas, un boton conectado al puerto P2.10 debe permitir pausar la cuenta con una pulsacion.
// Si el boton se vuelve a presionar, la cuenta debe reanudarse desde el valor en el que quedo.
