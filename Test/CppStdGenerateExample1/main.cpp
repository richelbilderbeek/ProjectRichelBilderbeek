#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
  const int size = 5;
  std::vector<int> v(size);

  //Generate the random numbers by using a pointer-to-function to the function std::rand
  std::generate(std::begin(v), std::end(v), std::rand);

  //Output on screen
  std::copy(std::begin(v),std::end(v), std::ostream_iterator<int>(std::cout," "));
  std::cout << '\n';

  //Generate the random numbers by using a lambda function
  std::generate(std::begin(v), std::end(v), []() { return std::rand() % 100; } );

  //Output on screen
  std::copy(std::begin(v),std::end(v), std::ostream_iterator<int>(std::cout," "));
  std::cout << '\n';
}
