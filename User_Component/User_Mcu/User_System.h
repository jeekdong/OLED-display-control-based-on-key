// USER File $Revision: /main/3 $
// Checkin $Date: Oct 10, 2013   12:51:13 $
// Author£º
//###########################################################################
//
// FILE:   USER_System_H
//
// TITLE:  System config

#ifndef USER_SYSTEM_H
#define USER_SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TARGET_GLOBAL
   #define TARGET_EXT 	extern
#else
   #define TARGET_EXT
#endif

//includes
#include "F2802x_Component/F2802x_Device.h"


TARGET_EXT CLK_Handle myClk;
TARGET_EXT CPU_Handle myCpu;
TARGET_EXT PLL_Handle myPll;
TARGET_EXT WDOG_Handle myWDog;
TARGET_EXT PIE_Handle myPie;
TARGET_EXT GPIO_Handle myGpio;
TARGET_EXT TIMER_Handle myTimer0;
TARGET_EXT PWM_Handle myPwm1;
TARGET_EXT PWM_Handle myPwm2;
TARGET_EXT ADC_Handle myAdc;
TARGET_EXT CAP_Handle myCap;
TARGET_EXT SCI_Handle mySci;

TARGET_EXT void System_initial(void);   //system initial
TARGET_EXT void System_config(void);    //system config
TARGET_EXT void SystemINT_start(void);     //PIE start

#ifdef __cplusplus
}
#endif /* extern "C" */



#endif



