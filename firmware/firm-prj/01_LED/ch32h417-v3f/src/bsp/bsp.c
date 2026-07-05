#include "bsp.h"
#include "hw_def.h"
#include "cli.h"


#define Core_V3F_StartAddr   0x00000000
#define Core_V5F_StartAddr   0x00010000


static volatile uint32_t systick_ms = 0;




bool bspInit(void)
{
  bool ret = true;


  #ifdef _USE_HW_CACHE
  #endif  

  SystemInit();
  SystemAndCoreClockUpdate();


  SysTick0->ISR  &= ~(1 << 0); // clear State flag
  SysTick0->CMP   = (uint32_t)((SystemCoreClock / 1000) - 1UL);
  SysTick0->CNT   = 0;
  SysTick0->CTLR  = 0x0F;

  NVIC_SetPriority(SysTick0_IRQn, 0xF0);
  NVIC_EnableIRQ(SysTick0_IRQn);

	NVIC_WakeUp_V5F(Core_V5F_StartAddr);//wake up V5
  RCC_HB1PeriphClockCmd(RCC_HB1Periph_PWR,ENABLE);
	// PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFE);

	// NVIC_WakeUp_V5F(Core_V5F_StartAddr);//wake up V5
	// HSEM_ITConfig(HSEM_ID0, ENABLE);
  //   NVIC->SCTLR |= 1<<4;
	// RCC_HB1PeriphClockCmd(RCC_HB1Periph_PWR,ENABLE);
	// PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFE);
	// HSEM_ClearFlag(HSEM_ID0);

  return ret;
}

void SysTick0_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void SysTick0_Handler(void)
{
  if (SysTick0->ISR == (1 << 0))
  {
    SysTick0->ISR &= ~(1 << 0); // clear State flag    
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

