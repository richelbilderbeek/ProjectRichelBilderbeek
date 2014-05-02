#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "steadystatekalmanfilter.h"

#include <boost/numeric/conversion/cast.hpp>

#include "matrix.h"
#include "kalmanfilter.h"
#include "kalmanfilterparameters.h"
#include "steadystatekalmanfilterparameters.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::kalman::SteadyStateKalmanFilter::SteadyStateKalmanFilter(
  const boost::shared_ptr<KalmanFilterCalculationElements>& calculation,
  const boost::shared_ptr<const KalmanFilterParameters>& parameters)
  : KalmanFilter{},
    m_last_calculation{boost::dynamic_pointer_cast<SteadyStateKalmanFilterCalculationElements>(calculation)},
    m_parameters{boost::dynamic_pointer_cast<const SteadyStateKalmanFilterParameters>(parameters)},
    m_state_estimate{dynamic_cast<const SteadyStateKalmanFilterParameters*>(parameters.get())->GetInitialStateEstimate()}
{
  assert(m_last_calculation);
  assert(m_parameters
    && "Initialize each Kalman filter type with the right type of parameters");
  #ifndef NDEBUG
  //Check for correct dimensionality
  const auto sz = m_state_estimate.size();
  assert(m_parameters->GetControl().size1() == sz);
  assert(m_parameters->GetControl().size2() == sz);
  assert(m_parameters->GetEstimatedOptimalKalmanGain().size1() == sz);
  assert(m_parameters->GetEstimatedOptimalKalmanGain().size2() == sz);
  assert(m_parameters->GetObservation().size1() == sz);
  assert(m_parameters->GetObservation().size2() == sz);
  assert(m_parameters->GetStateTransition().size1() == sz);
  assert(m_parameters->GetStateTransition().size2() == sz);
  assert(m_state_estimate.size() == sz);
  #endif

  //Initialize the last calculation with null values
  //NEW 2013-05-23
  //m_last_calculation->SetMeasurement(
  //  boost::numeric::ublas::zero_vector<double>(m_state_estimate.size()));
  //m_last_calculation->SetPredictedState(m_parameters->GetInitialStateEstimate());
  //m_last_calculation->SetPreviousStateEstimate(m_parameters->GetInitialStateEstimate());
  //m_last_calculation->SetUpdatedState(m_parameters->GetInitialStateEstimate());
}

int ribi::kalman::SteadyStateKalmanFilter::GetStateSize() const noexcept
{
  const int sz = boost::numeric_cast<int>(m_state_estimate.size());
  return sz;
}

std::string ribi::kalman::SteadyStateKalmanFilter::GetVersion() noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::kalman::SteadyStateKalmanFilter::GetVersionHistory() noexcept
{
  return {
    "2013-05-01: version 1.0: initial version",
    "2013-05-06: version 1.1: inherits from KalmanFilter"
  };
}

boost::numeric::ublas::vector<double> ribi::kalman::SteadyStateKalmanFilter::PredictState(
  const boost::numeric::ublas::vector<double>& input) const
{
  const boost::numeric::ublas::matrix<double> term_a
    = m_parameters->GetStateTransition()
    - Matrix::Prod(
      m_parameters->GetEstimatedOptimalKalmanGain(),
      m_parameters->GetObservation()
    );

  //m_last_measured must be set before calling PredictState!
  assert(!m_last_calculation->GetMeasurement().empty());

  const boost::numeric::ublas::vector<double> state_prediction
    = Matrix::Prod(term_a,this->GetStateEstimate())
    + Matrix::Prod(m_parameters->GetControl(),input)
    + Matrix::Prod(m_parameters->GetEstimatedOptimalKalmanGain(),m_last_calculation->GetMeasurement());
  return state_prediction;
}

void ribi::kalman::SteadyStateKalmanFilter::SupplyMeasurementAndInput(
  const boost::numeric::ublas::vector<double>& measurements,
  const boost::numeric::ublas::vector<double>& input)
{
  
  assert(measurements.size() == input.size());

  //Store the calculation
  m_last_calculation->Clear();
  assert(!m_last_calculation->IsComplete());
  m_last_calculation->SetPreviousStateEstimate(this->GetStateEstimate());

  //m_last_calculation->SetMeasurement must be set before calling PredictState!
  m_last_calculation->SetMeasurement(measurements);

  // 1/1) State prediction
  const boost::numeric::ublas::vector<double> state_prediction = PredictState(input);
  m_state_estimate = state_prediction;

  //Store the calculation
  m_last_calculation->SetPredictedState(state_prediction);
  m_last_calculation->SetUpdatedState(GetStateEstimate());
  assert(m_last_calculation->IsComplete());
}

