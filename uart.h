#define FOSC 8000000L
#define BAUD 9600L
#define MYUBRR (FOSC/(16*BAUD))-1

void ioinit(void);
static int uart_putchar(char c);
uint8_t uart_getchar(void);

#include "uart.c"
