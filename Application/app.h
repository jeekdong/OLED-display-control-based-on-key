
//#############################################################################
//
//! \file:   Application\app.h
//!
//! \brief:  the application
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


#ifndef _APP_H_
#define _APP_H_


// **************************************************************************
// the includes
#include <stdint.h>

// driver
#include "F2802x_Component/F2802x_Device.h"
#include "User_Component/User_Device.h"


#ifdef __cplusplus
extern "C" {
#endif


#ifndef TARGET_GLOBAL
   #define TARGET_EXT 	extern
#else
   #define TARGET_EXT
#endif


/*------- API description of the example module   -------------*/
// EXAMPLE API
// the function prototypes
//! \brief     EXAMPLE API
//! \param[in] None
//! \param[out] None
//TARGET_EXT void EXAMPLE_API(void);

//! \brief     LED Control
//! \param[in] None
//! \param[out] None
TARGET_EXT void LED_Control(void);

//! \brief     Delay
//! \param[in] time
//! \param[out] None
TARGET_EXT void Delay(uint32_t time);

//! \brief     LED Control by KEY
//! \param[in] None
//! \param[out] None
TARGET_EXT void LED_KEY_Control(void);

//! \brief     SCI Test
//! \param[in] None
//! \param[out] None
TARGET_EXT void SCI_Test(void);

//! \brief     SCI Test1
//! \param[in] None
//! \param[out] None
TARGET_EXT void SCI_Test1(void);

//! \brief     ��ʾTimer
//! \param[in] None
//! \param[out] None
TARGET_EXT void DisplayTimer(void);

//! \brief     SCI Test
//! \param[in] None
//! \param[out] None
TARGET_EXT void SCI_ExchageData(void);

/*-------end of API description -------------*/


/*------- Globals of the example module   -------------*/
// the globals

//! \brief Defines the Variable
//TARGET_EXT uint16_t  Example;

/*------- end of globals  -------------*/


/*------- Defines of the example module   -------------*/
// the defines

//! \brief Defines the constant
//#define EXAMPLE_DEF

/*------- end of defines  -------------*/



#ifdef __cplusplus
}
#endif // extern "C"


#endif  // end of _APP_H_ definition

