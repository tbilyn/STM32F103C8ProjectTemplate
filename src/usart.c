#include "main.h"
#include "usart.h"


void InitUSART1(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
    GPIOA->CRH |= GPIO_CRH_MODE9;
    GPIOA->CRH &= ~GPIO_CRH_CNF9;
    GPIOA->CRH |= GPIO_CRH_CNF9_1; // Alternate function output Push-pull

    GPIOA->CRH &= ~GPIO_CRH_MODE10;
    GPIOA->CRH &= ~GPIO_CRH_CNF10;
    GPIOA->CRH |= GPIO_CRH_CNF10_0;

    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    USART1->BRR = 0x1D4C;           // Baud rate 9600 on 72Mhz
    USART1->CR1 |= USART_CR1_UE;    // USART enable;
    USART1->CR1 |= USART_CR1_TE;  // Transciver enable
    USART1->CR1 |= USART_CR1_M;     // 9 bit data
    USART1->CR1 &= ~USART_CR1_PCE;  // Parity control disabled
    USART1->CR2 &= ~USART_CR2_STOP; // 1 stop bit

    USART1->CR1 |= USART_CR1_RXNEIE; // Receive Interupt enable
    //USART1->CR1 |= USART_CR1_TCIE;   // Transaction Complete Interupt enable

    
    USART1->CR1 &= ~USART_CR1_RE; // Receiver DISABLE, this will be anabled only after master sent anything
}