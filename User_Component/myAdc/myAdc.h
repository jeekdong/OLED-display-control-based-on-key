
//#############################################################################
//
//! \file User_Component/myAdc/myAdc.h
//!
//! \brief  ADC
//!
//  Quthor:
//  Group:          C2000
//  Target Device:  TMS320F2802x
//
//  (C) Copyright 2014, Fuzhou University.
//#############################################################################
// $TI Release: f2802x Support Library v210 $
// $Release Date: Mon Sep 17 09:13:31 CDT 2012 $
//#############################################################################


#ifndef _MYADC_H_
#define _MYADC_H_


// **************************************************************************
// the includes
#include <stdint.h>

// driver
#include "F2802x_Component/F2802x_Device.h"
#include "User_Component/User_Mcu/User_System.h"

#ifdef __cplusplus
extern "C" {
#endif


#ifndef TARGET_GLOBAL
   #define TARGET_EXT 	extern
#else
   #define TARGET_EXT
#endif


/*------- hardware description of the example module   -------------*/
// For example
// The module derived from GPIO
//
// the function prototypes
//! \brief     myAdc initail
//! \param[in] None
//! \param[out] None
TARGET_EXT void myAdc_initial(void);
//
//! \brief     myAdc configure
//! \param[in] None
//! \param[out] None
TARGET_EXT void myAdc_config(void);
//
/*******************************************/
//! \brief     Interrup configure
//! \param[in] None
//! \param[out] None
TARGET_EXT void myAdc_INT_config(void);
//
//! \brief     Interrupt Service Routine
//! \param[in] None
//! \param[out] None
TARGET_EXT interrupt void myAdc_ADCINT_isr(void);     //redefined in Isr.h
/*-------end of hardware description -------------*/


/*------- API description of the example module   -------------*/
// EXAMPLE API
// the function prototypes
//! \brief     Get Key Status
//! \param[in] key
//! \param[out] None
//TARGET_EXT uint16_t GetKeyStatus(GPIO_Number_e key);
/*-------end of API description -------------*/


/*------- Globals of the example module   -------------*/
// the globals

//! \brief Defines the Variable
//TARGET_EXT uint16_t  Example;
TARGET_EXT uint16_t  Temp;
TARGET_EXT uint16_t  TempC;

/*------- end of globals  -------------*/


/*------- Defines of the example module   -------------*/
// the defines

//! \brief Defines the constant
//#define KEYPRESSED 1

/*------- end of defines  -------------*/



#ifdef __cplusplus
}
#endif // extern "C"


#endif  // end of _EXAMPLE_H_ definition

