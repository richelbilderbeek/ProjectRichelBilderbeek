#include <iostream>

int main()
{
  const int dozen { 12 };
  //++dozen; //Will not compile: 'increment of read-only variable'
  std::cout << "A dozen is " << dozen << '\n';
}
