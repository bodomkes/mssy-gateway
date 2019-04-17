#include "protocols.h"

void create_command_packet(void *packet_buffer, uint8_t command, void *data, uint8_t size) {
    struct command_header_t header = {
            command,
            size
    };

    struct command_t message = {
            .header = header
    };
    memcpy(message.data, data, size);

    union command_packet_t packet = {
            .command = message
    };
    memcpy(packet_buffer, packet.bytes, sizeof(header) + size);
}

void create_device_packet(void *packet_buffer, struct device_header_t header, void *data, uint8_t size) {
    header.len = size;

    struct device_t device = {
            .header = header
    };
    memcpy(device.data, data, size);

    union device_packet_t packet = {
            .device = device
    };
    memcpy(packet_buffer, packet.bytes, sizeof(header) + size);
}
