#include <Huma_Buttons.h>

#if defined(ESP32)
#define BTN_1_PIN         9
#define BTN_2_PIN         10
#elif defined(ESP8266)
#define BTN_1_PIN         D5
#define BTN_2_PIN         D6
#endif

void setup()
{
  Serial.begin(115200);
  delay(2000); //Delay for Serial Monitor connection
#if defined(ESP8266)
  Serial.println("");
#endif

  Huma_Buttons.add(BTN_1_PIN);
  Huma_Buttons.add(BTN_2_PIN);

  Serial.println("Huma Buttons MonitorButtons Started!");
}

void loop()
{
  static HumaButtonStates_e prev_1_state = HUMA_RELEASED;
  static HumaButtonStates_e prev_2_state = HUMA_RELEASED;
  HumaButtonStates_e current_state = HUMA_RELEASED;

  if (Huma_Buttons.clicked(BTN_1_PIN)) {
    Serial.println("Button 1 clicked!");
  }

  if (Huma_Buttons.clicked(BTN_2_PIN)) {
    Serial.println("Button 2 clicked!");
  }

  current_state = Huma_Buttons.state(BTN_1_PIN);
  if (current_state != prev_1_state) {
    if (current_state == HUMA_PRESSED) {
      Serial.println("Button 1 pressed!");
    } else {
      Serial.println("Button 1 released!");
    }
    prev_1_state = current_state;
  }

  current_state = Huma_Buttons.state(BTN_2_PIN);
  if (current_state != prev_2_state) {
    if (current_state == HUMA_PRESSED) {
      Serial.println("Button 2 pressed!");
    } else {
      Serial.println("Button 2 released!");
    }
    prev_2_state = current_state;
  }
}