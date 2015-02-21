#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
  std::vector<int> v;
  for (int i=0; i!=5; ++i) v.push_back(i);

  std::cout << "Before shuffling:\n";

  for(int i=0;i!=5; ++i) std::cout << v[i] << '\n';

  std::random_shuffle(v.begin(),v.end());

  std::cout << "After shuffling:\n";

  for(int i=0;i!=5; ++i) std::cout << v[i] << '\n';
}
