#ifndef MSSY_GATEWAY_COMMON_H
#define MSSY_GATEWAY_COMMON_H

#define sbi(port, bit) (port |= (1<<bit))
#define cbi(port, bit) (port &= ~(1<<bit))
#define tbi(port, bit) (port ^= (1<<bit))

#endif //MSSY_GATEWAY_COMMON_H
