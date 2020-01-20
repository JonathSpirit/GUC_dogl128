/*
Author : Guillaume Guillet
Last modified : 20.01.2020
*/

#include "config.h"
#include "GUC_dogl128.h"

void Wait_ms(unsigned int ms);
void Timer5Init();

void main ()
{
   
   
   Init_Device();
   Timer5Init();
   
   GUC_dog_init();
   GUC_dog_clearScreen(0);
   GUC_dog_setCharPos(0, 0);
   
   while (1)
   {
      GUC_dog_setCharPos(0, 0);
      GUC_dog_stringWrite("abcdefghijklmnopqrstu", 0);
      GUC_dog_setCharPos(1, 0);
      GUC_dog_stringWrite("vwxyz+\"*ç%&/()=?`^|~[]", 0);
      GUC_dog_setCharPos(2, 0);
      GUC_dog_stringWrite("ABCDEFGHIJKLMNOPQRSTU", 0);
      GUC_dog_setCharPos(3, 0);
      GUC_dog_stringWrite("VWXYZ1234567890", 0);
      
      GUC_dog_setCharPos(4, 0);
      GUC_dog_stringWrite("abcdefghijklmnopqrstu", 0xff);
      GUC_dog_setCharPos(5, 0);
      GUC_dog_stringWrite("vwxyz+\"*ç%&/()=?`^|~[]", 0xff);
      GUC_dog_setCharPos(6, 0);
      GUC_dog_stringWrite("ABCDEFGHIJKLMNOPQRSTU", 0xff);
      GUC_dog_setCharPos(7, 0);
      GUC_dog_stringWrite("VWXYZ1234567890", 0xff);
      Wait_ms(500);
      
   } //End while(1)
}

void Wait_ms(unsigned int ms)
{
   SFRPAGE = CONFIG_PAGE;
   TR5 = 1; //start timer5
   while (ms)
   {
      while (!TF5H);
      --ms;
      TF5H = 0;
   }
   TR5 = 0; //stop timer 5
   SFRPAGE = LEGACY_PAGE;
}

void Timer5Init()
{
   SFRPAGE   = CONFIG_PAGE;
   CKCON1    = 0x04;         // SYSCLK
   TMR5CN    = 0x04;         // enable timer 5
   TMR5RLL   = 0x20;         // 0xD120
   TMR5RLH   = 0xD1;         // 1ms
   TMR5L     = 0x20;
   TMR5H     = 0xD1;
   SFRPAGE   = LEGACY_PAGE;
}