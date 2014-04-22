#include "slidingmodeobserver.h"

#ifdef TRY_GETTING_SLIDINGMODEOBSERVER_RIGHT_ONCE_8234752798253978650738

#include <cassert>
#include <cmath>

#include <boost/numeric/ublas/io.hpp>

#include "kalmanfilterexample.h"
#include "steadystatekalmanfilter.h"
#include "steadystatekalmanfilterfactory.h"
#include "trace.h"

SlidingModeObserver::SlidingModeObserver(const double d)
  : m_filter(CreateFilter(2,d))
    //m_control(CreateControl(2)),
    //m_state_estimates(boost::numeric::ublas::vector<double>(2,0.0)),
    //m_state_transition(CreateStateTransition(2,d))
{
  assert(m_filter);
  assert(m_filter->GetStateSize() == 2
    && "Only support two state estimates");
}


const boost::shared_ptr<SteadyStateKalmanFilter> SlidingModeObserver::CreateFilter(const int size, const double )
{
  assert(size == 2
    && "Only support two state estimates");

  const boost::shared_ptr<KalmanFilterExample> example = KalmanFilterExample::CreateExample9();
  assert(example);

  const boost::numeric::ublas::matrix<double> control
    = example->GetKalmanFilterParameters()->GetControl();
  const boost::numeric::ublas::vector<double> initial_state_estimate
    = boost::numeric::ublas::vector<double>(2, static_cast<double>(RAND_MAX) );
  assert(initial_state_estimate(0) == static_cast<double>(RAND_MAX));
  assert(initial_state_estimate(1) == static_cast<double>(RAND_MAX));
    //= example->GetKalmanFilterParameters()->GetInitialStateEstimate();
  const boost::numeric::ublas::matrix<double> observation
    = example->GetKalmanFilterParameters()->GetObservation();
  const boost::numeric::ublas::matrix<double> state_transition
    = example->GetKalmanFilterParameters()->GetStateTransition();
  const boost::numeric::ublas::matrix<double> initial_covariance
    = example->GetKalmanFilterParameters()->GetInitialCovarianceEstimate();
  const boost::numeric::ublas::matrix<double> measurement_noise
    = example->GetKalmanFilterParameters()->GetEstimatedMeasurementNoise();
  const boost::numeric::ublas::matrix<double> estimated_optimal_kalman_gain
    = SteadyStateKalmanFilterParameters::CalculateOptimalKalmanGain(
        initial_covariance,
        measurement_noise,
        observation,
        state_transition
      );

  const boost::shared_ptr<SteadyStateKalmanFilterParameters> parameters(
    new SteadyStateKalmanFilterParameters(
      control,
      estimated_optimal_kalman_gain,
      initial_state_estimate,
      observation,
      state_transition
    )
  );
  assert(parameters);

  const boost::shared_ptr<SteadyStateKalmanFilter> filter
    = SteadyStateKalmanFilterFactory::Create(parameters);
  assert(filter);

  //Give the filter a head start
  boost::numeric::ublas::vector<double> measurements(2,0.0);
  measurements(1) = static_cast<double>(RAND_MAX);
  const boost::numeric::ublas::vector<double> input(2,0.0);
  filter->SupplyMeasurementAndInput(measurements,input);

  return filter;
}


const boost::numeric::ublas::matrix<double> SlidingModeObserver::CreateControl(const int size)
{
  assert(size == 2);
  boost::numeric::ublas::matrix<double> m(2,2,0.0);
  m(0,0) = 1.0;
  return m;
}

const boost::numeric::ublas::matrix<double> SlidingModeObserver::CreateInitialCovariance(const int size)
{
  boost::numeric::ublas::matrix<double> m
    = boost::numeric::ublas::zero_matrix<double>(size);
  m(0,0) = 1.0;
  return m;
}

const boost::numeric::ublas::matrix<double> SlidingModeObserver::CreateObservation(const int size)
{
  boost::numeric::ublas::matrix<double> m
    = boost::numeric::ublas::identity_matrix<double>(size,size);
  m(0,0) = 1.0;
  m(1,1) = 1.0;
  return m;
}

const boost::numeric::ublas::matrix<double> SlidingModeObserver::CreateStateTransition(const int size, const double d)
{
  assert(size == 2);
  assert(d >= 0.0);
  assert(d <= 1.0);
  boost::numeric::ublas::matrix<double> m(2,2,0.0);
  m(0,0) = 1.0 - d;
  m(1,0) = 0.0 + d;
  m(0,1) = 0.0;
  m(1,1) = 1.0 - d;
  return m;
}


double SlidingModeObserver::Estimate(const double measurement)
{
  const boost::numeric::ublas::vector<double> input = boost::numeric::ublas::zero_vector<double>(2);

  boost::numeric::ublas::vector<double> prediction = m_filter->PredictState(input);

  boost::numeric::ublas::vector<double> measurements = boost::numeric::ublas::zero_vector<double>(2);
  //measurements(0) = measurement;
  measurements(0) = measurement;

  m_filter->SupplyMeasurementAndInput(measurements,input);

  return prediction(1);
  /*
  assert(m_state_estimates.size() == 2);

  boost::numeric::ublas::vector<double> input_vector(2,0.0);
  input_vector(0) = input;

  m_state_estimates
  = boost::numeric::ublas::prod(m_state_transition,m_state_estimates)
  + boost::numeric::ublas::prod(m_control,input_vector);

  return m_state_estimates(1);
  */
}


#endif
