/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : LCD1.h
**     Project     : FRDM-K64F_Adafruit_SSD1351
**     Processor   : MK64FN1M0VLL12
**     Component   : SSD1351
**     Version     : Component 01.037, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2018-07-26, 15:26, # CodeGen: 147
**     Abstract    :
**
Display driver for the SSD1351 (e.g. found on Hexiwear).
**     Settings    :
**          Component name                                 : LCD1
**          Type                                           : 128x128
**          Orientation                                    : portrait
**          Width                                          : 128
**          Height                                         : 128
**          Bytes in rows                                  : yes
**          Bytes in x direction                           : yes
**          MSB first                                      : no
**          Bits per pixel                                 : 16
**          Window capability                              : no
**          Display Memory Write                           : no
**          Display Memory Read                            : no
**          Use RAM Buffer                                 : yes
**          Clear display in init                          : no
**          Initialize on Init                             : no
**          HW                                             : 
**            HW SPI Delay (us)                            : 0
**            SW SPI                                       : Disabled
**            LDD HW SPI                                   : Enabled
**              HW SPI                                     : SM1
**            HW SPI                                       : Disabled
**            Slave Select                                 : Enabled
**              SCE                                        : SCE
**            Reset                                        : Enabled
**              Reset                                      : RES
**              D_C                                        : D_C
**            Power                                        : Disabled
**          System                                         : 
**            Wait                                         : WAIT1
**            SDK                                          : MCUC1
**     Contents    :
**         GetWidth              - LCD1_PixelDim LCD1_GetWidth(void);
**         GetHeight             - LCD1_PixelDim LCD1_GetHeight(void);
**         GetLongerSide         - LCD1_PixelDim LCD1_GetLongerSide(void);
**         GetShorterSide        - LCD1_PixelDim LCD1_GetShorterSide(void);
**         SetDisplayOrientation - void LCD1_SetDisplayOrientation(LCD1_DisplayOrientation newOrientation);
**         GetDisplayOrientation - LCD1_DisplayOrientation LCD1_GetDisplayOrientation(void);
**         WriteData             - void LCD1_WriteData(uint8_t data);
**         WriteDataWord         - void LCD1_WriteDataWord(uint16_t data);
**         WriteDataWordRepeated - void LCD1_WriteDataWordRepeated(uint16_t data, size_t nof);
**         WriteDataBlock        - void LCD1_WriteDataBlock(uint8_t *data, size_t dataSize);
**         WriteCommand          - void LCD1_WriteCommand(uint8_t cmd);
**         OpenWindow            - void LCD1_OpenWindow(LCD1_PixelDim x0, LCD1_PixelDim y0, LCD1_PixelDim x1,...
**         CloseWindow           - void LCD1_CloseWindow(void);
**         Clear                 - void LCD1_Clear(void);
**         UpdateFull            - void LCD1_UpdateFull(void);
**         UpdateRegion          - void LCD1_UpdateRegion(LCD1_PixelDim x, LCD1_PixelDim y, LCD1_PixelDim w,...
**         Init                  - void LCD1_Init(void);
**         InitCommChannel       - void LCD1_InitCommChannel(void);
**         GetLCD                - void LCD1_GetLCD(void);
**         GiveLCD               - void LCD1_GiveLCD(void);
**         OnDataReceived        - void LCD1_OnDataReceived(void);
**
** * Copyright (c) 2014-2017, Erich Styger
**  * Web:         https://mcuoneclipse.com
**  * SourceForge: https://sourceforge.net/projects/mcuoneclipse
**  * Git:         https://github.com/ErichStyger/McuOnEclipse_PEx
**  * All rights reserved.
**  *
**  * Redistribution and use in source and binary forms, with or without modification,
**  * are permitted provided that the following conditions are met:
**  *
**  * - Redistributions of source code must retain the above copyright notice, this list
**  *   of conditions and the following disclaimer.
**  *
**  * - Redistributions in binary form must reproduce the above copyright notice, this
**  *   list of conditions and the following disclaimer in the documentation and/or
**  *   other materials provided with the distribution.
**  *
**  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**  * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**  * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**  * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**  * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**  * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**  * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
** ###################################################################*/
/*!
** @file LCD1.h
** @version 01.00
** @brief
**
Display driver for the SSD1351 (e.g. found on Hexiwear).
*/         
/*!
**  @addtogroup LCD1_module LCD1 module documentation
**  @{
*/         

#ifndef __LCD1_H
#define __LCD1_H

/* MODULE LCD1. */

/* MODULE LCD1. */
#include "MCUC1.h" /* SDK and API used */
#include "LCD1config.h" /* configuration */
#include <stddef.h> /* for size_t */

/* Include inherited components */
#include LCD1_CONFIG_SPI_HEADER_FILE  /* SPI driver */
#include "SM1.h"
#include "SCEpin1.h"
#include "RESpin1.h"
#include "D_Cpin1.h"
#include "WAIT1.h"
#include "MCUC1.h"


#define LCD1_DISPLAY_HW_NOF_COLUMNS  128u /* number of columns in hardware */
#define LCD1_DISPLAY_HW_NOF_ROWS     128u /* number of rows in hardware */

typedef uint16_t LCD1_PixelColor;      /* type to hold color information */
typedef uint16_t LCD1_PixelDim;        /* one word is enough to describe an x/y position */
typedef uint32_t LCD1_PixelCount;      /* need a 32bit type to hold the number of pixels on the display. */

extern LCD1_PixelColor LCD1_DisplayBuf[LCD1_DISPLAY_HW_NOF_ROWS][LCD1_DISPLAY_HW_NOF_COLUMNS]; /* buffer for the display */

/* Predefined colors and pixel values. The display is using words for a pixel/color. Using 16bits for color (65k: 5:red + 6:green + 5:blue */
#if LCD1_CONFIG_USE_RAM_BUFFER  /* && is Little endian! */
  /* if using RAM buffer, we use an array of 16bit entries. Because for ARM, the data is little endian, we need to swap the bits */
  #define LCD1_COLOR_RED            0b0000000011111000
  #define LCD1_COLOR_BRIGHT_RED     0b1110001111111000
  #define LCD1_COLOR_DARK_RED       0b0000000010011000

  #define LCD1_COLOR_GREEN          0b1110000000000111
  #define LCD1_COLOR_DARK_GREEN     0b0110000000000011
  #define LCD1_COLOR_BRIGHT_GREEN   0b1111001110011111

  #define LCD1_COLOR_BLUE           0b0001111100000000
  #define LCD1_COLOR_BRIGHT_BLUE    0b1101111111011110
  #define LCD1_COLOR_DARK_BLUE      0b0001001100000000

  #define LCD1_COLOR_YELLOW         0b1110000011111111
  #define LCD1_COLOR_BRIGHT_YELLOW  0b1100110011111111
  #define LCD1_COLOR_ORANGE         0b1100011011111100

  #define LCD1_COLOR_WHITE          0b1111111111111111
  #define LCD1_COLOR_BLACK          0b0000000000000000
  #define LCD1_COLOR_GREY           0b1110011100111000
  #define LCD1_COLOR_BRIGHT_GREY    0b1110111101111011
#else
  #define LCD1_COLOR_RED            0b1111100000000000
  #define LCD1_COLOR_BRIGHT_RED     0b1111100011100011
  #define LCD1_COLOR_DARK_RED       0b1001100000000000

  #define LCD1_COLOR_GREEN          0b0000011111100000
  #define LCD1_COLOR_DARK_GREEN     0b0000001101100000
  #define LCD1_COLOR_BRIGHT_GREEN   0b1001111111110011

  #define LCD1_COLOR_BLUE           0b0000000000011111
  #define LCD1_COLOR_BRIGHT_BLUE    0b1101111011011111
  #define LCD1_COLOR_DARK_BLUE      0b0000000000010011

  #define LCD1_COLOR_YELLOW         0b1111111111100000
  #define LCD1_COLOR_BRIGHT_YELLOW  0b1111111111001100
  #define LCD1_COLOR_ORANGE         0b1111110011000110

  #define LCD1_COLOR_WHITE          0b1111111111111111
  #define LCD1_COLOR_BLACK          0b0000000000000000
  #define LCD1_COLOR_GREY           0b0011100011100111
  #define LCD1_COLOR_BRIGHT_GREY    0b0111101111101111
#endif

#define LCD1_PIXEL_ON  LCD1_COLOR_WHITE /* value of a pixel if it is 'on' */
#define LCD1_PIXEL_OFF LCD1_COLOR_BLACK /* value of a pixel if it is 'off' */

#define LCD1_WIDTH  128u                /* Logical display width in pixels */
#define LCD1_HEIGHT 128u                /* Logical display height in pixels */
#define LCD1_HW_WIDTH  LCD1_WIDTH       /* Hardware display width in pixels */
#define LCD1_HW_HEIGHT LCD1_HEIGHT      /* Hardware display height in pixels */
#define LCD1_HW_LONGER_SIDE  LCD1_WIDTH /* Hardware display longer side in pixels */
#define LCD1_HW_SHORTER_SIDE LCD1_HEIGHT /* Hardware display shorter side in pixels */

typedef enum {
  LCD1_ORIENTATION_PORTRAIT    = 0,
  LCD1_ORIENTATION_PORTRAIT180 = 1,
  LCD1_ORIENTATION_LANDSCAPE   = 2,
  LCD1_ORIENTATION_LANDSCAPE180= 3
} LCD1_DisplayOrientation;

#define LCD1_WritePixel(data)  \
  LCD1_WriteDataWord(data)

#define LCD1_ReadPixel(data)  \
  0 /* with the serial interface it is NOT possible to read from display memory */



void LCD1_Clear(void);
/*
** ===================================================================
**     Method      :  Clear (component SSD1351)
**
**     Description :
**         Clears the whole display memory.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void LCD1_Init(void);
/*
** ===================================================================
**     Method      :  Init (component SSD1351)
**
**     Description :
**         Display driver initialization
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void LCD1_UpdateFull(void);
/*
** ===================================================================
**     Method      :  UpdateFull (component SSD1351)
**
**     Description :
**         Updates the whole display. This is only a stub for this
**         display as we are using windowing.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/* implemented as macro
void LCD1_UpdateRegion(LCD1_PixelDim x, LCD1_PixelDim y, LCD1_PixelDim w, LCD1_PixelDim h);
*/
#define LCD1_UpdateRegion(x,y,w,h) /* nothing to do, as this display type does not require a refresh */
/*
** ===================================================================
**     Method      :  UpdateRegion (component SSD1351)
**
**     Description :
**         Updates a region of the display. This is only a stub for
**         this display as we are using windowing.
**     Parameters  :
**         NAME            - DESCRIPTION
**         x               - x coordinate
**         y               - y coordinate
**         w               - width of the region
**         h               - Height of the region
**     Returns     : Nothing
** ===================================================================
*/

void LCD1_OpenWindow(LCD1_PixelDim x0, LCD1_PixelDim y0, LCD1_PixelDim x1, LCD1_PixelDim y1);
/*
** ===================================================================
**     Method      :  OpenWindow (component SSD1351)
**
**     Description :
**         Opens a window inside the display we want to write to.
**     Parameters  :
**         NAME            - DESCRIPTION
**         x0              - 
**         y0              - 
**         x1              - 
**         y1              - 
**     Returns     : Nothing
** ===================================================================
*/

#define LCD1_CloseWindow()  /* nothing to do */

/*
** ===================================================================
**     Method      :  CloseWindow (component SSD1351)
**
**     Description :
**         Closes a window previously opened with OpenWindow()
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void LCD1_WriteData(uint8_t data);
/*
** ===================================================================
**     Method      :  WriteData (component SSD1351)
**
**     Description :
**         Writes a data byte to the bus
**     Parameters  :
**         NAME            - DESCRIPTION
**         data            - data byte to send
**     Returns     : Nothing
** ===================================================================
*/

LCD1_DisplayOrientation LCD1_GetDisplayOrientation(void);
/*
** ===================================================================
**     Method      :  GetDisplayOrientation (component SSD1351)
**
**     Description :
**         Returns the current display orientation
**     Parameters  : None
**     Returns     :
**         ---             - current display orientation
** ===================================================================
*/

void LCD1_SetDisplayOrientation(LCD1_DisplayOrientation newOrientation);
/*
** ===================================================================
**     Method      :  SetDisplayOrientation (component SSD1351)
**
**     Description :
**         Sets the display orienation. If you enable this method, then
**         the orientation of the display can be changed at runtime.
**         However, this requires additional ressources.
**     Parameters  :
**         NAME            - DESCRIPTION
**         newOrientation  - new orientation to
**                           be used
**     Returns     : Nothing
** ===================================================================
*/

#if LCD1_CONFIG_DYNAMIC_DISPLAY_ORIENTATION
  LCD1_PixelDim LCD1_GetWidth(void);
#elif LCD1_CONFIG_FIXED_DISPLAY_ORIENTATION==LCD1_CONFIG_ORIENTATION_PORTRAIT
  #define LCD1_GetWidth()    LCD1_HW_SHORTER_SIDE
#elif LCD1_CONFIG_FIXED_DISPLAY_ORIENTATION==LCD1_CONFIG_ORIENTATION_PORTRAIT180
  #define LCD1_GetWidth()    LCD1_HW_SHORTER_SIDE
#elif LCD1_CONFIG_FIXED_DISPLAY_ORIENTATION==LCD1_CONFIG_ORIENTATION_LANDSCAPE
  #define LCD1_GetWidth()    LCD1_HW_LONGER_SIDE
#elif LCD1_CONFIG_FIXED_DISPLAY_ORIENTATION==LCD1_CONFIG_ORIENTATION_LANDSCAPE180
  #define LCD1_GetWidth()    LCD1_HW_LONGER_SIDE
#endif
/*
** ===================================================================
**     Method      :  GetWidth (component SSD1351)
**
**     Description :
**         Returns the width of the display in pixels (in x direction)
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

#if LCD1_CONFIG_DYNAMIC_DISPLAY_ORIENTATION
  LCD1_PixelDim LCD1_GetHeight(void);
#elif LCD1_CONFIG_FIXED_DISPLAY_ORIENTATION==LCD1_CONFIG_ORIENTATION_PORTRAIT
  #define LCD1_GetHeight()    LCD1_HW_LONGER_SIDE
#elif LCD1_CONFIG_FIXED_DISPLAY_ORIENTATION==LCD1_CONFIG_ORIENTATION_PORTRAIT180
  #define LCD1_GetHeight()    LCD1_HW_LONGER_SIDE
#elif LCD1_CONFIG_FIXED_DISPLAY_ORIENTATION==LCD1_CONFIG_ORIENTATION_LANDSCAPE
  #define LCD1_GetHeight()    LCD1_HW_SHORTER_SIDE
#elif LCD1_CONFIG_FIXED_DISPLAY_ORIENTATION==LCD1_CONFIG_ORIENTATION_LANDSCAPE180
  #define LCD1_GetHeight()    LCD1_HW_SHORTER_SIDE
#endif
/*
** ===================================================================
**     Method      :  GetHeight (component SSD1351)
**
**     Description :
**         Returns the height of the display in pixels (in y direction)
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

#define LCD1_GetLongerSide() \
  LCD1_HW_LONGER_SIDE
/*
** ===================================================================
**     Method      :  GetLongerSide (component SSD1351)
**
**     Description :
**         Returns the size of the longer side of the display
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

#define LCD1_GetShorterSide() \
  LCD1_HW_SHORTER_SIDE
/*
** ===================================================================
**     Method      :  GetShorterSide (component SSD1351)
**
**     Description :
**         Returns the size of the shorter side of the display
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

void LCD1_WriteCommand(uint8_t cmd);
/*
** ===================================================================
**     Method      :  WriteCommand (component SSD1351)
**
**     Description :
**         Sends a command byte to the bus
**     Parameters  :
**         NAME            - DESCRIPTION
**         cmd             - the command to be sent
**     Returns     : Nothing
** ===================================================================
*/

void LCD1_WriteDataWord(uint16_t data);
/*
** ===================================================================
**     Method      :  WriteDataWord (component SSD1351)
**
**     Description :
**         Sends a data word to the display
**     Parameters  :
**         NAME            - DESCRIPTION
**         data            - data to write
**     Returns     : Nothing
** ===================================================================
*/

void LCD1_GetLCD(void);
/*
** ===================================================================
**     Method      :  GetLCD (component SSD1351)
**
**     Description :
**         Method to be called for mutual exclusive access to the LCD
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void LCD1_GiveLCD(void);
/*
** ===================================================================
**     Method      :  GiveLCD (component SSD1351)
**
**     Description :
**         Method to be called for mutual exclusive access to the LCD
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void LCD1_InitCommChannel(void);
/*
** ===================================================================
**     Method      :  InitCommChannel (component SSD1351)
**
**     Description :
**         Method to initialize communication to the LCD. Needed if the
**         bus to the LCD is shared with other components and settings
**         are different.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void LCD1_OnDataReceived(void);
/*
** ===================================================================
**     Method      :  OnDataReceived (component SSD1351)
**
**     Description :
**         callback to be called from SPI interrupt
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void LCD1_WriteDataBlock(uint8_t *data, size_t dataSize);
/*
** ===================================================================
**     Method      :  WriteDataBlock (component SSD1351)
**
**     Description :
**         Sends a data buffer to the display
**     Parameters  :
**         NAME            - DESCRIPTION
**       * data            - Pointer to data to write
**         dataSize        - 
**     Returns     : Nothing
** ===================================================================
*/

void LCD1_WriteDataWordRepeated(uint16_t data, size_t nof);
/*
** ===================================================================
**     Method      :  WriteDataWordRepeated (component SSD1351)
**
**     Description :
**         Sends a data word to the display a number of times
**     Parameters  :
**         NAME            - DESCRIPTION
**         data            - data to write
**         nof             - How many times the data word shall be sent
**     Returns     : Nothing
** ===================================================================
*/

/* END LCD1. */

#endif
/* ifndef __LCD1_H */
/*!
** @}
*/
