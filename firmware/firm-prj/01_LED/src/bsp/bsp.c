#include "bsp.h"
#include "hw_def.h"
#include "cli.h"



bool bspInit(void)
{
  bool ret = true;


  #ifdef _USE_HW_CACHE
  #endif  


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

