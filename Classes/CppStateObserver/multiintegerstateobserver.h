#ifndef MULTIINTEGERSTATEOBSERVER_H
#define MULTIINTEGERSTATEOBSERVER_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "integeralphafilter.h"
#include "integerstateobserver.h"
#pragma GCC diagnostic pop

namespace ribi {

struct MultiIntegerStateObserver : public IntegerStateObserver
{
  MultiIntegerStateObserver(
    std::vector<boost::shared_ptr<IntegerStateObserver> >& filters
  );

  ///Get the current state estimate
  int64_t GetEstimate() const;

  ///Supply a measurement, which will update the state estimate
  void Update(const int64_t measurement);

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  private:
  std::vector<boost::shared_ptr<IntegerStateObserver> > m_filters;
};

} //~namespace ribi

#endif // MULTIINTEGERSTATEOBSERVER_H
