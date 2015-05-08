#include "simulation.h"
#include <algorithm>
#include <cmath>
#include <random>
Simulation::Simulation(const Parameters& parameters)
  : m_parameters{parameters},
    m_axs{},
    m_ays{},
    m_bxs{},
    m_bys{},
    m_sumxs{},
    m_sumys{},
    m_a({},0.0,0.0,0),
    m_b({},0.0,0.0,0),
    m_sum({},0.0,0.0,0)
{
  #ifndef NDEBUG
  Test();
  #endif
}

void Simulation::Run() noexcept
{
  static std::mt19937 mt(42);
  std::normal_distribution<double> da(m_parameters.mean_a,m_parameters.stddev_a);
  std::normal_distribution<double> db(m_parameters.mean_b,m_parameters.stddev_b);

  std::vector<double> as;
  std::vector<double> bs;
  std::vector<double> sums;
  const int n{m_parameters.n};
  for (int i=0; i!=n; ++i)
  {
    const double a{da(mt)};
    const double b{db(mt)};
    const double sum{a+b};
    as.push_back(a);
    bs.push_back(b);
    sums.push_back(sum);
  }
  m_a = Histogram(
    as,
    *std::min_element(std::begin(as),std::end(as)) - 1.0,
    *std::max_element(std::begin(as),std::end(as)) + 1.0,
    std::sqrt(n)
  );
  m_b = Histogram(
    bs,
    *std::min_element(std::begin(bs),std::end(bs)) - 1.0,
    *std::max_element(std::begin(bs),std::end(bs)) + 1.0,
    std::sqrt(n)
  );
  m_sum = Histogram(
    sums,
    *std::min_element(std::begin(sums),std::end(sums)) - 1.0,
    *std::max_element(std::begin(sums),std::end(sums)) + 1.0,
    std::sqrt(n)
  );

  m_axs.clear();
  m_ays.clear();
  for (const auto& h: m_a.GetHistogram())
  {
    m_axs.push_back(h.GetMid());
    m_ays.push_back(static_cast<double>(h.GetCnt()));
  }

  m_bxs.clear();
  m_bys.clear();
  for (const auto& h: m_b.GetHistogram())
  {
    m_bxs.push_back(h.GetMid());
    m_bys.push_back(static_cast<double>(h.GetCnt()));
  }


  m_sumxs.clear();
  m_sumys.clear();
  for (const auto& h: m_sum.GetHistogram())
  {
    m_sumxs.push_back(h.GetMid());
    m_sumys.push_back(static_cast<double>(h.GetCnt()));
  }


}
