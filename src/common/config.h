#ifndef _CONFIG_H_
#define _CONFIG_H_

// Address must be set to 0 for the first device, and to 1 for the second one.
#define APP_ADDR                  0
#define APP_PANID                 0x4567
#define APP_ENDPOINT              13

#define APP_CHANNEL             0x0f


#define HAL_UART_CHANNEL          1
#define HAL_UART_RX_FIFO_SIZE     200
#define HAL_UART_TX_FIFO_SIZE     200


#define NWK_BUFFERS_AMOUNT                  3
#define NWK_DUPLICATE_REJECTION_TABLE_SIZE  10
#define NWK_DUPLICATE_REJECTION_TTL         3000 // ms
#define NWK_ROUTE_TABLE_SIZE                100
#define NWK_ROUTE_DEFAULT_SCORE             3
#define NWK_ACK_WAIT_TIME                   1000 // ms

#define NWK_ENABLE_ROUTING


#endif // _CONFIG_H_
