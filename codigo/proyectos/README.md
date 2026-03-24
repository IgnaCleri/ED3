# Proyectos

Carpeta de trabajo para proyectos y prototipos de ED3, incluyendo desarrollo asistido con Codex.

## Objetivo

- Crear prototipos y bases de proyectos embebidos en C.
- Mantener proyectos reutilizables separados de los ejercicios cortos y del codigo hecho en clase.

## Convencion sugerida para proyectos

- `codigo/proyectos/01-lpc1769-base/`: primer esqueleto del proyecto LPC1769.
- `codigo/proyectos/02-gpio-interrupts/`: practicas de GPIO e interrupciones.
- `codigo/proyectos/03-timers/`: temporizadores y PWM.

Cada carpeta de proyecto deberia incluir:

- `README.md` con objetivo y pasos de build/debug.
- `src/` con fuentes C.
- `include/` con headers.
- `startup/` con startup y vector table.
- `linker/` con script `.ld`.

## Nota de compatibilidad

El debug se realizara con MCUXpresso IDE. La organizacion de archivos se mantiene simple para facilitar importar el proyecto al IDE cuando sea necesario.

## Referencia documental

La documentacion formal del LPC1769 en formato LaTeX se mantiene en `docs/latex/`.
Esta carpeta (`codigo/proyectos/`) se reserva para practicas y prototipos de codigo.
