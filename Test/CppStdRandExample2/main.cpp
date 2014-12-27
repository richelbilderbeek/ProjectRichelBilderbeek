#include <cstdlib>
#include <iostream>

int main()
{
  for (int i=0; i!=10; ++i)
  {
    std::srand(0);
    std::cout << std::rand() << std::endl;
  }
}
