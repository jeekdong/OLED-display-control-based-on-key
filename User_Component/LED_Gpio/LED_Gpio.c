//#############################################################################
//
//! \file  User_Component/LED_Gpio/LED_Gpio.c
//!
//! \brief LED control by GPIO
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
#include "User_Component/LED_Gpio/LED_Gpio.h"


// **************************************************************************
// the defines


// **************************************************************************
// the globals


// **************************************************************************
// the functions

//! \brief      LED_GPIO initail
//! \param[in]  None
//! \param[out] None
void LED_GPIO_initial(void)
{
	LED_off(LED1);
}
//
//! \brief      LED_GPIO configure
//! \param[in]  None
//! \param[out] None
void LED_GPIO_config(void)
{
	// 1. set mode
	//void GPIO_setMode(GPIO_Handle gpioHandle,const GPIO_Number_e gpioNumber,const GPIO_Mode_e mode);
	GPIO_setMode(LED_Gpio_obj, LED1, GPIO_0_Mode_GeneralPurpose);

	// 2. set pullup
	//void GPIO_setPullUp(GPIO_Handle gpioHandle,const GPIO_Number_e gpioNumber,const GPIO_PullUp_e pullUp);
	GPIO_setPullUp(LED_Gpio_obj, LED1, GPIO_PullUp_Disable);

	// 3. set direction
	//void GPIO_setDirection(GPIO_Handle gpioHandle,const GPIO_Number_e gpioNumber,const GPIO_Direction_e direction);
	GPIO_setDirection(LED_Gpio_obj, LED1, GPIO_Direction_Output);
}

// end of file
