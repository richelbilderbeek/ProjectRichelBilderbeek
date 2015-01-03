#include <boost/locale.hpp>
#include <boost/math/constants/constants.hpp>

int main()
{
  std::cout << "Current locale: " << std::locale().name() << std::endl;
  assert(std::locale().name() == "C");

  //It was observed in a Qt Desktop environment that
  //pi converted to a string as '3,14...', probably because
  //some locale was set to Dutch.
  //
  //In a console environment, however, it appears not to fail, as if
  //there is no locale set

  const double pi = boost::math::constants::pi<double>();

  boost::locale::generator gen;

  //Default (which is English)
  {
    std::locale::global(gen(""));
    //std::cout << "Current locale: " << std::locale().name() << std::endl;
    assert(std::locale().name() == "*");

    const std::string pi_str_boost{boost::lexical_cast<std::string>(pi)};
    assert(pi_str_boost[1] == '.' && "Default (English) please");
  }
  //English (which is the same as the default)
  {
    std::locale::global(gen("en_US.UTF-8"));
    //std::cout << "Current locale: " << std::locale().name() << std::endl;
    assert(std::locale().name() == "*");
    const std::string pi_str_boost{boost::lexical_cast<std::string>(pi)};
    assert(pi_str_boost[1] == '.' && "English please");
  }

  //German
  try
  {
    std::locale::global(std::locale("de_DE.UTF-8"));
    assert(std::locale().name() == "*");
    //std::cout << "Current locale: " << std::locale().name() << std::endl;
    const std::string pi_str_boost{boost::lexical_cast<std::string>(pi)};
    assert(pi_str_boost[1] == ',' && "German please");
  }
  catch (std::runtime_error&)
  {
    std::cout << "?German unknown locale" << std::endl;
  }

  //Dutch
  const auto my_locale = std::locale("nl_NL.UTF-8");
  std::locale::global(my_locale);
  assert(std::locale().name() == "nl_NL.UTF-8");
  std::cout << "Current locale: " << std::locale().name() << std::endl;

  const std::string pi_str_boost{boost::lexical_cast<std::string>(pi)};
  assert(pi_str_boost[1] == ',' && "Dutch please");
  std::cout << "Pi in Dutch (should have a comma): " << pi_str_boost << std::endl;
}
