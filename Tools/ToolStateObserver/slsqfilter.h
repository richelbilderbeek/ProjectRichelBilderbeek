#ifndef SLSQFILTER_H
#define SLSQFILTER_H

#include <cinttypes>

namespace ribi {

///Symmetric LSQ filter
struct SlsqFilter
{
  SlsqFilter(
    const int filter_shift,
    const int64_t value_active = 0,
    const int64_t value_hidden = 0);

  int64_t Estimate(const int64_t measurement);

  private:
  int m_filter_shift;
  int64_t m_value_active;
  int64_t m_value_hidden;
};

} //~namespace ribi

#endif // SLSQFILTER_H
