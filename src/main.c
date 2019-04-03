#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "config.h"
#include "hal.h"
#include "phy.h"
#include "sys.h"
#include "nwk.h"
#include "sysTimer.h"
#include "halBoard.h"
#include "halUart.h"

#define APP_BUFFER_SIZE     (NWK_MAX_PAYLOAD_SIZE - NWK_SECURITY_MIC_SIZE)

static void send_data(void *data, size_t length);
void print(char *str);
void println(char *str);

static NWK_DataReq_t appDataReq;
static uint8_t data_buffer[APP_BUFFER_SIZE];
static uint8_t buffer_position = 0;

static void data_confirmation(NWK_DataReq_t *req) {
	memset(data_buffer, 0, APP_BUFFER_SIZE);
	(void)req;
}

static void send_data(void *data, size_t length) {
	if (length == 0)
		return;

	memcpy(data_buffer, data, length);

	appDataReq.dstAddr = 1-APP_ADDR;
	appDataReq.dstEndpoint = APP_ENDPOINT;
	appDataReq.srcEndpoint = APP_ENDPOINT;
	appDataReq.options = NWK_OPT_ENABLE_SECURITY;
	appDataReq.data = data_buffer;
	appDataReq.size = length;
	appDataReq.confirm = data_confirmation;
	NWK_DataReq(&appDataReq);

	buffer_position = 0;
}

void HAL_UartBytesReceived(uint16_t bytes) {
	for (uint16_t i = 0; i < bytes; i++) {
		uint8_t byte = HAL_UartReadByte();
		HAL_UartWriteByte(byte);
	}
}

static bool data_received(NWK_DataInd_t *ind) {
	for (uint8_t i = 0; i < ind->size; i++)
		HAL_UartWriteByte(ind->data[i]);
	return true;
}

static void app_init(void) {
	NWK_SetAddr(APP_ADDR);
	NWK_SetPanId(APP_PANID);
	PHY_SetChannel(APP_CHANNEL);

	PHY_SetRxState(true);

	NWK_OpenEndpoint(APP_ENDPOINT, data_received);

	HAL_BoardInit();
}

static void task_handler(void) {
	
}

int main() {
	SYS_Init();
	HAL_UartInit(38400);
	app_init();

	while (1) {
		SYS_TaskHandler();
		HAL_UartTaskHandler();
		task_handler();
	}
}

void print(char *str) {
    // Do nothing
}

void println(char *str) {
    print(str);
    print("\r\n");
}
