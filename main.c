#include <reg52.h>
#include "Ports.h"
#include "Interrupt.h"
#include "Delay.h"
#include "DataTypes.h"


//#define TIMER_COUNTER 1
#define RED_DELAY 8
#define YELLOW_DELAY 3
#define GREEN_DELAY 12


states curState=red;
tWord ticks=0;
tWord i;

void initialization();
void operation();
void GOTO_SLEEP();
void task();

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

	redPin=0;
	yellowPin=0;
	greenPin=0;
	delay_50ms_Timer();
	
}


// ISR TIMER 2
void InterruptTimer2_ISR() interrupt InterruptTimer2{
	TF2 = 0;
	task();
}
	 
void task(){
		switch(curState){
			case red:
				redPin=1;
				Delay_s(RED_DELAY);
					curState=yellow;
					redPin=0;
					yellowPin=1;
					greenPin=0;
					ticks=0;
				break;
			case yellow:
				yellowPin=1;
				Delay_s(YELLOW_DELAY);
					curState=green;
					redPin=0;
					yellowPin=0;
					greenPin=1;
					ticks=0;
				break;
				case green:
					greenPin=1;
					Delay_s(GREEN_DELAY);
						curState=red;
						redPin=1;
						yellowPin=0;
						greenPin=0;
						ticks=0;
				break;
			default:
				redPin=0;
				yellowPin=0;
				greenPin=0;
		}
}

void operation(){
	while(1)
		GOTO_SLEEP();
}