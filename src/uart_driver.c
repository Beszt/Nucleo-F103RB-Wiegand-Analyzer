#include "uart_driver.h"

void uartConfig(void) {
	//Konfiguracja UART który jest podpiêty po konwerter UART<->USB w Nucleo
	uart.Instance = USART2;
	uart.Init.BaudRate = 115200;
	uart.Init.WordLength = UART_WORDLENGTH_8B;
	uart.Init.Parity = UART_PARITY_NONE;
	uart.Init.StopBits = UART_STOPBITS_1;
	uart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uart.Init.OverSampling = UART_OVERSAMPLING_16;
	uart.Init.Mode = UART_MODE_TX_RX;
	HAL_UART_Init(&uart);
}

void uartSendString(char* s) {
	HAL_UART_Transmit(&uart, (uint8_t*) s, strlen(s), 1000);
}

void uartSendInt(uint32_t d) {
	char itoaBuffer[10];
	itoa(d,&itoaBuffer[0],10);
	HAL_UART_Transmit(&uart, (uint8_t*) &itoaBuffer[0], strlen(&itoaBuffer[0]), 1000);
}
