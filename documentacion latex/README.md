# Flujo actual de trabajo del PDF (datasheet LPC1769)

Este documento resume el proceso actual para estudiar una seccion del datasheet, traducirla al apunte en LaTeX y validar el PDF final.

## Flujo de trabajo actual

1. Leer la seccion objetivo en `datasheet/lpc17xx_um_unlocked.pdf` y `datasheet/lpc17xx_um_unlocked.txt`.
2. Explicar y discutir el contenido primero en chat.
3. Volcar al LaTeX solo la version acordada:
   - estilo de consulta rapida,
   - datos frios y tablas como fuente principal,
   - minima narrativa dentro de `main.tex`.
4. Si hace falta una figura, extraerla desde el PDF fuente con recorte dedicado.
5. Registrar la trazabilidad de la figura en `figure_inventory.csv`.
6. Compilar `main.tex`.
7. Renderizar paginas afectadas del PDF a PNG y revisar legibilidad real.

## Criterios editoriales vigentes

- El documento final debe parecer un resumen tecnico del datasheet, no una explicacion didactica corrida.
- La explicacion conceptual ocurre en chat; el PDF queda para buscar informacion puntual y salir.
- Se conserva la estructura del manual original cuando eso ayuda a encontrar contenido.
- Se priorizan tablas, mapas, pinouts y notas tecnicas concretas.
- El indice del PDF debe quedar navegable con hipervinculos internos.

## Flujo para figuras

### Regla general

- No reutilizar capturas de pagina completas cuando la figura queda chica o pierde contraste.
- Preferir recortes dedicados en alta resolucion desde el PDF fuente.
- Guardar la figura final en `documentacion latex/images/`.
- Registrar coordenadas y DPI en `documentacion latex/figure_inventory.csv`.

### Metodo recomendado

Usar el script HD de la skill:

```powershell
powershell -ExecutionPolicy Bypass -File "C:\Users\Usuario\.codex\skills\latex-pdf-study-assistant\scripts\capture_pdf_region_hd.ps1" -WorkspaceRoot "C:\Users\Usuario\Documents\Ignacio\Facultad\TercerAño\ED3" -Page <pagina> -X <x> -Y <y> -W <w> -H <h> -OutputImage "documentacion latex/images/<archivo>.png"
```

### Figura 7.1 actual

- Fuente: `Fig 14. LPC176x LQFP100 pin configuration`
- Pagina del datasheet: `91`
- DPI: `450`
- Recorte final: `x=1180`, `y=1100`, `w=1650`, `h=900`
- Archivo final: `images/lpc176x_lqfp100_pin_configuration_hd.png`

## Compilacion y QA visual

### Compilar

```powershell
powershell -ExecutionPolicy Bypass -File "C:\Users\Usuario\.codex\skills\latex-pdf-study-assistant\scripts\compile_latex.ps1" -WorkspaceRoot "C:\Users\Usuario\Documents\Ignacio\Facultad\TercerAño\ED3"
```

### Renderizar paginas para control visual

```powershell
powershell -ExecutionPolicy Bypass -File "C:\Users\Usuario\.codex\skills\latex-pdf-study-assistant\scripts\render_pdf_pages.ps1" -WorkspaceRoot "C:\Users\Usuario\Documents\Ignacio\Facultad\TercerAño\ED3" -Pages "10-15"
```

### Validar

Confirmar siempre:
- compilacion sin errores fatales,
- indice navegable en el PDF,
- captions correctos,
- figuras recortadas sin arrastre de elementos vecinos,
- tablas legibles en zoom normal,
- continuidad visual con el resto del apunte.

## Cambios tecnicos relevantes del estado actual

- `main.tex` usa `hyperref` con `unicode,hidelinks` para hacer clickable el indice sin ensuciar el estilo visual.
- Se usa `longtable` para tablas extensas como las del capitulo 7.
- Se usa `lmodern` para evitar problemas de fuentes al compilar tablas con texto pequeno e italicas.

## Que se versiona / que no se versiona

Se versiona:
- `main.tex`
- `README.md`
- `scripts/`
- `images/`
- `figure_inventory.csv`
- `main.pdf` cuando corresponde a una entrega

No se versiona:
- `tmp/`
- `*.aux`, `*.log`, `*.toc`, `*.out`
- previews y verificaciones intermedias
- conversaciones de tooling (`conversations/*.json`)

## Nota de numeracion

Se mantienen saltos de numeracion porque el documento sigue la estructura del datasheet original.
