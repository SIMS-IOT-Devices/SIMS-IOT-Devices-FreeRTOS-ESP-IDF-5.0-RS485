// PC1 Transmitting string by using 9600 UART bit rate and UART_NUM_2

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

// Send a UART message
static void tx_task()
{
    int tx_bytes = 0;
    char *tx_data = "Hello from PC1\0"; // String to be send
    int tx_length = strlen(tx_data);

    while (1)
    {
        // Transmit string
        printf("Transmit data: %s\n", tx_data);
        tx_bytes = uart_write_bytes(UART_NUM_2, tx_data, tx_length); // Number of transmited bytes (-1 is an error)
        printf("Transmited bytes: %d\n\n", tx_bytes);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    // GPIO to DE pin on MAX485
    esp_rom_gpio_pad_select_gpio(pin15);            
    gpio_set_direction(pin15, GPIO_MODE_OUTPUT);    
    gpio_set_level(pin15, 1); // Transmit data

    init();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    xTaskCreate(tx_task, "uart_tx_task", 1024 * 2, NULL, configMAX_PRIORITIES - 1, NULL);

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(10000));  // Sleep for 10 second
        printf("Main is running...\n\n");
    }
}
