# Changelog

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
