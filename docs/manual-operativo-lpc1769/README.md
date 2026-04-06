# Manual operativo LPC1769

Esta carpeta contiene la nueva linea documental del repositorio para el LPC1769. El objetivo es construir un manual tecnico operativo, separado del apunte actual en LaTeX, sin modificar ni degradar el material ya consolidado en `docs/latex/`.

## Objetivo del nuevo manual

El nuevo manual debe servir como documento de trabajo para estudiar y configurar el LPC1769 de forma ordenada, manteniendo el rigor tecnico del datasheet original pero reorganizando la informacion para que sea mas facil de usar durante el desarrollo.

La idea no es resumir el datasheet eliminando detalle, sino volverlo mas operativo:

- conservar tablas completas y nombres tecnicos originales;
- explicar el orden real en que se configura cada bloque;
- incluir caracteristicas electricas y funcionales relevantes;
- incorporar informacion especifica de la placa de desarrollo usada en la materia;
- dejar visible el puntero CMSIS con el que se accede a cada registro, sin incluir codigo en C.

## Fuentes documentales que alimentan este manual

- `docs/referencia/lpc17xx_um_unlocked.pdf`
- `docs/referencia/lpc17xx_um_unlocked.txt`
- `docs/referencia/DATASHEET PLACA DE DESARROLLO.pdf`
- `lib/CMSISv2p00_LPC17xx/inc/LPC17xx.h`
- `lib/CMSISv2p00_LPC17xx/Drivers/inc/`

## Criterio editorial

Este nuevo documento tiene una impronta distinta del apunte actual:

- usa numeracion propia para sus capitulos;
- se organiza por unidades de la materia y no por numeracion del datasheet original;
- prioriza el uso operativo del hardware;
- no incluye codigo fuente en C;
- si incluye referencias CMSIS del tipo `LPC_ADC->ADCR`, `LPC_PINCON->PINSEL0`, etc.;
- mantiene las tablas del datasheet sin resumirlas ni reducirlas;
- agrega explicaciones antes de las tablas para que quede claro que se esta configurando y por que;
- puede incorporar observaciones de placa, alimentacion, conectores, jumpers, pinout y restricciones practicas.

## Estructura esperada del manual

La estructura general se ordena por unidades o bloques tematicos de la materia.

Las unidades concretas no quedan cerradas de antemano en este documento. Se iran definiendo e incorporando segun las necesidades de la cursada y segun las indicaciones del usuario.

El criterio base de organizacion sigue siendo pedagogico y operativo, no una copia lineal del datasheet.

## Plantilla editorial por capitulo

Cada capitulo nuevo deberia seguir, en lo posible, una plantilla comun:

### 1. Presentacion del bloque

- que es el bloque;
- para que sirve;
- por que es importante dentro de la materia;
- como se relaciona con otros bloques del microcontrolador o de la placa.

### 2. Caracteristicas tecnicas

- capacidades del bloque;
- limitaciones;
- requisitos de clock, tension, alimentacion o conexion;
- notas de hardware relevantes;
- datos especificos de la placa si corresponden.

### 3. Orden de configuracion

Esta seccion debe explicar el orden correcto en que se prepara el bloque. No lleva codigo, pero si una guia tecnica clara.

Ejemplo conceptual:

- primero se identifica el pin o canal involucrado;
- luego se configura su funcion en `PINSEL`;
- despues se ajusta `PINMODE`;
- mas tarde se habilita el bloque correspondiente;
- finalmente se ajustan los registros propios del periferico.

### 4. Registros involucrados

Se deben presentar los registros en orden de uso practico, no necesariamente en el orden en que aparecen en el datasheet.

### 5. Explicacion registro por registro

Para cada registro se espera documentar:

- nombre completo;
- direccion;
- funcion dentro del bloque;
- significado operativo de sus bits;
- que implica escribir `1` o `0` cuando eso sea relevante;
- advertencias importantes;
- puntero CMSIS correspondiente.

### 6. Tablas originales

Las tablas del datasheet deben mantenerse completas. No deben resumirse ni reemplazarse por listas abreviadas si esas tablas contienen informacion tecnica util para consulta real.

### 7. Referencia CMSIS

En cada bloque se debe indicar unicamente el acceso conceptual al registro desde CMSIS, por ejemplo:

- `LPC_PINCON->PINSEL0`
- `LPC_GPIO0->FIODIR`
- `LPC_ADC->ADCR`

No se deben agregar ejemplos de codigo, funciones helper ni fragmentos en C en esta etapa.

## Primera etapa aprobada para desarrollo

La primera etapa del manual queda acotada a la informacion general de la placa y del sistema. Antes de avanzar sobre perifericos como GPIO o ADC, el documento nuevo debe cubrir:

- que microcontrolador se usa;
- quien lo fabrica;
- arquitectura general;
- caracteristicas principales;
- informacion de la placa de desarrollo utilizada;
- conectores relevantes;
- pinout y funciones practicas visibles en la placa;
- consideraciones de alimentacion y depuracion;
- relacion entre la placa y los pines/perifericos del LPC1769.

## Uso del PDF de la placa de desarrollo

El archivo `docs/referencia/DATASHEET PLACA DE DESARROLLO.pdf` debe usarse como fuente para incorporar informacion concreta de la placa empleada en la materia. A partir de la revision preliminar, ese PDF aporta al menos:

- identificacion de la placa `LPCXpresso LPC1769`;
- numero de placa NXP `OM13085`;
- presencia de interfaz `CMSIS-DAP`;
- conectores de expansion;
- alimentacion por USB y opciones de alimentacion externa;
- relacion entre el microcontrolador objetivo y la placa portadora.

Cuando se redacte el capitulo de introduccion general, esta informacion debe integrarse junto con el pinout y las notas practicas de uso de la placa.

## Limites actuales del proyecto

Por decision editorial actual:

- no se modifica `docs/latex/`;
- no se reutiliza su numeracion de capitulos;
- no se agrega codigo C;
- no se simplifican tablas del datasheet;
- no se prioriza una explicacion academica larga, sino una explicacion operativa y tecnicamente fiel.

## Proximo paso esperado

Una vez validado este documento base, el siguiente paso sera definir la estructura concreta del nuevo documento fuente dentro de esta carpeta y redactar la primera unidad:

- informacion general del microcontrolador;
- informacion general de la placa de desarrollo;
- mapa base de referencias que se usaran en los capitulos siguientes.
