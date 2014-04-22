#include <cstdlib>
#include <iostream>

int main()
{
  const int value = 1 + (std::rand() % 6);
  if (6 == value) //A Yoda condition
  {
    std::cout << "Six you drawn have\n"; //Yoda grammar
  }
}
