/////////////////////////////////////////////////////////////////////////////
// 9S12X Program: ICA 03 - PORT J Interrupts
// Processor:     MC9S12XDP512
// Bus Speed:     20 MHz (Requires Active PLL)
// Author:        Cole Yaremko
// Details:       Using PORT J interrupts to create a simple stop watch
// Date:          September 7, 2023
// Revision History :
//                See GIT   
/////////////////////////////////////////////////////////////////////////////
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "sw_led.h"
#include "segs.h"
#include "lcd.h"
#include "rti.h"
#include "clock.h"
#include "sci.h"

// other system includes or your includes go here
//#include "pll.h"
#include <stdlib.h>
#include <stdio.h>
#include "string.h"

/////////////////////////////////////////////////////////////////////////////
// Local Prototypes
/////////////////////////////////////////////////////////////////////////////
void DelaySeconds(void);

/////////////////////////////////////////////////////////////////////////////
// Global Variables
/////////////////////////////////////////////////////////////////////////////
unsigned char rxData;  // the data being received
SwState left;
SwState ctr;
SwState rgt;

/////////////////////////////////////////////////////////////////////////////
// Constants
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Main Entry
/////////////////////////////////////////////////////////////////////////////
void main(void)
{
  // main entry point - these two lines must appear first
  _DISABLE_COP();
  EnableInterrupts;
  
  /////////////////////////////////////////////////////////////////////////////
  // one-time initializations
  /////////////////////////////////////////////////////////////////////////////
  Clock_Set20MHZ();                // Set the clock to 20MHZ
  SWL_Init();                      // initialize the LEDS
  sci0_Init(115200, 1);            // initialize the SCI

  /////////////////////////////////////////////////////////////////////////////
  // main program loop
  /////////////////////////////////////////////////////////////////////////////
  for (;;)
  {
    if (Sw_Process(&left, SWL_LEFT) == Pressed)
    {
      sci0_txByte('r');
    }
    if(Sw_Process(&left, SWL_LEFT) == Released)
    {
      sci0_txByte('R');
    
    }

    if (Sw_Process(&ctr, SWL_CTR) == Pressed)
    {
      sci0_txByte('y');
    }
    if(Sw_Process(&ctr, SWL_CTR) == Released)
    {
      sci0_txByte('Y');
    
    }

    if (Sw_Process(&rgt, SWL_RIGHT) == Pressed)
    {
      sci0_txByte('g');
    }
    if(Sw_Process(&rgt, SWL_RIGHT) == Released)
    {
      sci0_txByte('G');
    
    }
  }                 
}

/////////////////////////////////////////////////////////////////////////////
// Functions
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Interrupt Service Routines
/////////////////////////////////////////////////////////////////////////////

// ISR for the SCI
interrupt VectorNumber_Vsci0 void Vsci0_ISR(void)
{
  // poll for receiving a character
  if(SCI0SR1 & SCI0SR1_RDRF_MASK)
  {
    rxData = SCI0DRL; //store the character
    
    if (rxData == 'r')
    {
      SWL_ON(SWL_RED);
    }
    if (rxData == 'R')
    {
      SWL_OFF(SWL_RED);
    }

    if (rxData == 'y')
    {
      SWL_ON(SWL_YELLOW);
    }
    if (rxData == 'Y')
    {
      SWL_OFF(SWL_YELLOW);
    }

    if (rxData == 'g')
    {
      SWL_ON(SWL_GREEN);
    }
    if (rxData == 'G')
    {
      SWL_OFF(SWL_GREEN);
    }
  }
}
