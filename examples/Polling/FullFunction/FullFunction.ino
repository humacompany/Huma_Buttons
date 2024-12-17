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

  /* Set debounce time for all buttons */
  /* Default value is 30 ms */
  Huma_Buttons.setDebounce(40); //ms

  /* Add button */
  Huma_Buttons.add(BTN_1_PIN);
  Huma_Buttons.add(BTN_2_PIN);

  /* Remove button */
  Huma_Buttons.remove(BTN_2_PIN);

  Serial.println("Huma Buttons FullFunction Started!");
}

void loop()
{
  static bool btn_hold = false;
  static HumaButtonStates_e prev_1_state = HUMA_RELEASED;
  HumaButtonStates_e current_state = HUMA_RELEASED;

  /* Check if button is clicked */
  if (Huma_Buttons.clicked(BTN_1_PIN)) {
    Serial.println("Button 1 clicked!");
  }

  /* Check current button's state */
  current_state = Huma_Buttons.state(BTN_1_PIN);
  if (current_state != prev_1_state) {
    if (current_state == HUMA_PRESSED) {
      Serial.print("Button 1 pressed at: ");
      /* Get button's pressed time */
      Serial.print(Huma_Buttons.pressedTime(BTN_1_PIN));
      Serial.println("");
    } else {
      Serial.println("Button 1 released!");
    }
    prev_1_state = current_state;
  }

  /* Check if button is pressed and held for 3 seconds */
  if ( ! btn_hold) {
    if (Huma_Buttons.hold(BTN_1_PIN, 3000)) {
      Serial.println("Button 1 pressed for 3 seconds");
      btn_hold = true;
    }
  } else {
    if (current_state == HUMA_RELEASED) {
      btn_hold = false;
    }
  }
}