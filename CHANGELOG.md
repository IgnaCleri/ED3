# Changelog

## 2026-03-24

### Reorganizacion de estructura
- Se reorganizo la raiz del repositorio para separar documentacion, codigo, vendor y artifacts.
- `documentacion latex/` paso a `docs/latex/`.
- `pdfs clases/` paso a `docs/clases/`.
- `datasheet/` paso a `docs/referencia/`.
- `hecho en clase/clase1/` paso a `codigo/clases/clase1/`.
- `codex-made/` se integro en `codigo/proyectos/`.
- `CMSISv2p00_LPC17xx2/` y `LPC17xx-CMSIS-Driver-Enhancement/` pasaron a `vendor/`.
- Los logs de RTOS y el soporte local de MCUXpresso pasaron a `artifacts/`.
- Se actualizaron `README.md`, `.gitignore` y la documentacion interna para reflejar la nueva taxonomia.

## 2026-03-15

### Documentacion latex
- Se reviso tecnicamente `documentacion latex/chapter3.tex` contra `datasheet/lpc17xx_um_unlocked.txt` para el `Chapter 3: LPC17xx System control`.
- Se corrigio la seccion de reset para explicar cuando ocurre cada fuente de reinicio: reset externo, Watchdog, `Power-On Reset (POR)` y `Brown-Out Detect (BOD)`.
- Se agrego en `3.4` una secuencia practica paso a paso del arranque posterior al reset, alineada con la `Fig 5` del datasheet.
- Se hizo explicita la semantica de limpieza de `EXTINT`: el flag se limpia escribiendo `1` en el bit correspondiente.
- Se reforzo la nota diagnostica de `RSID` para `BODR`, aclarando que solo es interpretable cuando `POR=0`.
- Se agrego en `Brown-out detection` la posibilidad de vigilar el evento mediante `Raw Interrupt Status Register` cuando la interrupcion no esta habilitada.
- Se documento en `SCS` que `OSCEN=1` solo arranca el oscilador principal si la circuiteria externa correcta esta conectada a `XTAL1` y `XTAL2`.
- Se agrego una nota en el mapa de registros aclarando alineacion a palabra y que los valores de reset `0x0/0x00` aplican solo a bits usados.
- Se recompilo `documentacion latex/main.pdf` para validar que el documento siga compilando despues de las correcciones del capitulo 3.

## 2026-03-12

### Documentacion latex
- Se agrego `documentacion latex/chapter9.tex` con el resumen tecnico del `Chapter 9: LPC17xx General Purpose Input/Output (GPIO)`.
- `documentacion latex/main.tex` ahora integra el capitulo 9 mediante `\input{chapter9.tex}` y tolera la ausencia de `chapter8.tex`.
- Se incorporaron las tablas `100` a `123` del capitulo 9 y una nota tecnica breve sobre `bit-banding`.
- Se actualizo `.gitignore` para permitir versionar `documentacion latex/chapter*.tex` y excluir `documentacion latex/qa_png/`.
- Se recompilo `documentacion latex/main.pdf` con el nuevo bloque documental.

### Documentacion latex
- Se agrego `documentacion latex/chapter8.tex` con el resumen tecnico completo del `Chapter 8: LPC17xx Pin connect block`.
- `documentacion latex/main.tex` ahora integra el capitulo 8 mediante `\input{chapter8.tex}`.
- Se incorporaron en el apunte las tablas `74` a `99` del capitulo 8, manteniendo el orden del datasheet.
- Se documento en `documentacion latex/README.md` el proceso concreto usado para integrar y validar este capitulo.
- Se recompilo `documentacion latex/main.pdf` con el nuevo bloque documental.

## 2026-03-09

### Documentacion y estructura
- Se agrego `README.md` en la raiz con alcance del repositorio para ED3 y LPC1769.
- Se agrego `codex-made/README.md` con convenciones para proyectos trabajados con Codex.
- Se agrego `AGENTS.md` al repositorio.
- Se agrego `documentacion latex/README.md` con el pipeline de extraccion de figuras del datasheet.
- Se agrego `documentacion latex/main.tex` como fuente principal del informe tecnico LPC1769.
- Se agrego `documentacion latex/scripts/extract_figures_from_datasheet.ps1` como comando estandar de extraccion.
- Se agrego `documentacion latex/figure_inventory.csv` para trazabilidad de figuras.
- Se agregaron imagenes de trabajo en `documentacion latex/images/`.

### Proyecto inicial GPIO
- Se creo `codex-made/01-lpc1769-puertos/README.md`.
- Se creo `codex-made/01-lpc1769-puertos/src/main.c` con ejemplo bare-metal para LPC1769.
- El ejemplo se amplio para cubrir:
  - salida push-pull,
  - salida open-drain,
  - entrada pull-up,
  - entrada pull-down,
  - entrada repeater,
  - entrada sin pull-up/pull-down (tristate).

### Material de referencia
- Se incorporo `datasheet/lpc17xx_um_unlocked.txt` como version de texto extraida del manual PDF para facilitar busquedas locales.

### Limpieza y politica documental (pushes de 2026-03-09)
- Se eliminaron archivos temporales en `tmp/` que se habian usado para pipeline y revision visual.
- Se define como politica versionar solo fuentes y assets del flujo LaTeX.
- `main.pdf` se mantiene como opcion de versionado solo cuando sea una entrega.
- No se consideran entregables los intermedios `*.aux`, `*.log`, `*.toc`, previews/verificaciones ni conversaciones de tooling.

### Git
- Se creo y fusiono la rama de trabajo `codex/lpc1769-gpio-starter` en `main`.
- Se elimino la rama `codex/lpc1769-gpio-starter` (local y remota) luego de la fusion.
