#include <cassert>
#include <memory>

struct Test { int m_x; };

int main()
{
  {
    std::unique_ptr<Test> p; //Uninitialized pointer
    //assert(p);  //Good: uninitialized pointer is detected
    //p->m_x = 3; //Bad: results in an access violation
  }
  {
    std::unique_ptr<Test> p(new Test);
    p->m_x = 3; //OK
  }
  {
    std::unique_ptr<Test> p;
    p.reset(new Test);
    p->m_x = 3; //OK
  }
  {
    std::unique_ptr<Test> p(new Test);
    //std::unique_ptr<Test> q(p); //std::unique_ptr cannot be copied
  }
  {
    std::unique_ptr<Test> p(new Test);
    std::shared_ptr<Test> q(p.release()); //Transfer ownership
    assert(!p);
    assert(q);
  }
}
