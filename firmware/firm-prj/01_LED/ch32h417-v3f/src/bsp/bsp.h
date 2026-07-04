#ifndef BSP_H_
#define BSP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "def.h"
#include "ch32h417.h"


void logPrintf(const char *fmt, ...);



bool bspInit(void);

void delay(uint32_t time_ms);
void delayUs(uint32_t delay_us);
uint32_t millis(void);
uint32_t micros(void);



#ifdef __cplusplus
}
#endif

#endif