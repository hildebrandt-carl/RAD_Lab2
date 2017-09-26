#include "header.h"
static uint8_t PROGRESS=0;
/*counters to keep track of task progress*/
static uint16_t count=0;
static uint8_t blinkcounter1=0;
static uint8_t blinkcounter2=0;
static uint8_t blinkcounter3=0;

static struct etimer et;

PROCESS(main_process, "Main Task");
AUTOSTART_PROCESSES(&main_process);

void incrementCOUNTER(uint8_t i)
{
	switch(i)   
	{  
		case 1:  
			blinkcounter1++;  
		case 2:  
			blinkcounter2++;  
		case 3:  
			blinkcounter3++;  
		default :  
			printf("ERROR! Wrong counter incremement value");  
	}
}

uint8_t getCOUNTER(uint8_t i)
{
	switch(i)   
	{  
		case 1:  
			return(blinkcounter1);  
		case 2:  
			return(blinkcounter2);  
		case 3: 
			return(blinkcounter3);
		default :  
			printf("ERROR! Wrong counter get value");  
	}	
}

uint8_t getPROGRESS()
{
	return PROGRESS;
}

void clearPROGRESS(){
	PROGRESS=0;
}

void setPROGRESS(uint8_t i){


}

PROCESS_THREAD(main_process, ev, data){

	/*begin the process*/
	PROCESS_BEGIN();	
	
	/*initialize the watchdog below by uncommenting the line and then redefine the WDTIS bits according to the time period you need for the watchdog. Note that WDTIS0 refers to bit 0 among WDTIS bits and so on. */
	//WDTCTL = WDTPW + WDTCNTCL + WDTHOLD +WDTISx;

	//start the watchdog
	WDTCTL = (WDTCTL_L&~(WDTHOLD))+ WDTPW;
	
	WDTCTL = WDTPW + WDTCNTCL + WDTHOLD + WDTIS0;
	
	while(1){
 	/* Delay 1 seconds */
	/*start the event timer and set its event period to 1 second*/
	etimer_set(&et, 1*CLOCK_SECOND);
	PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

	process_start(&LED1,NULL);
	
	process_start(&LED2, NULL);
	
	process_start(&LED3,NULL);	
 	
	}
	PROCESS_END();



}

