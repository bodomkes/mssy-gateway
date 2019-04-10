#ifndef MSSY_GATEWAY_CONFIG_H
#define MSSY_GATEWAY_CONFIG_H

#define APP_BUFFER_SIZE     (NWK_MAX_PAYLOAD_SIZE - NWK_SECURITY_MIC_SIZE)

// Address must be set to 0 for the first device, and to 1 for the second one.
#define APP_ADDR                  0
#define APP_PANID                 0x4567
#define APP_ENDPOINT_0            0
#define APP_ENDPOINT_1            1
#define APP_ENDPOINT_2            2
#define APP_ENDPOINT_3            3
#define APP_ENDPOINT_4            4
#define APP_ENDPOINT_5            5
#define APP_ENDPOINT_6            6
#define APP_ENDPOINT_7            7
#define APP_ENDPOINT_8            8
#define APP_ENDPOINT_9            9
#define APP_ENDPOINT_10           10
#define APP_ENDPOINT_11           11
#define APP_ENDPOINT_12           12

#define APP_CHANNEL               0x0f

#define NWK_BUFFERS_AMOUNT                  3
#define NWK_DUPLICATE_REJECTION_TABLE_SIZE  10
#define NWK_DUPLICATE_REJECTION_TTL         3000 // ms
#define NWK_ROUTE_TABLE_SIZE                100
#define NWK_ROUTE_DEFAULT_SCORE             3
#define NWK_ACK_WAIT_TIME                   1000 // ms

#define NWK_ENABLE_ROUTING


#endif // MSSY_GATEWAY_CONFIG_H
