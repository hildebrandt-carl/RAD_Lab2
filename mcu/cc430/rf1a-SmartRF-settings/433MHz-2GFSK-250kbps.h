/* Sync word qualifier mode = 30/32 sync word bits detected */
/* CRC autoflush = false */
/* Channel spacing = 199.951172 */
/* Data format = Normal mode */
/* Data rate = 174.957 */
/* RX filter BW = 464.285714 */
/* PA ramping = false */
/* Preamble count = 4 */
/* Whitening = true */
/* Address config = No address check */
/* Carrier frequency = 867.999939 */
/* Device address = 0 */
/* TX power = 0 */
/* Manchester enable = false */
/* CRC enable = true */
/* Deviation = 95.214844 */
/* Packet length mode = Variable packet length mode. Packet length */
/*                      configured by the first byte after sync word */
/* Packet length = 255 */
/* Modulation format = 2-GFSK */
/* Base frequency = 867.999939 */
/* Modulated = true */
/* Channel number = 0 */
/***************************************************************
 *  SmartRF Studio(tm) Export
 *
 *  Radio register settings specifed with C-code
 *  compatible #define statements.
 *
 *  RF device: CC430
 *
 ***************************************************************/

#ifndef __SMARTRF_CC430_H__
#define __SMARTRF_CC430_H__

#define SMARTRF_IOCFG0     0x06 /* gdo0 output configuration */
#define SMARTRF_FSCTRL1    0x08 /* frequency synthesizer control */
#define SMARTRF_FREQ2      0x10 /* frequency control word, high byte */
#define SMARTRF_FREQ1      0xB1 /* frequency control word, middle byte */
#define SMARTRF_FREQ0      0x3B /* frequency control word, low byte */
#define SMARTRF_MDMCFG4    0xCB /* modem configuration */
#define SMARTRF_MDMCFG3    0x18 /* modem configuration */
#define SMARTRF_MDMCFG2    0x93 /* modem configuration */
#define SMARTRF_DEVIATN    0x48 /* modem deviation setting */
#define SMARTRF_MCSM0      0x18 /* main radio control state machine config */
#define SMARTRF_FOCCFG     0x16 /* frequency offset compensation config */
#define SMARTRF_BSCFG      0x6C /* bit synchronization configuration */
#define SMARTRF_AGCCTRL2   0x43 /* agc control */
#define SMARTRF_AGCCTRL1   0x40 /* agc control */
#define SMARTRF_AGCCTRL0   0x91 /* agc control */
#define SMARTRF_WORCTRL    0xFB /* wake on radio control */
#define SMARTRF_FREND1     0x56 /* front end rx configuration */
#define SMARTRF_FSCAL3     0xE9 /* frequency synthesizer calibration */
#define SMARTRF_FSCAL2     0x2A /* frequency synthesizer calibration */
#define SMARTRF_FSCAL1     0x00 /* frequency synthesizer calibration */
#define SMARTRF_FSCAL0     0x1F /* frequency synthesizer calibration */
#define SMARTRF_TEST0      0x09 /* various test settings */
//#define SMARTRF_PKTCTRL0      0x05 /* various test settings */

/* values for Glossy (measured with the logic analyzer, in ns) */
#define TAU1 (rtimer_clock_t)16200  /* 16.20 us */
#define TAU2 (rtimer_clock_t)13630  /* 13.63 us */
#define T2R  (rtimer_clock_t)416000 /* 416.0 us */
#define R2T  (rtimer_clock_t)386200 /* 386.2 us */
#define T_TX_BYTE   (rtimer_clock_t)45729 /* 45.729 us */
#define T_TX_OFFSET (rtimer_clock_t)5717  /* 5.717 us */

#endif /* __SMARTRF_CC430_H__ */

