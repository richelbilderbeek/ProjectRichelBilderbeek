#include <cassert>
#include <locale>
#include <boost/lexical_cast.hpp>

int main()
{
  const double my_double{1.5};
  const int my_int{1234};
  const std::string prev_locale_name = std::locale().name();
  const bool prev_is_dot = std::to_string(my_double)[1] == '.';

  std::locale::global(std::locale("nl_NL.UTF-8"));

  assert(std::locale().name() == "nl_NL.UTF-8");
  assert(boost::lexical_cast<std::string>(my_double)[1] == ',' && "Dutch");
  assert(std::to_string(my_double)[1] == ',' && "Dutch");
  assert(std::to_string(my_int) == "1234" && "Dutch");

  std::locale::global(std::locale("en_US.UTF-8"));

  assert(std::locale().name() == "en_US.UTF-8");
  assert(boost::lexical_cast<std::string>(my_double)[1] == '.' && "English");
  assert(std::to_string(my_double)[1] == '.' && "English");
  assert(std::to_string(my_int) == "1234");

  //Restore
  std::locale::global(std::locale(prev_locale_name.c_str()));
  assert(std::locale().name() == prev_locale_name);
  assert((boost::lexical_cast<std::string>(my_double)[1] == '.') == prev_is_dot);
  assert((std::to_string(my_double)[1] == '.') == prev_is_dot);
  assert(std::to_string(my_int) == "1234");
}
