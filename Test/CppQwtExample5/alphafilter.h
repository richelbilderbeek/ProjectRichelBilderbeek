#ifndef ALPHAFILTER_H
#define ALPHAFILTER_H

struct AlphaFilter
{
  AlphaFilter(
    const double alpha = 0.1 ,
    const double dt    = 1.0
  );

  double Estimate(const double input);

  private:
  const double m_alpha;
  const double m_dt;

  double m_output;
};

#endif // ALPHAFILTER_H
