#include <iostream>
#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include <boost/checked_delete.hpp>
#include <boost/weak_ptr.hpp>
#pragma GCC diagnostic pop

int main()
{
  {
    //nullptr do not add to use_count
    const boost::weak_ptr<int> a;
    assert(a.expired());
    assert(a.use_count() == 0);
    const boost::weak_ptr<int> b(a);
    assert(b.expired());
    assert(b.use_count() == 0);
  }
  {
    //using multiple weak_ptrs does not increase use_count
    const boost::shared_ptr<int> p(new int);
    const boost::weak_ptr<int> a(p);
    assert(!a.expired());
    assert(a.use_count() == 1);
    const boost::weak_ptr<int> b(p);
    assert(!b.expired());
    assert(b.use_count() == 1);

  }
}
