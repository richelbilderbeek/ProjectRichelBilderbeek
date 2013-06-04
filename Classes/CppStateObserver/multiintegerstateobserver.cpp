#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "multiintegerstateobserver.h"

#include <cassert>
#include <boost/foreach.hpp>
MultiIntegerStateObserver::MultiIntegerStateObserver(
  std::vector<boost::shared_ptr<IntegerStateObserver> >& filters)
  : m_filters(filters)
{

}

/*
const std::vector<boost::shared_ptr<IntegerStateObserver> > MultiIntegerStateObserver::CreateFilters(
  const std::vector<int> alphas)
{
  std::vector<boost::shared_ptr<IntegerStateObserver> > v;

  BOOST_FOREACH(const int alpha, alphas)
  {
    boost::shared_ptr<IntegerStateObserver> filter(new IntegerStateObserver(alpha));
    assert(filter);
    v.push_back(filter);
  }
  return v;
}
*/

int64_t MultiIntegerStateObserver::Estimate(int64_t measurement)
{
  const std::size_t sz = m_filters.size();
  for (std::size_t i = 0; i!=sz; ++i)
  {
    assert(i < m_filters.size() );
    assert(m_filters[i]);
    measurement = m_filters[i]->Estimate(measurement); //One's output is the next one's output
  }

  return measurement;
}

const std::string MultiIntegerStateObserver::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> MultiIntegerStateObserver::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2013-06-04: version 1.0: initial version");
  return v;
}
