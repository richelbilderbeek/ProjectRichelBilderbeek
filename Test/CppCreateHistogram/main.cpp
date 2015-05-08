#include <algorithm>
#include <cassert>
#include <vector>
#include <sstream>
#include <iostream>

struct HistogramCategory
{
  HistogramCategory(const double min, const double max, const int cnt)
    : m_min{min}, m_max{max}, m_cnt{cnt}
  {
    assert(m_min < m_max);
  }
  int GetCnt() const noexcept { return m_cnt; }
  double GetMid() const noexcept { return (m_min + m_max) / 2.0; }
  double GetMin() const noexcept { return m_min; }
  double GetMax() const noexcept { return m_max; }
  //void AddCount(const int n) noexcept { m_cnt += n; }
  bool IsInRange(const double x) { return x >= m_min && x < m_max; }
  private:
  const double m_min;
  const double m_max; //Non inclusive
  const int m_cnt;
};

struct Histogram
{
  Histogram(
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
  const std::vector<HistogramCategory>& GetHistogram() const noexcept { return m_v; }
  private:
  std::vector<HistogramCategory> m_v;
};

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

int main()
{
  std::vector<double> v{-1.0,0.0,1.0};
  Histogram h(v,-2.0,2.0,4);
  std::cout << h << '\n';
}
