
//#############################################################################
//
//! \file   User_Component/KEY/KEY.h
//!
//! \brief  KEY
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


#ifndef _KEY_H_
#define _KEY_H_


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
#define   KEY_obj      myGpio          //here myGpio is defined in System.h
#define   KEY1         GPIO_Number_12  //pin
//
// the function prototypes
//! \brief      KEY initail
//! \param[in]  None
//! \param[out] None
TARGET_EXT void KEY_initial(void);
//
//! \brief      KEY configure
//! \param[in]  None
//! \param[out] None
TARGET_EXT void KEY_config(void);
//
/*******************************************/
//! \brief      Interrup configure
//! \param[in]  None
//! \param[out] None
TARGET_EXT void KEY_INT_config(void);
//
//! \brief      Interrupt Service Routine
//! \param[in]  None
//! \param[out] None
TARGET_EXT interrupt void KEY_XINT_isr(void);     //redefined in Isr.h
/*-------end of hardware description -------------*/


/*------- API description of the example module   -------------*/
// EXAMPLE API
// the function prototypes

//! \brief     Get Key Status
//! \param[in] key
//! \param[out] None
TARGET_EXT uint16_t inline GetKeyStatus(GPIO_Number_e key)
{
	return GPIO_getData(KEY_obj, key);

}
/*-------end of API description -------------*/


/*------- Globals of the example module   -------------*/
// the globals

//! \brief Defines the Variable
//TARGET_EXT uint16_t  Example;

/*------- end of globals  -------------*/


/*------- Defines of the example module   -------------*/
// the defines

//! \brief Defines the constant
#define    KEYPRESSED   1

/*------- end of defines  -------------*/



#ifdef __cplusplus
}
#endif // extern "C"


#endif  // end of _KEY_H_ definition

