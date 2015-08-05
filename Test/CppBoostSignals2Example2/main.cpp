#include <iostream>

#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/signals2.hpp>

struct Thing
{
  Thing(const int id) : m_signal{}, m_id(id) {}
  boost::signals2::signal<void (const Thing*)> m_signal;
  const int m_id;
  void EmitMe() const { m_signal(this); }
};

struct Manager
{
  Manager(): m_v{}
  {
    for (int i=0; i!=5; ++i)
    {
      boost::shared_ptr<Thing> t(new Thing(i));
      //Do not forget the placeholder!
      t->m_signal.connect(boost::bind(&Manager::OnSignal,this, boost::lambda::_1));
      m_v.push_back(t);
    }
  }
  void EmitRandom()
  {
    const int i = std::rand() % 5;
    m_v[i]->EmitMe();
  }

  private:

  std::vector<boost::shared_ptr<Thing> > m_v;

  void OnSignal(const Thing* thing)
  {
    std::cout << thing->m_id << '\n';
  }
};

int main()
{
  Manager m;
  for (int i=0; i!=10; ++i) m.EmitRandom();
}

/* Screen output:

3
1
2
0
3
0
1
2
4
1

*/
