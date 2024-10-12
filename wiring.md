# MIDI Program Controller Wiring Description

This wiring description provides the details of the connections for the MIDI program controller using the following components:
- LOLIN D1 Mini (ESP8266-based microcontroller)
- Rotary Encoder
- Push Button
- OLED Display (SSD1306)
- MIDI Output Connector

## Components and Connections

### 1. LOLIN D1 Mini (ESP8266) Pins
| Component          | LOLIN D1 Mini Pin | Description                                  |
|--------------------|-------------------|----------------------------------------------|
| MIDI TX Pin        | D7 (GPIO 13)      | MIDI output for communication                |
| Rotary Encoder CLK | D5 (GPIO 14)      | Rotary encoder clock line                    |
| Rotary Encoder DT  | D6 (GPIO 12)      | Rotary encoder data line                     |
| Rotary Encoder SW  | D3 (GPIO 13)      | Rotary encoder switch (button)               |
| Push Button        | D0 (GPIO 16)      | Button to send MIDI program change command   |
| OLED SDA           | D2 (GPIO 4)       | I2C data line for OLED display               |
| OLED SCL           | D1 (GPIO 5)       | I2C clock line for OLED display              |
| OLED VCC           | 3V3               | Power supply for OLED display (3.3V)         |
| OLED GND           | GND               | Ground connection for OLED display           |

### 2. Rotary Encoder
- **CLK (Clock Line)**: Connect to D5 (GPIO 14) on LOLIN D1 Mini.
- **DT (Data Line)**: Connect to D6 (GPIO 12) on LOLIN D1 Mini.
- **SW (Switch/Button)**: Connect to D3 (GPIO 13) on LOLIN D1 Mini.
- **VCC**: Connect to 3.3V on LOLIN D1 Mini.
- **GND**: Connect to GND on LOLIN D1 Mini.

### 3. Push Button
- **One Terminal**: Connect to D0 (GPIO 16) on LOLIN D1 Mini.
- **Other Terminal**: Connect to GND.
- **Internal Pull-up**: Configured in software using `INPUT_PULLUP`.

### 4. OLED Display (SSD1306)
- **SDA (Data Line)**: Connect to D2 (GPIO 4) on LOLIN D1 Mini.
- **SCL (Clock Line)**: Connect to D1 (GPIO 5) on LOLIN D1 Mini.
- **VCC**: Connect to 3.3V on LOLIN D1 Mini.
- **GND**: Connect to GND on LOLIN D1 Mini.

### 5. MIDI Output Connector
- **Pin 4 (5V Power)**: Connect to a 220-ohm resistor, then to 5V.
- **Pin 5 (TX Line)**: Connect to a 220-ohm resistor, then to TX (D7 / GPIO 13) on LOLIN D1 Mini.
- **Pin 2 (Ground)**: Connect to GND on LOLIN D1 Mini.

## Summary
This wiring setup connects the LOLIN D1 Mini with the rotary encoder, push button, OLED display, and MIDI output connector to create a MIDI program controller. The rotary encoder is used to select MIDI channels and programs, while the push button sends the selected MIDI program change command. The OLED display provides visual feedback for the current channel, program, and bank selection.
