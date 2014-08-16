#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "kalmanfiltercalculationelementsfactory.h"
#pragma GCC diagnostic pop

#include <cassert>

#include "standardkalmanfiltercalculationelements.h"
#include "steadystatekalmanfiltercalculationelements.h"
#include "fixedlagsmootherkalmanfiltercalculationelements.h"
#include "testtimer.h"

ribi::kalman::KalmanFilterCalculationElementsFactory::KalmanFilterCalculationElementsFactory()
{
  #ifndef NDEBUG
  Test();
  #endif
}

boost::shared_ptr<ribi::kalman::KalmanFilterCalculationElements>
  ribi::kalman::KalmanFilterCalculationElementsFactory::Create(
  const KalmanFilterType type) const noexcept
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

boost::shared_ptr<ribi::kalman::KalmanFilterCalculationElements> ribi::kalman::KalmanFilterCalculationElementsFactory::DeepCopy(
  const boost::shared_ptr<KalmanFilterCalculationElements>& original) const noexcept
{
  assert(original);

  const boost::shared_ptr<KalmanFilterCalculationElements> my_copy = original->Clone();

  assert(my_copy);
  assert(original->GetType() == my_copy->GetType());

  return my_copy;
}

#ifndef NDEBUG
void ribi::kalman::KalmanFilterCalculationElementsFactory::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    //Matrix();
    //const boost::shared_ptr<LaggedWhiteNoiseSystem> my_system
    //  = LaggedWhiteNoiseSystemFactory().Create(
    //    Matrix::CreateMatrix(1,1, { 1.0 } ), //control
    //    Matrix::CreateVector(     { 0.0 } ), //initial_state,
    //    0,
    //    Matrix::CreateVector(     { 0.0 } ), //real_measurement_noise
    //    Matrix::CreateVector(     { 0.0 } ), //real_process_noise
    //    Matrix::CreateMatrix(1,1, { 1.0 } )  //state_transition
    //);
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
