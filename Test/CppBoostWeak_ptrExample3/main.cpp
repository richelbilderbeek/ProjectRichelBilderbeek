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
  boost::weak_ptr<int> w;
  {
    const boost::shared_ptr<int> p(new int);
    w = p;

    const boost::shared_ptr<int> q(w.lock());
    assert(q);
  }

  const boost::shared_ptr<int> q(w.lock());
  assert(!q);
}
