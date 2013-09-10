#include <iostream>
#include <map>

int main()
{
  std::map<std::string, int> phonebook;
  phonebook["Bilderbikkel"] = 1234567890; //Store
  std::cout << phonebook["Bilderbikkel"] << std::endl; //Read
}

/* Screen output:

1234567890
Press <RETURN> to close this window...

*/
