//#############################################################################
//
//! \file   Application\Isr.c
//!
//! \brief  Interrupt Service Routine
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
#include "Application/isr.h"


// **************************************************************************
// the defines


// **************************************************************************
// the globals


// **************************************************************************
// the functions

//interrupt void isr(void)
//{
//
//    // Acknowledge this interrupt to get more from group 1
//    PIE_clearInt(myPie, PIE_GroupNumber_1);
//
//}

//! \brief      Interrupt Service Routine
//! \param[in]  None
//! \param[out] None
interrupt void KEY_XINT_isr(void)
{
	LED_toggle(LED1);

	// Acknowledge this interrupt to get more from group 1
	PIE_clearInt(myPie, PIE_GroupNumber_1);

}

//! \brief      Interrupt Service Routine
//! \param[in]  None
//! \param[out] None
interrupt void myTimer_CpuTimer0_isr(void)
{
	HalfSecond ++;
	if(2 <= HalfSecond)
	{	HalfSecond = 0;
		LED_toggle(LED1);
		Second ++;
		if(Second >= 60)
		{
			Second = 0;
			Minute ++;
			if(Minute >= 60)
			{
				Minute = 0;
				Hour ++;
				if(Hour >=24)
				{
					Second = 0;
					Minute = 0;
					Hour = 0;
				}
			}
		}
	}

	// Acknowledge this interrupt to get more from group 1
	PIE_clearInt(myPie, PIE_GroupNumber_1);

}

//! \brief      Interrupt Service Routine
//! \param[in]  None
//! \param[out] None
interrupt void LED_EPWM1_isr(void)
{
	myCmpA++;
	if(myCmpA >=60000 ) myCmpA = 0;
	PWM_setCmpA(myPwm1, myCmpA);

	//void PWM_clearIntFlag(PWM_Handle pwmHandle)
	PWM_clearIntFlag(myPwm1);

	// Acknowledge this interrupt to get more from group 1
	PIE_clearInt(myPie, PIE_GroupNumber_3);

}

//! \brief      Interrupt Service Routine
//! \param[in]  None
//! \param[out] None
interrupt void myAdc_ADCINT_isr(void)
{

	Temp = ADC_readResult(myAdc, ADC_ResultNumber_0);
	TempC = ADC_getTemperatureC(myAdc, Temp);

	//void PWM_clearSocAFlag(PWM_Handle pwmHandle)
	PWM_clearSocAFlag(myPwm1);

	//void ADC_clearIntFlag(ADC_Handle adcHandle, const ADC_IntNumber_e intNumber)
	ADC_clearIntFlag(myAdc, ADC_IntNumber_1);

	// Acknowledge this interrupt to get more from group 1
	PIE_clearInt(myPie, PIE_GroupNumber_10);

}

//! \brief      Interrupt Service Routine
//! \param[in]  None
//! \param[out] None
interrupt void mySCI_TXINT_isr(void)
{   if(false == SciSentOk)
	{
		SciSendPoint +=1 ;
		if('\0' != SciSendBuf[SciSendPoint] && SciSendPoint <=50)
			SCI_putData(mySci, SciSendBuf[SciSendPoint]);
		else
		{
			SciSentOk = true;
		}
	}

	// Acknowledge this interrupt to get more from group 1
	PIE_clearInt(myPie, PIE_GroupNumber_9);

}

//! \brief      Interrupt Service Routine
//! \param[in]  None
//! \param[out] None
interrupt void mySCI_RXINT_isr(void)
{   uint16_t ch;
    if(false == SciReceivedOk)
    {
    	ch = SCI_getData(mySci);
    	SciReceiveBuf[SciReceivePoint] = ch;
    	SciReceivePoint += 1;
    	if( SciReceivePoint >=50)
    	{
    		SciReceivePoint = 0;
    	}

    	if('\0' == ch)
    	{
    		SciReceivedOk = true;
    	}

	}
	// Acknowledge this interrupt to get more from group 1
	PIE_clearInt(myPie, PIE_GroupNumber_9);

}

// end of file
