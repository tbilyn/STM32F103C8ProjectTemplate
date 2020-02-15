#include "main.h"

#define HSE_STARTUP_TIMEOUT ((uint16_t)0x0500) /*!< Time out for HSE start up */

uint8_t CustomSystemInit72MHz();

void blocking_delay_ms(uint16_t ms);
