#include <stdint.h>
#include <stdlib.h>
#include "protocols.h"

#ifndef MSSY_GATEWAY_DATABASE_H
#define MSSY_GATEWAY_DATABASE_H

#define ENDPOINT_COUNT 13
#define DEVICE_COUNT 10

#define SUCCESS 0
#define ERR_ENDPOINT_EXISTS 1
#define ERR_DB_FULL 2

void init_database();

uint8_t add_endpoint(uint8_t endpoint);

void print_devices();


#endif //MSSY_GATEWAY_DATABASE_H
