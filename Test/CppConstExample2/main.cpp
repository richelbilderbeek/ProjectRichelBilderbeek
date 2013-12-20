#include <cassert>

int main()
{
  //Non-const pointer to non-const int
  {
    int * p = new int(42);
    assert(p);
    assert(*p == 42);
    *p = 24;
    assert(*p == 24);
    delete p;
    p = nullptr;
    assert(!p);
  }
  //Const pointer to non-const int
  {
    int * const p = new int(42);
    assert(p);
    assert(*p == 42);
    *p = 24;
    assert(*p == 24);
    delete p;
    //p = nullptr;
    //assert(!p);
  }
  //Non-const pointer to const int
  {
    const int * p = new int(42);
    assert(p);
    assert(*p == 42);
    //*p = 24;
    //assert(*p == 24);
    delete p;
    p = nullptr;
    assert(!p);
  }
  //Const pointer to const int
  {
    const int * const p = new int(42);
    assert(p);
    assert(*p == 42);
    //*p = 24;
    //assert(*p == 24);
    delete p; //It is still possible to delete p
    //p = nullptr;
    //assert(!p);
  }
}
