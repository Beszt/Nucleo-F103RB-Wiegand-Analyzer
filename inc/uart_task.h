#ifndef UART_TASK_H_
#define UART_TASK_H_

#include "decoder_task.h"
#include "stm32f1xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "uart_driver.h"


void vTaskUART(void * pvParameters); //W�a�ciwiy task obs�uguj�cy komunikacj� przez UART

#endif /* UART_TASK_H_ */
