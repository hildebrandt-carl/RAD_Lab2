/*
 * Copyright (c) 2015, Swiss Federal Institute of Technology (ETH Zurich).
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Author:  Reto Da Forno
 *          Federico Ferrari
 */

#include "contiki.h"
#include "platform.h"

/*---------------------------------------------------------------------------*/
#ifndef NODE_ID
uint16_t TOS_NODE_ID = 0x1122;  /* do NOT change this default value! */
volatile uint16_t node_id;
#endif /* NODE_ID */
/*---------------------------------------------------------------------------*/
void
print_processes(struct process *const processes[])
{
  uart_enable(1);
  printf("Starting");
  while(*processes != NULL) {
    printf(" '%s'", (*processes)->name);
    processes++;
  }
  printf("\r\n");
}
/*---------------------------------------------------------------------------*/
/* prints some info about the system */
void
print_device_info(void)
{
  /* note: this device does not offer an LPMx.5 mode, therefore there's no
   * corresponding reset source */
  static uint32_t rst_flag;         
  rst_flag = SYSRSTIV; /* flag is automatically cleared by reading it */
  
  printf("\r\n\r\nReset Source: ");
  /* when the PMM causes a reset, a value is generated in the system reset
     interrupt vector generator register (SYSRSTIV), corresponding to the
     source of the reset */
  /* note: do not use switch .. case construct due to contiki!*/
  if(SYSRSTIV_BOR == rst_flag) {         
    printf("BOR");        /* brownout reset (BOR) */
  } else if(SYSRSTIV_RSTNMI == rst_flag) {
    printf("Reset Pin");
  } else if(SYSRSTIV_DOBOR == rst_flag) {
    printf("Software BOR");
  } else if(SYSRSTIV_SECYV == rst_flag) {
    printf("Security violation");
  } else if(SYSRSTIV_SVSL == rst_flag || SYSRSTIV_SVSH == rst_flag) {
    printf("SVS");
  } else if(SYSRSTIV_SVML_OVP == rst_flag || SYSRSTIV_SVMH_OVP == rst_flag) {
    printf("SVM");
  } else if(SYSRSTIV_DOPOR == rst_flag) {
    printf("Software POR");
  } else if(SYSRSTIV_WDTTO == rst_flag) {
    printf("Watchdog timeout");
  } else if(SYSRSTIV_WDTKEY == rst_flag) {
    printf("Watchdog password violation");
  } else if(SYSRSTIV_KEYV == rst_flag) {
    printf("KEYV");
  } else if(SYSRSTIV_PLLUL == rst_flag) {
    printf("PLLUL");
  } else if(SYSRSTIV_PERF == rst_flag) {
    printf("Peripheral area fetch");
  } else if(SYSRSTIV_PMMKEY == rst_flag) {
    printf("PMMKEY");
  } else {
    printf("Unknown");
  }

  printf("\r\nMCU: " MCU_TYPE " (%ukB SRAM, %ukB ROM, %ukB used)\r\n",
         SRAM_SIZE >> 10,
         FLASH_SIZE >> 10,
         flash_code_size() >> 10);
  printf("Compiler: " COMPILER_INFO "\r\nDate: " COMPILE_DATE "\r\n");

  /* don't disable UART module here */
}
/*---------------------------------------------------------------------------*/
int
main(int argc, char **argv)
{
  watchdog_init();

  /* initialize hardware */
  P1DIR = BIT0;                  /* don't set other pins as outputs */
  //PORT_CLR_I(1);
  PORT_CFG_OUT_I(1);
  PORT_CLR_I(1);
  PORT_CFG_OUT_I(3);
  PORT_CLR_I(3);
  PORT_CFG_OUT_I(J);
  PORT_CLR_I(J);
    
  PIN_SET(LED_STATUS);


//   /* board-specific optimal configuration of unused pins */
// #ifndef FLOCKLAB
//   //PIN_SET_I(1, 1);    /* push-button, tied to 3V */
// #endif /* FLOCKLAB */
  //PIN_SET_I(1, 6);    /* UART TX, set high if pin is in use */
  //PIN_SET_I(1, 7);    /* SPI B0 STE (is tied to 3V) */
 
  /* pin mappings */
#ifdef RF_GDO0_PIN
  PIN_MAP_AS_OUTPUT(RF_GDO0_PIN, PM_RFGDO0);
#endif
#ifdef RF_GDO1_PIN
  PIN_MAP_AS_OUTPUT(RF_GDO1_PIN, PM_RFGDO1);
#endif
#ifdef RF_GDO2_PIN
  PIN_MAP_AS_OUTPUT(RF_GDO2_PIN, PM_RFGDO2);
#endif
#ifdef MCLK_PIN
  PIN_MAP_AS_OUTPUT(MCLK_PIN, PM_MCLK);
#endif
#ifdef SMCLK_PIN
  PIN_MAP_AS_OUTPUT(SMCLK_PIN, PM_SMCLK);
#endif
#ifdef ACLK_PIN
  PIN_MAP_AS_OUTPUT(ACLK_PIN, PM_ACLK);
#endif
  
#ifdef DEBUG_SWITCH
  PIN_CFG_INT(DEBUG_SWITCH);
#endif

  clock_init();
  rtimer_init();
  uart_init();
  uart_enable(1);
  uart_set_input_handler(serial_line_input_byte);
  print_device_info();


#if RF_CONF_ON
  /* init the radio module and set the parameters */
  rf1a_init();

#endif /* RF_CONF_ON */

  /* set the node ID */
#ifndef NODE_ID
  node_id = TOS_NODE_ID;
#endif /* NODE_ID */

  if(node_id > 0) {
    printf(CONTIKI_VERSION_STRING " started. Node ID is set to %u.\r\n",
           node_id);
  } else {
    printf(CONTIKI_VERSION_STRING " started. Node ID is not set.\r\n");
  }
  
#if FRAM_CONF_ON
  if (!fram_init()) {
    DEBUG_PRINT_FATAL("ERROR: FRAM failure");
  }
#endif

#if BOLT_CONF_ON
  bolt_init(0);
#endif /* BOLT_CONF_ON */  

  process_init();
  process_start(&etimer_process, NULL);

  random_init(node_id * TA0R);
  serial_line_init();
  /* note: do not start the debug process here */

  energest_init();
  ENERGEST_ON(ENERGEST_TYPE_CPU);

#if NULLMAC_CONF_ON
  nullmac_init();
#endif /* NULLMAC_CONF_ON */

#if WATCHDOG_CONF_ON
  watchdog_start();
#endif /* WATCHDOG_CONF_ON */

  /* start processes */
  print_processes(autostart_processes);
  autostart_start(autostart_processes); // stop here because process started?
  debug_print_init();  
  /* note: start debug process as last due to process_poll() execution order */

  /* init done */
  PIN_CLR(LED_STATUS);     
    printf("Initialization done\r\n");
  //__eint();
  
  while(1) {
    int r;
    do {
#if WATCHDOG_CONF_ON
      watchdog_reset();
#endif /* WATCHDOG_CONF_ON */
      r = process_run();
    } while(r > 0);
    /* idle processing */
    /* disable interrupts */
    __dint();
    __nop();
    if(process_nevents() != 0 || UART_ACTIVE) {
      /* re-enable interrupts */
      __eint();
      __nop();
    } else {
      /* re-enable interrupts and go to sleep atomically */
      ENERGEST_OFF(ENERGEST_TYPE_CPU);
#if WATCHDOG_CONF_ON
      watchdog_stop();
#endif /* WATCHDOG_CONF_ON */
      /* enter low-power mode 3 */
         // PIN_SET(LED_ORANGE);
      __bis_status_register(GIE | SCG0 | SCG1 | CPUOFF);
      __no_operation();
#if WATCHDOG_CONF_ON
      watchdog_start();
#endif /* WATCHDOG_CONF_ON */
      ENERGEST_ON(ENERGEST_TYPE_CPU);
    }
  }

  return 0;
}
/*---------------------------------------------------------------------------*/
