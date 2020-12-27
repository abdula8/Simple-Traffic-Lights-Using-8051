
#include <reg52.h>
#include "Delay.h"
#include "DataTypes.h"


/* The timer function to calculate 1ms delay */
void delay_1ms_Timer(){
	// TIMER 2
	T2CON = 0x04; 		// Load Timer 2 Control Register
	
	TH2 		= 0xFC;//0x3C;  			// Load Timer 2 high byte
	RCAP2H 	= 0xFC; 		// Load Timer 2 reload Capt. reg. high byte
	TL2 		= 0x18;//0xB0;  			// Load Timer 2 Low byte
	RCAP2L	= 0x18; 		// Load Timer 2 reload Capt. reg. low byte
		
	// Timer 2 interrupt is enabled, and ISR will be called
	// whenever the timer overflows – see below.
	ET2=1;
	TR2 = 1;	 				// Start Timer 2
	EA=1;
	//IE=0xA0;
}



void Delay_1s(){
	tWord i;
	for (i=0;i<32000;i++)
		delay_1ms_Timer();
}


void Delay_s(tWord x)
{
	tWord i;
	for(i=0;i<x;i++){
		Delay_1s();
	}
}










/*------------------------------------------------------------*-
sEOS_Init_Timer2()
Sets up Timer 2 to drive the simple EOS.
Parameter gives tick interval in MILLISECONDS.
Max tick interval is ~60ms (12 MHz oscillator).
Note: Precise tick intervals are only possible with certain
oscillator / tick interval combinations. If timing is
important, you should check the timing calculations manually.
-*------------------------------------------------------------*/
/*
#define OSC_FREQ 12000000
#define OSC_PER_INST 12
void sEOS_Init_Timer2(const tByte TICK_MS)
{
		tLong Inc;
		tWord Reload_16;
		tByte Reload_08H, Reload_08L;
		
		// Timer 2 is configured as a 16-bit timer,
		// which is automatically reloaded when it overflows
		T2CON = 0x04; // Load Timer 2 control register
	
		// Number of timer increments required (max 65536)
		Inc = ((tLong)TICK_MS * (OSC_FREQ/1000)) / (tLong)OSC_PER_INST;
		
		// 16-bit reload value;
		Reload_16 = (tWord)(65536UL - Inc);
		//(tWord)(65536UL - Inc);
		// 8-bit reload values (High & Low)
		Reload_08H = (tByte)(Reload_16 / 256);
		Reload_08L = (tByte)(Reload_16 % 256);
		
		// Used for manually checking timing (in simulator)
		//P2 = Reload_08H;
		//P3 = Reload_08L;
		TH2 = Reload_08H; // Load T2 high byte
		RCAP2H = Reload_08H; // Load T2 reload capt. reg. high byte
		TL2 = Reload_08L; // Load T2 low byte
		RCAP2L = Reload_08L; // Load T2 reload capt. reg. low byte
		
		
		// Timer 2 interrupt is enabled, and ISR will be called
		// whenever the timer overflows.
		ET2 = 1;
		
		
		// Start Timer 2 running
		TR2 = 1;
		EA = 1; // Globally enable interrupts

}

*/