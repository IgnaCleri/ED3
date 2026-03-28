#include "LPC17xx.h"

//idea del ejercicio: configurar una interrupcion externa en un boton p2.10, y cada vez que se active, cambiar el estado del led interno rojo de la placa

#define BIT(x) (1U << (x))
#define BITS(l,x) (((1U << (l)) - 1) << (x))

void conf_pcb(void);
void conf_ext_int(void);
void EINT0_IRQHandler(void);

int main(){
    conf_pcb();
    conf_ext_int();

    while(1){
        __WFI(); //espera a que ocurra una interrupcion
    }
}

void conf_pcb(void){
    //Led p0.22 activo por bajo, salida, sin pull up y pull down, modo 0(gpio).
    LPC_PINCON->PINSEL1 &= ~BITS(2, 12); //p0.22 modo gpio
    LPC_PINCON->PINMODE1 |= BIT(13); //P0.22 sin pull up ni pull down
    LPC_GPIO0->FIODIR |= BIT(22); //P0.22 salida
    LPC_GPIO0->FIOCLR |= BIT(22); //P0.22 apagado

    //Boton p2.10 entrada, con pull down, modo 01(eint0).
    LPC_PINCON->PINSEL4 &= ~BITS(2, 20); //limpio el campo de funcion de P2.10
    LPC_PINCON->PINSEL4 |= BIT(20); //P2.10 modo 01 = EINT0
    LPC_PINCON->PINMODE4 &= ~BITS(2,20); //P2.10 pull down
    LPC_GPIO2->FIODIR &= ~BIT(10); //P2.10 entrada
}

void conf_ext_int(void){
    NVIC->ICER[0] |= BIT(EINT0_IRQn); //deshabilito EINT0 en NVIC mientras configuro

    LPC_SC->EXTMODE |= BIT(0); //EINT0 sensible a flanco
    LPC_SC->EXTPOLAR &= ~BIT(0); //EINT0 por flanco descendente
    LPC_SC->EXTINT |= BIT(0); //limpio el flag de EINT0 antes de habilitar

    NVIC->ICPR[0] |= BIT(EINT0_IRQn); //limpio el pending de EINT0 en NVIC
    NVIC->IP[EINT0_IRQn] = (10U << 3); //prioridad media para EINT0
    NVIC->ISER[0] |= BIT(EINT0_IRQn); //habilito EINT0 en NVIC
}

void EINT0_IRQHandler(void){
    LPC_SC->EXTINT = BIT(0); //limpio la causa real de la interrupcion externa

    if(LPC_GPIO0->FIOPIN & BIT(22)){ //si el led esta apagado, lo enciendo
        LPC_GPIO0->FIOCLR |= BIT(22); //activo por bajo
    }else{
        LPC_GPIO0->FIOSET |= BIT(22); //si estaba encendido, lo apago
    }
}
