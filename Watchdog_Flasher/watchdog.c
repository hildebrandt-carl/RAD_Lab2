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

void ErrorLogging(uint8_t i)
{
	printf("Error code %d\r\n",i);
}

// Increments the blink counter relating to the passed integer.
void incrementCOUNTER(uint8_t i)
{
	switch(i)   
	{  
		case 1:  
			blinkcounter1++;
			break;
		case 2:  
			blinkcounter2++;
			break; 
		case 3:  
			blinkcounter3++;
			break;
		default :  
			printf("ERROR! Wrong counter incremement value");  
			break;
	}
}

// Returns the blink counter relating to the passed integer
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
			return 0;
	}
}


// The function clears the blink counter relating to the passed integer.
void clearCOUNTER(uint8_t i)
{
	switch(i)   
	{  
		case 1:  
			blinkcounter1 = 0;
			break; 
		case 2:  
			blinkcounter2 = 0;
			break;  
		case 3: 
			blinkcounter3 = 0;
			break;
		default :  
			printf("ERROR! Wrong counter get value");
	}	
}

// Returns the progress variable
uint8_t getPROGRESS()
{
	return PROGRESS;
}

// Clears the progress variable. Sets all bits to 0
void clearPROGRESS(){
	PROGRESS=0;
}

// Takes and integer which represents a progress is complete. It saves this integer in the progress variable as a single bit
void setPROGRESS(uint8_t i){
	switch(i)
	{
		case 1:
			PROGRESS |= (1<<1);
			break;
		case 2:
			PROGRESS |= (1<<2);
			break;
		case 3:
			PROGRESS |= (1<<3);
			break;
		default:
			printf("ERROR!");
			break;
	}
}

PROCESS_THREAD(main_process, ev, data){

	/*begin the process*/
	PROCESS_BEGIN();	
	
	// Sets up the watchdog timer to use interval of 16s
	WDTCTL = WDTPW + WDTSSEL0 + WDTHOLD + WDTIS1 + WDTIS0;

	//start the watchdog
	WDTCTL = (WDTCTL_L&~(WDTHOLD))+ WDTPW;

	printf("Starting up the system\r\n");
	static int i_cnt = 0;
	while(1){
 	// Delay 1 seconds 
	// start the event timer and set its event period to 1 second
	etimer_set(&et, 1*CLOCK_SECOND);
	PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
	i_cnt++;
	printf("System has been running for %d seconds.\r\n",i_cnt);

	// Call the different processors in tasks.c
	process_start(&LED1,NULL);
	
	process_start(&LED2, NULL);
	
	process_start(&LED3,NULL);	
 	
	}
	PROCESS_END();



}

