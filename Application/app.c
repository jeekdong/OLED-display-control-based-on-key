//#############################################################################
//
//! \file  Application\app.c
//!
//! \brief  application
//
//  Author:
//  Group:          C2000
//  Target Device:  TMS320F2802x
//
//  (C) Copyright 2014, Texas Instruments, Inc.
//#############################################################################
// $TI Release: f2802x Support Library v210 $
// $Release Date: Mon Sep 17 09:13:31 CDT 2012 $
//#############################################################################

// **************************************************************************
// the includes
#include "Application/app.h"


// **************************************************************************
// the defines


// **************************************************************************
// the globals


// **************************************************************************
// the functions

//! \brief     LED Control
//! \param[in] None
//! \param[out] None
void LED_Control(void)
{
	LED_on(LED1);
    Delay(1000000L);
    LED_off(LED1);
    Delay(1000000L);
}

//! \brief     Delay
//! \param[in] time
//! \param[out] None
void Delay(uint32_t time)
{
	while(time--) ;
}

//! \brief     LED Control by KEY
//! \param[in] None
//! \param[out] None
void LED_KEY_Control(void)
{
	 if ( KEYPRESSED == GetKeyStatus(KEY1))
	 {
		 LED_on(LED1);
	 }
	 else
	 {
		 LED_off(LED1);
	 }

}

//! \brief     SCI Test
//! \param[in] None
//! \param[out] None
void SCI_Test(void)
{   uint16_t ch;
    uint16_t * msg;
    msg =  (uint16_t *)"\r\nEnter a character: \0";
	mySCI_sendMessageBlocking(msg);
	ch = mySCI_receiveCharBlocking(); //waiting for a char
	mySCI_sendCharBlocking(ch); //send the received char
}

//! \brief     SCI Test1
//! \param[in] None
//! \param[out] None
void SCI_Test1(void)
{   uint16_t ch;

    while(1)
    {
    	ch = mySCI_receiveCharBlocking(); //waiting for a char
    	mySCI_sendCharBlocking(ch); //send the received char
    }
}

//! \brief     SCI Test
//! \param[in] None
//! \param[out] None
TARGET_EXT void SCI_ExchageData(void)
{
	uint16_t ch,i;
	if(true == SciReceivedOk && true == SciSentOk)
	{   SciReceivePoint = 0;
		do
	 	{   ch = SciReceiveBuf[SciReceivePoint];
			SciSendBuf[SciReceivePoint] = ch;
			SciReceivePoint ++;
	 	}while(ch != '\0');
        if(SciReceivePoint>3)
        {
    		for(i=0;i<=SciReceivePoint-3;i++)
    		{
    			if('#'==SciSendBuf[i])
    			{
    				Hour = SciSendBuf[i+1];
    				Minute = SciSendBuf[i+2];
    				Second = SciSendBuf[i+3];
    			}
    		}
        }
		SciReceivePoint = 0;
		SciReceivedOk = false;
		SciSentOk = false;
		SciSendPoint = 0;
		SCI_putData(mySci, SciSendBuf[0]);
    }

}

//! \brief     显示Timer
//! \param[in] None
//! \param[out] None
#define CLOCK_X     64
#define CLOCK_Y     28
#define CLOCK_RS    26
#define CLOCK_RM    19
#define CLOCK_RH    13

void DisplayTimer(void)
{   uint16_t BH,BL;
	_iq20 _iq20Temp,_iq20x,_iq20y;
	int32_t x,y;
    OLED_clearImage();
/*-------------------------------------------------------*/
    _iq20Temp = _IQ20mpy(_IQ20(Second),_IQ20(2*3.1415926/60));
	_iq20x = _IQ20sin(_iq20Temp);
	_iq20y = _IQ20cos(_iq20Temp);
	x = _IQ20mpy(_IQ20(CLOCK_RS),_iq20x);
	x = x >> 20;
	x = CLOCK_X + x;
	y = _IQ20mpy(_IQ20(CLOCK_RS),_iq20y);
	y = y >> 20;
	y = CLOCK_Y - y;
    OLED_showLine(CLOCK_X, CLOCK_Y, (uint16_t)x, (uint16_t)y, 0);
/*-------------------------------------------------------*/
	_iq20Temp = _IQ20mpy(_IQ20(Minute),_IQ20(2*3.1415926/60));
	_iq20x = _IQ20sin(_iq20Temp);
	_iq20y = _IQ20cos(_iq20Temp);
	x = _IQ20mpy(_IQ20(CLOCK_RM),_iq20x);
	x = x >> 20;
	x = CLOCK_X + x;
	y = _IQ20mpy(_IQ20(CLOCK_RM),_iq20y);
	y = y >> 20;
	y = CLOCK_Y - y;
    OLED_showLine(CLOCK_X, CLOCK_Y, (uint16_t)x, (uint16_t)y, 0);
    /*-------------------------------------------------------*/
	_iq20Temp = _IQ20mpy(_IQ20(Hour),_IQ20(2*3.1415926/12));
	_iq20x = _IQ20sin(_iq20Temp);
	_iq20y = _IQ20cos(_iq20Temp);
	x = _IQ20mpy(_IQ20(CLOCK_RH),_iq20x);
	x = x >> 20;
	x = CLOCK_X + x;
	y = _IQ20mpy(_IQ20(CLOCK_RH),_iq20y);
	y = y >> 20;
	y = CLOCK_Y - y;
    OLED_showLine(CLOCK_X, CLOCK_Y, (uint16_t)x, (uint16_t)y, 0);
/*-------------------------------------------------------*/



    BH = Hour/10;
    BL = Hour%10;
    OLED_showImage8x8(32+0*8,7,BH,0); //时
    OLED_showImage8x8(32+1*8,7,BL,0); //时
    OLED_showImage8x8(32+2*8,7,10,0); //:

	BH = Minute/10;
    BL = Minute%10;
    OLED_showImage8x8(32+3*8,7,BH,0); //分
    OLED_showImage8x8(32+4*8,7,BL,0); //分
    OLED_showImage8x8(32+5*8,7,10,0); //:

    BH = Second/10;
    BL = Second%10;
    OLED_showImage8x8(32+6*8,7,BH,0); //秒
    OLED_showImage8x8(32+7*8,7,BL,0); //秒

    OLED_showImage();
}


// end of file
