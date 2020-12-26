#include <reg52.h>
#include "Ports.h"
#include "Interrupt.h"
#include "Delay.h"
#include "DataTypes.h"

#define TIMER_COUNTER 50

tWord ticks=0;
typedef enum {red, yellow, green} states;
states curState=red;


void initialization();
void operation();
void GOTO_SLEEP();

void main(void){
	initialization();
	operation();
}

/* The function to save power of the uProcessor during the periods of interrupt */
void GOTO_SLEEP(){
	PCON |=1; // power down mode
}

/* The function used to initialize variables as input and output and also to initialize the timer */
void initialization(){
	//ButtonPort=0xff;
	redPin=0;
	yellowPin=0;
	greenPin=0;
	
	// TIMER 2
	T2CON = 0x04; 		// Load Timer 2 Control Register
	TH2 = 0x3C;  			// Load Timer 2 high byte
	RCAP2H = 0x3C; 		// Load Timer 2 reload Capt. reg. high byte
	TL2 = 0xB0;  			// Load Timer 2 Low byte
	RCAP2L = 0xB0; 		// Load Timer 2 reload Capt. reg. low byte
	TR2 = 1;	 				// Start Timer 2
	IT0 = 1; 					// EX0 INT0 Edge Triggred
	IE=0xA5; 					// 1010 0000 TO Enabel Timer 2 Interrupt INT0 and INT1

}



// ISR TIMER 2
void InterruptTimer2_ISR() interrupt InterruptTimer2{
	TF2 = 0;
	//if (isOk==true){
	//if(ticks>TIMER_COUNTER){
		switch(curState){
			case red:
				redPin=1;
				if((ticks++)==TIMER_COUNTER){
					curState=yellow;
					redPin=0;
					yellowPin=1;
					greenPin=0;
					ticks=0;
				}
				//}
				break;
			case yellow:
				yellowPin=1;
				if((ticks++)==TIMER_COUNTER){
					curState=green;
					redPin=0;
					yellowPin=0;
					greenPin=1;
					ticks=0;
				}
				break;
				case green:
				greenPin=1;
				if((ticks++)==TIMER_COUNTER){
					curState=red;
					redPin=1;
					yellowPin=0;
					greenPin=0;
					ticks=0;
				}
				break;
			default:
				redPin=0;
				yellowPin=0;
				greenPin=0;
		}
		/*
	}else{
		ticks++;
		}*/
	//}
}
	 

void operation(){
	while(1)
		GOTO_SLEEP();
}