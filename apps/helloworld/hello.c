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
 *          Marco Zimmerling
 */
 
/**
 * @brief Low-Power Wireless Bus Test Application
 * 
 * All source nodes sample the temperature and supply voltage and send this
 * information to the host node.
 * The used scheduler is static, i.e. the period is constant. A source node
 * may send a stream request in each round.
 */


#include "contiki.h"
#include "platform.h"
 #include "dev/serial-line.h"

/*---------------------------------------------------------------------------*/
#ifdef APP_TASK_ACT_PIN
#define TASK_ACTIVE             PIN_SET(APP_TASK_ACT_PIN)
#define TASK_SUSPENDED          PIN_CLR(APP_TASK_ACT_PIN)
#else
#define TASK_ACTIVE
#define TASK_SUSPENDED
#endif /* APP_TASK_ACT_PIN */
// static struct etimer send_timer;
  uint16_t i = 0;
  #define RF_CONF_MAX_PKT_LEN           63
  #define PAYLOAD_LEN              15
#define HEADER_LEN              13
static uint8_t test_payload[RF_CONF_MAX_PKT_LEN];
static uint8_t test_head[HEADER_LEN];


/*---------------------------------------------------------------------------*/
PROCESS(hello_world_process, "Helloworld Task");
AUTOSTART_PROCESSES(&hello_world_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(hello_world_process, ev, data)
{ 
  static struct etimer et;

  PROCESS_BEGIN();

  while(1) {
    
    /* Delay 2-4 seconds */
    etimer_set(&et, 2*CLOCK_SECOND);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

    broadcast_send("Hello", 6);
    // printf("broadcast message sent\r\n");
  
    
    /* since this process is only executed at the end of an LWB round, we 
     * can now configure the MCU for minimal power dissipation for the idle
     * period until the next round starts */
#if LWB_CONF_USE_LF_FOR_WAKEUP
  #if FRAM_CONF_ON
    fram_sleep();
  #endif /* FRAM_CONF_ON */
    /* disable all peripherals, reconfigure the GPIOs and disable XT2 */
    TA0CTL   &= ~MC_3; /* stop TA0 */
    DISABLE_XT2();
  #ifdef MUX_SEL_PIN
    PIN_CLR(MUX_SEL_PIN);
  #endif /* MUX_SEL_PIN */
    P1SEL = 0; /* reconfigure GPIOs */
    P1DIR = 0xff;
    /* set clock source to DCO */
    UCSCTL4 = SELA__XT1CLK | SELS__DCOCLKDIV | SELM__DCOCLKDIV;
#endif /* LWB_CONF_USE_LF_FOR_WAKEUP */
    
    TASK_SUSPENDED;
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
