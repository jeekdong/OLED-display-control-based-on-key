// User File $Revision: /main/1 $
// Checkin $Date: Oct 11, 2013   11:11:30 $
// Author：CFH
//###########################################################################
//
// FILE:	User_System.c
// TITLE:	System config

//###########################################################################


#include "User_Component/User_Mcu/User_System.h"

// system initial
void System_initial(void)
{
}

void System_config(void)    //system config
{
    //0.
	myCpu = CPU_init((void *)NULL, sizeof(CPU_Obj));
    myWDog = WDOG_init((void *)WDOG_BASE_ADDR, sizeof(WDOG_Obj));
    myPll = PLL_init((void *)PLL_BASE_ADDR, sizeof(PLL_Obj));
    myClk = CLK_init((void *)CLK_BASE_ADDR, sizeof(CLK_Obj));
	myGpio = GPIO_init((void *)GPIO_BASE_ADDR, sizeof(GPIO_Obj));
	myPie = PIE_init((void *)PIE_BASE_ADDR, sizeof(PIE_Obj));   //中断指针赋值
	myTimer0 = TIMER_init((void *)TIMER0_BASE_ADDR, sizeof(TIMER_Obj)); // CPU Timer0
	myPwm1 = PWM_init((void *)PWM_ePWM1_BASE_ADDR, sizeof(PWM_Obj)); // PWM1
	myPwm2 = PWM_init((void *)PWM_ePWM2_BASE_ADDR, sizeof(PWM_Obj)); // PWM2
	myAdc = ADC_init((void *)ADC_BASE_ADDR, sizeof(ADC_Obj));
	myCap = CAP_init((void *)CAPA_BASE_ADDR, sizeof(CAP_Obj));
	mySci = SCI_init((void *)SCIA_BASE_ADDR, sizeof(SCI_Obj));

	// 1. disable watch DOG
    WDOG_disable(myWDog);
    // 2. disable interrupt
    CPU_disableGlobalInts(myCpu);
    // 3. Select the internal oscillator 1(10MHz) as the clock source
    CLK_setOscSrc(myClk, CLK_OscSrc_Internal);
    // 4. Setup the PLL for x12 /2 which will yield 60Mhz = 10Mhz * 12 / 2
    PLL_setup(myPll, PLL_Multiplier_12, PLL_DivideSelect_ClkIn_by_2);
    // 5. PIE configure
    PIE_disable(myPie);                                      //禁止PIE
    PIE_disableAllInts(myPie);                                //禁止PIE中断
    CPU_disableGlobalInts(myCpu);                            //CPU全局中断禁止
    CPU_clearIntFlags(myCpu);                               //CPU中断标志位清零
    PIE_setDefaultIntVectorTable(myPie);                      //中断入口地址赋予默认值
    PIE_enable(myPie);                                      //使能PIE
}


void SystemINT_start(void)      //User PIE start
{
	// （8）。 Enable Global Interrupts
	    CPU_enableGlobalInts(myCpu);      //允许CPU全局中断
}
//===========================================================================
// End of file.
//===========================================================================
