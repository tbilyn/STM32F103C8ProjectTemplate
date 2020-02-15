#include "common.h"


void SysTick_Handler(void)
{
    systickCounter += 1;
}

uint8_t CustomSystemInit72MHz()
{
    uint16_t startUpCounter = 0;
    RCC->CR |= RCC_CR_HSEON; // enable HSE

    // HSE requires some time to be ready. Hardware sets HSERDY bit when HSE is ready to be used
    // here we wait for that bit to be set. Also if it is not ready for some amount of time - we skip waiting.
    while (!(RCC->CR & RCC_CR_HSERDY) && startUpCounter < HSE_STARTUP_TIMEOUT)
    {
        startUpCounter += 1;
    }
    if ((RCC->CR & RCC_CR_HSERDY) == 0)
    {
        // HSE failed to start
        RCC->CR &= ~RCC_CR_HSEON;

        return 1;
    }

    // when clock frequency is high - we need to configure flash in a particular way
    FLASH->ACR |= FLASH_ACR_PRFTBE;
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;

    RCC->CFGR &= ~RCC_CFGR_PLLXTPRE; // select HSE (with no divider)
    RCC->CFGR |= RCC_CFGR_PLLSRC;    // as source for PLL
    RCC->CFGR &= ~RCC_CFGR_PLLMULL;  // reset bits related to PLLMULL
    RCC->CFGR |= RCC_CFGR_PLLMULL9;  // Use 9 as PLL multiplier

    RCC->CFGR &= ~RCC_CFGR_HPRE;  // AHB prescaler set to 1
    RCC->CFGR &= ~RCC_CFGR_PPRE1; // APB1 prescaler set to 1
    RCC->CFGR &= ~RCC_CFGR_PPRE2; // APB2 prescaler set to 1

    RCC->CR |= RCC_CR_PLLON; // enable PLL
    // wait while PLL is ready
    while (!(RCC->CR & RCC_CR_PLLON))
        ;

    RCC->CFGR &= ~RCC_CFGR_SW;    // clear SW bits
    RCC->CFGR |= RCC_CFGR_SW_PLL; // select PLL as SystemClock

    // wait while system clock is selected
    while (!(RCC->CFGR & RCC_CFGR_SWS_PLL))
        ;

    // Done
    SystemCoreClockUpdate();
    return 0;
}

void blocking_delay_ms(uint16_t ms)
{
    while (systickCounter < ms)
        ;
    systickCounter = 0;
}
