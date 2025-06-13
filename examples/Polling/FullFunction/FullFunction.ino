#include <Huma_Buttons.h>

#if defined(ESP32)
#define BTN_1_PIN         6
#define BTN_2_PIN         5
#define BTN_3_PIN         15
#define BTN_4_PIN         7
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
  Huma_Buttons.add(BTN_3_PIN);
  Huma_Buttons.add(BTN_4_PIN);

  /* Remove button */
  Huma_Buttons.remove(BTN_2_PIN);

  /* If button 3 is long pressed, releasing WILL trigger clicked event */
  Huma_Buttons.setLongPressClicked(BTN_3_PIN, true);

  Serial.println("Huma Buttons FullFunction Started!");
}

void loop()
{
  static bool btn3_hold = false;
  static bool btn4_hold = false;
  static HumaButtonStates_e btn1_prev_state = HUMA_RELEASED;
  HumaButtonStates_e btn1_state = HUMA_RELEASED;
  HumaButtonStates_e btn3_state = HUMA_RELEASED;
  HumaButtonStates_e btn4_state = HUMA_RELEASED;

  /* Check if button is clicked */
  if (Huma_Buttons.clicked(BTN_1_PIN)) {
    Serial.println("Button 1 clicked!");
  }

  if (Huma_Buttons.clicked(BTN_2_PIN)) {
    Serial.println("Button 2 clicked!");
  }

  if (Huma_Buttons.clicked(BTN_3_PIN)) {
    Serial.println("Button 3 clicked!");
  }

  if (Huma_Buttons.clicked(BTN_4_PIN)) {
    Serial.println("Button 4 clicked!");
  }

  /* Check current button's state */
  btn1_state = Huma_Buttons.state(BTN_1_PIN);
  if (btn1_state != btn1_prev_state) {
    if (btn1_state == HUMA_PRESSED) {
      Serial.print("Button 1 pressed at: ");
      /* Get button's pressed time */
      Serial.print(Huma_Buttons.pressedTime(BTN_1_PIN));
      Serial.println("");
    } else {
      Serial.println("Button 1 released!");
    }
    btn1_prev_state = btn1_state;
  }

  /* Check if button is long pressed for 3 seconds */
  btn3_state = Huma_Buttons.state(BTN_3_PIN);
  if ( ! btn3_hold) {
    if (Huma_Buttons.hold(BTN_3_PIN, 3000)) {
      Serial.println("Button 3 pressed for 3 seconds");
      btn3_hold = true;
    }
  } else {
    if (btn3_state == HUMA_RELEASED) {
      btn3_hold = false;
    }
  }

  /* Check if button is long pressed for 3 seconds */
  btn4_state = Huma_Buttons.state(BTN_4_PIN);
  if ( ! btn4_hold) {
    if (Huma_Buttons.hold(BTN_4_PIN, 3000)) {
      Serial.println("Button 4 pressed for 3 seconds");
      btn4_hold = true;
    }
  } else {
    if (btn4_state == HUMA_RELEASED) {
      btn4_hold = false;
    }
  }
}