
/*
 * main.c
 */

#define TARGET_GLOBAL 1

#include "User_Component/User_Device.h"
#include "Application\app.h"

void main(void)
{
    //1. configure
	System_config();
	LED_GPIO_config();
	//KEY_config();
	myTimer_config();
	//LED_PWM_config();
	//myAdc_config();
	//mySCI_config();
	OLED_config();
	mySCI_config();


	//2. initial
	System_initial();
	LED_GPIO_initial();
	//KEY_initial();
	myTimer_initial();
	//LED_PWM_initial();
	//myAdc_initial();
	//mySCI_initial();
	OLED_initial();
	mySCI_initial();

	//3. Interrupt configure and initial (if use interrupt)
	//KEY_INT_config();
	myTimer_INT_config();
	//LED_PWM_INT_config();
	//myAdc_INT_config();
	mySCI_TXINT_config();
	mySCI_RXINT_config();

	//4. the global interrupt start (if use interrupt)
    SystemINT_start();

	//5. main LOOP
	SciReceivedOk = false;
	SciSentOk = true;
    for( ; ; )
    {
    	// call API from app.h
    	//LED_Control();
    	//LED_KEY_Control();
    	//SCI_Test1();
    	DisplayTimer();
    	SCI_ExchageData();

    }


}

