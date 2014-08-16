#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "standardkalmanfilter.h"

#include <boost/numeric/conversion/cast.hpp>

#include "matrix.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::kalman::StandardKalmanFilter::StandardKalmanFilter(
  const boost::shared_ptr<StandardKalmanFilterCalculationElements>& calculation,
  const boost::shared_ptr<const KalmanFilterParameters>& parameters
  )
  : KalmanFilter{},
    m_covariance_estimate{boost::dynamic_pointer_cast<const StandardKalmanFilterParameters>(parameters)->GetInitialCovarianceEstimate()},
    m_last_standard_calculation{boost::dynamic_pointer_cast<StandardKalmanFilterCalculationElements>(calculation)},
    m_standard_parameters{boost::dynamic_pointer_cast<const StandardKalmanFilterParameters>(parameters)},
    m_state_estimate{boost::dynamic_pointer_cast<const StandardKalmanFilterParameters>(parameters)->GetInitialStateEstimate()}
{
  assert(m_last_standard_calculation);
  assert(m_standard_parameters);
  assert(this->GetType() == m_last_standard_calculation->GetType());
  assert(this->GetType() == parameters->GetType());
  assert(this->GetType() == m_standard_parameters->GetType());
  assert(this->GetType() == GetParameters()->GetType()
    && "Initialize each Kalman filter type with the right type of parameters");

  //m_covariance_estimate = m_standard_parameters->GetInitialCovarianceEstimate();
  //m_state_estimate = m_standard_parameters->GetInitialStateEstimate();

  //Do not initialize the calculation yet
  //m_last_standard_calculation->m_predicted_state = m_standard_parameters->GetInitialStateEstimate();
  //m_last_standard_calculation->m_predicted_covariance = m_standard_parameters->GetInitialCovarianceEstimate();

  #ifndef NDEBUG
  //Check for correct dimensionality
  const auto sz = m_state_estimate.size();
  assert(m_standard_parameters->GetControl().size1() == sz);
  assert(m_standard_parameters->GetControl().size2() == sz);
  assert(m_standard_parameters->GetEstimatedMeasurementNoise().size1() == sz);
  assert(m_standard_parameters->GetEstimatedMeasurementNoise().size2() == sz);
  assert(m_standard_parameters->GetObservation().size1() == sz);
  assert(m_standard_parameters->GetObservation().size2() == sz);
  assert(m_covariance_estimate.size1() == sz);
  assert(m_covariance_estimate.size2() == sz);
  assert(m_standard_parameters->GetEstimatedProcessNoiseCovariance().size1() == sz);
  assert(m_standard_parameters->GetEstimatedProcessNoiseCovariance().size2() == sz);
  assert(m_standard_parameters->GetStateTransition().size1() == sz);
  assert(m_standard_parameters->GetStateTransition().size2() == sz);
  assert(m_state_estimate.size() == sz);
  #endif
}

int ribi::kalman::StandardKalmanFilter::GetStateSize() const noexcept
{
  const int sz = boost::numeric_cast<int>(m_state_estimate.size());
  return sz;
}

std::string ribi::kalman::StandardKalmanFilter::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::kalman::StandardKalmanFilter::GetVersionHistory() noexcept
{
  return {
    "2013-04-28: version 1.0: initial version"
  };
}

boost::numeric::ublas::vector<double> ribi::kalman::StandardKalmanFilter::PredictState(
  const boost::numeric::ublas::vector<double>& input) const
{
  const boost::numeric::ublas::vector<double> state_prediction
    = Matrix::Prod(m_standard_parameters->GetStateTransition(),m_state_estimate)
    + Matrix::Prod(m_standard_parameters->GetControl(),input);
  return state_prediction;
}

boost::numeric::ublas::matrix<double> ribi::kalman::StandardKalmanFilter::PredictCovariance() const
{
  const boost::numeric::ublas::matrix<double> covariance_prediction
    = Matrix::MultiProd(
      m_standard_parameters->GetStateTransition(),
      m_covariance_estimate,
      trans(m_standard_parameters->GetStateTransition())
    )
    + m_standard_parameters->GetEstimatedProcessNoiseCovariance();
  return covariance_prediction;
}


