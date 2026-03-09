# Changelog

## 2026-03-09

### Documentacion y estructura
- Se agrego `README.md` en la raiz con alcance del repositorio para ED3 y LPC1769.
- Se agrego `codex-made/README.md` con convenciones para proyectos trabajados con Codex.
- Se agrego `AGENTS.md` al repositorio.

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

### Git
- Se creo y fusiono la rama de trabajo `codex/lpc1769-gpio-starter` en `main`.
- Se elimino la rama `codex/lpc1769-gpio-starter` (local y remota) luego de la fusion.
