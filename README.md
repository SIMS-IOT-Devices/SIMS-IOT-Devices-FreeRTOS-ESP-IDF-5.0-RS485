Video 1 - ESP32 sends a UART message to the scope<br>
RS485_Output.c: - ESP32 sends a UART message to the MAX485 board. The MAX485 board converts the message to an RS485 message, which is measured by scope.<br><br>

Video 2 - The message is sent by the following connection ESP32 -> MAX485 -> MAX485 -> ESP32 <br>
ESP32toESP32_Transmit.c - PC1 transmitting a RS485 message from ESP32 to ESP32 by using a UART <br>
ESP32toESP32_Receive.c - PC2 receiving a RS485 message from ESP32 to ESP32 by using a UART <br>

Video 3 - The message is sent by the following connection ESP32 -> MAX485 -> Converter -> PC <br>
RS485_from_ESP32_to_Converter.c - ESP32 transmitting a UART to MAX485 <br>
RS485_from_Converter_to_PC.py - PC receiving a RS485 message from the Converter connected via USB <br>
