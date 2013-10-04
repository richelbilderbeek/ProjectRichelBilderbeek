#include <cstdlib>

int main()
{
  for(int i=0; i!=100; ++i)
  {
    if (i==69 && std::rand()%2==0) break;
  }
}
