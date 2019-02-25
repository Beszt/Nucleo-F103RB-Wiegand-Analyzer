#include "lcd_driver.h"

static uint8_t lcdBuffer[LCD_BUFFER_SIZE];

void lcdConfig(void) {
	//Konfiguracja wyœwietlacza pod SPI
	spi.Instance = SPI1;
	spi.Init.Mode = SPI_MODE_MASTER;
	spi.Init.NSS = SPI_NSS_SOFT;
	spi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16; // 4MHz
	spi.Init.Direction = SPI_DIRECTION_2LINES;
	spi.Init.CLKPhase = SPI_PHASE_2EDGE;
	spi.Init.CLKPolarity = SPI_POLARITY_HIGH;
	spi.Init.DataSize = SPI_DATASIZE_8BIT;
	spi.Init.FirstBit = SPI_FIRSTBIT_MSB;
	spi.Init.TIMode = SPI_TIMODE_DISABLE;
	spi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	spi.Init.CRCPolynomial = 7;
	HAL_SPI_Init(&spi);
	__HAL_SPI_ENABLE(&spi);
}

void lcdInit(void) {
	lcdReset();

	lcdSendCmd(PCD8544_FUNCTION_SET | 1);
	lcdSendCmd(PCD8544_H_BIAS | 4);
	lcdSendCmd(PCD8544_H_VOP | 0x30); //Ustawienie kontrastu
	lcdSendCmd(PCD8544_FUNCTION_SET);
	lcdSendCmd(PCD8544_DISP_NORMAL);
}

void lcdReset(void) {
	HAL_GPIO_WritePin(GPIOC, LCD_RST, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, LCD_RST, GPIO_PIN_SET);
}

void lcdClear(void) {
	memset(lcdBuffer, 0, LCD_BUFFER_SIZE);
	lcdCopy();
}

void lcdCopy(void) {
	HAL_GPIO_WritePin(GPIOC, LCD_DC, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, LCD_CS, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&spi, lcdBuffer, LCD_BUFFER_SIZE, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(GPIOC, LCD_CS, GPIO_PIN_SET);
}

void lcdSendCmd(uint8_t cmd) {
	HAL_GPIO_WritePin(GPIOC, LCD_CS | LCD_DC, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&spi, &cmd, 1, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(GPIOC, LCD_CS | LCD_DC, GPIO_PIN_SET);
}

void lcdSendData(const uint8_t* data, int size) {
	HAL_GPIO_WritePin(GPIOC, LCD_DC, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, LCD_CS, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&spi, (uint8_t*) data, size, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(GPIOC, LCD_CS, GPIO_PIN_SET);
}

void lcdDrawBitmap(const uint8_t* data) {
	memcpy(lcdBuffer, data, LCD_BUFFER_SIZE);
	lcdCopy();
}

void lcdDrawText(int row, int col, const char* text) {
	int i;
	uint8_t* pbuf = &lcdBuffer[row * 84 + col];
	while ((*text) && (pbuf < &lcdBuffer[LCD_BUFFER_SIZE - 6])) {
		int ch = *text++;
		const uint8_t* font = &font_ASCII[ch - ' '][0];
		for (i = 0; i < 5; i++) {
			*pbuf++ = *font++;
		}
		*pbuf++ = 0;
	}
	lcdCopy();
}

void lcdDrawInt(int row, int col, uint32_t d) {
	char itoaBuffer[10];
	itoa(d,&itoaBuffer[0],10);
	lcdDrawText(row, col, &itoaBuffer[0]);
}
