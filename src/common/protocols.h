#include <stdint.h>
#include <string.h>
#include "config.h"

#ifndef MSSY_GATEWAY_PROTOCOLS_H
#define MSSY_GATEWAY_PROTOCOLS_H

#define COMMAND_CONNECT 128
#define COMMAND_DISCONNECT 64
#define COMMAND_DISCOVERY_REQUEST 32
#define COMMAND_DISCOVERY_RESPONSE 16
#define COMMAND_READ_REQUEST 8
#define COMMAND_WRITE 4
#define COMMAND_READ_RESPONSE 2
#define COMMAND_DESCRIPTION_REQUEST 1
#define COMMAND_DESCRIPTION_RESPONSE 3

#define DEVICE_TYPE_KEYBOARD 255
#define DEVICE_TYPE_OLED 128
#define DEVICE_TYPE_MAGNETIC_CONTACT 64
#define DEVICE_TYPE_RELAY 32
#define DEVICE_TYPE_THERMO_REGULATOR 16
#define DEVICE_TYPE_TEMP 10
#define DEVICE_TYPE_PRESSURE 8
#define DEVICE_TYPE_HUMIDITY 6
#define DEVICE_TYPE_MOTOR 4
#define DEVICE_TYPE_SLEEP 2
#define DEVICE_TYPE_TIMER 1

struct command_header_t {
    uint8_t command_id;
    size_t len;
};

#define COMMAND_DATA_BUFFER APP_BUFFER_SIZE - sizeof(struct command_header_t)

struct command_t {
    struct command_header_t header;
    uint8_t data[COMMAND_DATA_BUFFER];
};

struct device_header_t {
    uint8_t device_type;
    uint8_t r_w;
    uint8_t device_id;
    uint8_t len;
};

#define DEVICE_DATA_BUFFER COMMAND_DATA_BUFFER - sizeof(struct device_header_t)

struct device_t {
    struct device_header_t header;
    uint8_t data[DEVICE_DATA_BUFFER];
};

union command_packet_t {
    struct command_t command;
    uint8_t bytes[sizeof(struct command_t)];
};

union device_packet_t {
    struct device_t device;
    uint8_t bytes[sizeof(struct device_t)];
};

uint8_t create_command_packet(void *packet_buffer, uint8_t command, void *data, uint8_t size);

uint8_t create_device_packet(void *packet_buffer, struct device_header_t header, void *data, uint8_t size);

#endif //PROJEKT2_COMMAND_CONTEXT_H
