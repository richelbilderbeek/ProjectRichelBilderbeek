#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "multiintegerstateobserver.h"

#include <cassert>


#pragma GCC diagnostic pop

ribi::MultiIntegerStateObserver::MultiIntegerStateObserver(
  std::vector<boost::shared_ptr<IntegerStateObserver> >& filters)
  : m_filters(filters)
{

}

int64_t ribi::MultiIntegerStateObserver::GetEstimate() const
{
  return m_filters.back()->GetEstimate();
}

void ribi::MultiIntegerStateObserver::Update(int64_t measurement)
{
  const std::size_t sz = m_filters.size();
  for (std::size_t i = 0; i!=sz; ++i)
  {
    assert(i < m_filters.size() );
    assert(m_filters[i]);
    m_filters[i]->Update(measurement); //One's output is the next one's output
    measurement = m_filters[i]->GetEstimate(); //One's output is the next one's output
  }
}

std::string ribi::MultiIntegerStateObserver::GetVersion() noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::MultiIntegerStateObserver::GetVersionHistory() noexcept
{
  return {
    "2013-06-04: version 1.0: initial version",
    "2013-06-18: version 1.1: derive from IntegerStateObserver"
  };
}
