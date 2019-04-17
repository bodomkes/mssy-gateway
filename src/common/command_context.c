#include "command_context.h"

struct command_context {
    // By using 8 bit we can define up to 8 contexts
    uint8_t context;
    char *command_name;
    char *command_desc;

    void (*command)(void);
};

uint8_t context;

void print_menu();

void switch_context(uint8_t ctx);

// COMMAND DEFINITION BLOCK

// extern void board_init(); Example definition

struct command_context commands[COMMAND_LEN] = {
        //  {CONTEXT_NORMAL,  "0",     "Board Init",                 &board_init}  Example definition
};

// COMMAND DEFINITION BLOCK


void decode_command(char *cmd) {
    int8_t found = -1;
    for (int i = 0; i < COMMAND_LEN; i++) {
        struct command_context current = commands[i];
        if ((current.context & context) > 0 && strcmp(cmd, current.command_name) == 0) {
            found = 1;
            (*current.command)();
            break;
        }
    }
    if (found < 0) {
        printf("Invalid command!\n");
        print_menu();
    }

}

void print_menu() {
    printf("Menu:\n");
    for (int i = 0; i < COMMAND_LEN; i++) {
        struct command_context current = commands[i];
        if ((current.context & context) > 0) {
            printf("%s - %s", current.command_name, current.command_desc);
        }
    }
}

void switch_context(uint8_t ctx) {
    context = ctx;
    print_menu();
}
