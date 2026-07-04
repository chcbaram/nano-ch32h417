#include "bsp.h"
#include "hw_def.h"
#include "cli.h"


#define Core_V3F_StartAddr   0x00000000
#define Core_V5F_StartAddr   0x00010000



bool bspInit(void)
{
  bool ret = true;


  #ifdef _USE_HW_CACHE
  #endif  

  SystemInit();
  SystemAndCoreClockUpdate();

	NVIC_WakeUp_V5F(Core_V5F_StartAddr);//wake up V5
  RCC_HB1PeriphClockCmd(RCC_HB1Periph_PWR,ENABLE);
	PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFE);

  return ret;
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
  // uint32_t tickstart = millis();
  // uint32_t wait      = ms;

  // /* Add a freq to guarantee minimum wait */
  // if (wait < HAL_MAX_DELAY)
  // {
  //   wait += (uint32_t)(uwTickFreq);
  // }

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
  return 0;
}

