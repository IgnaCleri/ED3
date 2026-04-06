# Arcoiris

Proyecto MCUXpresso para LPC1769 que muestra un arcoiris suave usando los tres LEDs internos de la placa.

## LEDs usados

- Rojo: `P0.22`
- Verde: `P3.25`
- Azul: `P3.26`
- Los tres LEDs son activos por bajo.

## Dependencia CMSIS

- Headers y fuentes base se resuelven desde `lib/CMSISv2p00_LPC17xx/`.
- El zip en `vendor/LPC17xx-CMSIS-Driver-Enhancement-main.zip` queda como snapshot de terceros, no como include directo de compilacion.

## Nota de portabilidad

Este proyecto no depende de un workspace externo de MCUXpresso para encontrar `LPC17xx.h` ni para enlazar una libreria precompilada de CMSIS.

Para el arranque y la inicializacion del sistema, el build compila localmente estas unidades CMSIS:

- `system_LPC17xx.c`
- `core_cm3.c`

## Build y carga

- Compilar: `make clean all` dentro de `Debug/` usando el toolchain ARM de MCUXpresso.
- Cargar en placa: `LinkServer flash -p '#1' LPC1769 load Debug/arcoiris.axf`
