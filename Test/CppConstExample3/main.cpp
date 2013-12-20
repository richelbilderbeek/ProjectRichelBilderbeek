#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

int main()
{
  //Non-const pointer to non-const int
  {
    boost::shared_ptr<int> p(new int(42));
    assert(p);
    assert(*p == 42);
    *p = 24;
    assert(*p == 24);
    p = nullptr;
    assert(!p);
  }
  //Const pointer to non-const int
  {
    const boost::shared_ptr<int> p(new int(42));
    assert(p);
    assert(*p == 42);
    *p = 24;
    assert(*p == 24);
    //p = nullptr;
    //assert(!p);
  }
  //Non-const pointer to const int
  {
    boost::shared_ptr<const int> p(new int(42));
    assert(p);
    assert(*p == 42);
    //*p = 24;
    //assert(*p == 24);
    p = nullptr;
    assert(!p);
  }
  //Const pointer to const int
  {
    const boost::shared_ptr<const int> p(new int(42));
    assert(p);
    assert(*p == 42);
    //*p = 24;
    //assert(*p == 24);
    //p = nullptr;
    //assert(!p);
  }
}
