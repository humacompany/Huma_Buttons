#pragma once

#include <Arduino.h>
#include <Huma_ButtonStates.h>

#define BTN_CLICKED_REMAIN_TIME       500   //ms
#define BTN_DEBOUNCE_TIME             30    //ms
#define HUMA_BUTTONS_MAX              40    //Maximum number of buttons

class Huma_ButtonClass
{
public:
  /*!
   * @brief Constructor
   * @param debounce debounce time for all buttons 
   * @return N/A
   */
  Huma_ButtonClass(uint16_t debounce = BTN_DEBOUNCE_TIME);

  /*!
   * @brief Destructor
   * @param N/A
   * @return N/A
   */
  ~Huma_ButtonClass() {}

  /*!
   * @brief Add a button to use
   * @param btn_pin Pin number
   * @return Return current number of buttons
   *         -1 if maximum buttons reached
   */
  int8_t add(byte btn_pin);

  /*!
   * @brief Remove a button
   * @param btn_pin Pin number
   * @return true if successfull
   *         false if invalid pin number
   */
  bool remove(byte btn_pin);

  /*!
   * @brief Get the pressed time of a button
   * @param btn_pin Pin number
   * @return pressed time in ms
   *         0 if button is not pressed
   */
  unsigned long long pressedTime(uint8_t btn_pin);

  /*!
   * @brief Check if a button is clicked
   * @param btn_pin Pin number
   * @return true if button is just clicked within clicked remain time ms
   *         false if button is not clicked
   */
  bool clicked(uint8_t btn_pin);

  /*!
   * @brief Get current button's state
   * @param btn_pin Pin number
   * @return Current button's sate
   *         HUMA_RELEASED
   *         HUMA_PRESSED
   */
  HumaButtonStates_e state(uint8_t btn_pin);

  /*!
   * @brief Set debounce time for all buttons. Default is 30ms
   * @param debounce Debounce time in ms
   * @return N/A
   */
  void setDebounce(uint16_t debounce);

private:
  /*!
   * @brief Get button object by button pin
   * @param btn_pin Pin number
   * @return Button object if exist
   *         NULL if no such button
   */
  HumaButtonStates *LocalGetButton(byte btn_pin);

  /*!
   * @brief Check if a button pin exists
   * @param btn_pin Pin number
   * @return Index of existing button
   *         -1 if no button found
   */
  int8_t LocalCheckPinExist(byte btn_pin);

private:
  HumaButtonStates *btns[HUMA_BUTTONS_MAX];
  uint8_t _buttonNum;
  uint16_t _clickedRemainTime;
};

extern Huma_ButtonClass Huma_Buttons;
