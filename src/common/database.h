#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "protocols.h"

#ifndef MSSY_GATEWAY_DATABASE_H
#define MSSY_GATEWAY_DATABASE_H

#define ENDPOINT_COUNT 13
#define DEVICE_COUNT 10

#define SUCCESS 0
#define ERR_NOT_FOUND -1
#define ERR_DB_FULL -2
#define ERR_ENDPOINT_EXISTS -3

void init_database();

int8_t add_endpoint(uint8_t endpoint);

void print_endpoints();

void print_devices(uint8_t endpoint);

int8_t index_of(uint8_t endpoint);

void store_devices(uint8_t endpoint, void *devices, size_t len);

void remove_endpoint(uint8_t endpoint);

#endif //MSSY_GATEWAY_DATABASE_H
