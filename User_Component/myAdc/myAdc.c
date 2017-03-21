//#############################################################################
//
//! \file User_Component/myAdc/myAdc.c
//!
//! \brief
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
#include "User_Component/myAdc/myAdc.h"


// **************************************************************************
// the defines


// **************************************************************************
// the globals


// **************************************************************************
// the functions
//! \brief     myAdc initail
//! \param[in] None
//! \param[out] None
void myAdc_initial(void)
{
	Temp = 0;
	TempC = 0;
}

//
//! \brief     myAdc configure
//! \param[in] None
//! \param[out] None
void myAdc_config(void)
{
	//1. ADC clock
	//void CLK_enableAdcClock(CLK_Handle clkHandle);
	CLK_enableAdcClock(myClk);
	//2. setup power
	//void ADC_powerUp(ADC_Handle adcHandle);
	//void ADC_enableBandGap(ADC_Handle adcHandle);
	//void ADC_enableRefBuffers(ADC_Handle adcHandle);
	ADC_powerUp(myAdc);
	ADC_enableBandGap(myAdc);
	ADC_enableRefBuffers(myAdc);
	//3. enable ADC
	//void ADC_enable(ADC_Handle adcHandle);
	ADC_enable(myAdc);
	//4. Volt ref
	ADC_setVoltRefSrc(myAdc, ADC_VoltageRefSrc_Int);
    //5. SOC
	//void ADC_setSocChanNumber(ADC_Handle adcHandle, const ADC_SocNumber_e socNumber, const ADC_SocChanNumber_e chanNumber);
	//void ADC_setSocSampleWindow(ADC_Handle adcHandle, const ADC_SocNumber_e socNumber, const ADC_SocSampleWindow_e sampleWindow);
	//void ADC_setSocTrigSrc(ADC_Handle adcHandle, const ADC_SocNumber_e socNumber, const ADC_SocTrigSrc_e trigSrc);
	ADC_setSocChanNumber(myAdc, ADC_SocNumber_0, ADC_SocChanNumber_A5);
	ADC_setSocSampleWindow(myAdc, ADC_SocNumber_0, ADC_SocSampleWindow_7_cycles);
	ADC_setSocTrigSrc(myAdc, ADC_SocNumber_0, ADC_SocTrigSrc_EPWM1_ADCSOCA);
    //6. temp sensor
	//void ADC_enableTempSensor(ADC_Handle adcHandle);
	ADC_enableTempSensor(myAdc);
}

//! \brief     Interrup configure
//! \param[in] None
//! \param[out] None
void myAdc_INT_config(void)
{
	//3. register PIE vector
//	void PIE_registerPieIntHandler(PIE_Handle pieHandle,
//	                           const PIE_GroupNumber_e groupNumber,
//	                           const PIE_SubGroupNumber_e subGroupNumber,
//	                           const intVec_t vector);
	PIE_registerPieIntHandler(myPie, PIE_GroupNumber_10, PIE_SubGroupNumber_1, (intVec_t) &myAdc_ADCINT_isr);
    //4. interrupt source configure
	//void ADC_setIntMode(ADC_Handle adcHandle, const ADC_IntNumber_e intNumber, const ADC_IntMode_e intMode);
	//void ADC_setIntPulseGenMode(ADC_Handle adcHandle, const ADC_IntPulseGenMode_e pulseMode);
	//void ADC_setIntSrc(ADC_Handle adcHandle, const ADC_IntNumber_e intNumber, const ADC_IntSrc_e intSrc);
	ADC_setIntMode(myAdc, ADC_IntNumber_1, ADC_IntMode_ClearFlag);
	ADC_setIntPulseGenMode(myAdc, ADC_IntPulseGenMode_Prior);
	ADC_setIntSrc(myAdc, ADC_IntNumber_1, ADC_IntSrc_EOC0);

	//5 module IE
	//void ADC_enableInt(ADC_Handle adcHandle, const ADC_IntNumber_e intNumber);
	ADC_enableInt(myAdc, ADC_IntNumber_1);


	//6 PIE PIEIERx.y
	//void PIE_enableInt(PIE_Handle pieHandle, const PIE_GroupNumber_e group, const PIE_InterruptSource_e intSource);
	PIE_enableInt(myPie, PIE_GroupNumber_10, PIE_InterruptSource_ADCINT_10_1);
	//7. CPU IERx
	//void CPU_enableInt(CPU_Handle cpuHandle,const CPU_IntNumber_e intNumber);
	CPU_enableInt(myCpu, CPU_IntNumber_10);

}





// end of file
