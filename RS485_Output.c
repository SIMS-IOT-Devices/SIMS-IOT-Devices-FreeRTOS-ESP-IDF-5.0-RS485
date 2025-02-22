// Transmitting one character via RS485 ("A" = 01000001 and "A"+parity bit = 010000010)
// Using 9600 bit rate and UART_NUM_2

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

static const int RX_BUF_SIZE = 1024;

#define UART_2_TX 17
#define UART_2_RX 16

#define pin15 15
// #define pin2  2

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
    uart_driver_install(UART_NUM_2, RX_BUF_SIZE * 2, 0, 0, NULL, 0);
}

static void tx_task()
{
    int txBytes = 0;
    char *data = "A";
    int len = strlen(data);

    while (1)
    {
        txBytes = uart_write_bytes(UART_NUM_2, data, len);
        printf("uart_write_bytes reply - %d\n", txBytes);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    
    esp_rom_gpio_pad_select_gpio(pin15);            // GPIO to DE pin on MAX485
    gpio_set_direction(pin15, GPIO_MODE_OUTPUT);    
    gpio_set_level(pin15, 1);

    // esp_rom_gpio_pad_select_gpio(pin2);            // GPIO to RE pin on MAX485
    // gpio_set_direction(pin2, GPIO_MODE_OUTPUT);    
    // gpio_set_level(pin2, 1);

    printf("Send data:\n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    init();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    xTaskCreate(tx_task, "uart_tx_task", 1024 * 2, NULL, configMAX_PRIORITIES - 1, NULL);

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(10000));  // Sleep for 10 second
        printf("Main is running...\n");
    }
}