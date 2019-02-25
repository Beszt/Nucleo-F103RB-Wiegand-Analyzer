/*
 * TODO:
 * - Czasami odczytuje samo z siebie (mo�liwe, �e jakie� zak��cenia) ilo�c bit�w = 1 albo 2.
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
#define MAX_WIEGAND_BIT_TIME 20 //Maksymalny czas w milisekundach mi�dzy wysy�anymi przez wiegand bitami.

xSemaphoreHandle xSemaphoreCardReadUART; //Semafor dla taska osb�uguj�cego uart,czy karta zosta�a odczytana
xSemaphoreHandle xSemaphoreCardReadLCD; //Semafor dla taska osb�uguj�cego lcd, czy karta zosta�a odczytana

xQueueHandle xQueueCardStructUART; //Kolejka dla taska osb�uguj�cego uart na struktur� danych
xQueueHandle xQueueCardStructLCD; //Kolejka dla taska osb�uguj�cego lcd na struktur� danych

struct Card {
	uint8_t read; //Stan odczytu karty, 0 - brak aktywno�ci (domy�lnie), 1 - karta odczytana
	char bites[255]; // Tablica na dekodowane bity
	uint8_t bitesQnt; //Liczba odebranych bit�w
	char standard[10]; //Zmienna okre�laj�ca nazw� standardu Wiegand
	uint32_t inum; //Numer instalacji
	uint32_t unum; //Numer u�ytkownika
} card;

void vTaskDecoder(void *pvParameters); //W�a�ciwy task
uint8_t decodeWiegand(); //Funkcja dekoduj�ca przypuszczalny numer instalacji oraz numer u�ytkownika na podstawie ilo�ci odebranych bit�w
void decodeWiegandFields(uint8_t inumStart, uint8_t inumLength, uint8_t unumStart, uint8_t unumLength); //Funkcja dekoduj�ca konkretne pola Wieganda
/*
  * Funkcja zliczaj�ca bity parzysto�ci - UWAGA: parityXType to
  * dope�nienie z X strony (lewa i prawa, obs�uga tylko dw�ch bit�w),
  * 0 oznacza dope�nienie do parzystej ilo�ci jedynek, 1 nieparzyst�.
  * Laft = pierwszy bit parzysto�ci po lewej stronie,
  * Right = lewy bit parzysto�ci po prawej stronie.
 */
uint8_t verifyWiegandParity (uint8_t parityLeftType, uint8_t parityLeftStart, uint8_t parityLeftEnd,
		uint8_t parityRightType, uint8_t parityRightStart, uint8_t parityRightEnd);
uint32_t strBinToInt (char* strBin); //Funkcja zmieniaj�ca binarny ci�g znakowy na int
void readWiegand(void); //Funkcja odczytuj�ca biti z linii wieganda.
void cardClear(); //Zerowanie struktury karty

#endif /* DECODER_TASK_H_ */
