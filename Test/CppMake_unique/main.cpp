#include <cassert>
#include <memory>
#include <iostream>

int main()
{
  std::cout << __cplusplus << std::endl;
  #if __cplusplus >= 201300
  std::cout << "C++14" << '\n';
  const std::unique_ptr<int> i{std::make_unique<int>()};
  assert(i);
  #else
  #if __cplusplus >= 201103
  std::cout << "C++11" << '\n';
  //const std::unique_ptr<int> i{std::make_unique<int>()};
  assert(i);
  #endif
  #endif
}
