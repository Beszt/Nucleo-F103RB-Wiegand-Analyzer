#include "uart_task.h"

void vTaskUART(void *pvParameters) {
	uartConfig();
	uartSendString("Analizator interfejsow czytnikow. Podepnij czytnik i przyloz karte.\r\n\r\n");

	struct Card rQueueCard;

	for (;;) {
		if (xSemaphoreTake(xSemaphoreCardReadUART, 0)) {
			xQueueReceive(xQueueCardStructUART, &rQueueCard, (portTickType) 10);

			uartSendString("Przeczytano karte!\r\nOdczytane bity: ");
			uartSendString(&rQueueCard.bites[0]);
			uartSendString("\r\n");
			uartSendString("Liczba bitow: ");
			uartSendInt(rQueueCard.bitesQnt);
  			uartSendString("\r\n");
  			uartSendString("Prawdopodobny standard: ");
  			uartSendString(&rQueueCard.standard[0]);
  			uartSendString("\r\n");
  			uartSendString("Prawdopodobny numer instalacji: ");
  			uartSendInt(rQueueCard.inum);
  			uartSendString("\r\n");
  			uartSendString("Prawdopodobny numer uzytkownika: ");
  			uartSendInt(rQueueCard.unum);
  			uartSendString("\r\n\r\n");
		}
	}
}
