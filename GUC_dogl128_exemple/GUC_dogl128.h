#ifndef _GUC_DOGL128_H_INCLUDED_
#define _GUC_DOGL128_H_INCLUDED_

/***********************\
* GUC_DogL128 LIB       *
|***********************|
* Author : Guillaume G. *
* Version : 1.1         *
* Date : 20.01.2020     *
\***********************/

/*
CHANGELOG 1.0

- Creating the LIB

CHANGELOG 1.1

- Adding "GUC_dog_setStat"
- Setting default output to "GUC_DOG_CFG_OUTPUT_SPISIMULATE"
*/


#include <REG51F380.H>


/*********************\
* MACRO CONFIGURATION *
\*********************/

/*******************
GUC_DOG_CFG_OUTPUT :
********************
Set the output mod of the uc.
*/
#define GUC_DOG_CFG_OUTPUT_SPISIMULATE 0
/*
   Choose a simulated SPI.
   - Slower and expensive but manipulable PIN
*/
#define GUC_DOG_CFG_OUTPUT_SPI3WIRE 1
/*
   Choose the internal SPI (3 wire master)
   - Faster but no manipulable PIN
*/
#define GUC_DOG_CFG_OUTPUT GUC_DOG_CFG_OUTPUT_SPISIMULATE


/*********************************
GUC_DOG_CFG_FONT_COMPILE_DEFAULT :
**********************************
Compile the default font.
   0 : No default font, cheap
   1 : Compile the default font, expensive
*/
#define GUC_DOG_CFG_FONT_COMPILE_DEFAULT 1


/***********************************
GUC_DOG_CFG_FONT_CUSTOMISABLE_SIZE :
************************************
With this option on, you can change
the default x size of the default 5x8 font.
   0 : Default size only, faster and cheap
   1 : Custom size, slower and expensive
*/
#define GUC_DOG_CFG_FONT_CUSTOMISABLE_SIZE 0


/************\
* DEFINITION *
\************/

#define _GUC_DOG_FONT_DEFAULT_SIZEX 5
#define _GUC_DOG_FONT_DEFAULT_SIZEX_WINTERVAL 6
#define _GUC_DOG_FONT_DEFAULT_SIZEY 1

#define _GUC_DOG_FONT_X 0
#define _GUC_DOG_FONT_ZERO 1
#define _GUC_DOG_FONT_SIZE 2
#define _GUC_DOG_FONT_HEADER_SIZE 3


/********************\
* SBIT CONFIGURATION *
\********************/

sbit GUC_DOG_CS = P2^3;
sbit GUC_DOG_A0 = P2^4;

#if GUC_DOG_CFG_OUTPUT == GUC_DOG_CFG_OUTPUT_SPISIMULATE
sbit GUC_DOG_MOSI = P2^2;
sbit GUC_DOG_SCLK = P2^0;
#endif //GUC_DOG_CFG_OUTPUT_SPISIMULATE


/********************\
* FUNCTION PROTOTYPE *
\********************/

//Initialization of the DogL128
void GUC_dog_init();
   
//Send data to the display through SPI
void GUC_dog_sendByte(const unsigned char _byte, bit _a0);
//Set the cursor position, _page 0 to 7, _row 0 to 127.
void GUC_dog_setCursorPos(const unsigned char _page, const unsigned char _row);
//Clear the screen with a specify value (0x00 for a empty screen).
void GUC_dog_clearScreen(const unsigned char _value);

//Write a ASCII character where the cursor is (_invert can switch the black and white pixel).
void GUC_dog_charWrite(unsigned char _valueChar, const unsigned char _invert);
//Write a Null-terminated ASCII text where the cursor is (_invert can switch the black and white pixel).
void GUC_dog_stringWrite(const unsigned char* _str, const unsigned char _invert);
//Write a Length-prefixed ASCII text where the cursor is (_invert can switch the black and white pixel).
void GUC_dog_pstringWrite(const unsigned char* _str, const unsigned char _invert);


/****************\
* FUNCTION MACRO *
\****************/

//Set display 1:ON, 0:OFF.
#define GUC_dog_setStat(_stat) GUC_dog_sendByte(_stat ? 0xAF : 0xAE, 0)

//Write a byte where the cursor is.
#define GUC_dog_write(_byte) GUC_dog_sendByte(_byte, 1)

//Set the cursor position relative to the character X size, _page 0 to 7, _pos.
#if GUC_DOG_CFG_FONT_CUSTOMISABLE_SIZE == 1
#define GUC_dog_setCharPos(_page, _pos) GUC_dog_setCursorPos(_page, _pos*(__gucdog_font_data[_GUC_DOG_FONT_X]+1))
#else
#define GUC_dog_setCharPos(_page, _pos) GUC_dog_setCursorPos(_page, _pos*_GUC_DOG_FONT_DEFAULT_SIZEX_WINTERVAL)
#endif //GUC_DOG_CFG_FONT_CUSTOMISABLE_SIZE


/*****************\
* VARIABLE EXTERN *
\*****************/

extern xdata unsigned char* __gucdog_font_data;


#endif //_GUC_DOGL128_H_INCLUDED_