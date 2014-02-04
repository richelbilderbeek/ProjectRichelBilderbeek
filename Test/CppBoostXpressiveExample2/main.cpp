#include <cassert>
#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/xpressive/xpressive.hpp>
#pragma GCC diagnostic pop

int main()
{
  const std::string str = "The zip code 1234AB is correct";
  const boost::xpressive::sregex regex
    = boost::xpressive::sregex::compile("(\\d{4})()([A-Z]{2})");
  const std::string fix("($1) ($3)");
  const std::string s
    = boost::xpressive::regex_replace(
      str,
      regex,
      fix,
        boost::xpressive::regex_constants::match_default
      | boost::xpressive::regex_constants::format_all);
  assert(s == "The zip code 1234 AB is correct");
}
