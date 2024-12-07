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

  Serial.println("Huma Buttons RemoveButton Started!");
}

void loop()
{
  if (Huma_Buttons.clicked(BTN_1_PIN)) {
    Serial.println("Button 1 clicked!");
    Serial.println("Button 1 removed and NOT functioning anymore!");
    Serial.println("Button 2 added!");
    Huma_Buttons.remove(BTN_1_PIN);
    Huma_Buttons.add(BTN_2_PIN);
  }

  if (Huma_Buttons.clicked(BTN_2_PIN)) {
    Serial.println("Button 2 clicked!");
    Serial.println("Button 2 removed and NOT functioning anymore!");
    Serial.println("Button 1 added!");
    Huma_Buttons.remove(BTN_2_PIN);
    Huma_Buttons.add(BTN_1_PIN);
  }
}