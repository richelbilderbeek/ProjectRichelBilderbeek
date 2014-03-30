#include <cassert>

int main()
{
  {
    int * p = new int;
    assert(p);
    //Leak memory here
  }
}
