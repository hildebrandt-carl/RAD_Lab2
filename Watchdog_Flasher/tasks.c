#include "header.h"

PROCESS(LED1,"LED1 TASK");
PROCESS(LED2,"LED2 TASK");
PROCESS(LED3,"LED3 TASK");
PROCESS(WDTCHECK,"WDTCHECK TASK");

/*process 1: control GREEN LED*/
PROCESS_THREAD(LED1,ev,data){

	PROCESS_BEGIN();
<<<<<<< HEAD
=======
<<<<<<< HEAD

        P3OUT ^= (1<<6); // toggle bit 6 in P3OUT (GREEN LED)
        P3DIR ^= (1<<6); // toggle bit 6 in P3DIR (GREEN LED)

=======
	printf("Soup Starter\n");
	int i = 0;
	int j = 0;

	P3OUT |= (1 << 6); //set bit 6 in P3OUT to 1
	P3DIR |= (1 << 6); //Since Green LED is connected to P3.6, set bit 6 in P3DIR to 1
	printf("ghello\n");
	for(j=0;j<1000;j++)
	{
		for(i=0;i<1275;i++);
	}
	printf("goodbye\n");
	
>>>>>>> 60f9debc6dfc319ce4f34b462ad771553bd73b9e

        P3OUT ^= (1<<6); // toggle bit 6 in P3OUT (GREEN LED)
        P3DIR ^= (1<<6); // toggle bit 6 in P3DIR (GREEN LED)

<<<<<<< HEAD
=======
	for(j=0;j<1000;j++)
	{
		for(i=0;i<1275;i++);
	}
	
>>>>>>> 27e4f05eb5e26393f2278a92ded1827741365d1b
>>>>>>> 60f9debc6dfc319ce4f34b462ad771553bd73b9e
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
