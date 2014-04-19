#include "kalmanfilter.h"

std::string ribi::kalman::KalmanFilter::GetVersion() noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::kalman::KalmanFilter::GetVersionHistory() noexcept
{
  return {
    "2013-05-06: version 1.0: initial version",
    "2013-09-09: version 1.1: removed data members"
  };
}
