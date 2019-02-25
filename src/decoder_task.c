#include "decoder_task.h"

uint32_t strBinToInt (char* strBin) {
	uint32_t result = 0;
	uint32_t p2 = 1;

    for (int c = strlen(strBin) - 1;c >= 0;c--) {
        if (strBin[c] == '1') {
            result += p2;
        }
        p2 *= 2;
    }

    return result;
}

void cardClear() {
	card.read = 0;
	for (int i = 0; i <= sizeof(card.bites); i++) {
		card.bites[i] = 0;
	}
	card.bitesQnt = 0; //Liczba odebranych bitów
	for (int i = 0; i <= sizeof(card.standard); i++) {
		card.standard[i] = 0;
	}
	strcpy(card.standard,"Nieznany");
	card.inum = 0; //Inum;
	card.unum = 0; //Unum
}

uint8_t verifyWiegandParity (uint8_t parityLeftType, uint8_t parityLeftStart, uint8_t parityLeftEnd, uint8_t parityRightType, uint8_t parityRightStart, uint8_t parityRightEnd) {
	uint8_t parityLeftBit = 0;
	if (card.bites[0] == '0')
	{
		parityLeftBit = 0;
	}
	else {
		parityLeftBit = 1;
	}

	uint8_t parityRightBit = 0;
	if (card.bites[36] == '0') {
		parityRightBit = 0;
	}
	else {
		parityRightBit = 1;
	}

	uint8_t parityLeftCount = 0;
	uint8_t parityRightCount = 0;
	//Zliczanie bitów dodatnich
	for (uint8_t i = parityLeftStart; i <= parityRightEnd; i++) {
		if (card.bites[i] == '1' && i >= parityLeftStart && i <= parityLeftEnd) {
			parityLeftCount++;
		}
		if (card.bites[i] == '1' && i >= parityRightStart && i <= parityRightEnd) {
			parityRightCount++;
		}
	}
	/*
	* Jeœli
	* parzystoœæ zliczonych bitow po lewej razem z lewym bitem parzystoœci = typ parzystoœci lewej strony
	* oraz
	* parzystoœæ zliczonych bitow po prawej razem z prawym bitem parzystoœci = typ parzystoœci prawej strony
	* to parzystoœæ jest zgodna.
	*/
	if (((parityLeftCount + parityLeftBit) % 2 == parityLeftType) && ((parityRightCount + parityRightBit) % 2 == parityRightType)) {
		return 1;
	}
	else {
		return 0;
	}
}

void decodeWiegandFields(uint8_t inumStart, uint8_t inumLength, uint8_t unumStart, uint8_t unumLength) {
	if (inumLength != 0) {
		char strInum[inumLength];
		memcpy(strInum, &card.bites[inumStart], inumLength);
		strInum[inumLength] = '\0';
		card.inum = strBinToInt(&strInum[0]);
	}
	else {
		card.inum = 0;
	}

	if (unumLength != 0) {
		char strUnum[unumLength];
		memcpy(strUnum, &card.bites[unumStart], unumLength);
		strUnum[unumLength] = '\0';
		card.unum = strBinToInt(&strUnum[0]);
	}
	else {
		card.unum = 0;
	}
}


uint8_t decodeWiegand() {
	switch (card.bitesQnt) {
		case 26: { //Wiegand 26 z numerem instalacji
			if (verifyWiegandParity(0, 1, 12, 1, 13, 24)) {
				decodeWiegandFields(1, 8, 9, 16);
				strcpy(card.standard, "H10301");
			}
		break;
		}
		
		default: {
			strcpy(card.standard,"Nieznany");
			card.inum = 0;
			card.unum = 0;
		break;
		}
	}
	return 1;
}

uint32_t interruptTime = 0;
uint32_t osTime = 0;
//Obs³uga przerwania od DATA 0 i DATA 1
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	//readWiegand();
	interruptTime = HAL_GetTick();

	if (GPIO_Pin == PIN_DATA_0) {
		card.bites[card.bitesQnt] = '0';
		card.bitesQnt++;
	}

	if (GPIO_Pin == PIN_DATA_1) {
		card.bites[card.bitesQnt] = '1';
		card.bitesQnt++;
	}
}

void vTaskDecoder(void *pvParameters) {
	//Ustawianie czasów
	interruptTime = HAL_GetTick();
	osTime = HAL_GetTick();

	//Uchwyty na semafory
	xSemaphoreCardReadUART = xSemaphoreCreateBinary();
	xSemaphoreCardReadLCD = xSemaphoreCreateBinary();

	//Uchwyty na kolejki
	xQueueCardStructUART = xQueueCreate(1, sizeof(card));
	xQueueCardStructLCD = xQueueCreate(1, sizeof(card));

	for (;;) {
		vTaskDelay(1); //Minimalnie opóŸnienie dla synchronizacji interruptTime i osTime.
		osTime = HAL_GetTick();
		if (abs(osTime - interruptTime) > MAX_WIEGAND_BIT_TIME && interruptTime > 0) {
			//Zerowanie czasów
			interruptTime = 0;
			osTime = 0;

			//Dekodowanie Wieganda
			decodeWiegand();

			//Ustawianie semafora dla UART i LCD
			xSemaphoreGive(xSemaphoreCardReadUART);
			xSemaphoreGive(xSemaphoreCardReadLCD);

			//Wysy³anie kolejki z danymi odczytu do UART i LCD
			xQueueSend(xQueueCardStructUART, (void *) &card, (portTickType) 10);
			xQueueSend(xQueueCardStructLCD, (void *) &card, (portTickType) 10);

			cardClear();
		}
	}
}
