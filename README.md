# ED3 - Programacion de Microprocesadores en C (LPC1769)

Espacio de trabajo para la materia Electronica Digital 3, orientado al desarrollo en C para el microcontrolador **NXP LPC1769**.

## Objetivo del repositorio

- Centralizar practicas, TP y codigo hecho en clase.
- Documentar decisiones tecnicas del entorno (compilacion, flasheo, debug).
- Mantener ejemplos de C de referencia para consolidar base de lenguaje.

## Estructura actual

- `datasheet/`: documentacion tecnica (incluye `lpc17xx_um_unlocked.pdf`).
- `repo recursos c/C-Seminars/`: ejemplos introductorios de C por tema (`001` a `015`).
- `tps/`: espacio para trabajos practicos.
- `hecho en clase/`: ejercicios y avances de cursada.
- `codex-made/`: material generado durante las sesiones de trabajo.
- `documentacion latex/`: informe tecnico LPC1769 en LaTeX (fuentes, figuras y script de extraccion).
- `.vscode/`: configuraciones locales del editor.

## Convencion para nuevos ejercicios

- Crear carpetas numeradas y progresivas por tema cuando aplique (ejemplo: `016/nombre_tema.c`).
- Usar nombres de archivo en minuscula con guiones bajos.
- Compilar siempre con banderas de advertencia:

```powershell
gcc -Wall -Wextra -pedantic "ruta/al/archivo.c" -o programa
```

## Estado inicial (marzo 2026)

- El repositorio no tiene un sistema de build global (`Makefile` o `CMakeLists.txt`).
- Los ejemplos existentes en `C-Seminars` son de C general, no especificos de LPC1769.
- Ya esta disponible la referencia principal del micro en `datasheet/`.

## Plan de arranque sugerido para ED3

1. Definir toolchain embebido (compilador, linker, startup, CMSIS).
2. Crear un "proyecto minimo" para LPC1769 (blink por GPIO).
3. Documentar flujo completo: compilar, generar binario, grabar y debuggear.
4. Estandarizar estructura de practicas (`tps/` y `hecho en clase/`).

## Configuracion acordada (8 de marzo de 2026)

- Microcontrolador/placa objetivo: **LPC1769** (asumido en placa de la familia LPCXpresso de NXP; pendiente confirmar modelo exacto).
- Entorno principal de debug: **MCUXpresso IDE**.
- Flujo de desarrollo adicional: asistencia y generacion de codigo con **Codex** dentro de este repositorio.
- Carpeta de trabajo conjunta con Codex: **`codex-made/`**.
- Uso de otras carpetas:
  - `tps/` para trabajos practicos.
  - `hecho en clase/` para avances de cursada.
- Alcance inicial: **C bare-metal** (RTOS se evaluara mas adelante).

## Flujo de documentacion tecnica (LPC1769)

1. Extraer y recortar figuras desde el datasheet:

```powershell
powershell -ExecutionPolicy Bypass -File "documentacion latex/scripts/extract_figures_from_datasheet.ps1" -WorkspaceRoot "."
```

2. Compilar el informe:

```powershell
pdflatex -interaction=nonstopmode -output-directory "documentacion latex" "documentacion latex/main.tex"
```

La trazabilidad de figuras se mantiene en `documentacion latex/figure_inventory.csv`.

## Politica de versionado para LaTeX (desde 2026-03-09)

- Se prioriza versionar **fuentes reproducibles y assets**.
- Se versionan: `main.tex`, `chapter*.tex`, `README.md`, `scripts/`, `images/`, `figure_inventory.csv`.
- `main.pdf` solo se versiona cuando corresponde a una entrega.
- No se versionan artefactos intermedios (`*.aux`, `*.log`, `*.toc`), previews/verificaciones como `qa_png/` ni temporales de `tmp/`.

## Historial de cambios

- Ver [CHANGELOG.md](CHANGELOG.md) para el detalle de cambios realizados.

---

Siguiente paso recomendado: crear en `codex-made/` un proyecto base LPC1769 con plantilla minima (`main.c`, startup/linker y guia de compilacion/debug).
