# Flujo de trabajo para figuras (datasheet LPC1769)

Este documento resume el pipeline para capturar figuras del datasheet y usarlas en `main.tex`.

## Pipeline acordado

1. Render de la página fuente del datasheet a **300 DPI**.
2. Recorte exacto de la figura usando coordenadas `(x, y, w, h)`.
3. Copia del recorte final en `documentacion latex/images/`.
4. Registro de trazabilidad en `documentacion latex/figure_inventory.csv`.

## Ejecutar extracción

Desde la raíz del repo:

```powershell
powershell -ExecutionPolicy Bypass -File "documentacion latex/scripts/extract_figures_from_datasheet.ps1" -WorkspaceRoot "."
```

## Convenciones de QA visual

- Compilar con `pdflatex`.
- Renderizar páginas de `main.pdf` a PNG para revisar legibilidad.
- Confirmar:
  - títulos y tabla de contenidos en español coherente,
  - figuras 2 y 4 legibles en zoom normal,
  - tablas APB sin celdas ambiguas.

## Que se versiona / que no se versiona (politica desde 2026-03-09)

Se versiona:
- `main.tex`
- `README.md`
- `scripts/`
- `images/`
- `figure_inventory.csv`
- `main.pdf` solo cuando corresponde a una entrega.

No se versiona:
- `tmp/`
- `*.aux`, `*.log`, `*.toc`
- previews y verificaciones intermedias (imagenes de control visual)
- conversaciones de tooling (`conversations/*.json`)

## Checklist de regeneracion

1. Ejecutar la extracción de figuras desde `datasheet/` con el script de `scripts/`.
2. Compilar `main.tex` con `pdflatex`.
3. Revisar legibilidad visual del `main.pdf` antes de publicar/entregar.

## Nota de numeración

Se mantienen saltos de numeración porque el documento sigue la estructura del datasheet original.
