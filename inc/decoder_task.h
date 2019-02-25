/*
 * TODO:
 * - Czasami odczytuje samo z siebie (mo¿liwe, ¿e jakieœ zak³ócenia) iloœc bitów = 1 albo 2.
 * - Dekoder AbaTrack II
 */

#ifndef DECODER_TASK_H_
#define DECODER_TASK_H_

#include <lcd_task.h>
#include <stdlib.h>
#include "uart_task.h"

#include "stm32f1xx.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"


#define PIN_DATA_0 GPIO_PIN_1 //Pin wiegand data 0
#define PIN_DATA_1 GPIO_PIN_2 //Pin wiegand data 1
#define MAX_WIEGAND_BIT_TIME 20 //Maksymalny czas w milisekundach miêdzy wysy³anymi przez wiegand bitami.

xSemaphoreHandle xSemaphoreCardReadUART; //Semafor dla taska osb³uguj¹cego uart,czy karta zosta³a odczytana
xSemaphoreHandle xSemaphoreCardReadLCD; //Semafor dla taska osb³uguj¹cego lcd, czy karta zosta³a odczytana

xQueueHandle xQueueCardStructUART; //Kolejka dla taska osb³uguj¹cego uart na strukturê danych
xQueueHandle xQueueCardStructLCD; //Kolejka dla taska osb³uguj¹cego lcd na strukturê danych

struct Card {
	uint8_t read; //Stan odczytu karty, 0 - brak aktywnoœci (domyœlnie), 1 - karta odczytana
	char bites[255]; // Tablica na dekodowane bity
	uint8_t bitesQnt; //Liczba odebranych bitów
	char standard[10]; //Zmienna okreœlaj¹ca nazwê standardu Wiegand
	uint32_t inum; //Numer instalacji
	uint32_t unum; //Numer u¿ytkownika
} card;

void vTaskDecoder(void *pvParameters); //W³aœciwy task
uint8_t decodeWiegand(); //Funkcja dekoduj¹ca przypuszczalny numer instalacji oraz numer u¿ytkownika na podstawie iloœci odebranych bitów
void decodeWiegandFields(uint8_t inumStart, uint8_t inumLength, uint8_t unumStart, uint8_t unumLength); //Funkcja dekoduj¹ca konkretne pola Wieganda
/*
  * Funkcja zliczaj¹ca bity parzystoœci - UWAGA: parityXType to
  * dope³nienie z X strony (lewa i prawa, obs³uga tylko dwóch bitów),
  * 0 oznacza dope³nienie do parzystej iloœci jedynek, 1 nieparzyst¹.
  * Laft = pierwszy bit parzystoœci po lewej stronie,
  * Right = lewy bit parzystoœci po prawej stronie.
 */
uint8_t verifyWiegandParity (uint8_t parityLeftType, uint8_t parityLeftStart, uint8_t parityLeftEnd,
		uint8_t parityRightType, uint8_t parityRightStart, uint8_t parityRightEnd);
uint32_t strBinToInt (char* strBin); //Funkcja zmieniaj¹ca binarny ci¹g znakowy na int
void readWiegand(void); //Funkcja odczytuj¹ca biti z linii wieganda.
void cardClear(); //Zerowanie struktury karty

#endif /* DECODER_TASK_H_ */
