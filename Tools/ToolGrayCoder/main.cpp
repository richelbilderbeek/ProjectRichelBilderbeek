#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>

#include "toolgraycodermenudialog.h"
#include "toolgraycodermaindialog.h"

#pragma GCC diagnostic pop

int main(int argc, char * argv[])
{
  try
  {
    ribi::GrayCoderMainDialog d;
    if (argc == 1) throw std::exception();
    const int i = boost::lexical_cast<int>(argv[1]);
    d.SetNormalInt(i);
    std::cout << d.GetNormalInt() << " (normal) -> " << d.GetGrayInt() << " (Gray code)\n";
    std::cout << d.GetNormalIntAsBitStr() << " (normal) -> " << d.GetGrayIntAsBitStr() << " (Gray code)\n";
    std::cout << '\n';
    d.SetGrayInt(i);
    std::cout << d.GetGrayInt() << " (Gray code) -> " << d.GetNormalInt() << " (normal)\n";
    std::cout << d.GetGrayIntAsBitStr() << " (Gray code) -> " << d.GetNormalIntAsBitStr() << " (normal)\n";
    std::cout << '\n';
  }
  catch (...)
  {
    std::cout <<
      "Usage: " << argv[0] << " [value],\n"
      "where [value] is an integer value\n"
      "\n"
      "For example:"
      "\n"
      "  " << argv[0] << " 123\n"
      "\n";
  }

  for (const std::string&s : ribi::GrayCoderMenuDialog().GetAbout().CreateAboutText())
  {
    std::cout << s << '\n';
  }
  std::cout << '\n';
  for (const std::string&s : ribi::GrayCoderMenuDialog().GetAbout().CreateLicenceText())
  {
    std::cout << s << '\n';
  }
}
