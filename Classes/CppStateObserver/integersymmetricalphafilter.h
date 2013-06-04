#ifndef INTEGERSYMMETRICALPHAFILTER_H
#define INTEGERSYMMETRICALPHAFILTER_H

#include <string>
#include <vector>

#include "integerstateobserver.h"

struct IntegerSymmetricalAlphaFilter : public IntegerStateObserver
{
  IntegerSymmetricalAlphaFilter(
    const int alpha,
    const int64_t value_active = 0);

  int64_t Estimate(const int64_t measurement);

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  private:
  ///The bitshift used for division
  int m_alpha;
  int64_t m_value_active;
};

#endif // INTEGERSYMMETRICALPHAFILTER_H
