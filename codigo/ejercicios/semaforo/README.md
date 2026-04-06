# Semaforo

Proyecto MCUXpresso para LPC1769 que ahora usa la CMSIS local del repo.

## Dependencia CMSIS

- Headers y fuentes base se resuelven desde `lib/CMSISv2p00_LPC17xx/`.
- El zip en `vendor/LPC17xx-CMSIS-Driver-Enhancement-main.zip` queda como snapshot de terceros, no como include directo de compilacion.

## Nota de portabilidad

Este proyecto ya no depende de un workspace externo de MCUXpresso para encontrar `LPC17xx.h` ni para enlazar una libreria `CMSISv2p00_LPC17xx` precompilada.

Para el arranque y la inicializacion del sistema, el build del proyecto compila localmente estas unidades CMSIS:

- `system_LPC17xx.c`
- `core_cm3.c`
