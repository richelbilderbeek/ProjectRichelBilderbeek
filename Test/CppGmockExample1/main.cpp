#include <cassert>
#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/regex.hpp>
#pragma GCC diagnostic pop

int main()
{
  //Define how a dutch zip code is formatted
  const boost::regex dutch_zip_code("\\d{4}\\s[A-Z]{2}");

  //Check if the regex works properly
  assert(boost::regex_match("1234 AB",dutch_zip_code)==true);
  assert(boost::regex_match("1234 ab",dutch_zip_code)==false);
  assert(boost::regex_match("1234ab",dutch_zip_code)==false);

  //Define a sentence with a Dutch zip code in it
  const std::string s = "My Dutch zip code is 1234 AB.";

  //Show how boost::regex_match and boost::regex_search work
  assert(boost::regex_match(s,dutch_zip_code)==false
    && "the std::string does not match a dutch zip code");
  assert(boost::regex_search(s,dutch_zip_code)==true
    && "but the std::string does contain a dutch zip code");

  //Show how to obtain a Dutch zip code from a std::string
  const boost::sregex_iterator i(s.begin(),s.end(),dutch_zip_code);
  const std::string t = i->str();
  assert(t=="1234 AB");
}
