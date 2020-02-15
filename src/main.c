#include "main.h"
#include "common.h"
#include "usart.h"



void USART1_IRQHandler(void)
{
    if (USART1->SR & USART_SR_RXNE)
    {
       
    }
    // else if (USART1->SR & USART_SR_TC)
    // {
    //     tc_ticks = systickCounter;
    //     USART1->SR &= ~USART_SR_TC;
    // }
}

int main(void)
{
    CustomSystemInit72MHz();
    SysTick_Config(72000);
    InitUSART1();
    
    NVIC_EnableIRQ(USART1_IRQn);

    while (1)
    {
        
    }
    
}