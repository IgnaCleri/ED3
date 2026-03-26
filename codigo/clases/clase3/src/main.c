#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include <cr_section_macros.h>
void retardo(uint32_t time_ms);
void EINT0_Config();
uint32_t inte;
uint32_t Delay;
uint32_t duty=1;
int main(void) {
SysTick_Config(SystemCoreClock/1000);
LPC_GPIO0->FIODIR|= 1<<22;
EINT0_Config();
while(1) {
if(inte<duty) {
    LPC_GPIO0->FIOCLR |= 1<<22;
}
else
{
LPC_GPIO0->FIOSET|= 1<<22;
}
//retardo(10);
}
return 0 ;
}
void SysTick_Handler(void){
inte++;
inte = inte%11;
Delay--;
if(Delay < 0){
Delay = 0;
}
SysTick->CTRL &= SysTick->CTRL;
}
void retardo(uint32_t time_ms){
Delay = time_ms;
while(Delay !=0);
}
void EINT0_Config(){
LPC_PINCON->PINSEL4 |= 1<<20 ;
LPC_SC->EXTINT |= 1;// es lp mismo que 1<<0 ;
LPC_SC->EXTMODE |= 1 ;
LPC_SC->EXTPOLAR |= 0 ;
NVIC_EnableIRQ(EINT0_IRQn);// terminamos la configuracion con el nvic siempre
//NVIC_SetPriority(EINT0_IRQn,1);
return;
}
void EINT0_IRQHandler(void){
static int j;
switch(j){
case 1:
duty = 1;
j++;
break;
case 2:
duty = 2;
j++;
break;
case 3:
duty = 3;
j++;
break;
case 4:
duty = 4;
j++;
break;
case 5:
duty = 5;
j++;
break;
case 6:
duty = 6;
j++;
break;
case 7:
duty = 7;
j++;
break;
case 8:
duty = 8;
j++;
break;
case 9:
duty = 9;
j++;
break;
case 10:
duty = 10;
j++;
break;
default:
duty = 1;
j++;
break;
}
j = j%11;
LPC_SC->EXTINT |= 1;// es lp mismo que 1<<0
return;
}
