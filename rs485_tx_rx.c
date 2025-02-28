// PC2 Receiving data by RS485 from PC1

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/uart.h"
#include "soc/uart_struct.h"
#include "string.h"
#include <stdio.h>
#include "esp_event.h"
#include "driver/gpio.h"
#include "esp_rom_gpio.h"

static const int BUF_SIZE = 1024;

#define UART_2_TX 17
#define UART_2_RX 16
#define pin15 15

// UART communication definition
void init()
{
    const uart_config_t uart_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE, // 0
        .stop_bits = UART_STOP_BITS_1,
        .source_clk = UART_SCLK_APB, // APB Clock
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE};
    uart_param_config(UART_NUM_2, &uart_config);
    uart_set_pin(UART_NUM_2, UART_2_TX, UART_2_RX, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(UART_NUM_2, BUF_SIZE * 2, 0, 0, NULL, 0);
}

// Receive a UART message
static void tx_task()
{
    int rx_length = 0;
    uint8_t rx_data[BUF_SIZE];

    while (1)
    {
        rx_length = uart_read_bytes(UART_NUM_2, rx_data, BUF_SIZE, 100);
        if (rx_length > 0)
        {
            rx_data[rx_length] = '\0';
            printf("Received data: %.*s\n\n", rx_length, rx_data);
        }
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    // GPIO to DE pin on MAX485
    esp_rom_gpio_pad_select_gpio(pin15);            
    gpio_set_direction(pin15, GPIO_MODE_OUTPUT);    
    gpio_set_level(pin15, 0); // 0 - Receive data

    init();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    xTaskCreate(tx_task, "uart_tx_task", 4096, NULL, configMAX_PRIORITIES - 1, NULL);

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(10000));  // Sleep for 10 second
        printf("Main is running...\n");
    }
}