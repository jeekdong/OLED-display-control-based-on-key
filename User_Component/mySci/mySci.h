
//#############################################################################
//
//! \file   User_Component/mySci/mySci.h
//!
//! \brief  SCI
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


#ifndef _MYSCI_H_
#define _MYSCI_H_


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

//
// the function prototypes
//! \brief     SCI initail
//! \param[in] None
//! \param[out] None
TARGET_EXT void mySCI_initial(void);
//
//! \brief     SCI configure
//! \param[in] None
//! \param[out] None
TARGET_EXT void mySCI_config(void);
//
/*******************************************/
//! \brief      Interrup configure
//! \param[in]  None
//! \param[out] None
TARGET_EXT void mySCI_TXINT_config(void);
//
//! \param[in]  None
//! \param[out] None
TARGET_EXT void mySCI_RXINT_config(void);

//! \brief      Interrupt Service Routine
//! \param[in]  None
//! \param[out] None
TARGET_EXT interrupt void mySCI_TXINT_isr(void);     //redefined in Isr.h

//! \brief      Interrupt Service Routine
//! \param[in]  None
//! \param[out] None
TARGET_EXT interrupt void mySCI_RXINT_isr(void);     //redefined in Isr.h
/*-------end of hardware description -------------*/


/*------- API description of the example module   -------------*/
// EXAMPLE API
// the function prototypes
//! \brief     EXAMPLE API
//! \param[in] None
//! \param[out] None
//TARGET_EXT void EXAMPLE_API(void);

//! \brief     Transmit a char from the SCI
//! \param[in] string
//! \param[out] None
TARGET_EXT void inline mySCI_sendCharBlocking(uint16_t ch)
{
	SCI_putDataBlocking(mySci, ch);
}

//! \brief     Transmit a string from the SCI
//! \param[in] string
//! \param[out] None
TARGET_EXT void mySCI_sendMessageBlocking(uint16_t * msg);

//! \brief     Receive a char from the SCI
//! \param[in] None
//! \param[out] receive data
TARGET_EXT uint16_t inline mySCI_receiveCharBlocking(void)
{
	return SCI_getDataBlocking(mySci);
}

//! \brief     Receive a char from the SCI
//! \param[in] None
//! \param[out] SciReceiveBuf: receive data; <50 data
TARGET_EXT uint16_t* mySCI_receiveMessageBlocking(void);

/*-------end of API description -------------*/


/*------- Globals of the example module   -------------*/
// the globals

//! \brief Defines the Variable
//TARGET_EXT uint16_t  Example;
TARGET_EXT uint16_t SciSendBuf[50];
TARGET_EXT uint16_t SciSendPoint;
TARGET_EXT uint16_t SciReceiveBuf[50];
TARGET_EXT uint16_t SciReceivePoint;
TARGET_EXT uint16_t SciSentOk;
TARGET_EXT uint16_t SciReceivedOk;



/*------- end of globals  -------------*/


/*------- Defines of the example module   -------------*/
// the defines

//! \brief Defines the constant
//#define EXAMPLE_DEF


/*------- end of defines  -------------*/



#ifdef __cplusplus
}
#endif // extern "C"


#endif  // end of _MYSCI_H_ definition