void ribi::kalman::StandardKalmanFilter::SupplyMeasurementAndInput(
  const boost::numeric::ublas::vector<double>& measurements,
  const boost::numeric::ublas::vector<double>& input)
{
  
  using boost::numeric::ublas::identity_matrix;
  using boost::numeric::ublas::matrix;
  using boost::numeric::ublas::trans;
  using boost::numeric::ublas::vector;
  
  ///Debug statements to keep code below clean
  assert(measurements.size() == input.size());
  
  assert(m_standard_parameters->GetStateTransition().size2() == m_covariance_estimate.size1());
  
  assert(Matrix::Prod(m_standard_parameters->GetStateTransition(),m_covariance_estimate).size2()
    ==  trans(m_standard_parameters->GetStateTransition()).size1() );
  
  assert(matrix<double>(Matrix::Prod(
      matrix<double>(Matrix::Prod(m_standard_parameters->GetStateTransition(),m_covariance_estimate)),
      trans(m_standard_parameters->GetStateTransition()))).size1()
    == m_standard_parameters->GetEstimatedProcessNoiseCovariance().size1());
  
  assert(matrix<double>(Matrix::Prod(
      matrix<double>(Matrix::Prod(m_standard_parameters->GetStateTransition(),m_covariance_estimate)),
      trans(m_standard_parameters->GetStateTransition()))).size2()
    == m_standard_parameters->GetEstimatedProcessNoiseCovariance().size2());
  



  //Store calculation for KalmanFilterExperiment
  m_last_standard_calculation->Clear();
  //assert(!m_last_standard_calculation->IsComplete()); //Can be empty and thus complete
  m_last_standard_calculation->SetPreviousStateEstimate(this->GetStateEstimate()); //1
  assert(!m_last_standard_calculation->IsComplete() || input.empty()); //Can be empty or incomplete
  m_last_standard_calculation->SetPreviousCovarianceEstimate(this->GetEstimationErrorCovariance()); //2

  
  // 1/7) State prediction
  const vector<double> state_prediction = PredictState(input);
  // 2/7) Covariance prediction
  const matrix<double> covariance_prediction = PredictCovariance();
  // 3/7) Innovation (y with a squiggle above it)
  const vector<double> innovation = measurements - Matrix::Prod(m_standard_parameters->GetObservation(),state_prediction);
  // 4/7) Innovation covariance (S)
  const matrix<double> innovation_covariance
    = Matrix::MultiProd(m_standard_parameters->GetObservation(),covariance_prediction,trans(m_standard_parameters->GetObservation()))
    + m_standard_parameters->GetEstimatedMeasurementNoise();
  // 5/7) Kalman gain (K)
  
  if (Matrix::CalcDeterminant(innovation_covariance) == 0.0)
  {
    throw std::runtime_error("Innovation covariance became degenerate");
  }
  
  const matrix<double> kalman_gain
    = Matrix::MultiProd(covariance_prediction,trans(m_standard_parameters->GetObservation()),Matrix::Inverse(innovation_covariance));
  // 6/7) Update state prediction
  m_state_estimate = state_prediction + Matrix::Prod(kalman_gain,innovation);
  // 7/7) Update covariance prediction
  const identity_matrix<double> my_identity_matrix(kalman_gain.size1());
  m_covariance_estimate = Matrix::Prod(
    my_identity_matrix
      - Matrix::Prod(kalman_gain,m_standard_parameters->GetObservation()),
    covariance_prediction
  );

  //Store calculation for KalmanFilterExperiment
  
  m_last_standard_calculation->SetPredictedState(state_prediction); //1
  m_last_standard_calculation->SetPredictedCovariance(covariance_prediction); //2
  m_last_standard_calculation->SetInnovation(innovation); //3
  m_last_standard_calculation->SetMeasurement(measurements); //3
  m_last_standard_calculation->SetInnovationCovariance(innovation_covariance); //4
  m_last_standard_calculation->SetKalmanGain(kalman_gain); //5
  m_last_standard_calculation->SetUpdatedState(m_state_estimate); //6
  m_last_standard_calculation->SetUpdatedCovariance(m_covariance_estimate); //7
  assert(m_last_standard_calculation->IsComplete());
  
}

