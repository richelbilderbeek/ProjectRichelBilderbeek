#include "histogram.h"

#include <algorithm>
#include <cassert>
#include <sstream>

HistogramCategory::HistogramCategory(const double min, const double max, const int cnt)
  : m_min{min}, m_max{max}, m_cnt{cnt}
{
  assert(m_min < m_max);
}


Histogram::Histogram(
  const std::vector<double>& v,
  const double lowest, const double highest, const int n
)
  : m_v{}
{
  //const int sz{static_cast<int>(v.size())};
  //const int n{1+static_cast<int>(std::sqrt(static_cast<double>(sz)))};
  //const double lowest{*std::min_element(std::begin(v),std::end(v))};
  //const double highest{*std::max_element(std::begin(v),std::end(v))};
  const double total_range{highest-lowest};
  const double category_width{total_range/static_cast<double>(n)};
  for (int i=0; i!=n; ++i)
  {
    const double min{lowest + (static_cast<double>(i + 0) * category_width)};
    const double max{lowest + (static_cast<double>(i + 1) * category_width)};
    const int n_values{
      std::count_if(std::begin(v),std::end(v),
        [min,max](const double x) { return x >= min && x < max; }
      )
    };
    m_v.push_back(HistogramCategory(min,max,n_values));
  }

}

std::ostream& operator<<(std::ostream& os, const Histogram& h)
{
  std::stringstream s;
  for (const HistogramCategory& c: h.GetHistogram())
  {
    s << "[" << c.GetMin() << "," << c.GetMax() << "): " << c.GetCnt() << '\n';
  }
  std::string t{s.str()};
  if (!t.empty()) t.pop_back();
  os << t;
  return os;
}
