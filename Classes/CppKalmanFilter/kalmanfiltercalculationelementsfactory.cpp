#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorPperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "kalmanfiltercalculationelementsfactory.h"

#include <cassert>

#include "standardkalmanfiltercalculationelements.h"
#include "steadystatekalmanfiltercalculationelements.h"
#include "fixedlagsmootherkalmanfiltercalculationelements.h"


const boost::shared_ptr<KalmanFilterCalculationElements> KalmanFilterCalculationElementsFactory::Create(
  const KalmanFilterType type)
{
  boost::shared_ptr<KalmanFilterCalculationElements> p;
  switch (type)
  {
    case KalmanFilterType::fixed_lag_smoother:
      p.reset(new FixedLagSmootherKalmanFilterCalculationElements);
    break;
    case KalmanFilterType::standard:
      p.reset(new StandardKalmanFilterCalculationElements);
    break;
    case KalmanFilterType::steady_state:
      p.reset(new SteadyStateKalmanFilterCalculationElements);
    break;
    case KalmanFilterType::n_types:
      assert(!"Unimplemented KalmanFilterType");
  }
  assert(p);
  assert(p->GetType() == type);
  return p;
}

const boost::shared_ptr<KalmanFilterCalculationElements> KalmanFilterCalculationElementsFactory::DeepCopy(
  const boost::shared_ptr<KalmanFilterCalculationElements>& original)
{
  assert(original);

  const boost::shared_ptr<KalmanFilterCalculationElements> my_copy = original->Clone();

  assert(my_copy);
  assert(original->GetType() == my_copy->GetType());

  return my_copy;
}
