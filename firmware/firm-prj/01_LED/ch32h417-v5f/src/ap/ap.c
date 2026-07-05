#include "ap.h"


void apInit(void)
{
}

void apMain(void)
{
  int cnt = 0;

  int clock = HCLKClock;
  int clock2 = SystemCoreClock;
  
  ledOn(0);
  
  while (1)
  {
    cnt++;
    cnt++;
    cnt++;
    cnt++;
    cnt++;
    cnt++;    
    delay(500);
    ledToggle(0);
  }
}
