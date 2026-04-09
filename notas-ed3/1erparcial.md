# Resumen práctico CMSIS - 1er parcial ED3

## Temas

- Punteros CMSIS y macros
- GPIO
- NVIC e interrupciones
- SysTick
- ADC
- Clocks internos

---

## 1. Punteros CMSIS y macros

### Idea base

CMSIS ya define punteros a los periféricos:

```c
LPC_GPIO0
LPC_SC
LPC_ADC
SysTick
NVIC
```

Acceso general:

```c
periferico->registro
```

### Macro útil

```c
#define BIT(n) (1U << (n))
```

### Operaciones básicas

Poner un bit en `1`:

```c
registro |= BIT(n);
```

Poner un bit en `0`:

```c
registro &= ~BIT(n);
```

Alternar un bit:

```c
registro ^= BIT(n);
```

Leer un bit:

```c
if (registro & BIT(n))
{
    // bit en 1
}
```

### Campos de varios bits

Si un campo ocupa varios bits, conviene limpiar y luego cargar:

```c
registro = (registro & ~mascara) | valor_nuevo;
```

### Regla práctica

- usar `=` solo si querés sobrescribir todo el registro
- usar `|=` y `&= ~` para tocar un solo bit
- usar máscara para campos de varios bits
---

## 2. GPIO

### Registros principales

- `PINSEL`: selecciona la función del pin
- `PINMODE`: configura la resistencia interna
- `PINMODE_OD`: configura open-drain
- `FIODIR`: define entrada o salida
- `FIOSET`: pone la salida en `1`
- `FIOCLR`: pone la salida en `0`
- `FIOPIN`: lee o escribe el estado del pin

### Función del pin

- cada pin tiene un campo de 2 bits en `PINSEL`
- `00` suele ser GPIO
- otros valores seleccionan funciones alternativas del periférico
- para configurar un pin conviene limpiar el campo y luego cargar el valor nuevo

### Modo del pin

`PINMODE` define la resistencia interna:

- `00`: pull-up
- `01`: repeater
- `10`: sin pull-up / sin pull-down
- `11`: pull-down

### Dirección

- `FIODIR = 1`: salida
- `FIODIR = 0`: entrada

### Escritura y lectura

- `FIOSET` escribe `1` sin afectar otros bits
- `FIOCLR` escribe `0` sin afectar otros bits
- `FIOPIN` permite leer el estado actual del pin

### Open-drain

- se configura con `PINMODE_OD`
- `0`: salida normal
- `1`: open-drain
- en open-drain, escribir `0` fuerza nivel bajo
- en open-drain, escribir `1` libera la línea

### Orden típico de configuración

1. Configurar función en `PINSEL`.
2. Configurar modo en `PINMODE` si hace falta.
3. Configurar `PINMODE_OD` si se usa open-drain.
4. Configurar dirección en `FIODIR`.
5. Escribir o leer con `FIOSET`, `FIOCLR` o `FIOPIN`.

## 3. NVIC e interrupciones

> Pendiente.
>
> Orden importante:
> - deshabilitar la interrupción
> - configurar periférico y flags
> - limpiar pending
> - habilitar al final

## 4. SysTick

> Pendiente.
>
> Registros:
> - `CTRL`
> - `LOAD`
> - `VAL`
>
> Ecuaciones:
>
> ```c
> tiempo = (LOAD + 1) / f_clock
> LOAD = tiempo * f_clock - 1
> ```

## 5. ADC

> Pendiente.
>
> Idea general:
> - habilitar clock
> - configurar pin
> - elegir canal
> - iniciar conversión
> - leer resultado

## 6. Clocks internos

> Pendiente.
>
> Registros a incluir:
> - `PCONP`
> - `PCLKSEL0`
> - `PCLKSEL1`
> - `SystemCoreClock`
