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
  ///ABC must have public virtual destructor
  // * Herb Sutter, Andrei Alexandrescu. C++ coding standards: 101 rules, guidelines, and best practices.
  //   ISBN: 0-32-111358-6. Item 50: 'Make base class destructors public and virtual, or protected and nonvirtual'
  virtual ~IntegerStateObserver() {}

  ///Get the current state estimate
  virtual int64_t GetEstimate() const = 0;

  ///Supply a measurement, which will update the state estimate
  virtual void Update(const int64_t measurement) = 0;

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();
};

} //~namespace ribi

#endif // INTEGERSTATEOBSERVER_H
