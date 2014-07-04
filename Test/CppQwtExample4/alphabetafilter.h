#ifndef ALPHABETAFILTER_H
#define ALPHABETAFILTER_H

struct AlphaBetaFilter
{
  AlphaBetaFilter(
    const double alpha = 0.1 ,
    const double beta  = 0.01,
    const double dt    = 1.0
  );

  double Estimate(const double input);

  private:
  const double m_alpha;
  const double m_beta;
  const double m_dt;

  double m_hidden;
  double m_output;
};

#endif // ALPHABETAFILTER_H
