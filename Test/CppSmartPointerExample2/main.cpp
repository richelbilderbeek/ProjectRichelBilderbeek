#include <memory>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

struct Test { int m_x; };

int main()
{
  {
    std::shared_ptr<Test> p { new Test };
    assert(p);
    //p.reset(nullptr); //Invalid: std::shared_ptr cannot be reset to nullptr
    //assert(!p);
  }
  {
    std::unique_ptr<Test> p { new Test };
    assert(p);
    p.reset(nullptr); //Valid: std::unique_ptr can be reset to nullptr
    assert(!p);
  }
  {
    boost::shared_ptr<Test> p { new Test };
    assert(p);
    //p.reset(nullptr); //Invalid: boost::shared_ptr cannot be reset to nullptr
    //assert(!p);
  }
  {
    boost::scoped_ptr<Test> p { new Test };
    assert(p);
    p.reset(nullptr); //Valid: boost::scoped_ptr can be reset to nullptr
    assert(!p);
  }
}
