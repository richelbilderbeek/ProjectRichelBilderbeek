#include <cassert>
#include <iostream>
#include <boost/program_options.hpp>

//Thanks to http://www.cl.cam.ac.uk/freshers/raspberrypi/tutorials/temperature/#step-six

void SetOutputHigh(const int pin)
{
  {
    const std::string cmd = "echo \"" + boost::lexical_cast<std::string>(pin) + "\" > /sys/class/gpio/export";
    std::clog << cmd << '\n';
    const int error = std::system(cmd.c_str());
    assert(!error);
  }
  {
    const std::string cmd = "echo \"out\" > /sys/class/gpio/gpio" + boost::lexical_cast<std::string>(pin)+ "/direction";
    std::clog << cmd << '\n';
    const int error = std::system(cmd.c_str());
    assert(!error);
  }
  {
    const std::string cmd = "echo \"1\" > /sys/class/gpio/gpio" + boost::lexical_cast<std::string>(pin)+ "/value";
    std::clog << cmd << '\n';
    const int error = std::system(cmd.c_str());
    assert(!error);
  }
}

void SetOutputLow(const int pin)
{
  {
    const std::string cmd = "echo \"0\" > /sys/class/gpio/gpio" + boost::lexical_cast<std::string>(pin)+ "/value";
    std::clog << cmd << '\n';
    const int error = std::system(cmd.c_str());
    assert(!error);
  }
  {
    const std::string cmd = "echo \"" + boost::lexical_cast<std::string>(pin) + "\" > /sys/class/gpio/unexport";
    std::clog << cmd << '\n';
    const int error = std::system(cmd.c_str());
    assert(!error);
  }
}

int main(int argc, char* argv[])
{
  // Declare the supported options.
  boost::program_options::options_description d("Allowed options for CppRpiExample2");
  d.add_options()
      ("help",
        "produce this help message")
      ("pin",
         boost::program_options::value<int>(),
         "the pin to be modified (must be in pin list)")
      ("value",
         boost::program_options::value<int>(),
         "set the value of a pin (zero or one)")
      ("pin_list",
         "display the list of pins")
      ;

  boost::program_options::variables_map m;
  boost::program_options::store(
    boost::program_options::parse_command_line(
      argc, argv, d), m);
  boost::program_options::notify(m);

  //If one of the options is set to 'help'...
  if (m.count("help"))
  {
    //Display the options_description
    std::cout << d << "\n";
    return 0;
  }

  const std::vector<int> pins = { 2,3,4,7,8,9,10,11,14,15,17,18,22,23,24,25,27 };
  if (m.count("pin_list"))
  {
    std::cout << "Pin list:\n";
    for(int pin: pins)
    {
      std::cout << pin << " ";
    }
    std::cout << '\n';
    return 0;
  }

  int pin = 2;
  if (m.count("pin"))
  {
    pin = m["pin"].as<int>();
    std::cout << "pin number: " << pin << '\n';
  }
  if (std::find(pins.begin(),pins.end(),pin) == pins.end())
  {
    std::cout << "Pin #" << pin << " is not a valid pin index\n"
      << "Use --pin_list for a list of valid pins\n";
    return 1;
  }
  int value = 1;
  if (m.count("value"))
  {
    value = m["value"].as<int>();
    std::cout << "value: " << value << '\n';
  }
  if (value)
  {
    SetOutputHigh(pin);
  }
  else
  {
    SetOutputLow(pin);
  }
}
