#ifndef INTEGERSTATEOBSERVER_H
#define INTEGERSTATEOBSERVER_H

#include <cinttypes>
#include <string>
#include <vector>

namespace ribi {

///An observer for integer values:
///The measurements it works must be int,
///The estimates it gives will be int
struct IntegerStateObserver
{
  virtual ~IntegerStateObserver() noexcept {}

  ///Get the current state estimate
  virtual int64_t GetEstimate() const = 0;

  ///Supply a measurement, which will update the state estimate
  virtual void Update(const int64_t measurement) = 0;

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;
};

} //~namespace ribi

#endif // INTEGERSTATEOBSERVER_H
