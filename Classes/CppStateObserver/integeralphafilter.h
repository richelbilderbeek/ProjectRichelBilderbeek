#ifndef INTEGERALPHAFILTER_H
#define INTEGERALPHAFILTER_H

#include <string>
#include <vector>
#include "integerstateobserver.h"

struct IntegerAlphaFilter : public IntegerStateObserver
{
  IntegerAlphaFilter(
    const int alpha,
    const int64_t value_active = 0);

  ///Get the current state estimate
  int64_t GetEstimate() const { return m_value_active; }

  ///Supply a measurement, which will update the state estimate
  void Update(const int64_t measurement);

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  private:

  ///The bitshift used for division
  int m_alpha;

  int64_t m_value_active;
};

#endif // INTEGERALPHAFILTER_H
