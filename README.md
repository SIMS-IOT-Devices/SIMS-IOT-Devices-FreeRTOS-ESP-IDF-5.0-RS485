Video 1 - ESP32 sends a UART message to the scope<br>
RS485_Output.c: - ESP32 sends a UART message to the MAX485 board. The MAX485 board converts the message to an RS485 message, which is measured by scope.<br><br>

Video 2 - The message is sent by the following connection ESP32 -> MAX485 -> MAX485 -> ESP32 <br>
ESP32toESP32_Transmit.c - Transmit a RS485 message from ESP32 to ESP32 by using a UART <br>
ESP32toESP32_Receive.c - Recieve a RS485 message from ESP32 to ESP32 by using a UART <br>
