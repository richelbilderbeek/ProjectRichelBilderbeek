#ifndef RASPBERRYPIGPIOPIN_H
#define RASPBERRYPIGPIOPIN_H

#include <set>

namespace rpi {

namespace gpio {

constexpr int GetMaxPinNumber() { return 26; }

struct Pin
{
  ///Create a pin and set its output to high
  Pin(const int pin_number);

  ///Create all valid Pin indices
  static const std::set<int> CreatePinNumbers();

  ///Get the pin number
  int GetPinNumber() const { return m_pin_number; }

  ///Set the output to high
  void SetOutputHigh();

  ///Set the output to low
  void SetOutputLow();

  //Toggle the output value
  void Toggle();

  private:
  ///Is the output high? Or is it low?
  bool m_is_high;

  ///The pin number
  const int m_pin_number;
};

bool operator<(const Pin& lhs, const Pin& rhs);

} //namespace gpio

} //namespace rpi

#endif // RASPBERRYPIGPIOPIN_H
