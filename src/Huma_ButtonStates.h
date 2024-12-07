#pragma once

#include <Arduino.h>

typedef enum {
  HUMA_RELEASED = (0),
  HUMA_PRESSED,
  HUMA_CLICKED
} HumaButtonStates_e;

class HumaButtonStates
{
public:
  HumaButtonStates(byte pin = 0) {
    _clicked = false;
    _state = HUMA_RELEASED;
    _pin = pin;
    _state_time = _clicked_time = 0;
  }
  ~HumaButtonStates() {}

public:
  /* Getter */
  bool clicked() const { return _clicked; }
  uint8_t pin() const { return _pin; }
  HumaButtonStates_e state() const { return _state; }
  unsigned long long state_time() const { return _state_time; }
  unsigned long long clicked_time() const { return _clicked_time; }

  /* Setter */
  void setClicked(bool val) { _clicked = val; }
  void setPin(uint8_t pin) { _pin = pin; }
  void setState(HumaButtonStates_e stt) { _state = stt; };
  void setStateTime(unsigned long long t) { _state_time = t; }
  void setClickedTime(unsigned long long t) { _clicked_time = t; }

private:
  bool               _clicked;
  uint8_t            _pin;
  HumaButtonStates_e _state;
  unsigned long long _state_time;
  unsigned long long _clicked_time;
};

