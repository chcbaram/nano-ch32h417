#include "ap.h"


void apInit(void)
{
}

void apMain(void)
{
  int clock = HCLKClock;
  int clock2 = SystemCoreClock;
  int cnt = 0;

  ledOn(0);
  
  
  while (1)
  {
    cnt++;
    cnt++;
    cnt++;
    cnt++;
    cnt++;    
    delay(500);
    ledToggle(0);
  }
}
