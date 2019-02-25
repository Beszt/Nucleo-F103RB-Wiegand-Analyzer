/*
 * uart_driver.h
 *
 *  Created on: 07.02.2019
 *      Author: maciej.obarzanek
 */

#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_

#include <string.h>
#include <stdlib.h>

#include "stm32f1xx.h"

UART_HandleTypeDef uart; //Uchwyt na UART

void uartConfig(void);
void uartSendString(char* s); //Funkcja wysy�aj�ca ci�g testowy do UART
void uartSendInt(uint32_t d); //Funkcja wysy�aj�ca liczb� ca�kowit� do UART

#endif /* UART_DRIVER_H_ */
