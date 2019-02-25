/*
 * LCD_5110_driver.h
 *
 *  Created on: 03.02.2019
 *      Author: Macie
 */

#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_

#include <string.h>
#include <stdlib.h>

#include "stm32f1xx.h"
#include "FreeRTOS.h"
#include "lcd_font.h"


SPI_HandleTypeDef spi; //Uchwyt na wyœwietlacz LCD

#define LCD_DC			GPIO_PIN_1
#define LCD_CS			GPIO_PIN_2
#define LCD_RST			GPIO_PIN_3

#define LCD_BUFFER_SIZE			(84 * 48 / 8)

#define PCD8544_FUNCTION_SET		0x20
#define PCD8544_DISP_CONTROL		0x08
#define PCD8544_DISP_NORMAL			0x0c
#define PCD8544_SET_Y				0x40
#define PCD8544_SET_X				0x80
#define PCD8544_H_TC				0x04
#define PCD8544_H_BIAS				0x10
#define PCD8544_H_VOP				0x80

void lcdConfig(void); //Konfiguracja interfejsu SPI
void lcdInit(void); //Inizjalizacja wyœwietlacza
void lcdReset(void);
void lcdCopy(void); //Kopiuje zawartoœc bufora z uC do LCD
void lcdClear(void);
void lcdSendCmd(uint8_t cmd); //Wysy³anie komendy
void lcdSendData(const uint8_t* data, int size); //Wysy³anie danych
void lcdDrawBitmap(const uint8_t* data);
void lcdDrawText(int row, int col, const char* text);
void lcdDrawInt(int row, int col, uint32_t d);


#endif /* LCD_DRIVER_H_ */
