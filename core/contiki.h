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
 */

#ifndef __CONTIKI_H__
#define __CONTIKI_H__

#ifndef CONTIKI_VERSION_STRING
#define CONTIKI_VERSION_STRING "Contiki 2.7"
#endif /* CONTIKI_VERSION_STRING */

#include "contiki-conf.h"

/* unchanged Contiki files: */
#include "sys/process.h"
#include "sys/autostart.h"

#include "sys/timer.h"
#include "sys/etimer.h"
#include "sys/ctimer.h"
#include "sys/pt.h"
#include "sys/energest.h"

#include "lib/list.h"
#include "lib/memb.h"
#include "lib/random.h"

#include "dev/serial-line.h"

/* custom files: */
#include "lib/membx.h"
#include "lib/fifo.h"
#include "net/lwb.h"
#include "net/glossy.h"
#include "net/nullmac.h"
#include "dev/xmem.h"
#include "dev/debug-print.h"
#include "dev/fram.h"

// #include "net/synt.h"
// #include "net/rime/multihop.h"
// #include "net/linkaddr.h"
// #include "net/rime/route.h"



#endif /* __CONTIKI_H__ */
