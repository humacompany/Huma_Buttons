# Huma_Buttons

Simple Push Button libarry for ESP32, ESP8266 using interrupts.

Currently the library only supports polling method.

This library uses `INPUT_PULLUP` pin mode by default, so please use the pins which support internal pullup resistors.

If the pin has no internal pullup resistor, please add an external pullup resistor to your circuit as below:

![Alt text](https://github.com/humacompany/public-assets/blob/master/Huma_Buttons/assets/esp32-button-pullup-diagram.png "ESP32 Button With Pullup Diagram")

# Functions

* `int8_t add(byte btn_pin)`: Add a button to use
* `bool remove(byte btn_pin)`: Remove a button
* `unsigned long long pressedTime(uint8_t btn_pin)`: Get the pressed time of a button
* `bool clicked(uint8_t btn_pin)`: Check if a button is clicked
* `HumaButtonStates_e state(uint8_t btn_pin)`: Get current button's state
* `void setDebounce(uint16_t debounce)`: Set debounce time for all buttons. Default is 30ms

# Contacts

* Email: contacts.humacompany@gmail.com
* Facebook: https://www.facebook.com/humacompanyvn