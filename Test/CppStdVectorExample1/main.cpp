#include <iostream>
#include <vector>

int main()
{
  const std::size_t size = 10;
  std::vector<int> v(size);
  for (int i=0; i!=size; ++i)
  {
    v[i]=i; //Store in v
    std::cout << v[i] << std::endl; //Read from v
  }
}

/* Screen output:

0
1
2
3
4
5
6
7
8
9
Press <RETURN> to close this window...

*/
