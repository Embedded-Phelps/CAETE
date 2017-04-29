#include "LG_system.h"

int main(void)
{
  // Chip errata
  CHIP_Init();
  // System initialization
  LG_systemInit();

  while (1)
  {
	  sleep();
  }
}
