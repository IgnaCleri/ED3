# codex-made

Carpeta de trabajo para desarrollo asistido con Codex en la materia ED3 (LPC1769).

## Objetivo

- Crear prototipos y bases de proyectos embebidos en C.
- Dejar documentados comandos, decisiones y estructura para poder migrar facilmente a `tps/` o `hecho en clase/`.

## Convencion sugerida para proyectos

- `codex-made/01-lpc1769-base/`: primer esqueleto del proyecto LPC1769.
- `codex-made/02-gpio-interrupts/`: practicas de GPIO e interrupciones.
- `codex-made/03-timers/`: temporizadores y PWM.

Cada carpeta de proyecto deberia incluir:

- `README.md` con objetivo y pasos de build/debug.
- `src/` con fuentes C.
- `include/` con headers.
- `startup/` con startup y vector table.
- `linker/` con script `.ld`.

## Nota de compatibilidad

El debug se realizara con MCUXpresso IDE. La organizacion de archivos se mantiene simple para facilitar importar el proyecto al IDE cuando sea necesario.

## Referencia documental

La documentacion formal del LPC1769 en formato LaTeX se mantiene en `documentacion latex/`.
Esta carpeta (`codex-made/`) se reserva para practicas y prototipos de codigo.
