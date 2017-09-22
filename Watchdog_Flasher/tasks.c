#include "header.h"
PROCESS(LED1,"LED1 TASK");
PROCESS(LED2,"LED2 TASK");
PROCESS(LED3,"LED3 TASK");
PROCESS(WDTCHECK,"WDTCHECK TASK");

/*process 1: control RED LED1*/
PROCESS_THREAD(LED1,ev,data){

	PROCESS_BEGIN();


	process_start(&WDTCHECK, NULL);
	PROCESS_END();

}



/*process 2: control YELLOW LED*/
PROCESS_THREAD(LED2,ev,data){

	PROCESS_BEGIN();
	
	P3OUT |= 1 << 6; //set bit 6 in P3OUT to 1
	P3DIR |= 1 << 6; //Since Green LED is connected to P3.6, set bit 6 in P3DIR to 1

	process_start(&WDTCHECK, NULL);
	PROCESS_END();

}

/*process 3: control GREEN LED*/
PROCESS_THREAD(LED3,ev,data){

	PROCESS_BEGIN();

	P3OUT |= 1 << 7; //set bit 7 in P3OUT to 1
	P3DIR |= 1 << 7; //Since Yellow LED is connected to P3.7, set bit 7 in P3DIR to 1

	process_start(&WDTCHECK, NULL);
	PROCESS_END();

}

/*function to kick the watchdog*/
PROCESS_THREAD(WDTCHECK,ev,data){

	PROCESS_BEGIN();

	P1OUT=1<<7; //set bit 7 in P1OUT to 1
	P1DIR=1<<7; //Since RED LED is connected to P1.7, set bit 7 in P1DIR to 1

	PROCESS_END();

}
