#include <cassert>
#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/xpressive/xpressive.hpp>
#pragma GCC diagnostic pop

int main()
{
  //Define how a dutch zip code is formatted
  const boost::xpressive::sregex dutch_zip_code
   = boost::xpressive::sregex::compile("\\d{4}\\s[A-Z]{2}");

  //Check if the regex works properly
  assert( boost::xpressive::regex_match(std::string("1234 AB"),dutch_zip_code));
  assert(!boost::xpressive::regex_match(std::string("1234 ab"),dutch_zip_code));
  assert(!boost::xpressive::regex_match(std::string("1234ab"),dutch_zip_code));

  //Define a sentence with a Dutch zip code in it
  const std::string s = "My Dutch zip code is 1234 AB.";

  //Show how boost::xpressive::regex_match and boost::xpressive::regex_search work
  assert(!boost::xpressive::regex_match(s,dutch_zip_code)
    && "the std::string does not match a dutch zip code");
  assert(boost::xpressive::regex_search(s,dutch_zip_code)
    && "but the std::string does contain a dutch zip code");

  //Show how to obtain a Dutch zip code from a std::string
  const boost::xpressive::sregex_iterator i(s.begin(),s.end(),dutch_zip_code);
  const std::string t = i->str();
  assert(t=="1234 AB");
}
