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
 * @addtogroup  Net
 * @{
 *
 * @defgroup    synt The Low-Power Wireless Bus (SYNT)
 * @{
 *
 * @file 
 * 
 * @brief    the low-power wireless bus (SYNT)
 */
 
#ifndef __SYNT_H__
#define __SYNT_H__


#include "contiki.h"
#include "platform.h"   /* necessary for SMCLK_SPEED in clock.h */

#ifndef HOST_ID
#warning "HOST_ID not defined, set to 0"
#define HOST_ID                         0
#endif

#ifndef SYNT_VERSION
#define SYNT_VERSION     1       /* default version */
#endif /* SYNT_VERSION */

typedef struct {
    uint8_t  relay_cnt;
    uint8_t  period_last;
    uint8_t  unsynced_cnt;
    uint8_t  bootstrap_cnt;
    uint16_t reset_cnt;
    uint16_t pck_cnt;     /* total number of received packets */
    uint16_t t_sched_max; /* max. time needed to calculate the new schedule */
    uint16_t t_proc_max;  /* max. time needed to process the rcvd data pkts */
    uint16_t crc;         /* crc of this struct (with crc set to 0!) */
    uint32_t t_slot_last; /* last slot assignment (in seconds) */
    uint32_t data_tot;
} synt_statistics_t;

/**
 * @brief simplified 'connection state' of a source node
 * When a source node first boots, it is in SYNT_STATE_INIT state. The node 
 * then tries to connect to a host. Upon successful reception of a schedule 
 * packet, its state chances to SYNT_STATE_CONNECTED. When no schedule packet
 * is received for a certain amount of time, the node's state is degraded to 
 * SYNT_STATE_CONN_LOST.
 */
typedef enum {
    SYNT_STATE_INIT = 0, /* bootstrap */
    SYNT_STATE_CONNECTED, 
    SYNT_STATE_CONN_LOST,
} synt_conn_state_t;

void synt_start(void (*pre_synt_func)(void), void *post_synt_proc);
void synt_resume(void);


#endif