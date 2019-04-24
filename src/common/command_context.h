#include <stdint.h>
#include <string.h>
#include <stdio.h>

#ifndef MSSY_GATEWAY_COMMAND_CONTEXT_H
#define MSSY_GATEWAY_COMMAND_CONTEXT_H

#define COMMAND_LEN 6 // This has to be increased with every command in array!

#define CONTEXT_NORMAL 1

void decode_command(char *cmd);

void switch_context(uint8_t ctx);

#endif //MSSY_GATEWAY_COMMAND_CONTEXT_H
