#include "database.h"

struct row_t {
    uint8_t app_endpoint;
    struct device_header_t devices[DEVICE_COUNT];
    uint8_t is_free;
};

struct row_t rows[DEVICE_COUNT];

void init_database() {
    for (int i = 0; i < DEVICE_COUNT; i++) {
        struct row_t row = {
                .is_free = 1
        };
        rows[i] = row;
    }
}

int8_t add_endpoint(uint8_t endpoint) {
    if (index_of(endpoint) != ERR_NOT_FOUND) {
        return ERR_ENDPOINT_EXISTS;
    }

    for (int i = 0; i < DEVICE_COUNT; i++) {
        if (rows[i].is_free) {
            struct row_t row = {
                    .app_endpoint = endpoint,
                    .is_free = 0
            };
            rows[i] = row;
            return SUCCESS;
        }
    }
    return ERR_DB_FULL;
}

void print_endpoints() {
    printf("-- Registered endpoints -- \n");
    for (int i = 0; i < DEVICE_COUNT; i++) {
        if (!rows[i].is_free) {
            printf("Device endpoint id: %d\n", rows[i].app_endpoint);
        }
    }
}

void remove_endpoint(uint8_t endpoint) {
    int8_t index = index_of(endpoint);

    if(index == ERR_NOT_FOUND) {
        return;
    }

    struct row_t row = {
            .is_free = 1
    };
    rows[index] = row;
}

int8_t index_of(uint8_t endpoint) {
    for (int i = 0; i < DEVICE_COUNT; i++) {
        if (!rows[i].is_free && rows[i].app_endpoint == endpoint) {
            return i;
        }
    }
    return ERR_NOT_FOUND;
}

void store_devices(uint8_t endpoint, void *devices, size_t len) {
    struct row_t *current = &rows[index_of(endpoint)];

    size_t header_len = sizeof(struct device_header_t);
    for (uint8_t i = 0; i < len; i += header_len) {
        uint8_t index = i / header_len;

        if (index == DEVICE_COUNT) {
            break;
        }

        union device_packet_t packet = {
                .bytes = {0}
        };
        memcpy(packet.bytes, devices + i, header_len);
        struct device_header_t header = packet.device.header;
        current->devices[index] = header;
        printf("Adding new device type: %d, R/W: %d, id: %d.\n", header.device_type, header.r_w, header.device_id);
    }
}

void print_devices(uint8_t endpoint) {
    struct row_t *current = &rows[index_of(endpoint)];

    printf("-- Stored devices -- \n");
    for (int i = 0; i < DEVICE_COUNT; i++) {
        struct device_header_t header = current->devices[i];
        if (!header.device_type) {
            break;
        }
        printf("Device index: %d, type: %d, R/W: %d, id: %d.\n", i, header.device_type, header.r_w, header.device_id);
    }
}
