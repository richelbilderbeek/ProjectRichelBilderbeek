#ifndef MULTIINTEGERSTATEOBSERVER_H
#define MULTIINTEGERSTATEOBSERVER_H

#include <vector>
#include <boost/shared_ptr.hpp>
#include "integeralphafilter.h"

struct MultiIntegerStateObserver
{
  MultiIntegerStateObserver(
    std::vector<boost::shared_ptr<IntegerStateObserver> >& filters
  );

  int64_t Estimate(const int64_t measurement);

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  private:
  std::vector<boost::shared_ptr<IntegerStateObserver> > m_filters;
};

#endif // MULTIINTEGERSTATEOBSERVER_H
