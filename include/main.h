#include <newlib.h>
#include <string.h>
#include "stm32f103xb.h"

#define SYSTICK_CONFIG_TICKS        ((uint32_t)72000)

volatile uint16_t systickCounter;
