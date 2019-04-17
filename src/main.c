#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "config.h"
#include "hal.h"
#include "phy.h"
#include "sys.h"
#include "nwk.h"
#include "sysTimer.h"
#include "protocols.h"
#include "uart.h"
#include "database.h"

static void send_data(uint8_t app_endpoint, void *data, size_t length);

void handle_command(struct command_t *command, uint8_t endpoint);

int uart_putchar(char byte, FILE *stream);

void send_discovery_request(uint8_t endpoint);

static FILE mystdout = FDEV_SETUP_STREAM(&uart_putchar, NULL, _FDEV_SETUP_WRITE);

static NWK_DataReq_t appDataReq;
static uint8_t data_buffer[APP_BUFFER_SIZE];
static uint8_t buffer_position = 0;
uint8_t ready_to_send = 0;

char uart_buffer[UART_BUFFER_LEN];
volatile uint8_t uart_int = 0;

static void data_confirmation(NWK_DataReq_t *req) {
    memset(data_buffer, 0, APP_BUFFER_SIZE);
    ready_to_send = 1;
    (void) req;
}

static void send_data(uint8_t app_endpoint, void *data, size_t length) {
    if (length == 0 || ready_to_send == 0) {
        return;
    }

    memcpy(data_buffer, data, length);

    appDataReq.dstAddr = 1 - APP_ADDR;
    appDataReq.dstEndpoint = app_endpoint;
    appDataReq.srcEndpoint = app_endpoint;
    appDataReq.options = NWK_OPT_ENABLE_SECURITY;
    appDataReq.data = data_buffer;
    appDataReq.size = length;
    appDataReq.confirm = data_confirmation;
    NWK_DataReq(&appDataReq);

    buffer_position = 0;
    ready_to_send = 0;
}

static bool data_received(NWK_DataInd_t *ind) {
    union command_packet_t packet = {
            .bytes = {0}
    };

    memcpy(packet.bytes, ind->data, ind->size);
    handle_command(&packet.command, ind->srcEndpoint);
    return true;
}

void handle_command(struct command_t *command, uint8_t endpoint) {
    switch (command->header.command_id) {
        case COMMAND_CONNECT:
            if (add_endpoint(endpoint) != SUCCESS) {
                printf("Adding of endpoint %d has failed.\n", endpoint);
            } else {
                printf("New endpoint %d has been added.\n", endpoint);
                send_discovery_request(endpoint);
            }
            break;
        case COMMAND_DISCOVERY_RESPONSE:
            if (index_of(endpoint) != ERR_NOT_FOUND) {
                printf("Got discovery response from %d.\n", endpoint);
                store_devices(endpoint, command->data, command->header.len);
            } else {
                printf("Got discovery response from %d which is not in db!\n", endpoint);
            }
    }
}

void send_discovery_request(uint8_t endpoint) {
    uint8_t packet_buffer[APP_BUFFER_SIZE];

    uint8_t len = create_command_packet(packet_buffer, COMMAND_DISCOVERY_REQUEST, 0, 0);

    send_data(endpoint, packet_buffer, len);
    printf("Sending discovery to %d.\n", endpoint);
}

static void app_init(void) {
    NWK_SetAddr(APP_ADDR);
    NWK_SetPanId(APP_PANID);
    PHY_SetChannel(APP_CHANNEL);

    PHY_SetRxState(true);

    NWK_OpenEndpoint(APP_ENDPOINT_10, data_received);

    uart_init(38400);
    init_database();
    ready_to_send = 1;
}

static void task_handler(void) {
    if (uart_int) {
        memset((void *) uart_buffer, 0, UART_BUFFER_LEN);
        uart_recv_string((void *) uart_buffer);
    }
}

int main() {
    stdout = &mystdout;
    SYS_Init();
    app_init();

    while (1) {
        SYS_TaskHandler();
        task_handler();
    }
}

int uart_putchar(char byte, FILE *stream) {
    if (byte == '\n') {
        uart_send('\r');
    }
    uart_send(byte);

    return 0;
}
