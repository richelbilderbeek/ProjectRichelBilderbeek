#ifndef LORIPESCONSUMPTIONFUNCTION_H
#define LORIPESCONSUMPTIONFUNCTION_H

#include <iosfwd>
#include <memory>

#include "speciesdensity.h"

///The idea is that the more seagrass is present,
///the more Loripes lucinalis can consume sulfide, because
///
///the seagrass supplies it with oxygen
/*


 Sulfide consumption by Loripes

 |      __________
 |  _---
 | /
 |/
 +---------------- -> seagrass density

*/
struct LoripesConsumptionFunction
{
  LoripesConsumptionFunction()
  {
    #ifndef NDEBUG
    Test();
    #endif
  }
  virtual ~LoripesConsumptionFunction() {}
  ///The rate at which Loripes consumes sulfide
  virtual double CalculateConsumptionRate(const ribi::units::SpeciesDensity seagrass_density) const noexcept = 0;
  virtual std::string ToStr() const noexcept = 0;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

struct InvertedExponentialConsumption : LoripesConsumptionFunction
{
  InvertedExponentialConsumption(const double r = 0.05);
  ~InvertedExponentialConsumption() {}
  ///The rate at which Loripes consumes sulfide
  double CalculateConsumptionRate(const ribi::units::SpeciesDensity seagrass_density) const noexcept override;
  std::string ToStr() const noexcept override;
  const double m_r;
};

std::ostream& operator<<(std::ostream& os, const LoripesConsumptionFunction& f) noexcept;
std::istream& operator>>(std::istream& is, std::shared_ptr<LoripesConsumptionFunction>& f) noexcept;

#endif // LORIPESCONSUMPTIONFUNCTION_H
