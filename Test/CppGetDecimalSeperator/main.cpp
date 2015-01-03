#include <locale>
#include <iostream>
#include <sstream>

///Obtain the decimal seperator of the current std::locale from std::cout
//From http://www.richelbilderbeek.nl/CppGetDecimalSeperator.htm
std::string GetDecimalSeperator() noexcept
{
  const auto c
    = std::use_facet<std::numpunct<char>>(
        std::cout.getloc()
      ).decimal_point()
    ;
  std::string s(1,c);
  return s;
}

int main()
{
  std::cout << GetDecimalSeperator() << '\n';
}
/* Screen output:

.

*/
