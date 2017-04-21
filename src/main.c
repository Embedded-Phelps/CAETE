#include "LG_system.h"

int main(void)
{
	double i =18.22;
  /* Chip errata */
  CHIP_Init();
  LG_systemInit();
  /* Infinite loop */
  while (1) {
	  sleep();

  }
}
