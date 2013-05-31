#ifndef LSQFILTER_H
#define LSQFILTER_H

struct LsqFilter
{
  LsqFilter(
    const int filter_shift,
    const int value_active = 0,
    const int value_hidden = 0);

  int Estimate(const int measurement);

  private:
  int m_val1;
  int m_val2;
  int m_filter_shift;
};

#endif // LSQFILTER_H
