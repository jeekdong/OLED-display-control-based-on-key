//#############################################################################
//
//! \file     User_Component/KEY/KEY.c
//!
//! \brief    KEY
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
#include "User_Component/KEY/KEY.h"


// **************************************************************************
// the defines


// **************************************************************************
// the globals


// **************************************************************************
// the functions
//! \brief      KEY initail
//! \param[in]  None
//! \param[out] None
void KEY_initial(void)
{

}

//
//! \brief      KEY configure
//! \param[in]  None
//! \param[out] None
void KEY_config(void)
{
	// 1. set mode
	//void GPIO_setMode(GPIO_Handle gpioHandle,const GPIO_Number_e gpioNumber,const GPIO_Mode_e mode);
	GPIO_setMode(KEY_obj, KEY1, GPIO_12_Mode_GeneralPurpose);

	// 2. set pullup
	//void GPIO_setPullUp(GPIO_Handle gpioHandle,const GPIO_Number_e gpioNumber,const GPIO_PullUp_e pullUp);
	GPIO_setPullUp(KEY_obj, KEY1, GPIO_PullUp_Enable);

	//3. set direction
	//void GPIO_setDirection(GPIO_Handle gpioHandle,const GPIO_Number_e gpioNumber,const GPIO_Direction_e direction);
	GPIO_setDirection(KEY_obj, KEY1, GPIO_Direction_Input);

	//4. set Qualification
	//void GPIO_setQualification(GPIO_Handle gpioHandle, const GPIO_Number_e gpioNumber, const GPIO_Qual_e qualification);
	//void GPIO_setQualificationPeriod(GPIO_Handle gpioHandle, const GPIO_Number_e gpioNumber, const uint16_t period);
	GPIO_setQualification(KEY_obj, KEY1, GPIO_Qual_ASync);

}

//! \brief      Interrup configure
//! \param[in]  None
//! \param[out] None
void KEY_INT_config(void)
{
	//3. register PIE vector
	//	void PIE_registerPieIntHandler(PIE_Handle pieHandle,
	//	                           const PIE_GroupNumber_e groupNumber,
	//	                           const PIE_SubGroupNumber_e subGroupNumber,
	//	                           const intVec_t vector);
	PIE_registerPieIntHandler(myPie, PIE_GroupNumber_1, PIE_SubGroupNumber_5, (intVec_t) &KEY_XINT_isr);

	//4. interrupt source configure
	//	void PIE_setExtIntPolarity(PIE_Handle pieHandle,
	//	                           const CPU_ExtIntNumber_e intNumber,
	//	                           const PIE_ExtIntPolarity_e polarity);
	PIE_setExtIntPolarity(myPie, CPU_ExtIntNumber_2, PIE_ExtIntPolarity_FallingEdge);

	//	void GPIO_setExtInt(GPIO_Handle gpioHandle,const GPIO_Number_e gpioNumber,const CPU_ExtIntNumber_e intNumber);
	GPIO_setExtInt(KEY_obj, KEY1, CPU_ExtIntNumber_2);

	//5 module IE
	//	void PIE_enableExtInt(PIE_Handle pieHandle,const CPU_ExtIntNumber_e intNumber);
	PIE_enableExtInt(myPie, CPU_ExtIntNumber_2);

	//6 PIE PIEIERx.y
	//void PIE_enableInt(PIE_Handle pieHandle, const PIE_GroupNumber_e group, const PIE_InterruptSource_e intSource);
	PIE_enableInt(myPie, PIE_GroupNumber_1, PIE_InterruptSource_XINT_2);

	//7. CPU IERx
	//void CPU_enableInt(CPU_Handle cpuHandle,const CPU_IntNumber_e intNumber);
	CPU_enableInt(myCpu, CPU_IntNumber_1);
}

// end of file
