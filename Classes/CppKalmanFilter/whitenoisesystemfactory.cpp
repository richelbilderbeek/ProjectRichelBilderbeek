#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "whitenoisesystemfactory.h"
#pragma GCC diagnostic pop

#include <cassert>
#include "gapsfilledwhitenoisesystemfactory.h"
#include "laggedwhitenoisesystemfactory.h"
#include "standardwhitenoisesystemfactory.h"
#include "testtimer.h"

ribi::kalman::WhiteNoiseSystemFactory::WhiteNoiseSystemFactory()
{
  #ifndef NDEBUG
  Test();
  #endif
}

boost::shared_ptr<ribi::kalman::WhiteNoiseSystem> ribi::kalman::WhiteNoiseSystemFactory::Create(
  const boost::shared_ptr<WhiteNoiseSystemParameters>& parameters) const noexcept
{
  boost::shared_ptr<WhiteNoiseSystem> p;
  switch (parameters->GetType())
  {
    case WhiteNoiseSystemType::gaps_filled:
      p = GapsFilledWhiteNoiseSystemFactory().Create(parameters);
      break;
    case WhiteNoiseSystemType::lagged:
      p = LaggedWhiteNoiseSystemFactory().Create(parameters);
      break;
    case WhiteNoiseSystemType::standard:
      p = StandardWhiteNoiseSystemFactory().Create(parameters);
      break;
    case WhiteNoiseSystemType::n_types:
      assert(!"Unimplemented white noise system");
      throw std::logic_error(__func__);
  }
  assert(p);
  return p;
}

#ifndef NDEBUG
void ribi::kalman::WhiteNoiseSystemFactory::Test() noexcept
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
