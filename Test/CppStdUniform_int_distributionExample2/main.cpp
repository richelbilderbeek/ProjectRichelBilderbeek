#include <iostream>
#include <random>

int main()
{
  std::random_device rd;

  //Use a random seed
  std::mt19937 rng(rd());

  //Draw random numbers from 0 to and including 123
  std::uniform_int_distribution<int> distribution(0,123);

  for (int i=0; i!=10; ++i)
  {
    std::cout << distribution(rng) << '\n';
  }
}
