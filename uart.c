void ioinit (void)
{
    //1 = output, 0 = input
    DDRB = 0xFF  ^ (1 << 6);//0b11101111; //PB4 = MISO
    DDRC = 0xFF;//0b11111111; //
    DDRD = 0xFF  ^ (1 << 0);//0b11111110; //PORTD (RX on PD0)

    //USART Baud rate: 9600
    UBRRH = MYUBRR >> 8;
    UBRRL = MYUBRR;
    UCSRB = (1<<RXEN)|(1<<TXEN);
    UCSRC = (1<<URSEL)|(3<<UCSZ0);
}

static int uart_putchar(char c)
{
//    if (c == '\n') uart_putchar('\r', stream);
 
    loop_until_bit_is_set(UCSRA, UDRE);
    UDR = c;
   
    return 0;
}

uint8_t uart_getchar(void)
{
    while( !(UCSRA & (1<<RXC)) );
    return(UDR);
}
