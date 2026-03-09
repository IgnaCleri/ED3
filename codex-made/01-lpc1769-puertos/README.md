# 01 - LPC1769 Puertos GPIO

Proyecto inicial de practica para ED3: configuracion y uso basico de puertos del LPC1769 en C bare-metal.

## Que hace este ejemplo

- Configura 2 pines como salida GPIO:
  - `P1.18` como LED principal (toggle por software).
  - `P1.20` como LED de estado de entrada.
- Configura 1 pin como entrada GPIO:
  - `P0.15` como entrada digital (pulsador o señal externa).
- En el loop principal:
  - Hace blink en `P1.18`.
  - Lee `P0.15` y refleja su estado en `P1.20`.

## Archivo principal

- `src/main.c`

## Importante

Los pines elegidos son de ejemplo. Si tu placa usa otros pines para LED/boton, cambia solo los `#define` al inicio de `main.c`.

## Siguiente practica sugerida

- Agregar antirrebote por software para el pulsador.
- Reemplazar delay por temporizador (Timer0 o SysTick).
