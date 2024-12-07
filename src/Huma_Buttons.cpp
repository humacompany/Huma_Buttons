#include "Huma_Buttons.h"

static uint16_t g_humaBtnDebounceTime = BTN_DEBOUNCE_TIME;

/*!
  * @brief Rising edge ISR Handler
  * @param btn button object which is created by dynamic allocation
  * @return N/A
  */
void IRAM_ATTR humaBtnRisingIsr(HumaButtonStates *btn)
{
  if (btn && btn->state() == HUMA_PRESSED) {
    unsigned long long t = millis();
    if ((t - btn->state_time()) > g_humaBtnDebounceTime) {
      btn->setClicked(true);
      btn->setClickedTime(t);
      btn->setState(HUMA_RELEASED);
      btn->setStateTime(t);
    }
  }
}

/*!
  * @brief Falling edge ISR Handler
  * @param btn button object which is created by dynamic allocation
  * @return N/A
  */
void IRAM_ATTR humaBtnFallingIsr(HumaButtonStates *btn)
{
  if (btn && btn->state() == HUMA_RELEASED) {
    unsigned long long t = millis();
    if ((t - btn->state_time()) > g_humaBtnDebounceTime) {
      btn->setState(HUMA_PRESSED);
      btn->setStateTime(t);
    }
  }
}

/*!
  * @brief Button ISR Handler
  * @param param button object which is created by dynamic allocation
  * @return N/A
  */
void IRAM_ATTR humaBtnIsr(void *param) {
  HumaButtonStates *btn = (HumaButtonStates *)param;
  if (digitalRead(btn->pin())) {
    humaBtnRisingIsr(btn);
  } else {
    humaBtnFallingIsr(btn);
  }
}

Huma_ButtonClass::Huma_ButtonClass(uint16_t debounce)
{
  _buttonNum = 0;
  _clickedRemainTime = BTN_CLICKED_REMAIN_TIME;
  g_humaBtnDebounceTime = debounce;
}

int8_t Huma_ButtonClass::add(byte btn_pin)
{
  int8_t index = -1;

  if (_buttonNum < HUMA_BUTTONS_MAX - 1 && LocalCheckPinExist(btn_pin) < 0)
  {
    index = _buttonNum;
    pinMode(btn_pin, INPUT_PULLUP);

    HumaButtonStates *newBtn = new HumaButtonStates(btn_pin);
    btns[index] = newBtn;
    attachInterruptArg(btn_pin, humaBtnIsr, (void *)newBtn, CHANGE);
    _buttonNum++;
  }

  return index;
}

bool Huma_ButtonClass::remove(byte btn_pin)
{
  bool ret = false;
  byte i = 0;
  HumaButtonStates *btn = NULL;

  for (i = 0; i < _buttonNum; i++)
  {
    btn = btns[i];
    if (btn->pin() == btn_pin)
    {
      detachInterrupt(btn_pin);

      if (i < _buttonNum - 1) {
        memmove(&btns[i], &btns[i + 1], (_buttonNum - i - 1) * sizeof(HumaButtonStates *));
      }
      
      free(btn);
      _buttonNum--;
      ret = true;
      break;
    }
  }
  
  return ret;
}

unsigned long long Huma_ButtonClass::pressedTime(uint8_t btn_pin)
{
  unsigned long long time = 0;
  HumaButtonStates *btn = LocalGetButton(btn_pin);

  if ( btn && btn->state() == HUMA_PRESSED ) {
    time = btn->state_time();
  }

  return time;
}

bool Huma_ButtonClass::clicked(uint8_t btn_pin)
{
  bool isClicked = false;
  HumaButtonStates *btn = LocalGetButton(btn_pin);

  if (btn && btn->clicked()) {
    if (millis() - btn->clicked_time() <= _clickedRemainTime) {
      isClicked = true;
      btn->setClicked(false); //Reset state
      btn->setClickedTime(0);
    }
  }

  return isClicked;
}

HumaButtonStates_e Huma_ButtonClass::state(uint8_t btn_pin)
{
  HumaButtonStates_e state = HUMA_RELEASED;
  HumaButtonStates *btn = LocalGetButton(btn_pin);
  if (btn) {
    state = btn->state();
  }

  return state;
}

void Huma_ButtonClass::setDebounce(uint16_t debounce)
{
  g_humaBtnDebounceTime = debounce;
}

HumaButtonStates *Huma_ButtonClass::LocalGetButton(byte btn_pin)
{
  uint8_t i = 0;
  HumaButtonStates *btn = NULL;

  for ( i = 0; i < _buttonNum; i++ ) {
    if ( btns[i]->pin() == btn_pin ) {
      btn = btns[i];
      break;
    }
  }

  return btn;
}

int8_t Huma_ButtonClass::LocalCheckPinExist(byte btn_pin)
{
  int8_t index = -1;
  byte i = 0;

  for (i = 0; i < _buttonNum; i++) {
    if (btns[i] && btns[i]->pin() == btn_pin) {
      index = i;
      break;
    }
  }

  return index;
}


Huma_ButtonClass Huma_Buttons;
