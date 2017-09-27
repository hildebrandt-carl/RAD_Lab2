#include "header.h"

PROCESS(LED1,"LED1 TASK");
PROCESS(LED2,"LED2 TASK");
PROCESS(LED3,"LED3 TASK");
PROCESS(WDTCHECK,"WDTCHECK TASK");

/*process 1: control GREEN LED*/
PROCESS_THREAD(LED1,ev,data){

	PROCESS_BEGIN();

	printf("Process1\n");

    P3OUT ^= (1<<6); // toggle bit 6 in P3OUT (GREEN LED)
	P3DIR |= (1<<6); // toggle bit 6 in P3DIR (GREEN LED)

	incrementCOUNTER(1);
	int g = getCOUNTER(1);
	if(g > 6){
		setPROGRESS(1);
		clearCOUNTER(1);
	}
		
	process_start(&WDTCHECK, NULL);
	PROCESS_END();

}



/*process 2: control YELLOW LED*/
PROCESS_THREAD(LED2,ev,data){

	PROCESS_BEGIN();

	printf("Process2\n");
	
	if(getCOUNTER(2) % 2 == 0)
	{
		P3OUT ^= (1<<7); // toggle bit 7 in P3OUT (YELLOW LED)
		P3DIR |= (1<<7); // toggle bit 7 in P3DIR (YELLOW LED)
	}

	incrementCOUNTER(2);
	int g = getCOUNTER(2);
	if(g > 8){
		setPROGRESS(2);
		clearCOUNTER(2);
	}

	process_start(&WDTCHECK, NULL);
	PROCESS_END();

}

/*process 3: control RED LED*/
PROCESS_THREAD(LED3,ev,data){

	PROCESS_BEGIN();

	printf("Process3\n");

	P1OUT ^= (1<<7); // toggle bit 7 in P1OUT (RED LED)
	P1DIR |= (1<<7); // toggle bit 7 in P1DIR (RED LED)
	
	incrementCOUNTER(3);
	int g = getCOUNTER(3);
	if(g > 14){
		setPROGRESS(3);
		clearCOUNTER(3);
	}

	process_start(&WDTCHECK, NULL);
	PROCESS_END();

}

/*function to kick the watchdog*/
PROCESS_THREAD(WDTCHECK,ev,data){

	PROCESS_BEGIN();

	uint8_t p = getPROGRESS();
	if((p & 0x0E) == 0x0E){
		WDTCTL = (WDTCTL & 0xFF) + WDTPW + WDTCNTCL; //kick watchdog
		clearPROGRESS();
	}

	PROCESS_END();

}
