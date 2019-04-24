#include "uart.h"

extern volatile uint8_t uart_int;

volatile uint8_t buffer[UART_BUFFER_LEN];
volatile uint8_t buffer_pos;

static void handle_interrupt();

ISR(USART1_RX_vect) {
        handle_interrupt();
}


void uart_init(uint16_t baud) {
    uint16_t ubrr = F_CPU / 16 / baud - 1;

    UBRR1H = (uint8_t)(ubrr >> 8);
    UBRR1L = (uint8_t) ubrr;

    UCSR1B = (1 << RXEN1) | (1 << TXEN1) | (1 << RXCIE1);

    UCSR1C = (3 << UCSZ10);

    buffer_pos = 0;
}

void uart_send(char byte) {
    while (bit_is_clear(UCSR1A, UDRE1));

    UDR1 = byte;
}


static char uart_recv() {
    while (bit_is_clear(UCSR1A, RXC1));

    return UDR1;
}

void uart_send_string(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        uart_send(str[i]);
    }
}

static void uart_cli() {
    cbi(UCSR1B, RXCIE1);
}

static void uart_sei() {
    sbi(UCSR1B, RXCIE1);
}

size_t uart_recv_string(char *tmp) {
    if (uart_int) {
        // Guard the memory copy with disabled interrupt
        uart_cli();

        memcpy((void *) tmp, (void *) buffer, UART_BUFFER_LEN);

        // Clear everything before next iteration
        uart_int = 0;
        buffer_pos = 0;
        memset((void *) buffer, 0, UART_BUFFER_LEN);

        uart_sei();

        return UART_BUFFER_LEN;
    }
    return 0;
}

static void handle_interrupt() {
    char tmp = uart_recv();
    if (buffer_pos == UART_BUFFER_LEN - 1 || tmp == '\n' || tmp == '\r') {
        // Insert terminating char
        buffer[UART_BUFFER_LEN - 1] = '\0';
        uart_int = 1;
    } else {
        buffer[buffer_pos++] = tmp;
        uart_send(tmp);
    }
}

int read_and_convert() {
	while (uart_int != 1);
	char buffer[UART_BUFFER_LEN];
	memset((void *) buffer, 0, UART_BUFFER_LEN);
	uart_recv_string((void *) buffer);

	return atoi(buffer);
}
