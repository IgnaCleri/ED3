# Flujo actual de trabajo del PDF (datasheet LPC1769)

Este documento resume el proceso actual para estudiar una seccion del datasheet, traducirla al apunte en LaTeX y validar el PDF final.

## Flujo de trabajo actual

1. Leer la seccion objetivo en `docs/referencia/lpc17xx_um_unlocked.pdf` y `docs/referencia/lpc17xx_um_unlocked.txt`.
2. Explicar y discutir el contenido primero en chat.
3. Si el usuario pide un capitulo completo, reconstruir primero su estructura y recorrerlo por subseccion o bloque.
4. Explicar una subseccion o bloque por vez y abrir checkpoint de dudas antes de pasar al siguiente.
5. No editar LaTeX hasta terminar la discusion del bloque o conjunto de bloques acordado.
6. Antes de escribir, respetar el criterio editorial vigente del documento.
7. Volcar al LaTeX solo la version acordada:
   - estilo de consulta rapida,
   - datos frios y tablas como fuente principal,
   - minima narrativa dentro de `main.tex`.
8. Si hace falta una figura, extraerla desde el PDF fuente con recorte dedicado.
9. Registrar la trazabilidad de la figura en `figure_inventory.csv`.
10. Compilar `main.tex`.
11. Renderizar paginas afectadas del PDF a PNG y revisar legibilidad real.

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
- Si ya existe un recorte HD validado para esa figura, reutilizarlo antes de generar uno nuevo.
- Guardar la figura final en `docs/latex/images/`.
- Registrar coordenadas y DPI en `docs/latex/figure_inventory.csv`.

### Metodo recomendado

Usar el script HD de la skill:

