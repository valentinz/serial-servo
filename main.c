#define F_CPU 16000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"

#define SERVO_PORT PORTC
#define SERVO_DDR DDRC
#define SERVO_COUNT 3 
#define COMMAND_LENGTH 40

volatile unsigned char servopos[SERVO_COUNT];

void servo_init() {
	SERVO_DDR  = 0xff;

	TIMSK |= (1<<OCIE2);
	TCCR2 |= (1<<WGM21) | (1<<CS20);	//Prescale=1, CTC mode
	OCR2 = F_CPU/100000;			//alle 10µS ein IRQ
};

ISR(TIMER2_COMP_vect) {
	static int count;
	int i;
	for (i = 0; i < SERVO_COUNT; i++) {
		if (count > servopos[i]) {
			SERVO_PORT &= ~(1<<i);
		} else {
			SERVO_PORT |= (1<<i);
		}
	}

	if (count < 2000) count++;
	else count=0;
};

void setServo(uint8_t servoId, uint8_t value) {
	servopos[0] = value;
	uart_putchar(value);
	uart_putchar(-value);
	uart_putchar(0);
}

void getServo(uint8_t servoId) {
	uint8_t value = servopos[servoId-1];
	uart_putchar(value);
	uart_putchar(-value);
	uart_putchar(0);
}

int main (void) {
	uint8_t i = 0;
	uint8_t j = 0;
	char read = 0;
	char command[COMMAND_LENGTH];
	uint8_t commandPosition = 0;
	uint8_t checksum = 0;

	for (i = 0; i < SERVO_COUNT; i++) {
		servopos[i] = 100;
	}

	sei();
	servo_init();
	ioinit();

	while (1) {
		read = uart_getchar();
		command[commandPosition] = read;
		checksum += read;

		if (read == 0) {
			if (checksum == 0) {
				// Handle command

				switch (command[0]) {
				case 0x01:
					setServo(command[1], command[2]);
					break;
				case 0x02:
					getServo(command[1]);
					break;
				}
			} else {
				// Command error
				uart_putchar(0xFF);
			}
			checksum = 0;
			commandPosition = 0;
		} else {
			commandPosition++;
		}
	}

	return 0;
}
