# 01 - LPC1769 Puertos GPIO

Proyecto inicial de practica para ED3: configuracion y uso basico de puertos del LPC1769 en C bare-metal.

## Que hace este ejemplo

- Configura salidas GPIO en Puerto 1:
  - `P1.18` como salida **push-pull** (blink).
  - `P1.20` como LED de estado.
  - `P1.19` como salida **open-drain**.
- Configura entradas GPIO en Puerto 0:
  - `P0.15` con modo **pull-up**.
  - `P0.16` con modo **pull-down**.
  - `P0.17` con modo **repeater**.
  - `P0.18` con modo **sin pull-up/pull-down** (tristate).
- En el loop principal:
  - Hace blink en `P1.18`.
  - Conmuta `P1.19` mostrando comportamiento open-drain.
  - Lee las 4 entradas y refleja estado consolidado en `P1.20`.

## Archivo principal

- `src/main.c`

## Importante

Los pines elegidos son de ejemplo. Si tu placa usa otros pines para LED/boton, cambia los `#define` al inicio de `main.c`.

## Siguiente practica sugerida

- Agregar antirrebote por software para el pulsador.
- Reemplazar delay por temporizador (Timer0 o SysTick).
