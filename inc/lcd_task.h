/*
 * TODO:
 * - Zmienic obs³ugê problemu z drgaj¹cym przyciskiem - póki co jest to zrobione na vTaskDelay().
 * - Wyœwietlanie bajtów w HEX. Dodatkowy tryb na wyœwietlaczu oraz informacja przez UART.
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
