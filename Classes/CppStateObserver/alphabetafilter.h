#ifndef ALPHABETAFILTER_H
#define ALPHABETAFILTER_H

#include <string>
#include <vector>

struct AlphaBetaFilter
{
  AlphaBetaFilter(
    const double alpha = 0.1 ,
    const double beta  = 0.01,
    const double dt    = 1.0
  );

  double Estimate(const double measurement);

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  private:
  const double m_alpha;
  const double m_beta;
  const double m_dt;

  double m_slope;
  double m_output;
};

#endif // ALPHABETAFILTER_H
