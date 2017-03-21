//#############################################################################
//
//! \file User_Component/mySci/mySci.h
//!
//! \brief  SCI
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
#include "User_Component/mySci/mySci.h"


// **************************************************************************
// the defines


// **************************************************************************
// the globals


// **************************************************************************
// the functions

 // the function prototypes
//! \brief      SCI initail
//! \param[in]  None
//! \param[out] None
void mySCI_initial(void)
{
	SciSendPoint = 0;
	SciReceivePoint = 0;
	SciSentOk = false;
	SciReceivedOk =false;

}
//
//! \brief      SCI RX configure
//! \param[in]  None
//! \param[out] None
void mySCI_config(void)
{ 	//1. GPIO configure
	//1.1 pullup
	GPIO_setPullUp(myGpio, GPIO_Number_28, GPIO_PullUp_Enable);
    GPIO_setPullUp(myGpio, GPIO_Number_29, GPIO_PullUp_Disable);
    //1.2 input qualification
    GPIO_setQualification(myGpio, GPIO_Number_28, GPIO_Qual_ASync);
    //1.3 mode
    GPIO_setMode(myGpio, GPIO_Number_28, GPIO_28_Mode_SCIRXDA);
    GPIO_setMode(myGpio, GPIO_Number_29, GPIO_29_Mode_SCITXDA);
    //2. enable SCIA clk
    CLK_enableSciaClock(myClk);
    //3. configure the low speed peripheral clock(LSPCLK) LSPCLK = SYSCLKOUT/4 =15MHz
    CLK_setLowSpdPreScaler(myClk, CLK_LowSpdPreScaler_SysClkOut_by_4);
    //4. SCI BRR = LSPCLK/(SCI BAUDx8) - 1
    SCI_setBaudRate(mySci, SCI_BaudRate_9_6_kBaud);
    //5. configure package(1 stop bit,  No loopback, No parity,8 char bits, async mode, idle-line protocol)
    SCI_disableParity(mySci);
    SCI_setNumStopBits(mySci, SCI_NumStopBits_One);
    SCI_setCharLength(mySci, SCI_CharLength_8_Bits);
    //6. enable SCI TX&RX
    SCI_enableTx(mySci);
    SCI_enableRx(mySci);
    //7. enable SCI module
    SCI_enable(mySci);
}

//! \brief      SCI TX configure
//! \param[in]  None
//! \param[out] None
void mySCI_TXINT_config(void)
{
	//3. register PIE vector
	//	void PIE_registerPieIntHandler(PIE_Handle pieHandle,
	//	                           const PIE_GroupNumber_e groupNumber,
	//	                           const PIE_SubGroupNumber_e subGroupNumber,
	//	                           const intVec_t vector);
	PIE_registerPieIntHandler(myPie, PIE_GroupNumber_9, PIE_SubGroupNumber_2, (intVec_t) &mySCI_TXINT_isr);

	//4. interrupt source configure

	//5 module IE
	//	void SCI_enableTxInt(SCI_Handle sciHandle);
	SCI_enableTxInt(mySci);

	//6 PIE PIEIERx.y
	//void PIE_enableInt(PIE_Handle pieHandle, const PIE_GroupNumber_e group, const PIE_InterruptSource_e intSource);
	PIE_enableInt(myPie, PIE_GroupNumber_9, PIE_InterruptSource_SCIATX);

	//7. CPU IERx
	//void CPU_enableInt(CPU_Handle cpuHandle,const CPU_IntNumber_e intNumber);
	CPU_enableInt(myCpu, CPU_IntNumber_9);

}

//
//! \param[in]  None
//! \param[out] None
void mySCI_RXINT_config(void)
{
	//3. register PIE vector
	//	void PIE_registerPieIntHandler(PIE_Handle pieHandle,
	//	                           const PIE_GroupNumber_e groupNumber,
	//	                           const PIE_SubGroupNumber_e subGroupNumber,
	//	                           const intVec_t vector);
	PIE_registerPieIntHandler(myPie, PIE_GroupNumber_9, PIE_SubGroupNumber_1, (intVec_t) &mySCI_RXINT_isr);

	//4. interrupt source configure

	//5 module IE
	//void SCI_enableRxInt(SCI_Handle sciHandle);
	SCI_enableRxInt(mySci);

	//6 PIE PIEIERx.y
	//void PIE_enableInt(PIE_Handle pieHandle, const PIE_GroupNumber_e group, const PIE_InterruptSource_e intSource);
	PIE_enableInt(myPie, PIE_GroupNumber_9, PIE_InterruptSource_SCIARX);

	//7. CPU IERx
	//void CPU_enableInt(CPU_Handle cpuHandle,const CPU_IntNumber_e intNumber);
	CPU_enableInt(myCpu, CPU_IntNumber_9);

}

//! \brief     Transmit a string from the SCI
//! \param[in] string
//! \param[out] None
void mySCI_sendMessageBlocking(uint16_t * msg)
{
    uint16_t i = 0;

    while('\0' != msg[i])
    {
    	mySCI_sendCharBlocking(msg[i]);
        i++;
    }
}

//! \brief     Receive a char from the SCI
//! \param[in] None
//! \param[out] SciReceiveBuf: receive data; <10 data
uint16_t* mySCI_receiveMessageBlocking(void)
{
	SciReceivePoint = 0;
	while( SciReceivePoint <10 )
	{
		SciReceiveBuf[SciReceivePoint]=mySCI_receiveCharBlocking();
		if('\0' == SciReceiveBuf[SciReceivePoint]) break;
		SciReceivePoint += 1;
	}
	return SciReceiveBuf;
}

// end of file
