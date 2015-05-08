#ifndef RIBI_HISTOGRAM_H
#define RIBI_HISTOGRAM_H

#include <vector>

struct HistogramCategory
{
  HistogramCategory(const double min, const double max, const int cnt);
  int GetCnt() const noexcept { return m_cnt; }
  double GetMid() const noexcept { return (m_min + m_max) / 2.0; }
  double GetMin() const noexcept { return m_min; }
  double GetMax() const noexcept { return m_max; }
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
  );
  const std::vector<HistogramCategory>& GetHistogram() const noexcept { return m_v; }
  private:
  std::vector<HistogramCategory> m_v;
};

#endif // RIBI_HISTOGRAM_H
