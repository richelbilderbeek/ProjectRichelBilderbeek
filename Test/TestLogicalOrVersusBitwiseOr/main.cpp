#include <iostream>

int main()
{
  if (1  | (1/0)) { std::cout << "X"; }
  if (1 || (1/0)) { std::cout << "Y"; }
  if (!(0  & (1/0))) { std::cout << "A"; }
  if (!(0 && (1/0))) { std::cout << "B"; }
  std::cout << std::endl;
}
