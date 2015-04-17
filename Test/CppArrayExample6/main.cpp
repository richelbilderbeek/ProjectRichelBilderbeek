#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/microsec_time_clock.hpp>
#include <iostream>
const int sz = 100000;

struct Individual
{
  Individual() : m_v{std::vector<int>(1000,0)}
  {

  }
  void Add() noexcept { ++m_v[0]; }
private:
  std::vector<int> m_v; //Make copying heavy
};

void f(Individual v[sz])
{
  for (int i=0; i!=sz; ++i)
  {
    v[i].Add();
  }
}

void g(Individual * const v)
{
  for (int i=0; i!=sz; ++i)
  {
    v[i].Add();
  }
}

int main()
{

  Individual v[sz];

  const boost::posix_time::ptime start{boost::date_time::microsec_clock<boost::posix_time::ptime>::local_time()};
  f(v);
  const boost::posix_time::ptime after_f(boost::date_time::microsec_clock<boost::posix_time::ptime>::local_time());
  g(v);
  const boost::posix_time::ptime after_g(boost::date_time::microsec_clock<boost::posix_time::ptime>::local_time());
  const boost::posix_time::time_duration d_f = after_f - start;
  const boost::posix_time::time_duration d_g = after_g - start;
  std::cout << d_f.total_microseconds() << " " << d_g.total_microseconds() << '\n' ;
}
