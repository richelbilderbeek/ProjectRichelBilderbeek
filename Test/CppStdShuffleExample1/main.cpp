#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
  std::vector<int> v = {0, 1, 2, 3, 4};

  //Initialize std::mt19937 with a random number
  std::random_device rd;
  std::mt19937 g(rd());

  std::cout << "Before shuffling:\n";

  for(const int i:v) std::cout << i << '\n';

  std::shuffle(v.begin(),v.end(),g);

  std::cout << "After shuffling:\n";

  for(const int i:v) std::cout << i << '\n';
}
