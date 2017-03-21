//#############################################################################
//
//! \file
//!
//! \brief
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
#include "User_Component/Oled/Oled.h"
#include "User_Component/Oled/Font.h"

// **************************************************************************
// the defines


// **************************************************************************
// the globals


// **************************************************************************
// the functions

// the function prototypes
//! \brief     OLED initail
//! \param[in] None
//! \param[out] None
void OLED_initial(void)
{
	uint16_t i,j;
	for(i=0; i<64; i++)
		for(j=0;j<8;j++)
		{
		   Image[i][j]=0x00;
		}
}
//
//! \brief     OLED configure
//! \param[in] None
//! \param[out] None
void OLED_config(void)
{
	// 1. set mode
	//void GPIO_setMode(GPIO_Handle gpioHandle,const GPIO_Number_e gpioNumber,const GPIO_Mode_e mode);
	GPIO_setMode(OLED_obj, OLED_SCL, GPIO_0_Mode_GeneralPurpose);
	GPIO_setMode(OLED_obj, OLED_SDA, GPIO_0_Mode_GeneralPurpose);
	GPIO_setMode(OLED_obj, OLED_RST, GPIO_0_Mode_GeneralPurpose);
	GPIO_setMode(OLED_obj, OLED_DC, GPIO_0_Mode_GeneralPurpose);
	// 2. set pullup
	//void GPIO_setPullUp(GPIO_Handle gpioHandle,const GPIO_Number_e gpioNumber,const GPIO_PullUp_e pullUp);
	GPIO_setPullUp(OLED_obj, OLED_SCL, GPIO_PullUp_Disable);
	GPIO_setPullUp(OLED_obj, OLED_SDA, GPIO_PullUp_Disable);
	GPIO_setPullUp(OLED_obj, OLED_RST, GPIO_PullUp_Disable);
	GPIO_setPullUp(OLED_obj, OLED_DC, GPIO_PullUp_Disable);
	//3. set direction
	//void GPIO_setDirection(GPIO_Handle gpioHandle,const GPIO_Number_e gpioNumber,const GPIO_Direction_e direction);
	GPIO_setDirection(OLED_obj, OLED_SCL, GPIO_Direction_Output);
	GPIO_setDirection(OLED_obj, OLED_SDA, GPIO_Direction_Output);
	GPIO_setDirection(OLED_obj, OLED_RST, GPIO_Direction_Output);
	GPIO_setDirection(OLED_obj, OLED_DC, GPIO_Direction_Output);
    //4. configure OLED
	OLED_setHigh(OLED_SCL);
	OLED_setLow(OLED_RST);
	OLED_delay(200);
	OLED_setHigh(OLED_RST);//从上电到下面开始初始化要有足够的时间，即等待RC复位完毕
	OLED_writeCommand(0xae);//--turn off oled panel
	OLED_writeCommand(0x00);//---set low column address
	OLED_writeCommand(0x10);//---set high column address
	OLED_writeCommand(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_writeCommand(0x81);//--set contrast control register
	OLED_writeCommand(0xcf); // Set SEG Output Current Brightness
	OLED_writeCommand(0xa1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_writeCommand(0xc8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_writeCommand(0xa6);//--set normal display
	OLED_writeCommand(0xa8);//--set multiplex ratio(1 to 64)
	OLED_writeCommand(0x3f);//--1/64 duty
	OLED_writeCommand(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_writeCommand(0x00);//-not offset
	OLED_writeCommand(0xd5);//--set display clock divide ratio/oscillator frequency
	OLED_writeCommand(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_writeCommand(0xd9);//--set pre-charge period
	OLED_writeCommand(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_writeCommand(0xda);//--set com pins hardware configuration
	OLED_writeCommand(0x12);
	OLED_writeCommand(0xdb);//--set vcomh
	OLED_writeCommand(0x40);//Set VCOM Deselect Level
	OLED_writeCommand(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_writeCommand(0x02);//
	OLED_writeCommand(0x8d);//--set Charge Pump enable/disable
	OLED_writeCommand(0x14);//--set(0x10) disable
	OLED_writeCommand(0xa4);// Disable Entire Display On (0xa4/0xa5)
	OLED_writeCommand(0xa6);// Disable Inverse Display On (0xa6/a7)
	OLED_writeCommand(0xaf);//--turn on oled panel
	OLED_fullShow(0x00);    //初始清屏
	OLED_setXY(0, 0);
}

//! \brief     OLED delay
//! \param[in] None
//! \param[out] None
void OLED_delay(uint16_t ms)
{
	while(ms--);
}

//! \brief     OLED write command
//! \param[in] None
//! \param[out] None
void OLED_writeCommand(uint16_t command)
{
	uint16_t i;
	OLED_setLow(OLED_DC);  //command
	for(i=0; i<8; i++) //发送一个八位数据
	{
		if((command << i) & 0x80)
			OLED_setHigh(OLED_SDA);
		else
			OLED_setLow(OLED_SDA);

		OLED_setLow(OLED_SCL);
		OLED_setHigh(OLED_SCL);
	}
}

//! \brief     OLED full show  ONE char
//! \param[in] None
//! \param[out] None
void OLED_fullShow(uint16_t bmp_dat)
{
	uint16_t y,x;
	for(y=0; y<8; y++)
	{
		OLED_writeCommand(0xb0+y);
		OLED_writeCommand(0x01);
		OLED_writeCommand(0x10);
		for(x=0; x<128; x++)
			OLED_writeData(bmp_dat);
	}
}

//! \brief     OLED write data
//! \param[in] None
//! \param[out] None
void OLED_writeData(uint16_t data)
{
	uint16_t i;
	OLED_setHigh(OLED_DC);  //data
	for(i=0; i<8; i++) //发送一个八位数据
	{
		if((data << i) & 0x80)
			OLED_setHigh(OLED_SDA);
		else
			OLED_setLow(OLED_SDA);
		OLED_setLow(OLED_SCL);
		OLED_setHigh(OLED_SCL);
	}
}

//! \brief     OLED set x and y
//! \param[in] None
//! \param[out] None
void OLED_setXY(uint16_t x, uint16_t y)
{
	OLED_writeCommand(0xB0+y);
	OLED_writeCommand(((x&0xF0)>>4)|0x10);
	OLED_writeCommand((x & 0x0F)|0x01);
}

//! \brief     OLED clear display
//! \param[in] None
//! \param[out] None
void OLED_clearDisp(void)
{
	OLED_fullShow(0);
}

//! \brief     显示8*16点阵,显示的坐标（x,y),y为页范围0～7
//! \param[in] None
//! \param[out] None
void OLED_show8x16(uint16_t x, uint16_t y, uint16_t N)
{
	uint16_t wm = 0;
	uint16_t addr = 16*N;  //
	OLED_setXY(x, y);
	for(wm=0; wm<8; wm++)  //
	 {
		OLED_writeData(show_8x16[addr]);
		addr += 1;
	 }
	OLED_setXY(x, y+1);
	for(wm=0; wm<8; wm++) //
	 {
		OLED_writeData(show_8x16[addr]);
		addr += 1;
	 }
}
//! \brief     显示16*16点阵,显示的坐标（x,y),y为页范围0～7
//! \param[in] None
//! \param[out] None
void OLED_show16x16(uint16_t x, uint16_t y, uint16_t N)
{
	uint16_t wm = 0;
	uint16_t addr = 32*N;  //
	OLED_setXY(x, y);
	for(wm=0; wm<16; wm++)  //
	 {
		OLED_writeData(show_16x16[addr]);
		addr += 1;
	 }
	OLED_setXY(x, y+1);
	for(wm = 0;wm < 16;wm++) //
	 {
		OLED_writeData(show_16x16[addr]);
		addr += 1;
	 }
}
//! \brief     显示8*8点阵,显示的坐标（x,y),y为页范围0～7
//! \param[in] None
//! \param[out] None
void OLED_showImage8x8(uint16_t x, uint16_t y, uint16_t N, uint16_t op)
{
	uint16_t wm = 0;
	uint16_t addr = 8*N;  //

	uint16_t x1,y1;
	uint16_t x1_1;
	if(0 == op)
	{   y1=y;
		for(wm=0; wm<8; wm++)  //
		 {
			x1 = x >> 1;
			x1_1 = x & 0x01;
		   	Image[y1][x1] |= ( (uint16_t)show_8x8[addr] << (x1_1*8));
            x += 1;
		   	addr += 1;
		 }
	}

}


//! \brief     显示8*16点阵,显示的坐标（x,y),y为页范围0～7
//! \param[in] None
//! \param[out] None
void OLED_showImage8x16(uint16_t x, uint16_t y, uint16_t N, uint16_t op)
{
	uint16_t wm = 0;
	uint16_t addr = 16*N;  //

	uint16_t x1,y1,x2=x;
	uint16_t x1_1;
	if(0 == op)
	{   y1=y;
		for(wm=0; wm<8; wm++)  //
		 {
			x1 = x >> 1;
			x1_1 = x & 0x01;
		   	Image[y1][x1] |= ( (uint16_t)show_8x16[addr] << (x1_1*8));
            x += 1;
		   	addr += 1;
		 }
		y1=y+1;
		x=x2;
		for(wm=0; wm<8; wm++) //
		 {
			x1 = x >> 1;
			x1_1 = x & 0x01;
		   	Image[y1][x1] |= ( (uint16_t)show_8x16[addr] << (x1_1*8));
		   	x += 1;
			addr += 1;
		 }
	}
}

//! \brief     显示16*16点阵,显示的坐标（x,y),y为页范围0～7
//! \param[in] None
//! \param[out] None
void OLED_showImage16x16(uint16_t x, uint16_t y, uint16_t N, uint16_t op)
{
	uint16_t wm = 0;
	uint16_t addr = 32*N;  //

	uint16_t x1,y1,x2=x;
	uint16_t x1_1;
	if(0 == op)
	{   y1=y;
	    for(wm=0; wm<16; wm++)  //
	    {
	    	x1 = x >> 1;
	    	x1_1 = x & 0x01;
	    	Image[y1][x1] |= ( (uint16_t)show_16x16[addr] << (x1_1*8));
	    	x += 1;
	    	addr += 1;
	    }
	    y1=y+1;
	    x=x2;
	    for(wm=0; wm<16; wm++) //
	    {
	    	x1 = x >> 1;
	    	x1_1 = x & 0x01;
	    	Image[y1][x1] |= ( (uint16_t)show_16x16[addr] << (x1_1*8));
	    	x += 1;
	    	addr += 1;
	    }
	}
}

//! \brief     画直线起始坐标(x,y),终点坐标（x1,y1)
//! \param[in] None
//! \param[out] None
void OLED_showLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t op)
{   int16_t dx=x2-x1;
	int16_t dy=y2-y1;
    int16_t ux=((dx>0) << 1) -1;
    int16_t uy=((dy>0) << 1) -1;
    int16_t x=x1,y=y1,eps=0;

    if(dx<0)
    	dx = -dx;

    if(dy<0)
    	dy = -dy;
    if(dx>dy)
    {
    	for(x=x1;x!=x2;x+=ux)
    	{
    	    OLED_showPixel(x,y,op);
    		eps += dy;
    		if((eps<<1)>=dx)
    		{
    			y += uy;
    			eps -= dx;
    		}
    	}
    }
    else
    {
    	for(y=y1;y!=y2;y+=uy)
    	{
    	    OLED_showPixel(x,y,op);
    		eps += dx;
    		if((eps<<1)>=dy)
    		{
    			x += ux;
    			eps -= dy;
    		}
    	}
    }
 }

//! \brief     在虚拟内存中画点坐标(x,y)
//! \param[in] None
//! \param[out] None
void OLED_showPixel(uint16_t x, uint16_t y, uint16_t op)
{   uint16_t x1,y1;
    uint16_t x1_1,y1_1;
    x1=x>>1;
    y1=y>>3;
    x1_1= x & 0x01;
    y1_1= y & 0x07;
    if(0 == op)
    {
    	Image[y1][x1] |= ( 1 << (x1_1*8 + y1_1) );
    }
}

//! \brief     清除虚拟内存
//! \param[in] None
//! \param[out] None
void OLED_clearImage(void)
{
	uint16_t i,j;
	for(i=0; i<8; i++)
		for(j=0;j<64;j++)
		{
		   Image[i][j]=0x0000;
		}

}

//! \brief     显示虚拟内存
//! \param[in] None
//! \param[out] None
void OLED_showImage(void)
{
	uint16_t wm, wn;
	uint16_t data;  //
	for(wn=0;wn<8;wn++)
	{
		OLED_setXY(0, wn);
		for(wm=0; wm<64; wm++)
		{   data = Image[wn][wm];
			OLED_writeData(data&0x00ff);
			data = data>>8;
			OLED_writeData(data&0x00ff);
		}

	 }

}

// end of file
