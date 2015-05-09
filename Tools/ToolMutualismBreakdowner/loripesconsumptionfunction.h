#ifndef LORIPESCONSUMPTIONFUNCTION_H
#define LORIPESCONSUMPTIONFUNCTION_H

///The idea is that the more seagrass is present,
///the more Loripes can consume sulfide, because
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
  ///The fraction that will survive
  virtual double operator()(const double seagrass_density) const noexcept = 0;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

struct InvertedExponentialConsumption : LoripesConsumptionFunction
{
  InvertedExponentialConsumption(const double r = 0.05);
  ~InvertedExponentialConsumption() {}
  ///The fraction that will survive
  double operator()(const double seagrass_density) const noexcept override;
  const double m_r;
};


#endif // LORIPESCONSUMPTIONFUNCTION_H
