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

## Proceso documentado para el capitulo 6

Se deja registrado el flujo real usado para integrar `Chapter 6: LPC17xx Nested Vectored Interrupt Controller (NVIC)` al apunte.

### Objetivo editorial

- Mantener formato de consulta rapida.
- Preservar la numeracion real del datasheet en el bloque `6.1` a `6.12`.
- Incluir completas las tablas `50` a `71`.
- Traducir las tablas al espanol conservando nombres tecnicos de registros, bits y senales.
- Incorporar notas tecnicas surgidas de la discusion conceptual previa.
- No agregar figura nueva en esta primera version del capitulo.

### Implementacion usada

1. Se relevo el `Chapter 6` en `docs/referencia/lpc17xx_um_unlocked.txt`, usando tambien `docs/referencia/lpc17xx_um_unlocked.pdf` como apoyo de lectura.
2. Antes de editar LaTeX, se explico el contenido en chat por bloques didacticos:
   - panorama del NVIC,
   - fuentes de interrupcion y tabla vectorial,
   - estados `enabled`, `pending` y `active`,
   - prioridades y arbitraje,
   - remapeo de tabla vectorial con `VTOR`,
   - disparo por software con `STIR`.
3. Se consolidaron como notas tecnicas del capitulo las aclaraciones surgidas en esa discusion:
   - jerarquia conceptual entre `Reset`, `NMI`, `HardFault`, excepciones del sistema e `IRQ`,
   - diferencia entre `Interrupt ID`, `Exception Number` y `Vector Offset`,
   - diferencia entre `enabled`, `pending` y `active`,
   - manejo automatico de `active` por el NVIC/Cortex-M3,
   - comportamiento de preemption sin volver la ISR interrumpida a `pending`,
   - uso practico de `ISPR` y diferencia con `STIR`,
   - aclaracion de que la tabla vectorial guarda direcciones de handlers, no el codigo del handler.
4. Se creo `docs/latex/chapter6.tex` como archivo separado para evitar seguir haciendo crecer `main.tex`.
5. Se integro el capitulo en `docs/latex/main.tex` con `\input{chapter6.tex}` antes del bloque actual de capitulos 8 y 9.
6. Se mantuvo el criterio editorial del apunte:
   - narrativa breve,
   - tablas como fuente principal de consulta,
   - notas tecnicas solo donde ayudan a interpretar el NVIC o a evitar errores de firmware.
7. Se incluyeron completas las tablas `50` a `71`, junto con una nota editorial sobre la inconsistencia del datasheet en `Table 59`.

### QA aplicada

1. Se compilo `docs/latex/main.tex` con `tectonic`:

```bash
tectonic --keep-logs --keep-intermediates --outdir docs/latex docs/latex/main.tex
```

2. Resultado: compilacion exitosa y generacion de `docs/latex/main.pdf`.
3. El indice del PDF incluyo el nuevo Chapter 6 en la posicion correcta.
4. El capitulo quedo ubicado entre las paginas `16` y `31` del PDF generado.
5. Se renderizaron paginas representativas a `artifacts/qa/chapter6/` para control visual.
6. Se revisaron visualmente, como minimo, estas paginas:
   - apertura del capitulo,
   - `Table 50`,
   - cierre de `Table 50` y bloque `VTOR`,
   - `Table 51`,
   - bloque `ISER/ICER`,
   - bloque `IPR`,
   - cierre con `STIR`.
7. Se observaron advertencias `Overfull \hbox` y `Underfull \hbox` durante la compilacion, pero no se detectaron fallas visuales graves en las paginas inspeccionadas del Chapter 6.

### Archivos tocados por este capitulo

- `docs/latex/main.tex`
- `docs/latex/chapter6.tex`
- `docs/latex/main.pdf`
- `artifacts/qa/chapter6/`

### Notas tecnicas o decisiones editoriales

- `Chapter 6` se resolvio sin figuras nuevas porque el contenido quedo suficientemente cubierto con tablas y notas tecnicas.
- Se mantuvo la estructura general del manual original para que el lector pueda cruzar facil el apunte con el datasheet.
- `tectonic` quedo registrado como compilador efectivo usado en esta integracion, sin invalidar otros flujos historicos del documento.

## Proceso documentado para el capitulo 23

Se deja registrado el flujo real usado para integrar `Chapter 23: LPC17xx System Tick Timer` al apunte.

### Objetivo editorial

- Mantener formato de consulta rapida.
- Preservar la numeracion real del datasheet en el bloque `23.1` a `23.6`.
- Incluir el mapa de registros y las tablas `438` a `442`.
- Resumir los cuatro ejemplos de c\'alculo de temporizaci\'on sin perder los valores concretos del manual.
- Incorporar la `Fig 118` del datasheet con un recorte dedicado para el diagrama de bloques del `SysTick`.

### Implementacion usada

1. Se relevo el `Chapter 23` en `docs/referencia/lpc17xx_um_unlocked.txt`, usando el PDF como apoyo cuando hac\'ia falta verificar la estructura del capitulo.
2. Por pedido del usuario se salte\'o la fase de explicaci\'on previa en chat y se pas\'o directo a la redacci\'on del resumen.
3. Se cre\'o `docs/latex/chapter23.tex` como archivo separado.
4. Se integr\'o el capitulo en `docs/latex/main.tex` sin alterar el orden interno de los cap\'itulos ya existentes; se preserv\'o el salto de numeraci\'on para seguir el datasheet.
5. Se mantuvo el criterio editorial del apunte:
   - narrativa breve,
   - tablas y mapa de registros como base principal,
   - notas t\'ecnicas s\'olo donde ayudan a interpretar `COUNTFLAG`, `STCURR` y `STCALIB`.
6. Se extrajo un recorte dedicado de la `Fig 118` desde la p\'agina del datasheet donde aparece el diagrama de bloques del `System Tick Timer` y se guard\'o en `docs/latex/images/`.

### QA aplicada

1. Se compil\'o `docs/latex/main.tex` con `tectonic`.
2. Resultado: compilaci\'on exitosa y generaci\'on de `docs/latex/main.pdf`.
3. El \'indice del PDF incluy\'o el nuevo Chapter 23 en la posici\'on correcta.
4. El cap\'itulo qued\'o ubicado entre las p\'aginas `64` y `68` del PDF generado.
5. Se renderizaron p\'aginas representativas a `artifacts/qa/chapter23/`.
6. Se revisaron visualmente estas p\'aginas del bloque:
   - apertura del cap\'itulo,
   - p\'agina con la figura del diagrama de bloques,
   - mapa de registros,
   - tablas de bits,
   - bloque de ejemplos.
7. Resultado de la revisi\'on:
   - tablas legibles en las p\'aginas inspeccionadas,
   - figura `Fig 118` integrada con recorte dedicado y legible en el PDF final,
   - sin errores visuales graves,
   - warnings de maquetado presentes en la compilaci\'on global, pero sin impacto claro en el Chapter 23 revisado.

### Archivos tocados por este capitulo

- `docs/latex/main.tex`
- `docs/latex/chapter23.tex`
- `docs/latex/images/lpc17xx_systick_block_diagram_fig118.png`
- `docs/latex/main.pdf`
- `artifacts/qa/chapter23/`
