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
	



	process_start(&WDTCHECK, NULL);
	PROCESS_END();

}

/*process 3: control GREEN LED*/
PROCESS_THREAD(LED3,ev,data){

	PROCESS_BEGIN();
	




	process_start(&WDTCHECK, NULL);
	PROCESS_END();

}

/*function to kick the watchdog*/
PROCESS_THREAD(WDTCHECK,ev,data){

	PROCESS_BEGIN();

	



	PROCESS_END();

}
