# ED3 - Programacion de Microprocesadores en C (LPC1769)

Espacio de trabajo para la materia Electronica Digital 3, orientado al desarrollo en C para el microcontrolador **NXP LPC1769**.

## Objetivo del repositorio

- Separar con claridad la documentacion del codigo.
- Centralizar practicas, ejercicios, proyectos y material de cursada.
- Mantener referencias tecnicas, codigo vendor y artefactos sin mezclar responsabilidades.

## Estructura actual

- `docs/`: documentacion del repositorio.
  - `docs/latex/`: apunte tecnico reproducible en LaTeX y PDF.
  - `docs/clases/`: PDFs y material de consulta de cursada.
  - `docs/referencia/`: datasheets y manuales base del microcontrolador y la placa.
- `codigo/`: codigo propio del workspace.
  - `codigo/clases/`: codigo hecho en clase.
  - `codigo/ejercicios/`: ejercicios cortos o material introductorio.
  - `codigo/proyectos/`: proyectos mas armados y practicas bare-metal.
  - `codigo/tps/`: trabajos practicos formales.
- `vendor/`: librerias externas, forks y snapshots de terceros.
- `artifacts/`: logs, capturas temporales y salidas generadas de soporte.

## Guia de clasificacion

- Si es fuente mantenida por nosotros, va en `codigo/`.
- Si es referencia o manual, va en `docs/referencia/`.
- Si es documentacion reproducible, va en `docs/latex/`.
- Si es libreria externa o un fork, va en `vendor/`.
- Si es una salida generada, va en `artifacts/` o se ignora por `.gitignore`.

## Convenciones para codigo

- Lenguaje principal: C.
- Usar nombres de archivo en minuscula con guiones bajos cuando se agreguen archivos nuevos.
- Compilar con banderas de advertencia como minimo:

```powershell
gcc -Wall -Wextra -pedantic "ruta/al/archivo.c" -o programa
```

- Ubicar cada trabajo segun su objetivo:
  - `codigo/clases/` para avances de cursada.
  - `codigo/ejercicios/` para practicas cortas.
  - `codigo/proyectos/` para proyectos con estructura propia.
  - `codigo/tps/` para entregas formales.

## Flujo de documentacion tecnica

1. Usar las referencias tecnicas desde `docs/referencia/`.
2. Mantener el apunte reproducible en `docs/latex/`.
3. Registrar cambios relevantes en [CHANGELOG.md](CHANGELOG.md).

El apunte LaTeX ya incorpora el `Chapter 6` del NVIC. Para capitulos largos, el flujo vigente combina:
- discusion conceptual previa del capitulo,
- edicion en archivo separado dentro de `docs/latex/`,
- compilacion del PDF con `tectonic`,
- QA visual por capturas temporales en `artifacts/`.

El detalle operativo de ese proceso queda documentado en `docs/latex/README.md`.

### Comandos base

Extraer y recortar figuras desde el datasheet:

```powershell
powershell -ExecutionPolicy Bypass -File "docs/latex/scripts/extract_figures_from_datasheet.ps1" -WorkspaceRoot "."
```

Compilar el informe:

```powershell
pdflatex -interaction=nonstopmode -output-directory "docs/latex" "docs/latex/main.tex"
```

La trazabilidad de figuras se mantiene en `docs/latex/figure_inventory.csv` cuando ese archivo forme parte del flujo activo.

## Vendor y dependencias externas

- `vendor/CMSISv2p00_LPC17xx2/`: base CMSIS/drivers para LPC17xx.
- `vendor/LPC17xx-CMSIS-Driver-Enhancement/`: fork o variante modernizada con tests y documentacion propia.

La deduplicacion entre copias CMSIS queda planificada para una etapa posterior. En esta reorganizacion solo se separo el codigo externo del codigo propio.

## Estado del repo

- No hay un sistema de build global unico (`Makefile` o `CMakeLists.txt`) en la raiz.
- El flujo principal de debug sigue dependiendo de MCUXpresso IDE para algunos proyectos.
- El apunte LaTeX y los proyectos bare-metal del LPC1769 son hoy los ejes mas consolidados del repositorio.

## Historial

- Ver [CHANGELOG.md](CHANGELOG.md) para el detalle de cambios realizados.