```powershell
powershell -ExecutionPolicy Bypass -File "C:\Users\Usuario\.codex\skills\latex-pdf-study-assistant\scripts\capture_pdf_region_hd.ps1" -WorkspaceRoot "C:\Users\Usuario\Documents\Ignacio\Facultad\TercerAño\ED3" -Page <pagina> -X <x> -Y <y> -W <w> -H <h> -OutputImage "docs/latex/images/<archivo>.png"
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
- `README.md`
- `main.tex`
- `images/`
- `main.pdf` cuando corresponde a una entrega

No se versiona:
- `.vscode/`
- `tmp/`
- `*.aux`, `*.log`, `*.toc`, `*.out`
- `figure_inventory.csv`
- `scripts/`
- previews y verificaciones intermedias
- conversaciones de tooling (`conversations/*.json`)

## Nota de numeracion

Se mantienen saltos de numeracion porque el documento sigue la estructura del datasheet original.

## Proceso documentado para el capitulo 3

Se deja registrado el trabajo de revision y correccion aplicado a `Chapter 3: LPC17xx System control`.

### Objetivo editorial

- Mantener formato de consulta rapida.
- Preservar la estructura del datasheet en las subsecciones `3.1` a `3.7.1`.
- Corregir simplificaciones que podian inducir errores de firmware, sobre todo en reset, `RSID`, `BOD`, `EXTINT` y `SCS`.
- Agregar solo las notas practicas que ayuden a interpretar la `Fig 5` y a usar correctamente los registros.

### Cambios aplicados

1. Se reviso `docs/latex/chapter3.tex` contra `docs/referencia/lpc17xx_um_unlocked.txt`.
2. En `3.4` se ampliaron las fuentes de reset para explicar cuando ocurre cada una:
   - reset externo por pin `RESET`,
   - reset por Watchdog,
   - `Power-On Reset (POR)`,
   - `Brown-Out Detect (BOD)`.
3. En esa misma seccion se agrego una secuencia practica de arranque posterior al reset basada en la `Fig 5`:
   - subida de `VDD(REG)(3V3)`,
   - arranque del `IRC`,
   - estabilizacion del clock,
   - liberacion sincronizada del reset,
   - temporizadores de wake-up,
   - acceso a flash,
   - ejecucion de boot ROM,
   - inicio de `user code`.
4. Se preciso la nota de `RSID` para dejar claro que `BODR` solo se interpreta con `POR=0`.
5. Se agrego en `Brown-out detection` que el evento tambien puede observarse por `Raw Interrupt Status Register` si la interrupcion no esta habilitada.
6. Se corrigio `EXTINT` para indicar explicitamente que el flag se limpia escribiendo `1`.
7. Se reforzo la advertencia de reconfiguracion de `EXTMODE` y `EXTPOLAR`, indicando deshabilitar NVIC y limpiar `EXTINT` antes de rehabilitar la interrupcion.
8. Se agrego en `SCS` la condicion de hardware externo en `XTAL1` y `XTAL2` para que `OSCEN=1` produzca el arranque real del oscilador principal.
9. Se agrego una nota al mapa de registros aclarando alineacion a palabra y el alcance de los valores de reset sobre bits usados.

### QA aplicada

1. Se compilo `docs/latex/main.tex` con el script de la skill.
2. Resultado: compilacion exitosa.
3. Advertencia observada:
   - MiKTeX no pudo escribir su log en `AppData` por acceso denegado.
4. Esa advertencia no impidio generar el PDF ni invalido la compilacion del documento.

## Proceso documentado para el capitulo 8

Se deja registrado el flujo concreto que se uso para integrar `Chapter 8: LPC17xx Pin connect block` al apunte.

### Objetivo editorial

- Mantener formato de consulta rapida.
- Conservar la estructura original `8.1` a `8.5.21`.
- Preservar completas y en orden las tablas `74` a `99`.
- Poner enfasis en la electronica de los modos de pin:
  - seleccion de funcion,
  - `pull-up`,
  - `pull-down`,
  - `repeater`,
  - `open-drain`,
  - excepciones de `I2C0` y USB.

### Implementacion usada

1. Se relevo el `Chapter 8` en `docs/referencia/lpc17xx_um_unlocked.txt` y se reconstruyo su estructura completa:
   - `8.1` a `8.5.21`,
   - tablas `74` a `99`,
   - notas especiales para `P0.27`, `P0.28`, `P0.29` y `P0.30`.
2. Se separo el contenido nuevo en `docs/latex/chapter8.tex`.
3. `main.tex` paso a incluir ese archivo con `\input{chapter8.tex}` para evitar que el archivo principal siga creciendo de forma monolitica.
4. Se usaron `longtable` y tablas compactas para que los registros extensos entren en pagina sin perder filas.
5. Se normalizaron algunas inconsistencias de la transcripcion TXT cuando el simbolo del registro dejaba claro el valor correcto:
   - `PINMODE1` describe `P0.16` a `P0.26`, aunque la transcripcion menciona `Port 1`.
   - en `PINMODE_OD3`, el bit de `P3.25` se corrigio respecto de un typo de la transcripcion.
   - en `PINMODE_OD4`, el bit 29 se documento como `P4.29OD`.
6. No se agregaron figuras nuevas para este capitulo porque todo el contenido relevante pudo resolverse con tablas y notas tecnicas.

### QA aplicada

1. Se compilo con el script de la skill:

```powershell
powershell -ExecutionPolicy Bypass -File "C:\Users\Usuario\.codex\skills\latex-pdf-study-assistant\scripts\compile_latex.ps1" -WorkspaceRoot "C:\Users\Usuario\Documents\Ignacio\Facultad\TercerAño\ED3"
```

2. Se verifico que el indice del PDF incluyera el nuevo capitulo 8.
3. El capitulo quedo ubicado entre las paginas `15` y `26` del PDF generado.
4. Se renderizaron paginas afectadas a `artifacts/qa_png/`.
5. Se revisaron visualmente paginas representativas del bloque nuevo, en particular:
   - `page_20-20.png`,
   - `page_26-26.png`.
6. Resultado de la revision:
   - tablas visibles y completas en las paginas inspeccionadas,
   - sin cortes evidentes de columnas,
   - sin necesidad de rasterizar tablas.

### Archivos tocados por este capitulo

- `docs/latex/main.tex`
- `docs/latex/chapter8.tex`
- `docs/latex/main.pdf`

### Criterio para capitulos futuros largos

- Si un capitulo nuevo agrega muchas tablas o registros, preferir archivo separado e inclusion con `\input{...}`.
- Mantener `main.tex` como orquestador del documento y no como unico contenedor de todo el contenido.
- Hacer QA por paginas representativas cuando el bloque agregado supera 5 paginas.
