#include "bsp.h"
#include "hw_def.h"
#include "cli.h"




static volatile uint32_t systick_ms = 0;


bool bspInit(void)
{
  bool ret = true;


  #ifdef _USE_HW_CACHE
  #endif  

  SystemAndCoreClockUpdate();
  if (SystemCoreClock != 400000000)
  {
    SystemInit();
    SystemAndCoreClockUpdate();
  }
  
  SysTick0->ISR  &= ~(1 << 1); // clear State flag
  SysTick1->CMP   = (uint32_t)((HCLKClock / 1000) - 1UL);
  SysTick1->CNT   = 0;
  SysTick1->CTLR  = 0x0F;

  NVIC_SetPriority(SysTick1_IRQn, 0xF0);
  NVIC_EnableIRQ(SysTick1_IRQn);

  return ret;
}

void SysTick1_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void SysTick1_Handler(void)
{
  if (SysTick0->ISR == (1 << 1))
  {
    SysTick0->ISR &= ~(1 << 1); // clear State flag    
    systick_ms++;    
  }
}

void delay(uint32_t ms)
{
#ifdef _USE_HW_RTOS
  if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
  {
    osDelay(ms);
  }
  else
  {
    HAL_Delay(ms);
  }
#else
  uint32_t pre_time = millis();

  while (millis() - pre_time < ms)
    ;

#ifdef _USE_HW_CLI 
  while ((millis() - tickstart) < wait)
  {
    cliLoopIdle();
  }
  #endif
#endif
}

uint32_t millis(void)
{
  return systick_ms;
}

