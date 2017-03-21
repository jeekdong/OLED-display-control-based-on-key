//#############################################################################
//
//! \file    User_Component/myTimer/myTimer.c
//!
//! \brief   CPU TIMER
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
#include "User_Component/myTimer/myTimer.h"


// **************************************************************************
// the defines


// **************************************************************************
// the globals


// **************************************************************************
// the functions
//! \brief     myTimer initail
//! \param[in] None
//! \param[out] None
void myTimer_initial(void)
{
	Hour = 20;
	Minute = 37;
	Second = 0;
	HalfSecond = 0;
}

//
//! \brief     myTimer configure
//! \param[in] None
//! \param[out] None
void myTimer_config(void)
{

}

//! \brief     Interrup configure
//! \param[in] None
//! \param[out] None
void myTimer_INT_config(void)
{
	//3. register PIE vector
//	void PIE_registerPieIntHandler(PIE_Handle pieHandle,
//	                           const PIE_GroupNumber_e groupNumber,
//	                           const PIE_SubGroupNumber_e subGroupNumber,
//	                           const intVec_t vector);
	PIE_registerPieIntHandler(myPie, PIE_GroupNumber_1, PIE_SubGroupNumber_7, (intVec_t) &myTimer_CpuTimer0_isr);
    //4. interrupt source configure
	//void TIMER_stop(TIMER_Handle timerHandle);
	//void TIMER_setDecimationFactor(TIMER_Handle timerHandle,
	//                               const uint16_t decFactor);
	//void TIMER_setPeriod(TIMER_Handle timerHandle,
	//                     const uint32_t period);
	//void TIMER_reload(TIMER_Handle timerHandle);
	//void TIMER_start(TIMER_Handle timerHandle);
	TIMER_stop(myTimer0);
	TIMER_setDecimationFactor(myTimer0, 0);
	TIMER_setPeriod(myTimer0, 30000000L);
	TIMER_reload(myTimer0);
	TIMER_start(myTimer0);

	//5 module IE
	//void TIMER_enableInt(TIMER_Handle timerHandle);
	TIMER_enableInt(myTimer0);

	//6 PIE PIEIERx.y
	//void PIE_enableInt(PIE_Handle pieHandle, const PIE_GroupNumber_e group, const PIE_InterruptSource_e intSource);
	PIE_enableInt(myPie, PIE_GroupNumber_1, PIE_InterruptSource_TIMER_0);
	//7. CPU IERx
	//void CPU_enableInt(CPU_Handle cpuHandle,const CPU_IntNumber_e intNumber);
	CPU_enableInt(myCpu, CPU_IntNumber_1);

}

// end of file
