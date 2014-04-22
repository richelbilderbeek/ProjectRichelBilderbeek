#include <cstdlib>
#include <iostream>
#include <string>

//From http://www.richelbilderbeek.nl/CppAskUserForString.htm
const std::string AskUserForString()
{
  std::string s;
  std::getline(std::cin,s);
  return s;
}

int main()
{
  while(1)
  {
    const std::string s = AskUserForString();
    if (s == "quit") break;
  }
}

/* Possible screen output:

hello
quit
Press <RETURN> to close this window...

*/
