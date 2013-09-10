#include <iostream>
#include <vector>

int main()
{
  const std::vector<int> v { 1, 2, 3 };

  //auto determines the type
  const auto j = v.end();
  for (auto i = v.begin(); i!=j; ++i)
  {
    std::cout << *i << '\n';
  }
}

/* Screen output:

1
2
3
Press <RETURN> to close this window...

*/
