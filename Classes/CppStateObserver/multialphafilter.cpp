#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "multialphafilter.h"

#include <cassert>


#pragma GCC diagnostic pop

ribi::MultiAlphaFilter::MultiAlphaFilter(
  const std::vector<double> alphas,
  const double dt)
  : m_filters(CreateFilters(alphas,dt))
{

}

const std::vector<boost::shared_ptr<ribi::AlphaFilter> > ribi::MultiAlphaFilter::CreateFilters(
  const std::vector<double> alphas,
  const double dt)
{
  std::vector<boost::shared_ptr<AlphaFilter> > v;

  for(const double alpha: alphas)
  {
    boost::shared_ptr<AlphaFilter> filter(new AlphaFilter(alpha,dt));
    assert(filter);
    v.push_back(filter);
  }
  return v;
}

double ribi::MultiAlphaFilter::GetEstimate() const
{
  return m_filters.back()->GetEstimate();
}

void ribi::MultiAlphaFilter::Update(double measurement)
{
  const std::size_t sz = m_filters.size();
  for (std::size_t i = 0; i!=sz; ++i)
  {
    assert(i < m_filters.size() );
    assert(m_filters[i]);
    m_filters[i]->Update(measurement); //One's output is the next one's output
    measurement = m_filters[i]->GetEstimate();
  }
}

const std::string ribi::MultiAlphaFilter::GetVersion() noexcept
{
  return "1.1";
}

const std::vector<std::string> ribi::MultiAlphaFilter::GetVersionHistory() noexcept
{
  return {
    "2013-05-25: version 1.0: initial version",
    "2013-06-18: version 1.1: derive from FloatingPointStateObserver"
  };
}
