#ifndef MULTIINTEGERSTATEOBSERVER_H
#define MULTIINTEGERSTATEOBSERVER_H

#include <vector>
#include <boost/shared_ptr.hpp>
#include "integeralphafilter.h"
#include "integerstateobserver.h"

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
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  private:
  std::vector<boost::shared_ptr<IntegerStateObserver> > m_filters;
};

} //~namespace ribi

#endif // MULTIINTEGERSTATEOBSERVER_H
