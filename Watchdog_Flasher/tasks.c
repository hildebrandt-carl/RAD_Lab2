#include "header.h"

PROCESS(LED1,"LED1 TASK");
PROCESS(LED2,"LED2 TASK");
PROCESS(LED3,"LED3 TASK");
PROCESS(WDTCHECK,"WDTCHECK TASK");

/*process 1: control GREEN LED*/
PROCESS_THREAD(LED1,ev,data){

	PROCESS_BEGIN();

        P3OUT ^= (1<<6); // toggle bit 6 in P3OUT (GREEN LED)
        P3DIR ^= (1<<6); // toggle bit 6 in P3DIR (GREEN LED)

	process_start(&WDTCHECK, NULL);
	PROCESS_END();

}



/*process 2: control YELLOW LED*/
PROCESS_THREAD(LED2,ev,data){

	PROCESS_BEGIN();
	
	P3OUT ^= (1<<7); // toggle bit 7 in P3OUT (YELLOW LED)
	P3DIR ^= (1<<7); // toggle bit 7 in P3DIR (YELLOW LED)

	process_start(&WDTCHECK, NULL);
	PROCESS_END();

}

/*process 3: control RED LED*/
PROCESS_THREAD(LED3,ev,data){

	PROCESS_BEGIN();

	P1OUT ^= (1<<7); // toggle bit 7 in P1OUT (RED LED)
	P1DIR ^= (1<<7); // toggle bit 7 in P1DIR (RED LED)

	process_start(&WDTCHECK, NULL);
	PROCESS_END();

}

/*function to kick the watchdog*/
PROCESS_THREAD(WDTCHECK,ev,data){

	PROCESS_BEGIN();

	//TODO: 
	printf(getPROGRESS());

	PROCESS_END();

}
