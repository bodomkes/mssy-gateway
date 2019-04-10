#include <avr/sfr_defs.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <string.h>

#include "common.h"

#ifndef MSSY_GATEWAY_UART_H
#define MSSY_GATEWAY_UART_H

#define UART_BUFFER_LEN 50

void uart_init(uint16_t baud);

void uart_send(char byte);

void uart_send_string(char *str);

size_t uart_recv_string(char *tmp);

#endif //MSSY_GATEWAY_UART_H
