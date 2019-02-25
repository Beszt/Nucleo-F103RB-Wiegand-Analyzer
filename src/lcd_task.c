#include "lcd_task.h"

const uint8_t unicardLogo [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x80, 0x40, 0x40, 0x20, 0x20, 0x40, 0x40, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18,
0x18, 0x18, 0x18, 0xB8, 0xB2, 0x71, 0x60, 0xE0, 0xC0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01,
0x02, 0x02, 0x04, 0x84, 0xC8, 0xC8, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00,
0x00, 0xF8, 0x38, 0xE0, 0x80, 0xF8, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0xF0, 0x18, 0x08, 0x08,
0x18, 0x10, 0x00, 0x80, 0xE0, 0xB8, 0xB8, 0xE0, 0x80, 0x00, 0x00, 0xF8, 0x48, 0x48, 0xC8, 0x78,
0x00, 0x00, 0x00, 0xF8, 0x08, 0x08, 0x18, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1B, 0x3B, 0x37, 0x77, 0xEE, 0xED, 0xDD, 0xDB, 0xBB,
0x77, 0x76, 0xEE, 0xEC, 0xEC, 0x6E, 0xB7, 0xBB, 0xDD, 0xEE, 0x60, 0x60, 0x60, 0x61, 0x63, 0x62,
0x63, 0x61, 0x60, 0x60, 0x60, 0x63, 0x60, 0x60, 0x61, 0x63, 0x60, 0x60, 0x60, 0x63, 0x60, 0x60,
0x61, 0x63, 0x62, 0x62, 0x63, 0x61, 0x60, 0x63, 0x61, 0x60, 0x60, 0x61, 0x63, 0x60, 0x60, 0x63,
0x60, 0x60, 0x61, 0x63, 0x62, 0x60, 0x60, 0x63, 0x62, 0x62, 0x63, 0x61, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x01, 0x01, 0x03, 0x03, 0x07, 0x06, 0x0E, 0x0E, 0x07, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

void vTaskLCD(void *pvParameters) {
	lcdConfig();
	lcdInit();

	lcdDrawBitmap(&unicardLogo[0]);
	vTaskDelay(2000);
	lcdClear();

	struct Card rQueueCard; // Struktura na odebrane dane od dekodera
	rQueueCard.bitesQnt = 0;

	uint8_t lcdSelectedMode = LCD_MODE_DEFAULT;

	for (;;) {
		//Odebranie kolejki
		if (xSemaphoreTake(xSemaphoreCardReadLCD, 0)) {
			xQueueReceive(xQueueCardStructLCD, &rQueueCard, (portTickType) 10);
			lcdClear();
		}

		//Zliczanie tryb�w
		if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET) {
			vTaskDelay(200); //Od�wie�anie do 100 takt�w systemu - prowizorka na drgaj�cy przycisk
			lcdSelectedMode++;
			lcdClear();
			if (lcdSelectedMode > LCD_MODES_QNT) {
				lcdSelectedMode = LCD_MODE_DEFAULT;
			}
		}

		if (rQueueCard.bitesQnt != 0) {
			switch (lcdSelectedMode) { //Obs�uga tryb�w kt�re zmienia wbudowany przycisk u�ytkownika

				case 1: { //Domy�lny, najpotrzebniejsze informacje
					lcdDrawText(0, 0, "Przeczytano!");
					lcdDrawText(1, 0, "Typ: ");
					lcdDrawText(1, 29, rQueueCard.standard);
					lcdDrawText(2, 0, "INUM: ");
					lcdDrawInt(2, 34, rQueueCard.inum);
					lcdDrawText(3, 0, "UNUM: ");
					lcdDrawInt(3, 34, rQueueCard.unum);
					lcdDrawText(4, 0, "Ile bitow: ");
					lcdDrawInt(4, 64, rQueueCard.bitesQnt); //Czemu nie 59?
					lcdDrawText(5, 0, "Wiecej: ->o<-");
					break;
				}

				case 2: { //Wy�wietlanie Poszczeg�lnych bit�w
					lcdDrawText(0, 0, "Bity:");
					lcdDrawText(1, 0, &rQueueCard.bites[0]);
					break;

					default:
						lcdSelectedMode = LCD_MODE_DEFAULT;
					break;
				}
			}
		}
	}
}
