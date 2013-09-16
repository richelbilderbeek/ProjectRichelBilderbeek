#ifndef INTEGERALPHAFILTER_H
#define INTEGERALPHAFILTER_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "integerstateobserver.h"
#pragma GCC diagnostic pop

namespace ribi {

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
  static const std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory() noexcept;

  private:

  ///The bitshift used for division
  int m_alpha;

  int64_t m_value_active;
};

} //~namespace ribi

#endif // INTEGERALPHAFILTER_H
