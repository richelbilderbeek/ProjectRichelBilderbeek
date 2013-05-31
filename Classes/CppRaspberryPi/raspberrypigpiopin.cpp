#include "raspberrypigpiopin.h"

#include <cassert>
#include <iostream>
#include <string>

#include <boost/lexical_cast.hpp>

namespace rpi {

namespace gpio {


Pin::Pin(const int pin)
  : m_is_high(true),
    m_pin_number(pin)
{
  #ifndef NDEBUG
  const std::set<int> pins = CreatePinNumbers();
  assert(pins.count(pin));
  #endif
  this->SetOutputHigh();
}

const std::set<int> Pin::CreatePinNumbers()
{
  //Note that I commented out pin number 27
  //I do not know why I have so often included it, but I must have read it somewhere
  const std::set<int> pins { 3,5,7,8,10,11,12,13,15,16,18,19,21,22,23,24,26 };
  return pins;
}

void Pin::SetOutputHigh()
{
  {
    const std::string cmd = "echo \"" + boost::lexical_cast<std::string>(GetPinNumber()) + "\" > /sys/class/gpio/export";
    std::clog << cmd << '\n';
    const int error = std::system(cmd.c_str());
    if (error) std::cerr << "Error: " << error << '\n';
  }
  {
    const std::string cmd = "echo \"out\" > /sys/class/gpio/gpio" + boost::lexical_cast<std::string>(GetPinNumber())+ "/direction";
    std::clog << cmd << '\n';
    const int error = std::system(cmd.c_str());
    if (error) std::cerr << "Error: " << error << '\n';
  }
  {
    const std::string cmd = "echo \"1\" > /sys/class/gpio/gpio" + boost::lexical_cast<std::string>(GetPinNumber())+ "/value";
    std::clog << cmd << '\n';
    const int error = std::system(cmd.c_str());
    if (error) std::cerr << "Error: " << error << '\n';
  }
  m_is_high = true;
}

void Pin::SetOutputLow()
{
  {
    const std::string cmd = "echo \"0\" > /sys/class/gpio/gpio" + boost::lexical_cast<std::string>(GetPinNumber())+ "/value";
    std::clog << cmd << '\n';
    const int error = std::system(cmd.c_str());
    if (error) std::cerr << "Error: " << error << '\n';
  }
  {
    const std::string cmd = "echo \"" + boost::lexical_cast<std::string>(GetPinNumber()) + "\" > /sys/class/gpio/unexport";
    std::clog << cmd << '\n';
    const int error = std::system(cmd.c_str());
    if (error) std::cerr << "Error: " << error << '\n';
  }
  m_is_high = false;
}

void Pin::Toggle()
{
  m_is_high ? SetOutputLow() : SetOutputHigh();
}

bool operator<(const Pin& lhs, const Pin& rhs)
{
  assert(lhs.GetPinNumber() != rhs.GetPinNumber());
  return lhs.GetPinNumber() < rhs.GetPinNumber();
}

} //namespace gpio


} //namespace rpi
