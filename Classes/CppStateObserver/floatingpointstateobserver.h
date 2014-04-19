#ifndef FLOATINGPOINTSTATEOBSERVER_H
#define FLOATINGPOINTSTATEOBSERVER_H

#include <string>
#include <vector>

namespace ribi {

///An observer for floating point values:
///The measurements it works must be floating point,
///The estimates it gives will be floating point
struct FloatingPointStateObserver
{
  ///ABC must have public virtual destructor
  // * Herb Sutter, Andrei Alexandrescu. C++ coding standards: 101 rules, guidelines, and best practices.
  //   ISBN: 0-32-111358-6. Item 50: 'Make base class destructors public and virtual, or protected and nonvirtual'
  virtual ~FloatingPointStateObserver() {}

  ///Get the current state estimate
  virtual double GetEstimate() const = 0;

  ///Supply a measurement, which will update the state estimate
  virtual void Update(const double measurement) = 0;

  ///Obtain the version of this class
  static std::string GetVersion();

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory();
};

} //~namespace ribi

#endif // FLOATINGPOINTSTATEOBSERVER_H
