//#############################################################################
//
//! \file
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
#include "User_Component/LED_Pwm/LED_Pwm.h"


// **************************************************************************
// the defines


// **************************************************************************
// the globals


// **************************************************************************
// the functions

//! \brief     LED_PWM initail
//! \param[in] None
//! \param[out] None
void LED_PWM_initial(void)
{
	myCmpA = 0;
}
//
//! \brief     LED_PWM configure
//! \param[in] None
//! \param[out] None
void LED_PWM_config(void)
{  // 1. set mode
	//void GPIO_setMode(GPIO_Handle gpioHandle,const GPIO_Number_e gpioNumber,const GPIO_Mode_e mode);
	GPIO_setMode(myGpio, GPIO_Number_0, GPIO_0_Mode_EPWM1A);
  // 2. set pullup
	//void GPIO_setPullUp(GPIO_Handle gpioHandle,const GPIO_Number_e gpioNumber,const GPIO_PullUp_e pullUp);
	GPIO_setPullUp(myGpio, GPIO_Number_0, GPIO_PullUp_Disable);
   //3. set direction
	//void GPIO_setDirection(GPIO_Handle gpioHandle,const GPIO_Number_e gpioNumber,const GPIO_Direction_e direction);
	GPIO_setDirection(myGpio, GPIO_Number_0, GPIO_Direction_Output);
	//4. ePWM1 clock
	//void CLK_enablePwmClock(CLK_Handle clkHandle,const PWM_Number_e pwmNumber);
	CLK_enablePwmClock(myClk, PWM_Number_1);
	//5. TBCLKSYNC = 0
	//void CLK_disableTbClockSync(CLK_Handle clkHandle);
	CLK_disableTbClockSync(myClk);
	//6. TBCLK
	//void PWM_setHighSpeedClkDiv(PWM_Handle pwmHandle,const PWM_HspClkDiv_e clkDiv);
	//void PWM_setClkDiv(PWM_Handle pwmHandle,const PWM_ClkDiv_e clkDiv);
	PWM_setHighSpeedClkDiv(myPwm1, PWM_HspClkDiv_by_14);
	PWM_setClkDiv(myPwm1, PWM_ClkDiv_by_128);
    //7. TBCTR
	//void PWM_setCounterMode(PWM_Handle pwmHandle,const PWM_CounterMode_e counterMode);
	PWM_setCounterMode(myPwm1, PWM_CounterMode_Up);
	//8. TBPRD
	//void PWM_setPeriod(PWM_Handle pwmHandle,const uint16_t period);
	PWM_setPeriod(myPwm1, 60000);
	//void PWM_setPeriodLoad(PWM_Handle pwmHandle,const PWM_PeriodLoad_e periodLoad);
	PWM_setPeriodLoad(myPwm1, PWM_PeriodLoad_Shadow);
	//9. CMPA
	//void PWM_setCmpA(PWM_Handle pwmHandle,const uint16_t pwmData)
	PWM_setCmpA(myPwm1, 30000);
	//void PWM_setShadowMode_CmpA(PWM_Handle pwmHandle,const PWM_ShadowMode_e shadowMode);
	PWM_setShadowMode_CmpA(myPwm1, PWM_ShadowMode_Shadow);
	//void PWM_setLoadMode_CmpA(PWM_Handle pwmHandle,const PWM_LoadMode_e loadMode);
	PWM_setLoadMode_CmpA(myPwm1, PWM_LoadMode_Zero);
	//10. CMPB
	//void PWM_setCmpB(PWM_Handle pwmHandle,const uint16_t pwmData)
	//PWM_setCmpB(myPwm1, 30000);
	//void PWM_setShadowMode_CmpB(PWM_Handle pwmHandle,const PWM_ShadowMode_e shadowMode);
	//PWM_setShadowMode_CmpB(myPwm1, PWM_ShadowMode_Shadow);
	//void PWM_setLoadMode_CmpB(PWM_Handle pwmHandle,const PWM_LoadMode_e loadMode);
	//PWM_setLoadMode_CmpB(myPwm1, PWM_LoadMode_Zero);
	//11. action
	PWM_setActionQual_CntUp_CmpA_PwmA(myPwm1, PWM_ActionQual_Set);
	PWM_setActionQual_Period_PwmA(myPwm1, PWM_ActionQual_Clear);
	//12. TBCLKSYNC = 1
	//void CLK_enableTbClockSync(CLK_Handle clkHandle);
	CLK_enableTbClockSync(myClk);
	//13. ADC EPWMxSOCA/EPWMxSOCA
	//void PWM_setSocAPulseSrc(PWM_Handle pwmHandle,const PWM_SocPulseSrc_e pulseSrc);
	//void PWM_setSocAPeriod(PWM_Handle pwmHandle,const PWM_SocPeriod_e intPeriod);
	//void PWM_enableSocAPulse(PWM_Handle pwmHandle);
	PWM_setSocAPulseSrc(myPwm1, PWM_SocPulseSrc_CounterEqualPeriod);
	PWM_setSocAPeriod(myPwm1, PWM_SocPeriod_FirstEvent);
	PWM_enableSocAPulse(myPwm1);

}

//! \brief     Interrup configure
//! \param[in] None
//! \param[out] None
void LED_PWM_INT_config(void)
{
	//3. register PIE vector
//	void PIE_registerPieIntHandler(PIE_Handle pieHandle,
//	                           const PIE_GroupNumber_e groupNumber,
//	                           const PIE_SubGroupNumber_e subGroupNumber,
//	                           const intVec_t vector);
	PIE_registerPieIntHandler(myPie, PIE_GroupNumber_3, PIE_SubGroupNumber_1, (intVec_t) &LED_EPWM1_isr);
    //4. interrupt source configure
	//void PWM_setIntMode(PWM_Handle pwmHandle,const PWM_IntMode_e intMode);
	//void PWM_setIntPeriod(PWM_Handle pwmHandle,const PWM_IntPeriod_e intPeriod);
	PWM_setIntMode(myPwm1, PWM_IntMode_CounterEqualZero);
	PWM_setIntPeriod(myPwm1, PWM_IntPeriod_FirstEvent);

	//5 module IE
	//void PWM_enableInt(PWM_Handle pwmHandle);
	PWM_enableInt(myPwm1);

	//6 PIE PIEIERx.y
	//void PIE_enableInt(PIE_Handle pieHandle, const PIE_GroupNumber_e group, const PIE_InterruptSource_e intSource);
	PIE_enableInt(myPie, PIE_GroupNumber_3, PIE_InterruptSource_EPWM1);
	//7. CPU IERx
	//void CPU_enableInt(CPU_Handle cpuHandle,const CPU_IntNumber_e intNumber);
	CPU_enableInt(myCpu, CPU_IntNumber_3);
}

// end of file
