/* vim: set ai et ts=4 sw=4: */
#ifndef __ILI9341_H__
#define __ILI9341_H__

#include "stm32f4xx_hal.h"
#include "fonts.h"
#include <stdbool.h>

/** 
 * Memory Data Access Control Register (0x36H)
 * MAP:     D7  D6  D5  D4  D3  D2  D1  D0 
 * param:   MY  MX  MV  ML  RGB MH  -   -
 * 
 */ 

#define ILI9341_MADCTL_MY  0x80
#define ILI9341_MADCTL_MX  0x40
#define ILI9341_MADCTL_MV  0x20
#define ILI9341_MADCTL_ML  0x10
#define ILI9341_MADCTL_RGB 0x00
#define ILI9341_MADCTL_BGR 0x08
#define ILI9341_MADCTL_MH  0x04

/*** Redefine if necessary ***/
#define ILI9341_SPI_PORT hspi2
extern SPI_HandleTypeDef ILI9341_SPI_PORT;

#define ILI9341_RES_Pin       GPIO_PIN_12
#define ILI9341_RES_GPIO_Port GPIOB
#define ILI9341_CS_Pin        GPIO_PIN_15
#define ILI9341_CS_GPIO_Port  GPIOB
#define ILI9341_DC_Pin        GPIO_PIN_14
#define ILI9341_DC_GPIO_Port  GPIOB
#define ILI9341_BLK_Pin       GPIO_PIN_15
#define ILI9341_BLK_GPIO_Port GPIOE

#define ILI9341_RST_PORT 	ILI9341_RES_GPIO_Port
#define ILI9341_RST_PIN 	ILI9341_RES_Pin
#define ILI9341_DC_PORT 	ILI9341_DC_GPIO_Port
#define ILI9341_DC_PIN 		ILI9341_DC_Pin
#define ILI9341_CS_PORT 	ILI9341_CS_GPIO_Port
#define ILI9341_CS_PIN 		ILI9341_CS_Pin
#define ILI9341_BLK_PORT 	ILI9341_BLK_GPIO_Port
#define ILI9341_BLK_PIN 	ILI9341_BLK_Pin

/* Basic operations */
#define ILI9341_RST_Clr() 	HAL_GPIO_WritePin(ILI9341_RST_PORT, ILI9341_RST_PIN, GPIO_PIN_RESET)
#define ILI9341_RST_Set() 	HAL_GPIO_WritePin(ILI9341_RST_PORT, ILI9341_RST_PIN, GPIO_PIN_SET)

#define ILI9341_DC_Clr() 	HAL_GPIO_WritePin(ILI9341_DC_PORT, ILI9341_DC_PIN, GPIO_PIN_RESET)
#define ILI9341_DC_Set() 	HAL_GPIO_WritePin(ILI9341_DC_PORT, ILI9341_DC_PIN, GPIO_PIN_SET)

#define ILI9341_Select() 	HAL_GPIO_WritePin(ILI9341_CS_PORT, ILI9341_CS_PIN, GPIO_PIN_RESET)
#define ILI9341_UnSelect() 	HAL_GPIO_WritePin(ILI9341_CS_PORT, ILI9341_CS_PIN, GPIO_PIN_SET)

#define ILI9341_Blk_Off() 	HAL_GPIO_WritePin(ILI9341_BLK_PORT, ILI9341_BLK_PIN, GPIO_PIN_RESET)
#define ILI9341_Blk_On() 	HAL_GPIO_WritePin(ILI9341_BLK_PORT, ILI9341_BLK_PIN, GPIO_PIN_SET)

#define ABS(x) ((x) > 0 ? (x) : -(x))

// default orientation
#define ILI9341_WIDTH  240
#define ILI9341_HEIGHT 320
#define ILI9341_ROTATION (ILI9341_MADCTL_MX | ILI9341_MADCTL_BGR)

// rotate right
/*
#define ILI9341_WIDTH  320
#define ILI9341_HEIGHT 240
#define ILI9341_ROTATION (ILI9341_MADCTL_MX | ILI9341_MADCTL_MY | ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR)
*/

// rotate left
/*
#define ILI9341_WIDTH  320
#define ILI9341_HEIGHT 240
#define ILI9341_ROTATION (ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR)
*/

// upside down
/*
#define ILI9341_WIDTH  240
#define ILI9341_HEIGHT 320
#define ILI9341_ROTATION (ILI9341_MADCTL_MY | ILI9341_MADCTL_BGR)
*/

/****************************/

// Color definitions
#define ILI9341_WHITE 			0xFFFF
#define ILI9341_BLACK 			0x0000
#define ILI9341_BLUE 			0x001F
#define ILI9341_RED 			0xF800
#define ILI9341_MAGENTA 		0xF81F
#define ILI9341_GREEN 			0x07E0
#define ILI9341_CYAN 			0x7FFF
#define ILI9341_YELLOW 			0xFFE0
#define ILI9341_GRAY 			0X8430
#define ILI9341_BRED 			0XF81F
#define ILI9341_GRED 			0XFFE0
#define ILI9341_GBLUE 			0X07FF
#define ILI9341_BROWN 			0XBC40
#define ILI9341_BRRED 			0XFC07
#define ILI9341_DARKBLUE 		0X01CF
#define ILI9341_LIGHTBLUE 		0X7D7C
#define ILI9341_GRAYBLUE 		0X5458

#define ILI9341_LIGHTGREEN 		0X841F
#define ILI9341_LGRAY 			0XC618
#define ILI9341_LGRAYBLUE 		0XA651
#define ILI9341_LBBLUE 			0X2B12

//#define	ILI9341_BLACK   0x0000
//#define	ILI9341_BLUE    0x001F
//#define	ILI9341_RED     0xF800
//#define	ILI9341_GREEN   0x07E0
//#define ILI9341_CYAN    0x07FF
//#define ILI9341_MAGENTA 0xF81F
//#define ILI9341_YELLOW  0xFFE0
//#define ILI9341_WHITE   0xFFFF
#define ILI9341_COLOR565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))

// call before initializing any SPI devices
//void ILI9341_Blk_On(void);
//void ILI9341_Blk_Off(void);
//void ILI9341_Unselect(void);

/* Basic functions. */
void ILI9341_Init(void);
void ILI9341_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
void ILI9341_DrawPixel_4px(uint16_t x, uint16_t y, uint16_t color);
void ILI9341_Fill_Color(uint16_t color);
void ILI9341_Fill(uint16_t xSta, uint16_t ySta, uint16_t xEnd, uint16_t yEnd, uint16_t color);

/* Graphical functions. */
void ILI9341_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void ILI9341_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void ILI9341_DrawCircle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color);
void ILI9341_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t *data);
void ILI9341_InvertColors(bool invert);

/* Text functions. */
void ILI9341_WriteChar(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor);
void ILI9341_WriteString(uint16_t x, uint16_t y, const char *str, FontDef font, uint16_t color, uint16_t bgcolor);

/* Extented Graphical functions. */
void ILI9341_DrawFilledRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void ILI9341_DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t color);
void ILI9341_DrawFilledTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t color);
void ILI9341_DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

/* Command functions */
void ILI9341_TearEffect(uint8_t tear);

/* Simple test function. */
void ILI9341_Test(void);

#endif // __ILI9341_H__
