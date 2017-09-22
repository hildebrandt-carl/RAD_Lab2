/*
 * Copyright (c) 2016, Swiss Federal Institute of Technology (ETH Zurich).
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
 *          Marco Zimmerling
 */

/**
 * @file
 *
 * an implementation of the Low-Power Wireless Bus
 */
 
#include "contiki.h"

#if SYNT_VERSION == 1

/*---------------------------------------------------------------------------*/
/* internal sync state of the LWB on the source node */
typedef enum {
  BOOTSTRAP = 0,
  QUASI_SYNCED,
  SYNCED,
  SYNCED_2,
  MISSED,
  UNSYNCED,
  UNSYNCED2,
  NUM_OF_SYNC_STATES
} synt_sync_state_t;
/*---------------------------------------------------------------------------*/
typedef enum {
  EVT_1ST_SCHED_RCVD = 0,
  EVT_2ND_SCHED_RCVD,
  EVT_SCHED_MISSED,
  NUM_OF_SYNC_EVENTS
} sync_event_t; 
/*---------------------------------------------------------------------------*/


static struct pt        synt_pt;
static void*            pre_proc;
static struct process*  post_proc;
static synt_sync_state_t sync_state;
static rtimer_clock_t   reception_timestamp;
static uint32_t         global_time;
static synt_statistics_t stats = { 0 };
static uint8_t          urgent_stream_req = 0;

PT_THREAD(synt_thread_host(rtimer_t *rt)) 
{
  PT_BEGIN(&synt_pt);

DEBUG_PRINT_INFO("imhere");


    debug_print_poll();
    if(post_proc) {
      process_poll(post_proc);
    }
DEBUG_PRINT_INFO("imhere2");  
  PT_END(&synt_pt);

}

PT_THREAD(synt_thread_src(rtimer_t *rt)) 
{
  PT_BEGIN(&synt_pt);

DEBUG_PRINT_INFO("imhere");


    debug_print_poll();
    if(post_proc) {
      process_poll(post_proc);
    }
  
  PT_END(&synt_pt);
}

/*---------------------------------------------------------------------------*/
/* define the process control block */
PROCESS(synt_process, "Communication Task (SYNT)");
/*---------------------------------------------------------------------------*/
/* define the body (protothread) of a process */
PROCESS_THREAD(synt_process, ev, data) 
{
  PROCESS_BEGIN();
  
// #if SYNT_CONF_STATS_NVMEM
//   synt_stats_load();    load the stats from the external memory 
// #endif /* SYNT_CONF_STATS_NVMEM */

  PT_INIT(&synt_pt); /* initialize the protothread */

  synt_resume();

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
void
synt_start(void (*pre_synt_func)(void), void *post_synt_proc)
{
  pre_proc = pre_synt_func;
  post_proc = (struct process*)post_synt_proc;
  
  uart_enable(1);
  printf("Starting '%s'\r\n", synt_process.name);    

  process_start(&synt_process, NULL);
}

void
synt_resume(void)
{

#if LWB_CONF_USE_LF_FOR_WAKEUP
  rtimer_clock_t start_time = rtimer_now_lf() + RTIMER_SECOND_LF / 10;
  rtimer_id_t timer_id = LWB_CONF_LF_RTIMER_ID;
#else /* LWB_CONF_USE_LF_FOR_WAKEUP */
  rtimer_clock_t start_time = rtimer_now_hf() + RTIMER_SECOND_HF / 10;
  rtimer_id_t timer_id = LWB_CONF_RTIMER_ID;
#endif /* LWB_CONF_USE_LF_FOR_WAKEUP */
    
  if(node_id == HOST_ID) {
    /* note: must add at least some clock ticks! */
    rtimer_schedule(timer_id, start_time, 0, synt_thread_host);
  } else {
    rtimer_schedule(timer_id, start_time, 0, synt_thread_src);
  }
}
#endif /* SYNT_VERSION */