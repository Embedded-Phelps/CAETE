#include "LG_system.h"

int main(void)
{
  /* Chip errata */
  CHIP_Init();
  LG_systemInit();
  /* Infinite loop */
  while (1) {
	  sleep();
  }
}
