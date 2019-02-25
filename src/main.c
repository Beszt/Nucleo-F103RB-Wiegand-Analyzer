#include "decoder_task.h"
#include "lcd_task.h"
#include "uart_task.h"
#include "clock_config.h"
#include "stm32f1xx.h"

#include "FreeRTOS.h"
#include "task.h"

void prvSetupHardware() {

	HAL_Init();

	//Konfiguracja RCC dla 64mhz
	SystemClock_Config();
	HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_SYSCLK, RCC_MCODIV_1);
	//SystemCoreClock = 8000000;

	//Obs³uga przerwañ dla odczytu karty
	HAL_NVIC_SetPriority(EXTI1_IRQn, 1, 0);
	HAL_NVIC_SetPriority(EXTI2_IRQn, 1, 0);
	HAL_NVIC_EnableIRQ(EXTI1_IRQn);
	HAL_NVIC_EnableIRQ(EXTI2_IRQn);

	//W³¹czanie odpowiednich portów
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_SPI1_CLK_ENABLE();

	//Konfiguracja pinów GPIO
	GPIO_InitTypeDef gpio;

	//Konfiguracja UART TX
	gpio.Mode = GPIO_MODE_AF_PP;
	gpio.Pin = GPIO_PIN_2;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &gpio);

	//Konfiguracja UART RX
	gpio.Mode = GPIO_MODE_AF_INPUT;
	gpio.Pin = GPIO_PIN_3;
	HAL_GPIO_Init(GPIOA, &gpio);

	//Konfiguracja wyœwietlacza na SPI
	gpio.Mode = GPIO_MODE_AF_PP;
	gpio.Pin = GPIO_PIN_5 | GPIO_PIN_7; // SCK, MOSI
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &gpio);

	gpio.Mode = GPIO_MODE_AF_INPUT;
	gpio.Pin = GPIO_PIN_6; // MISO - nie u¿ywane
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &gpio);

	gpio.Mode = GPIO_MODE_OUTPUT_PP;
	gpio.Pin = GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3; // DC, CS, RST
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOC, &gpio);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_SET);

	//Konfiguiracja przycisku u¿ytkownika
	gpio.Pin = GPIO_PIN_13;
	gpio.Mode = GPIO_MODE_INPUT;
	gpio.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOC, &gpio);

	//DATA / DATA 0
	gpio.Pin = GPIO_PIN_1;
	gpio.Mode = GPIO_MODE_IT_FALLING;
	gpio.Pull = GPIO_PULLUP;
	gpio.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &gpio);

	//CLOCK / DATA 1
	gpio.Pin = GPIO_PIN_2;
	gpio.Mode = GPIO_MODE_IT_FALLING;
	gpio.Pull = GPIO_PULLUP;
	gpio.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &gpio);
}

int main(void) {
	//Inicjalizacja sprzêtu
	prvSetupHardware();

	//Tworzenie zadania do interpretacji odebranych bitów
	xTaskCreate(vTaskDecoder, (const portCHAR *) "Decoder", 128, NULL, 1, NULL);

	//Tworzenie zadania do obs³ugi UART
	xTaskCreate(vTaskUART, (const portCHAR *) "UART", 128, NULL, 1, NULL);

	//Tworzenie zadania do obs³ugi wyœwietlacza LCD
	xTaskCreate(vTaskLCD, (const portCHAR *) "LCD", 128, NULL, 1, NULL);

	//W³aœciwy start FreeRTOS
	vTaskStartScheduler();

	//Jesli wszystko dzia³a ok, funkcja main nigdy nie zwróci wartoœci
	return 0;
}
