#include <Arduino.h>

/**
   Class to represent a debounced button for Arduino.

   This class facilitates button click detection, incorporating a debounce mechanism
   to ensure stable button state readings.

   @param pin Digital pin of Arduino to which the button is connected.
   @param debounceDelay Debounce time in milliseconds (default: 50 ms).
*/
class Button
{
private:
  byte pin;
  bool lastState;
  bool status;

  unsigned long lastDebounceTime = 0;
  unsigned long debounceDelay = 50;

public:
  Button(byte pin, unsigned long debounceDelay = 50)
  {
    this->pin = pin;
    pinMode(pin, INPUT);
    this->lastState = digitalRead(pin);
    this->debounceDelay = debounceDelay;
  }

  /**
     Checks if the button has been clicked, using debounce for stable readings.

     This function checks the current state of the button and uses debounce to ensure
     that only valid clicks are detected.

     @return true if a valid click was detected, false otherwise.
  */
  bool isClicked()
  {
    bool currentState = digitalRead(this->pin);

    if ((millis() - lastDebounceTime) >= debounceDelay && currentState == HIGH && this->lastState == LOW)
    {
      this->status = true;
    }
    else
    {
      this->status = false;
    }

    if (currentState != lastState)
    {
      this->lastDebounceTime = millis();
    }

    this->lastState = currentState;
    return this->status;
  }
};
