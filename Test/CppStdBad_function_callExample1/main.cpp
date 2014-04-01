//Example adapted from
// http://en.cppreference.com/w/cpp/utility/functional/bad_function_call
#include <iostream>
#include <functional>

int main()
{
  std::function<int()> f = nullptr;
  try
  {
    f();
  }
  catch(const std::bad_function_call& e)
  {
    std::cout << e.what() << '\n';
  }
}

/* Screen output:

bad_function_call
Press <RETURN> to close this window...

*/
