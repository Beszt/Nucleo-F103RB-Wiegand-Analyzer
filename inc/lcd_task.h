/*
 * TODO:
 * - Zmienic obs�ug� problemu z drgaj�cym przyciskiem - p�ki co jest to zrobione na vTaskDelay().
 * - Wy�wietlanie bajt�w w HEX. Dodatkowy tryb na wy�wietlaczu oraz informacja przez UART.
 */

#ifndef LCD_TASK_H_
#define LCD_TASK_H_

#include "decoder_task.h"
#include "lcd_driver.h"
#include "stm32f1xx.h"
#include "FreeRTOS.h"
#include "task.h"

#define LCD_MODES_QNT 2
#define LCD_MODE_DEFAULT 1

void vTaskLCD(void *pvParameters);

#endif /* LCD_TASK_H_ */
