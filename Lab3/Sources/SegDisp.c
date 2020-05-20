/*--------------------------------------------
File: SegDisp.c
Description:  Segment Display Module
---------------------------------------------*/

#include <stdtypes.h>
#include "mc9s12dg256.h"
#include "SegDisp.h"
#include "Delay_asm.h"


/*---------------------------------------------
Function: initDisp
Description: initializes hardware for the 
             7-segment displays.
-----------------------------------------------*/
void initDisp(void) 
{
  DDRB = 0xFF;
  PORTB = 0b10000000;
  DDRP = 0X3F;
  PTP = 0b11111111;
	
}

/*---------------------------------------------
Function: clearDisp
Description: Clears all displays.
-----------------------------------------------*/
void clearDisp(void) 
{
  PORTB = 0b10000000;
  PTP = 0b11111111;
  


}

/*---------------------------------------------
Function: setCharDisplay
Description: Receives an ASCII character (ch)
             and translates
             it to the corresponding code to 
             display on 7-segment display.  Code
             is stored in appropriate element of
             codes for identified display (dispNum).
-----------------------------------------------*/

  unsigned char display[4] = {0b11111110, 0b11111101, 0b11111011, 0b11110111};
  unsigned char numbers[10] = {0b00111110, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111};
  unsigned char alpha[6] = {0b01110111, 0b00011111, 0b01111101, 0b01001110, 0b01001111, 0b01000111};
  unsigned char char_to_display[4] = {0, 0, 0, 0};
void setCharDisplay(char ch, byte dispNum) 
{ 
  if (ch<58 && ch>47){
    char_to_display[dispNum] = numbers[ch - '0'];
  }
  if (ch<91 && ch>64){
    char_to_display[dispNum] = alpha[ch - 'A'];
  }
  if (ch<123 && ch>96){
    char_to_display[dispNum] = alpha[ch - 'a'];
  }
  if (ch == ' '){
    char_to_display[dispNum] = 0b00000000;
  }
  
}

/*---------------------------------------------
Function: segDisp
Description: Displays the codes in the code display table 
             (contains four character codes) on the 4 displays 
             for a period of 100 milliseconds by displaying 
             the characters on the displays for 5 millisecond 
             periods.
-----------------------------------------------*/
void segDisp(void) 
{
  int i = 5;
  while(i>0) {
  PORTB = char_to_display[0];
  PTP = display[0];
  delayms(5);
  PORTB = char_to_display[1];
  PTP = display[1];
  delayms(5);
  PORTB = char_to_display[2];
  PTP = display[2];
  delayms(5);
  PORTB = char_to_display[3];
  PTP = display[3];
  delayms(5);
  i--;
  }
}
