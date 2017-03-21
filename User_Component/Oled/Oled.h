
//#############################################################################
//
//! \file  User_Component/Oled/Oled.h
//!
//! \brief Oled
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


#ifndef _OLED_H_
#define _OLED_H_


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
//#define   EXAMPLE_obj   myGpio          //here myGpio is defined in System.h
//#define   EXAMPLE_PIN   GPIO_Number_??  //pin

#define   OLED_obj       myGpio           //here myGpio is defined in System.h
#define   OLED_SCL       GPIO_Number_16          //pin
#define   OLED_SDA       GPIO_Number_17          //pin
#define   OLED_RST       GPIO_Number_18          //pin
#define   OLED_DC        GPIO_Number_19          //pin


//
// the function prototypes
//! \brief     OLED initail
//! \param[in] None
//! \param[out] None
TARGET_EXT void OLED_initial(void);
//
//! \brief     OLED configure
//! \param[in] None
//! \param[out] None
TARGET_EXT void OLED_config(void);
//
/*******************************************/
//! \brief     Interrup configure
//! \param[in] None
//! \param[out] None
//TARGET_EXT void LED_PWM_INT_config(void);
//
//! \brief     Interrupt Service Routine
//! \param[in] None
//! \param[out] None
//TARGET_EXT interrupt void LED_EPWM1_isr(void);     //redefined in Isr.h
/*-------end of hardware description -------------*/


/*------- API description of the example module   -------------*/
// EXAMPLE API
// the function prototypes
//! \brief     EXAMPLE API
//! \param[in] None
//! \param[out] None
//TARGET_EXT void EXAMPLE_API(void);

//! \brief     OLED set high
//! \param[in] None
//! \param[out] None
#define OLED_setHigh(led)  GPIO_setHigh(OLED_obj, led)

//! \brief     OLED set low
//! \param[in] None
//! \param[out] None
#define OLED_setLow(led)   GPIO_setLow(OLED_obj, led)

//! \brief     OLED delay
//! \param[in] None
//! \param[out] None
TARGET_EXT void OLED_delay(uint16_t ms);

//! \brief     OLED write command
//! \param[in] None
//! \param[out] None
TARGET_EXT void OLED_writeCommand(uint16_t command);

//! \brief     OLED write data
//! \param[in] None
//! \param[out] None
TARGET_EXT void OLED_writeData(uint16_t data);

//! \brief     OLED set x and y
//! \param[in] None
//! \param[out] None
TARGET_EXT void OLED_setXY(uint16_t x, uint16_t y);

//! \brief     OLED clear display
//! \param[in] None
//! \param[out] None
TARGET_EXT void OLED_clearDisp(void);

//! \brief     OLED full show  ONE char
//! \param[in] None
//! \param[out] None
TARGET_EXT void OLED_fullShow(uint16_t bmp_dat);

//! \brief     ��ʾ8*16����,��ʾ�����꣨x,y),yΪҳ��Χ0��7
//! \param[in] None
//! \param[out] None
TARGET_EXT void OLED_show8x16(uint16_t x, uint16_t y, uint16_t N);

//! \brief     ��ʾ16*16����,��ʾ�����꣨x,y),yΪҳ��Χ0��7
//! \param[in] None
//! \param[out] None
TARGET_EXT void OLED_show16x16(uint16_t x, uint16_t y, uint16_t N);

//! \brief     ��ʾ8*8����,��ʾ�����꣨x,y),yΪҳ��Χ0��7
//! \param[in] None
//! \param[out] None
TARGET_EXT void OLED_showImage8x8(uint16_t x, uint16_t y, uint16_t N, uint16_t op);

//! \brief     ��ʾ8*16����,��ʾ�����꣨x,y),yΪҳ��Χ0��7
//! \param[in] None
//! \param[out] None
TARGET_EXT void OLED_showImage8x16(uint16_t x, uint16_t y, uint16_t N, uint16_t op);

//! \brief     ��ʾ16*16����,��ʾ�����꣨x,y),yΪҳ��Χ0��7
//! \param[in] None
//! \param[out] None
TARGET_EXT void OLED_showImage16x16(uint16_t x, uint16_t y, uint16_t N, uint16_t op);

//! \brief     ��ֱ����ʼ����(x,y),�յ����꣨x1,y1)
//! \param[in] None
//! \param[out] None
TARGET_EXT void OLED_showLine(uint16_t x, uint16_t y, uint16_t x1, uint16_t y1, uint16_t op);

//! \brief     �������ڴ��л�������(x,y)
//! \param[in] None
//! \param[out] None
TARGET_EXT void OLED_showPixel(uint16_t x, uint16_t y, uint16_t op);

//! \brief     ��������ڴ�
//! \param[in] None
//! \param[out] None
TARGET_EXT void OLED_clearImage(void);

//! \brief     ��ʾ�����ڴ�
//! \param[in] None
//! \param[out] None
TARGET_EXT void OLED_showImage(void);

/*-------end of API description -------------*/


/*------- Globals of the example module   -------------*/
// the globals

//! \brief Defines the Variable
//TARGET_EXT uint16_t  Example;
TARGET_EXT uint16_t  Image[8][64];



/*------- end of globals  -------------*/


/*------- Defines of the example module   -------------*/
// the defines

//! \brief Defines the constant
//#define EXAMPLE_DEF

/*------- end of defines  -------------*/



#ifdef __cplusplus
}
#endif // extern "C"


#endif  // end of _EXAMPLE_H_ definition

