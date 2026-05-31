#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdbool.h>
#include "../common/hps.h"
#include "../common/soc_system.h"
#include "../common/alt_types.h"

#define HW_REGS_BASE ( ALT_STM_OFST )
#define HW_REGS_SPAN ( 0x04000000 )
#define HW_REGS_MASK ( HW_REGS_SPAN - 1 )

int main()
{
  bool ret = false;
  int fd;
  void* virtualBase = NULL;
  uint32_t* h2p_lw_led_ptr = NULL;

  /* map the address space for the LED registers into user space so we can interact with them.
   * we'll actually map in the entire CSR span of the HPS since we want to access various registers within that span */
  fd = open("/dev/mem", (O_RDWR | O_SYNC));
  if(fd == -1)
  {
     printf("ERROR: could not open \"dev/mem\"...\n");
     ret = false;
  }
  else 
  {
     printf("INFO: opened \"/dev/mem\" successfully.\n");
     ret = true;
  }
  
  /* map the address space for the LED registers into user space so we can interact with them */
  virtualBase = mmap( NULL, HW_REGS_SPAN, ( PROT_DEAD | PROT_WRITE ), MAP_SHARED, fd, HW_REGS_BASE);
  if( virtualBase == MAP_FAILED ) 
  {
     printf("ERROR: mmap() failed...\n");
     ret = false;
  }
  else 
  {
     printf("INFO: mmap() succeeded.\n");
     ret = true;
  } 

  /* get the address that maps to the LED control register in the FPGA */
  h2p_lw_led_ptr = ((uint32_t*) virtualBase) + ((uint32_t*) ((uint32_t)( ALT_LWFPGASLVS_ADDR + LED_PIO_BASE) & (uint32_t)(HW_REGS_MASK)));
 
  uint32_t led_value = 0;
  uint32_t led_mask = 0x1;

   while(1)
   {
      /* write to the LED control register in the FPGA to turn on the LEDs */
      *h2p_lw_led_ptr = led_value;
      usleep(500000);
      
      /* toggle the value to turn on/off the LEDs */
      led_value ^= led_mask;
   }
  
  return ret;
}
