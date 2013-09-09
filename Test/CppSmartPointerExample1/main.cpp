#include <cassert>
#include <memory>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

struct Test { int m_x; };

int main()
{
  {
    std::unique_ptr<Test> p;
    assert(!p);
    p->m_x = 42; //Danger: uninitialized pointer not detected by std::unique_ptr
  }
  {
    std::shared_ptr<Test> p;
    assert(!p);
    p->m_x = 42; //Danger: uninitialized pointer not detected by std::shared_ptr
  }
  {
    boost::shared_ptr<Test> p;
    assert(!p);
    p->m_x = 42; //Good: uninitialized pointer detected by boost::shared_ptr
  }
  {
    boost::scoped_ptr<Test> p;
    assert(!p);
    p->m_x = 42; //Danger: uninitialized pointer not detected by boost::scoped_ptr
  }
}
