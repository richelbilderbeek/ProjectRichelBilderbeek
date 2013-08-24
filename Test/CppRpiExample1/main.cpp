#include <cassert>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/timer.hpp>

//Toggles all GPIO pins every second
//Thanks to http://www.cl.cam.ac.uk/freshers/raspberrypi/tutorials/temperature/#step-six

int main()
{
  const std::vector<int> gpios = { 2,3,4,7,8,9,10,11,14,15,17,18,22,23,24,25,27 };

  while (1)
  {
    //Set all GPIO pins high
    for(int i: gpios)
    {
      {
        const std::string cmd = "echo \"" + boost::lexical_cast<std::string>(i) + "\" > /sys/class/gpio/export";
        std::clog << cmd << '\n';
        const int error = std::system(cmd.c_str());
        assert(!error);
      }
      {
        const std::string cmd = "echo \"out\" > /sys/class/gpio/gpio" + boost::lexical_cast<std::string>(i)+ "/direction";
        std::clog << cmd << '\n';
        const int error = std::system(cmd.c_str());
        assert(!error);
      }
      {
        const std::string cmd = "echo \"1\" > /sys/class/gpio/gpio" + boost::lexical_cast<std::string>(i)+ "/value";
        std::clog << cmd << '\n';
        const int error = std::system(cmd.c_str());
        assert(!error);
      }
    }
    //Wait a second
    {
      boost::timer t;
      while (t.elapsed() < 1.0) {}
    }
    //Set all GPIO pins low
    for(int i: gpios)
    {
      {
        const std::string cmd = "echo \"0\" > /sys/class/gpio/gpio" + boost::lexical_cast<std::string>(i)+ "/value";
        std::clog << cmd << '\n';
        const int error = std::system(cmd.c_str());
        assert(!error);
      }
      {
        const std::string cmd = "echo \"" + boost::lexical_cast<std::string>(i) + "\" > /sys/class/gpio/unexport";
        std::clog << cmd << '\n';
        const int error = std::system(cmd.c_str());
        assert(!error);
      }
    }
    //Wait a second
    {
      boost::timer t;
      while (t.elapsed() < 1.0) {}
    }
  }

}
