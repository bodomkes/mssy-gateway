#include "protocols.h"

uint8_t create_command_packet(void *packet_buffer, uint8_t command, void *data, uint8_t size) {
    struct command_header_t header = {
            command,
            size
    };

    struct command_t message = {
            .header = header
    };

    if (size > 0) {
        memcpy(message.data, data, size);
    }

    union command_packet_t packet = {
            .command = message
    };
    uint8_t buffer_len = sizeof(header) + size;
    memcpy(packet_buffer, packet.bytes, buffer_len);

    return buffer_len;
}

uint8_t create_device_packet(void *packet_buffer, struct device_header_t header, void *data, uint8_t size) {
    header.len = size;

    struct device_t device = {
            .header = header
    };
    if (size > 0) {
        memcpy(device.data, data, size);
    }

    union device_packet_t packet = {
            .device = device
    };
    uint8_t buffer_len = sizeof(header) + size;
    memcpy(packet_buffer, packet.bytes, buffer_len);

    return buffer_len;
}
