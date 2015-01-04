#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtkalmanfilterexperimentmodel.h"

#include <cassert>
#include <string>
#include <vector>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QAbstractTableModel>
#include <QMessageBox>

#include "container.h"
#include "fixedlagsmootherkalmanfilterparameters.h"
#include "gapsfilledwhitenoisesystemparameters.h"
#include "kalmanfilterexperimentparameter.h"
#include "kalmanfilterfactory.h"
#include "kalmanfilterparameters.h"
#include "kalmanfilterparametertype.h"
#include "kalmanfiltertypes.h"
#include "laggedwhitenoisesystemparameters.h"
#include "matrix.h"
#include "qtkalmanfilterermodel.h"
#include "ribi_regex.h"
#include "standardkalmanfilterparameters.h"
#include "standardkalmanfilterparameters.h"
#include "standardwhitenoisesystemfactory.h"
#include "standardwhitenoisesystemparameters.h"
#include "templocale.h"
#include "testtimer.h"
#include "trace.h"
#include "whitenoisesystemfactory.h"
#include "whitenoisesystemparameters.h"
#include "whitenoisesystemtype.h"
#include "whitenoisesystemtypes.h"

#pragma GCC diagnostic pop

boost::numeric::ublas::matrix<double> ConvertToUblasMatrixDouble(
  const boost::numeric::ublas::matrix<std::string>& v
) noexcept
{

  boost::numeric::ublas::matrix<double> w(v.size1(),v.size2());
  const std::size_t n_rows = v.size1();
  const std::size_t n_cols = v.size2();
  for (std::size_t row=0; row!=n_rows; ++row)
  {
    for (std::size_t col=0; col!=n_cols; ++col)
    {
      #ifndef NDEBUG
      assert(row < v.size1());
      assert(col < v.size2());
      assert(row < w.size1());
      assert(col < w.size2());
      try { boost::lexical_cast<double>(v(row,col)); }
      catch (boost::bad_lexical_cast&)
      {
        TRACE("ERBREAKROR");
        TRACE(v(row,col));
        TRACE("BREAK");
        assert(!"Should not get here");
      }
      #endif
      w(row,col) = boost::lexical_cast<double>(v(row,col));
    }
  }
  return w;
}

boost::numeric::ublas::vector<int> ConvertToUblasVectorInt(const boost::numeric::ublas::matrix<std::string>& v) noexcept
{
  boost::numeric::ublas::vector<int> w(v.size1());
  const std::size_t n_rows = v.size1();
  assert(v.size2() == 1);
  const std::size_t n_cols = 1;
  for (std::size_t row=0; row!=n_rows; ++row)
  {
    for (std::size_t col=0; col!=n_cols; ++col)
    {
      #ifndef NDEBUG
      assert(row < v.size1());
      assert(col < v.size2());
      assert(row < w.size());
      assert(col < 1);
      try { boost::lexical_cast<int>(v(row,col)); }
      catch (boost::bad_lexical_cast&) { assert(!"Should not get here"); }
      #endif
      w(row) = boost::lexical_cast<int>(v(row,col));
    }
  }
  return w;
}

boost::numeric::ublas::vector<double> ConvertToUblasVectorDouble(const boost::numeric::ublas::matrix<std::string>& v) noexcept
{
  boost::numeric::ublas::vector<double> w(v.size1());
  const std::size_t n_rows = v.size1();
  assert(v.size2() == 1);
  const std::size_t n_cols = 1;
  for (std::size_t row=0; row!=n_rows; ++row)
  {
    for (std::size_t col=0; col!=n_cols; ++col)
    {
      #ifndef NDEBUG
      assert(row < v.size1());
      assert(col < v.size2());
      assert(row < w.size());
      assert(col < 1);
      try { boost::lexical_cast<double>(v(row,col)); }
      catch (boost::bad_lexical_cast&) { assert(!"Should not get here"); }
      #endif
      w(row) = boost::lexical_cast<double>(v(row,col));
    }
  }
  return w;
}

std::vector<std::string> ConvertToVectorString(const boost::numeric::ublas::matrix<std::string>& v)
{
  std::vector<std::string> w(v.size1());
  const std::size_t n_rows = v.size1();
  assert(v.size2() == 1);
  const std::size_t n_cols = 1;
  for (std::size_t row=0; row!=n_rows; ++row)
  {
    for (std::size_t col=0; col!=n_cols; ++col)
    {
      #ifndef NDEBUG
      assert(row < v.size1());
      assert(col < v.size2());
      assert(row < w.size());
      assert(col < 1);
      #endif
      w[row] = v(row,col);
    }
  }
  return w;
}

const int ribi::kalman::QtKalmanFilterExperimentModel::m_version_current = 2;

ribi::kalman::QtKalmanFilterExperimentModel::QtKalmanFilterExperimentModel(QObject *parent) noexcept
 : QObject(parent),
   m_signal_context_changed{},
   m_signal_kalman_filter_type_changed{},
   m_signal_number_of_timesteps_changed{},
   m_signal_white_noise_system_type_changed{},
   m_context{},
   m_kalman_filter_type(KalmanFilterType::standard),
   m_lag_estimated(0),
   m_lag_real(0),
   m_models(CreateMap()),
   m_number_of_timesteps(0),
   m_version(m_version_current),
   m_white_noise_system_type(WhiteNoiseSystemType::standard)
{
  #ifndef NDEBUG
  Test();
  assert(IsValid());

  const int n_rows = Find(KalmanFilterExperimentParameterType::state_names)->rowCount();
  const int n_cols = n_rows == 0 ? 0 : n_rows;
  assert(Find(KalmanFilterExperimentParameterType::control)->columnCount() == n_rows);
  assert(Find(KalmanFilterExperimentParameterType::control)->rowCount() == n_rows);
  assert(Find(KalmanFilterExperimentParameterType::estimated_measurement_noise)->columnCount() == n_rows);
  assert(Find(KalmanFilterExperimentParameterType::estimated_measurement_noise)->rowCount() == n_rows);
  assert(Find(KalmanFilterExperimentParameterType::estimated_optimal_kalman_gain)->columnCount() == n_rows);
  assert(Find(KalmanFilterExperimentParameterType::estimated_optimal_kalman_gain)->rowCount() == n_rows);
  assert(Find(KalmanFilterExperimentParameterType::estimated_process_noise_covariance)->columnCount() == n_rows);
  assert(Find(KalmanFilterExperimentParameterType::estimated_process_noise_covariance)->rowCount() == n_rows);
  assert(Find(KalmanFilterExperimentParameterType::initial_covariance_estimate)->columnCount() == n_rows);
  assert(Find(KalmanFilterExperimentParameterType::initial_covariance_estimate)->rowCount() == n_rows);
  assert(Find(KalmanFilterExperimentParameterType::initial_state_estimate)->columnCount() == n_cols);
  assert(Find(KalmanFilterExperimentParameterType::initial_state_estimate)->rowCount() == n_rows);
  assert(Find(KalmanFilterExperimentParameterType::initial_state_real)->columnCount() == n_cols);
  assert(Find(KalmanFilterExperimentParameterType::initial_state_real)->rowCount() == n_rows);
  assert(Find(KalmanFilterExperimentParameterType::input)->columnCount() == n_cols);
  assert(Find(KalmanFilterExperimentParameterType::input)->rowCount() == n_rows);
  assert(Find(KalmanFilterExperimentParameterType::measurement_frequency)->rowCount() == n_rows);
  assert(Find(KalmanFilterExperimentParameterType::measurement_frequency)->columnCount() == n_cols);
  assert(Find(KalmanFilterExperimentParameterType::observation)->columnCount() == n_rows);
  assert(Find(KalmanFilterExperimentParameterType::observation)->rowCount() == n_rows);
  assert(Find(KalmanFilterExperimentParameterType::real_measurement_noise)->columnCount() == n_cols);
  assert(Find(KalmanFilterExperimentParameterType::real_measurement_noise)->rowCount() == n_rows);
  assert(Find(KalmanFilterExperimentParameterType::real_process_noise)->columnCount() == n_cols);
  assert(Find(KalmanFilterExperimentParameterType::real_process_noise)->rowCount() == n_rows);
  assert(Find(KalmanFilterExperimentParameterType::state_names)->columnCount() == n_cols);
  assert(Find(KalmanFilterExperimentParameterType::state_names)->rowCount() == n_rows);
  assert(Find(KalmanFilterExperimentParameterType::state_transition)->columnCount() == n_rows);
  assert(Find(KalmanFilterExperimentParameterType::state_transition)->rowCount() == n_rows);
  assert(CreateKalmanFilter() && "Can create an empty Kalman filter");
  assert(CreateWhiteNoiseSystem() && "Can create an empty white noise system");
  assert(CreateExperiment() && "Can create an empty experiment");
  #endif


  //Let a state name change result in all models changing their headers
  {
    QAbstractTableModel * const m = Find(KalmanFilterExperimentParameterType::state_names);
    assert(m);
    QObject::connect(
      m,
      &QAbstractTableModel::dataChanged,
      this,
      &ribi::kalman::QtKalmanFilterExperimentModel::OnStateNamesChanged
    );
  }
}

std::map<ribi::kalman::KalmanFilterExperimentParameterType,QAbstractTableModel *> ribi::kalman::QtKalmanFilterExperimentModel::CreateMap() noexcept
{
  std::map<KalmanFilterExperimentParameterType,QAbstractTableModel *> m;

  const std::vector<KalmanFilterExperimentParameterType> v = KalmanFilterExperimentParameter().GetAll();

  const auto j = v.end();
  for (auto i = v.begin(); i!=j; ++i)
  {
    KalmanFilterExperimentParameterType type = *i;
    QAbstractTableModel * const model = CreateModel(type);
    assert(model);
    m.insert(std::make_pair(type,model));
  }
  assert(static_cast<int>(KalmanFilterExperimentParameterType::n_parameters) == boost::numeric_cast<int>(m.size()));
  return m;
}


void ribi::kalman::QtKalmanFilterExperimentModel::CalculateOptimalEstimatedKalmanGain() noexcept
{
  //Read
  const auto initial_covariance_estimate =
    dynamic_cast<const InitialCovarianceEstimateModel*>(
      this->Find(KalmanFilterExperimentParameterType::initial_covariance_estimate)
    )->GetRawData();

  const auto estimated_measurement_noise =
    dynamic_cast<const EstimatedMeasurementNoiseModel*>(
      this->Find(KalmanFilterExperimentParameterType::estimated_measurement_noise)
    )->GetRawData();

  const auto observation =
    dynamic_cast<const ObservationModel*>(
      this->Find(KalmanFilterExperimentParameterType::observation)
    )->GetRawData();

  const auto state_transition =
    dynamic_cast<const StateTransitionModel*>(
      this->Find(KalmanFilterExperimentParameterType::state_transition)
    )->GetRawData();

  //Calculate
  const boost::numeric::ublas::matrix<double> m
    = SteadyStateKalmanFilterParameters::CalculateOptimalKalmanGain(
      initial_covariance_estimate,
      estimated_measurement_noise,
      observation,
      state_transition
    );

  //Write
  dynamic_cast<EstimatedOptimalKalmanGainModel*>(
    this->Find(KalmanFilterExperimentParameterType::estimated_optimal_kalman_gain)
  )->SetRawData(m);
}

boost::shared_ptr<ribi::kalman::KalmanFilterExperiment> ribi::kalman::QtKalmanFilterExperimentModel::CreateExperiment() const noexcept
{

  boost::shared_ptr<KalmanFilterExperiment> experiment;


  const int n_timesteps_desired = this->m_number_of_timesteps;

  //assert(n_timesteps_desired > 0); //Can be zero

  const std::vector<std::string> input
    = dynamic_cast<const InputModel*>(
    this->Find(KalmanFilterExperimentParameterType::input)
  )->GetRawData();

  const boost::shared_ptr<KalmanFilter> kalman_filter = CreateKalmanFilter();
  if (!kalman_filter)
  {
    assert(!experiment);
    return experiment;
  }

  assert(kalman_filter->GetParameters());
  assert(input.size() == kalman_filter->GetParameters()->GetInitialStateEstimate().size());

  const std::vector<std::string> state_names
    = dynamic_cast<const StateNamesModel*>(
    this->Find(KalmanFilterExperimentParameterType::state_names)
  )->GetRawData();

  assert(input.size() == state_names.size());

  const boost::shared_ptr<WhiteNoiseSystem> white_noise_system = CreateWhiteNoiseSystem();

  if (!white_noise_system)
  {
    return experiment;
  }

  assert(state_names.size() == white_noise_system->PeekAtRealState().size());
  assert(Matrix::MatricesAreAboutEqual(
    kalman_filter->GetParameters()->GetControl(),
    white_noise_system->GetParameters()->GetControl())
    && "Parameters obtained from Kalman filter and white noise system must match");
  assert(Matrix::MatricesAreAboutEqual(
    kalman_filter->GetParameters()->GetStateTransition(),
    white_noise_system->GetParameters()->GetStateTransition())
    && "Parameters obtained from Kalman filter and white noise system must match");

  experiment.reset(
    new KalmanFilterExperiment(
      n_timesteps_desired,
      input,
      kalman_filter,
      state_names,
      white_noise_system,
      m_context)
    );

  assert(experiment);
  return experiment;
}


boost::shared_ptr<ribi::kalman::KalmanFilterParameters> ribi::kalman::QtKalmanFilterExperimentModel::CreateFixedLagSmootherKalmanFilterParameters() const noexcept
{
  const boost::shared_ptr<StandardKalmanFilterParameters> standard_parameters
    = CreateStandardKalmanFilterParameters();
  const int estimated_lag = this->m_lag_estimated;

  const boost::shared_ptr<FixedLagSmootherKalmanFilterParameters> p(
    new FixedLagSmootherKalmanFilterParameters(
      standard_parameters,
      estimated_lag
    )
  );
  assert(p);
  assert(p->GetType() == KalmanFilterType::fixed_lag_smoother);
  return p;
}

boost::shared_ptr<ribi::kalman::KalmanFilter> ribi::kalman::QtKalmanFilterExperimentModel::CreateKalmanFilter() const
{
  const boost::shared_ptr<const KalmanFilterParameters> parameters = CreateKalmanFilterParameters();
  assert(parameters);
  const boost::shared_ptr<KalmanFilter> kalman_filter = KalmanFilterFactory().Create(parameters);
  assert(kalman_filter);
  assert(parameters->GetType() == kalman_filter->GetType());
  return kalman_filter;
}

boost::shared_ptr<ribi::kalman::KalmanFilterParameters> ribi::kalman::QtKalmanFilterExperimentModel::CreateKalmanFilterParameters() const noexcept
{
  boost::shared_ptr<KalmanFilterParameters> parameters;
  switch (m_kalman_filter_type)
  {
    case KalmanFilterType::standard:
      parameters = CreateStandardKalmanFilterParameters();
      break;
    case KalmanFilterType::steady_state:
      parameters = CreateSteadyStateKalmanFilterParameters();
      break;
    case KalmanFilterType::fixed_lag_smoother:
      parameters = CreateFixedLagSmootherKalmanFilterParameters();
      break;
    case KalmanFilterType::n_types:
      assert(!"Unimplemented Kalman filter type");
      throw std::logic_error(__func__);
  }
  assert(parameters);
  assert(parameters->GetType() == m_kalman_filter_type);
  return parameters;
}

boost::shared_ptr<ribi::kalman::StandardKalmanFilterParameters> ribi::kalman::QtKalmanFilterExperimentModel::CreateStandardKalmanFilterParameters() const noexcept
{
  const auto control =
    dynamic_cast<const ControlModel*>(
      this->Find(KalmanFilterExperimentParameterType::control)
    )->GetRawData();

  const auto estimated_measurement_noise =
    dynamic_cast<const EstimatedMeasurementNoiseModel*>(
      this->Find(KalmanFilterExperimentParameterType::estimated_measurement_noise)
    )->GetRawData();

  const auto estimated_process_noise_covariance =
    dynamic_cast<const EstimatedProcessNoiseCovarianceModel*>(
      this->Find(KalmanFilterExperimentParameterType::estimated_process_noise_covariance)
    )->GetRawData();

  const auto initial_covariance_estimate =
    dynamic_cast<const InitialCovarianceEstimateModel*>(
      this->Find(KalmanFilterExperimentParameterType::initial_covariance_estimate)
    )->GetRawData();

  const auto initial_state_estimate =
    dynamic_cast<const InitialStateEstimateModel*>(
      this->Find(KalmanFilterExperimentParameterType::initial_state_estimate)
    )->GetRawData();

  assert(this->Find(KalmanFilterExperimentParameterType::observation));
  assert(dynamic_cast<const ObservationModel*>(this->Find(KalmanFilterExperimentParameterType::observation)));

  const auto observation =
    dynamic_cast<const ObservationModel*>(
      this->Find(KalmanFilterExperimentParameterType::observation)
    )->GetRawData();

  const auto state_transition =
    dynamic_cast<const StateTransitionModel*>(
      this->Find(KalmanFilterExperimentParameterType::state_transition)
    )->GetRawData();

  #ifndef NDEBUG
  const std::size_t sz = initial_state_estimate.size();
  //assert(sz >= 0); //Inevitable for std::size_t
  assert(sz == control.size1());
  assert(sz == control.size2());
  assert(sz == observation.size1());
  assert(sz == observation.size2());
  assert(sz == state_transition.size1());
  assert(sz == state_transition.size2());
  assert(sz == initial_state_estimate.size());
  #endif
  const boost::shared_ptr<StandardKalmanFilterParameters> p(
    new StandardKalmanFilterParameters(
      control,
      estimated_measurement_noise,
      estimated_process_noise_covariance,
      initial_covariance_estimate,
      initial_state_estimate,
      observation,
      state_transition
    )
  );
  assert(p);
  return p;
}

boost::shared_ptr<ribi::kalman::KalmanFilterParameters> ribi::kalman::QtKalmanFilterExperimentModel::CreateSteadyStateKalmanFilterParameters() const noexcept
{
  const auto control =
    dynamic_cast<const ControlModel*>(
      this->Find(KalmanFilterExperimentParameterType::control)
    )->GetRawData();

  const auto estimated_optimal_kalman_gain =
    dynamic_cast<const EstimatedOptimalKalmanGainModel*>(
      this->Find(KalmanFilterExperimentParameterType::estimated_optimal_kalman_gain)
    )->GetRawData();

  const auto initial_state_estimate =
    dynamic_cast<const InitialStateEstimateModel*>(
      this->Find(KalmanFilterExperimentParameterType::initial_state_estimate)
    )->GetRawData();

  const auto observation =
    dynamic_cast<const ObservationModel*>(
      this->Find(KalmanFilterExperimentParameterType::observation)
    )->GetRawData();

  const auto state_transition =
    dynamic_cast<const StateTransitionModel*>(
      this->Find(KalmanFilterExperimentParameterType::state_transition)
    )->GetRawData();

  const boost::shared_ptr<SteadyStateKalmanFilterParameters> p(
    new SteadyStateKalmanFilterParameters(
      control,
      estimated_optimal_kalman_gain,
      initial_state_estimate,
      observation,
      state_transition
    )
  );
  assert(p);
  return p;
}

boost::shared_ptr<ribi::kalman::WhiteNoiseSystemParameters> ribi::kalman::QtKalmanFilterExperimentModel::CreateLaggedWhiteNoiseSystemParameters() const noexcept
{
  const auto control =
    dynamic_cast<const ControlModel*>(
      this->Find(KalmanFilterExperimentParameterType::control)
    )->GetRawData();

  const auto initial_state_real =
    dynamic_cast<const InitialStateRealModel*>(
      this->Find(KalmanFilterExperimentParameterType::initial_state_real)
    )->GetRawData();

  const auto real_measurement_noise =
    dynamic_cast<const RealMeasurementNoiseModel*>(
      this->Find(KalmanFilterExperimentParameterType::real_measurement_noise)
    )->GetRawData();

  const auto real_process_noise =
    dynamic_cast<const RealProcessNoiseModel*>(
      this->Find(KalmanFilterExperimentParameterType::real_process_noise)
    )->GetRawData();

  const auto state_transition =
    dynamic_cast<const StateTransitionModel*>(
      this->Find(KalmanFilterExperimentParameterType::state_transition)
    )->GetRawData();

  const boost::shared_ptr<WhiteNoiseSystemParameters> p(
    new LaggedWhiteNoiseSystemParameters(
      control,
      initial_state_real,
      m_lag_real,
      real_measurement_noise,
      real_process_noise,
      state_transition
    )
  );
  assert(p);
  assert(p->GetType() == WhiteNoiseSystemType::lagged);
  return p;
}


QAbstractTableModel * ribi::kalman::QtKalmanFilterExperimentModel::CreateModel(const KalmanFilterExperimentParameterType type) noexcept
{
  switch (type)
  {
    case KalmanFilterExperimentParameterType::control:
      return new ControlModel;
    case KalmanFilterExperimentParameterType::estimated_measurement_noise:
      return new EstimatedMeasurementNoiseModel;
    case KalmanFilterExperimentParameterType::estimated_optimal_kalman_gain:
      return new EstimatedOptimalKalmanGainModel;
    case KalmanFilterExperimentParameterType::estimated_process_noise_covariance:
      return new EstimatedProcessNoiseCovarianceModel;
    case KalmanFilterExperimentParameterType::initial_covariance_estimate:
      return new InitialCovarianceEstimateModel;
    case KalmanFilterExperimentParameterType::initial_state_estimate:
      return new InitialStateEstimateModel;
    case KalmanFilterExperimentParameterType::initial_state_real:
      return new InitialStateRealModel;
    case KalmanFilterExperimentParameterType::measurement_frequency:
    {
      MeasurementFrequencyModel * const model = new MeasurementFrequencyModel;
      assert(model);
      //model->SetRawData( Matrix::CreateVector( { 1 } ) );
      //assert(model->GetRawData().size() == 1);
      //assert(model->GetRawData()(0) == 1);
      //Measured frequencies go from 1 to infinity, where 1 is the default value
      model->SetRange(1,std::numeric_limits<int>::max(),1);
      return model;
    }
    case KalmanFilterExperimentParameterType::real_measurement_noise:
      return new RealMeasurementNoiseModel;
    case KalmanFilterExperimentParameterType::real_process_noise:
      return new RealProcessNoiseModel;
    case KalmanFilterExperimentParameterType::input:
      return new InputModel("t");
    case KalmanFilterExperimentParameterType::observation:
      return new ObservationModel;
    case KalmanFilterExperimentParameterType::state_names:
      return new StateNamesModel;
    case KalmanFilterExperimentParameterType::state_transition:
      return new StateTransitionModel;
    case KalmanFilterExperimentParameterType::n_parameters:
      assert(!"Should not get here");
      throw std::logic_error("QtKalmanFiltererParameterDialog::ToModel");
  }
  assert(!"Should not get here");
  throw std::logic_error("QtKalmanFiltererParameterDialog::ToModel");
}

boost::shared_ptr<ribi::kalman::WhiteNoiseSystemParameters> ribi::kalman::QtKalmanFilterExperimentModel::CreateGapsFilledWhiteNoiseSystemParameters() const noexcept
{
  const auto control =
    dynamic_cast<const ControlModel*>(
      this->Find(KalmanFilterExperimentParameterType::control)
    )->GetRawData();

  assert(this->Find(KalmanFilterExperimentParameterType::initial_state_real));
  assert(dynamic_cast<const InitialStateRealModel*>(
      this->Find(KalmanFilterExperimentParameterType::initial_state_real)));

  const auto initial_state_real =
    dynamic_cast<const InitialStateRealModel*>(
      this->Find(KalmanFilterExperimentParameterType::initial_state_real)
    )->GetRawData();

  assert(this->Find(KalmanFilterExperimentParameterType::measurement_frequency));
  assert(dynamic_cast<const MeasurementFrequencyModel*>(
      this->Find(KalmanFilterExperimentParameterType::measurement_frequency)));
  const auto measurement_frequency =
    dynamic_cast<const MeasurementFrequencyModel*>(
      this->Find(KalmanFilterExperimentParameterType::measurement_frequency)
    )->GetRawData();

  const auto real_measurement_noise =
    dynamic_cast<const RealMeasurementNoiseModel*>(
      this->Find(KalmanFilterExperimentParameterType::real_measurement_noise)
    )->GetRawData();

  const auto real_process_noise =
    dynamic_cast<const RealProcessNoiseModel*>(
      this->Find(KalmanFilterExperimentParameterType::real_process_noise)
    )->GetRawData();

  const auto state_transition =
    dynamic_cast<const StateTransitionModel*>(
      this->Find(KalmanFilterExperimentParameterType::state_transition)
    )->GetRawData();

  const boost::shared_ptr<WhiteNoiseSystemParameters> p(
    new GapsFilledWhiteNoiseSystemParameters(
      control,
      initial_state_real,
      measurement_frequency,
      real_measurement_noise,
      real_process_noise,
      state_transition
    )
  );
  assert(p);
  assert(p->GetType() == WhiteNoiseSystemType::gaps_filled);
  return p;
}

boost::shared_ptr<ribi::kalman::StandardWhiteNoiseSystemParameters> ribi::kalman::QtKalmanFilterExperimentModel::CreateStandardWhiteNoiseSystemParameters() const noexcept
{
  const auto control =
    dynamic_cast<const ControlModel*>(
      this->Find(KalmanFilterExperimentParameterType::control)
    )->GetRawData();

  assert(this->Find(KalmanFilterExperimentParameterType::initial_state_real));
  assert(dynamic_cast<const InitialStateRealModel*>(
      this->Find(KalmanFilterExperimentParameterType::initial_state_real)));

  const auto initial_state_real =
    dynamic_cast<const InitialStateRealModel*>(
      this->Find(KalmanFilterExperimentParameterType::initial_state_real)
    )->GetRawData();

  const auto real_measurement_noise =
    dynamic_cast<const RealMeasurementNoiseModel*>(
      this->Find(KalmanFilterExperimentParameterType::real_measurement_noise)
    )->GetRawData();

  const auto real_process_noise =
    dynamic_cast<const RealProcessNoiseModel*>(
      this->Find(KalmanFilterExperimentParameterType::real_process_noise)
    )->GetRawData();

  const auto state_transition =
    dynamic_cast<const StateTransitionModel*>(
      this->Find(KalmanFilterExperimentParameterType::state_transition)
    )->GetRawData();

  const boost::shared_ptr<StandardWhiteNoiseSystemParameters> p(
    new StandardWhiteNoiseSystemParameters(
      control,
      initial_state_real,
      real_measurement_noise,
      real_process_noise,
      state_transition
    )
  );
  assert(p);
  assert(p->GetType() == WhiteNoiseSystemType::standard);
  return p;
}

boost::shared_ptr<ribi::kalman::WhiteNoiseSystem> ribi::kalman::QtKalmanFilterExperimentModel::CreateWhiteNoiseSystem() const noexcept
{
  const boost::shared_ptr<WhiteNoiseSystemParameters> parameters
    = CreateWhiteNoiseSystemParameters();
  assert(parameters);
  assert(this->m_white_noise_system_type == parameters->GetType());
  const boost::shared_ptr<WhiteNoiseSystem> my_system
    = WhiteNoiseSystemFactory().Create(parameters);
  assert(my_system);
  assert(my_system->GetType() == parameters->GetType());
  return my_system;
}

boost::shared_ptr<ribi::kalman::WhiteNoiseSystemParameters> ribi::kalman::QtKalmanFilterExperimentModel::CreateWhiteNoiseSystemParameters() const noexcept
{
  boost::shared_ptr<WhiteNoiseSystemParameters> parameters;
  switch (m_white_noise_system_type)
  {
    case WhiteNoiseSystemType::gaps_filled:
    {
      parameters = CreateGapsFilledWhiteNoiseSystemParameters();
    }
    break;
    case WhiteNoiseSystemType::lagged:
    {
      parameters = CreateLaggedWhiteNoiseSystemParameters();
    }
    break;
    case WhiteNoiseSystemType::standard:
    {
      parameters = CreateStandardWhiteNoiseSystemParameters();
    }
    break;
    case WhiteNoiseSystemType::n_types:
      assert(!"Unimplemented white noise system type");
  }
  assert(parameters);
  assert(parameters->GetType() == m_white_noise_system_type);
  return parameters;
}

QAbstractTableModel * ribi::kalman::QtKalmanFilterExperimentModel::Find(const KalmanFilterExperimentParameterType type)
{
  //Calls the const version of Find
  //To avoid duplication in const and non-const member functions
  // * Herb Sutter, Andrei Alexandrescu. C++ coding standards: 101 rules, guidelines,
  //   and best practices. 2005. ISBN: 0-32-111358-6. Chapter 94: 'Avoid casting away const', item 'Exceptions'
  return const_cast<QAbstractTableModel *>(const_cast<const QtKalmanFilterExperimentModel&>(*this).Find(type));
}

const QAbstractTableModel * ribi::kalman::QtKalmanFilterExperimentModel::Find(const KalmanFilterExperimentParameterType type) const
{
  assert(m_models.find(type) != m_models.end());
  const QAbstractTableModel * const model = (*m_models.find(type)).second;
  assert(model);
  return model;
}

void ribi::kalman::QtKalmanFilterExperimentModel::FromDokuWiki(const std::string& text)
{
  const std::vector<std::string> lines = Container().SeperateString(text,'\n');
  assert(!lines.empty());

  m_version = 0; //Only version 0 does not change the version number

  const int n_lines = boost::numeric_cast<int>(lines.size());
  for (int line=0; line!=n_lines; ++line)
  {
    const std::string& line_str = lines[line];

    //Have to do manually as Boost.Regex its boost::regex_replace
    //does not link under GCC 4.4.0
    ReadKalmanFilterType(line_str);
    Read(line_str,"Lag estimated",m_lag_estimated);
    Read(line_str,"Lag real",m_lag_real);
    Read(line_str,"Number of timesteps",m_number_of_timesteps);
    Read(line_str,"Version",m_version);
    ReadWhiteNoiseSystemType(line_str);
  }
  ReadContext(lines);

  //Go through all m_models
  {
    typedef std::map<KalmanFilterExperimentParameterType,QAbstractTableModel *>::const_iterator ConstIterator;
    const ConstIterator j = m_models.end();
    for (ConstIterator i = m_models.begin(); i!=j; ++i)
    {
      const std::pair<KalmanFilterExperimentParameterType,QAbstractTableModel *> p = *i;
      KalmanFilterExperimentParameterType type = p.first;
      QAbstractTableModel * const model = p.second;
      assert(type != KalmanFilterExperimentParameterType::n_parameters);
      assert(model);

      //version 0 did not support measurement_frequency
      if (m_version == 0 && type == KalmanFilterExperimentParameterType::measurement_frequency) continue;

      const std::string name = KalmanFilterExperimentParameter().ToName(type);
      Read(lines,name,model);
    }
  }
  if (m_version == 0)
  {
    assert(this->Find(KalmanFilterExperimentParameterType::state_names));
    const int n_rows = this->Find(KalmanFilterExperimentParameterType::state_names)->rowCount();
    typedef std::map<KalmanFilterExperimentParameterType,QAbstractTableModel *>::const_iterator Iterator;
    //conversion from 'std::_Rb_tree_const_iterator<std::pair<const KalmanFilterExperimentParameterType, QAbstractTableModel*> >'
    //to non-scalar type 'const ribi::kalman::QtKalmanFilterExperimentModel::FromDokuWiki(const std::string&)::Iterator' requested
    const Iterator iter = this->m_models.find(KalmanFilterExperimentParameterType::measurement_frequency);
    assert(iter != m_models.end());
    QAbstractItemModel * const abstract_model = iter->second;
    assert(abstract_model);
    QtUblasVectorIntModel * const model = dynamic_cast<QtUblasVectorIntModel *>(abstract_model);
    assert(model);
    model->SetRange(1,std::numeric_limits<int>::max(),1);
    model->SetRawData( Matrix::CreateVectorInt( std::vector<int>(n_rows,1) ) );
    m_version = 1;
  }
  if (m_version == 1)
  {
    //version 1 did not save/load a context from file
    this->SetContext("");
    m_version = 2;

    //Test if new version works OK
    #ifndef NDEBUG
    {
      TempLocale temp_english_locale("en_US.UTF-8");
      const std::string new_str = this->ToDokuWiki();
      QtKalmanFilterExperimentModel dummy_model;
      dummy_model.FromDokuWiki(new_str);
      assert(this->GetNumberOfTimesteps() == dummy_model.GetNumberOfTimesteps());
      if (new_str != dummy_model.ToDokuWiki())
      {
        //Error in number of timesteps
        TRACE(new_str);
        TRACE(dummy_model.ToDokuWiki());
      }
      assert(new_str == dummy_model.ToDokuWiki());
    }
    #endif
  }

  assert(m_version == m_version_current);

}

#ifndef NDEBUG
bool ribi::kalman::QtKalmanFilterExperimentModel::IsValid() const
{
  if (m_lag_estimated < 0)
  {
    TRACE("Estimated lag smaller than zero");
    return false;
  }
  if (m_lag_real < 0)
  {
    TRACE("Real lag smaller than zero");
    return false;
  }
  if (m_number_of_timesteps < 0)
  {
    TRACE("Number of timesteps smaller than zero");
    return false;
  }
  if (m_models.empty())
  {
    TRACE("No tables in m_models");
    return false;
  }
  if (m_version != m_version_current)
  {
    TRACE(m_version);
    TRACE(m_version_current);
    TRACE("Model not updated to latest version");
    return false;
  }
  typedef std::map<KalmanFilterExperimentParameterType,QAbstractTableModel *>::const_iterator Iterator;
  const Iterator j = m_models.end();
  for (Iterator i = m_models.begin(); i!=j; ++i)
  {

    const std::pair<KalmanFilterExperimentParameterType,QAbstractTableModel *> p = *i;
    const QAbstractTableModel * const table = p.second;
    if (table == 0)
    {
      TRACE("Uninitialized QAbstractTableModel");
      return false;
    }
    const KalmanFilterExperimentParameterType type = p.first;
    if (type == KalmanFilterExperimentParameterType::n_parameters)
    {
      TRACE("Use of n_parameters");
      return false;
    }
    const int n_rows_expected = Find(KalmanFilterExperimentParameterType::state_names)->rowCount();
    const int n_cols_expected
      = n_rows_expected == 0
      ? 0
      : (KalmanFilterExperimentParameter().IsMatrix(type) ? n_rows_expected : 1);

    const int n_rows_found = Find(type)->rowCount();
    const int n_cols_found = Find(type)->columnCount();

    if (n_rows_expected != n_rows_found)
    {
      TRACE(n_rows_expected);
      TRACE(n_rows_found);
      TRACE("Number of rows unexpected");
      return false;
    }
    if (n_cols_expected != n_cols_found)
    {
      TRACE(n_rows_expected);
      TRACE(n_rows_found);
      TRACE(n_cols_expected);
      TRACE(n_cols_found);
      TRACE("Number of columns unexpected");
      return false;
    }
  }
  return true;
}
#endif

void ribi::kalman::QtKalmanFilterExperimentModel::OnStateNamesChanged()
{
  //Read
  const std::vector<std::string> state_names =
  dynamic_cast<StateNamesModel*>(
    this->Find(KalmanFilterExperimentParameterType::state_names)
  )->GetRawData();

  //Write to all headers
  const auto j = m_models.end();
  for (auto i = m_models.begin(); i!=j; ++i)
  {
    const std::pair<KalmanFilterExperimentParameterType,QAbstractTableModel *> p = *i;
    const KalmanFilterExperimentParameterType type = p.first;
    QAbstractTableModel * const abstract_model = p.second;

    if (QtStdVectorStringModel * const svs_model = dynamic_cast<QtStdVectorStringModel *>(abstract_model))
    {
      const std::string title = KalmanFilterExperimentParameter().ToSymbol(type);
      svs_model->SetHeaderData(title,state_names);
    }
    else if (QtStdVectorFunctionModel * const svf_model = dynamic_cast<QtStdVectorFunctionModel *>(abstract_model))
    {
      const std::string title = KalmanFilterExperimentParameter().ToSymbol(type);
      svf_model->SetHeaderData(title,state_names);
    }
    else if (QtUblasMatrixDoubleModel * const umd_model = dynamic_cast<QtUblasMatrixDoubleModel *>(abstract_model))
    {
      umd_model->SetHeaderData(state_names,state_names);
    }
    else if (QtUblasVectorDoubleModel * const uvd_model = dynamic_cast<QtUblasVectorDoubleModel *>(abstract_model))
    {
      const std::string title = KalmanFilterExperimentParameter().ToSymbol(type);
      uvd_model->SetHeaderData(title,state_names);
    }
    else
    {
      QtUblasVectorIntModel * const uvi_model = dynamic_cast<QtUblasVectorIntModel *>(abstract_model);
      assert(uvi_model);
      const std::string title = KalmanFilterExperimentParameter().ToSymbol(type);
      uvi_model->SetHeaderData(title,state_names);
    }
  }

}

void ribi::kalman::QtKalmanFilterExperimentModel::ReadContext(const std::vector<std::string>& v)
{
  const auto begin = std::find(v.begin(),v.end(),"<html>");
  if (begin == v.end()) return;
  auto end = std::find(v.begin(),v.end(),"</html>");
  assert(end != v.end());
  std::string new_context;

  auto line = begin;

  for(++line; line!=end; ++line) //Skip first HTML tag
  {
    new_context += (*line) + "\n";
  }

  this->SetContext(new_context.substr(0,new_context.size() - 1)); //Strip \n
  //TRACE(m_context);
}

void ribi::kalman::QtKalmanFilterExperimentModel::ReadKalmanFilterType(const std::string& s)
{
  if (s.find("Kalman filter type") != std::string::npos)
  {
    const std::vector<KalmanFilterType> v = KalmanFilterTypes().GetAllTypes();
    for(const KalmanFilterType type: v)
    {
      if (s.find(KalmanFilterTypes().ToStr(type)) != std::string::npos)
      {
        this->SetKalmanFilterType(type);
        assert(m_kalman_filter_type == type);
      }
    }
  }
}

void ribi::kalman::QtKalmanFilterExperimentModel::Read(
  const std::vector<std::string>& text,
  const std::string& name,
  QAbstractTableModel * const model)
{
  assert(model);
  assert(!text.empty());
  const int sz = boost::numeric_cast<int>(text.size());

  //Find begin
  const std::string header = "^ " + name;
  int begin_tmp = -1;
  for (int i=0; i!=sz; ++i)
  {
    if (text[i].find(header) != std::string::npos) { begin_tmp = i; break; }
  }
  assert(begin_tmp != -1);
  assert(begin_tmp < boost::numeric_cast<int>(text.size()));

  const int begin = begin_tmp;

  //Calculate number of columns
  const int n_cols = std::count(text[begin].begin(),text[begin].end(),'^') - 2;
  if (n_cols == 0) return;
  assert(n_cols > 0);

  //Find end
  int end_tmp = -1;
  for (int i=begin; i!=sz; ++i)
  {
    if (boost::algorithm::trim_copy(text[i]).empty()) { end_tmp = i; break; }
  }
  assert(end_tmp != -1);
  assert(end_tmp < boost::numeric_cast<int>(text.size()));

  const int end = end_tmp;

  //Calculate number of rows
  const int n_rows = end - begin - 1; //-1 for header
  if (n_rows == 0) return;
  assert(n_rows > 0);

  #define BELIEF_RESIZE_MUST_BE_DONE_HERE_785897597850978665798458907
  #ifdef BELIEF_RESIZE_MUST_BE_DONE_HERE_785897597850978665798458907
  //Resize model
  //Rows
  if (model->rowCount() < n_rows)
  {
    const int n_to_add = n_rows - model->rowCount();
    model->insertRows(0,n_to_add);
    assert(model->rowCount() == n_rows);
  }
  else if (model->rowCount() > n_rows)
  {
    const int n_to_remove = model->rowCount() - n_rows;
    model->removeRows(0,n_to_remove);
    assert(model->rowCount() == n_rows);
  }
  assert(model->rowCount() == n_rows);

  //Columns
  if (model->columnCount() < n_cols)
  {
    const int n_to_add = n_cols - model->columnCount();
    model->insertColumns(0,n_to_add);
    assert(model->columnCount() == n_cols);
  }
  else if (model->columnCount() > n_cols)
  {
    const int n_to_remove = model->columnCount() - n_cols;
    model->removeColumns(0,n_to_remove);
    assert(model->columnCount() == n_cols);
  }
  assert(model->columnCount() == n_cols);
  #endif

  //Read data as std::string
  boost::numeric::ublas::matrix<std::string> v(n_rows,n_cols,"");
  for (int row = 0; row!=n_rows; ++row)
  {
    const int line = begin + 1 + row;
    assert(line < boost::numeric_cast<int>(text.size()));
    const std::vector<std::string> cols = Container().SeperateString(text[line],'|');
    assert(boost::numeric_cast<int>(cols.size()) == n_cols + 2); // HEADER | value | value | space
    assert(row < model->rowCount());
    for (int col = 0; col!=n_cols; ++col)
    {
      const int col_index = col + 1; //Skip header
      assert(col_index < boost::lexical_cast<int>(cols.size()));
      assert(row < model->rowCount());
      assert(col < model->columnCount());
      //Need to strip whitespace
      const std::string data_str = boost::algorithm::trim_copy(cols[col_index]).c_str();
      v(row,col) = data_str;
    }
  }

  #ifdef BELIEF_SET_DATA_PER_CELL_7826437863497863497586395786
  //Fill model with data
  for (int row = 0; row!=n_rows; ++row)
  {
    for (int col = 0; col!=n_cols; ++col)
    {
      const QString data = v(row,col).c_str();
      QModelIndex index = model->index(row,col);
      assert(index.isValid());
      model->setData(index,data);
    }
  }
  #else
  if (QtStdVectorStringModel * const svs_model = dynamic_cast<QtStdVectorStringModel *>(model))
  {
    const std::vector<std::string> w = ConvertToVectorString(v);
    svs_model->SetRawData(w);
  }
  else if (QtStdVectorFunctionModel * const svf_model = dynamic_cast<QtStdVectorFunctionModel *>(model))
  {
    const std::vector<std::string> w = ConvertToVectorString(v);
    svf_model->SetRawData(w);
  }
  else if (QtUblasMatrixDoubleModel * const umd_model = dynamic_cast<QtUblasMatrixDoubleModel *>(model))
  {
    const boost::numeric::ublas::matrix<double> w = ConvertToUblasMatrixDouble(v);
    umd_model->SetRawData(w);
  }
  else if (QtUblasVectorDoubleModel * const uvd_model = dynamic_cast<QtUblasVectorDoubleModel *>(model))
  {
    const boost::numeric::ublas::vector<double> w = ConvertToUblasVectorDouble(v);
    uvd_model->SetRawData(w);
  }
  else
  {
    QtUblasVectorIntModel * const uvi_model = dynamic_cast<QtUblasVectorIntModel *>(model);
    assert(uvi_model);
    const boost::numeric::ublas::vector<int> w = ConvertToUblasVectorInt(v);
    uvi_model->SetRawData(w);
  }
  #endif


}

void ribi::kalman::QtKalmanFilterExperimentModel::Read(const std::string& line,const std::string& sub, int& value_to_change)
{
  if (line.find(sub) != std::string::npos)
  {
    if (line.substr(line.size() - 5,5) == std::string("</li>"))
    {
      Read(line.substr(0,line.size() - 5),sub,value_to_change);
      return;
    }
    for (int n_digits = 1; ; ++n_digits)
    {
      try
      {
        const int value
          = boost::lexical_cast<int>(
            line.substr(
                line.size() - n_digits,n_digits
              )
            );
         value_to_change = value;
      }
      catch (boost::bad_lexical_cast&)
      {
        return;
      }
    }
  }
}

void ribi::kalman::QtKalmanFilterExperimentModel::ReadWhiteNoiseSystemType(const std::string& s)
{
  if (s.find("White noise system type") != std::string::npos)
  {
    const std::vector<WhiteNoiseSystemType> v = WhiteNoiseSystemTypes().GetAllTypes();
    for(const WhiteNoiseSystemType type: v)
    {
      if (s.find(WhiteNoiseSystemTypes().ToStr(type)) != std::string::npos)
      {
        this->SetWhiteNoiseSystemType(type);
        assert(m_white_noise_system_type == type);
      }
    }
  }
}

std::vector<std::string> ribi::kalman::QtKalmanFilterExperimentModel::SeperateString(
  const std::string& input,
  const char seperator)
{
  std::vector<std::string> v;
  boost::algorithm::split(v,input,
    std::bind2nd(std::equal_to<char>(),seperator),
    boost::algorithm::token_compress_on);
  return v;
}

void ribi::kalman::QtKalmanFilterExperimentModel::SetContext(const std::string& context)
{
  if (m_context != context)
  {
    m_context = context;
    m_signal_context_changed(m_context);
  }
  assert(m_context == context);
}

void ribi::kalman::QtKalmanFilterExperimentModel::SetExample(const boost::shared_ptr<const KalmanFilterExample>& example) noexcept
{
  //Set the state names first, as it resizes the tables
  assert(example);
  dynamic_cast<StateNamesModel*>(
    this->Find(KalmanFilterExperimentParameterType::state_names)
  )->SetRawData(example->GetStateNames());

  this->SetContext(example->GetContext());
  assert(this->GetContext() == example->GetContext());

  this->SetNumberOfTimesteps(example->GetNumberOfTimesteps());
  assert(this->GetNumberOfTimesteps() == example->GetNumberOfTimesteps());


  dynamic_cast<InputModel*>(
    this->Find(KalmanFilterExperimentParameterType::input)
  )->SetRawData(example->GetInputs());


  this->SetKalmanFilterType(example->GetKalmanFilterParameters()->GetType());


  assert(this->Find(KalmanFilterExperimentParameterType::control));
  assert(dynamic_cast<ControlModel*>(
    this->Find(KalmanFilterExperimentParameterType::control)
  ));

  dynamic_cast<ControlModel*>(
    this->Find(KalmanFilterExperimentParameterType::control)
  )->SetRawData(example->GetKalmanFilterParameters()->GetControl());


  dynamic_cast<EstimatedMeasurementNoiseModel*>(
    this->Find(KalmanFilterExperimentParameterType::estimated_measurement_noise)
  )->SetRawData(example->GetKalmanFilterParameters()->GetEstimatedMeasurementNoise());


  dynamic_cast<EstimatedProcessNoiseCovarianceModel*>(
    this->Find(KalmanFilterExperimentParameterType::estimated_process_noise_covariance)
  )->SetRawData(example->GetKalmanFilterParameters()->GetEstimatedProcessNoiseCovariance());


  dynamic_cast<InitialCovarianceEstimateModel*>(
    this->Find(KalmanFilterExperimentParameterType::initial_covariance_estimate)
  )->SetRawData(example->GetKalmanFilterParameters()->GetInitialCovarianceEstimate());


  dynamic_cast<InitialStateEstimateModel*>(
    this->Find(KalmanFilterExperimentParameterType::initial_state_estimate)
  )->SetRawData(example->GetKalmanFilterParameters()->GetInitialStateEstimate());


  assert(this->Find(KalmanFilterExperimentParameterType::observation));
  assert(dynamic_cast<ObservationModel*>(
    this->Find(KalmanFilterExperimentParameterType::observation)));

  dynamic_cast<ObservationModel*>(
    this->Find(KalmanFilterExperimentParameterType::observation)
  )->SetRawData(example->GetKalmanFilterParameters()->GetObservation());

  assert(Matrix::MatricesAreEqual(dynamic_cast<ObservationModel*>(
      this->Find(KalmanFilterExperimentParameterType::observation))->GetRawData(),
    example->GetKalmanFilterParameters()->GetObservation()));

  dynamic_cast<StateTransitionModel*>(
    this->Find(KalmanFilterExperimentParameterType::state_transition)
  )->SetRawData(example->GetKalmanFilterParameters()->GetStateTransition());

  assert(example);
  assert(example->GetWhiteNoiseSystemParameters());
  this->SetWhiteNoiseSystemType(example->GetWhiteNoiseSystemParameters()->GetType());

  assert(
    Matrix::MatricesAreEqual(
      example->GetWhiteNoiseSystemParameters()->GetControl(),
      example->GetKalmanFilterParameters()->GetControl()
    )
    && "This is the purpose of using model/view: these must be the same");

  dynamic_cast<InitialStateRealModel*>(
    this->Find(KalmanFilterExperimentParameterType::initial_state_real)
  )->SetRawData(example->GetWhiteNoiseSystemParameters()->GetInitialState());

  dynamic_cast<RealMeasurementNoiseModel*>(
    this->Find(KalmanFilterExperimentParameterType::real_measurement_noise)
  )->SetRawData(example->GetWhiteNoiseSystemParameters()->GetMeasurementNoise());

  dynamic_cast<RealProcessNoiseModel*>(
    this->Find(KalmanFilterExperimentParameterType::real_process_noise)
  )->SetRawData(example->GetWhiteNoiseSystemParameters()->GetProcessNoise());

  assert(
    Matrix::MatricesAreEqual(
      example->GetWhiteNoiseSystemParameters()->GetStateTransition(),
      example->GetKalmanFilterParameters()->GetStateTransition()
    )
    && "This is the purpose of using model/view: these must be the same");


}

void ribi::kalman::QtKalmanFilterExperimentModel::SetKalmanFilterType(const KalmanFilterType type) noexcept
{
  if (m_kalman_filter_type != type)
  {
    m_kalman_filter_type = type;
    m_signal_kalman_filter_type_changed(m_kalman_filter_type);
  }
}

void ribi::kalman::QtKalmanFilterExperimentModel::SetLagReal(const int lag) noexcept
{
  m_lag_real = lag;
}

void ribi::kalman::QtKalmanFilterExperimentModel::SetNumberOfTimesteps(const int n) noexcept
{
  assert(n >= 0);
  if (m_number_of_timesteps != n)
  {
    m_number_of_timesteps = n;
    m_signal_number_of_timesteps_changed(m_number_of_timesteps);
  }
}

void ribi::kalman::QtKalmanFilterExperimentModel::SetWhiteNoiseSystemType(const WhiteNoiseSystemType type) noexcept
{
  if (m_white_noise_system_type != type)
  {
    m_white_noise_system_type = type;
    m_signal_white_noise_system_type_changed(m_white_noise_system_type);
  }
}

#ifndef NDEBUG
void ribi::kalman::QtKalmanFilterExperimentModel::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  Container();
  Matrix();
  KalmanFilterTypes();
  KalmanFilterFactory();
  KalmanFilterExperimentParameter();
  WhiteNoiseSystemTypes();
  QtKalmanFilterExperimentModel().CreateWhiteNoiseSystemParameters();
  WhiteNoiseSystemFactory().Create(QtKalmanFilterExperimentModel().CreateWhiteNoiseSystemParameters());
  QtKalmanFilterExperimentModel().CreateExperiment();
  QtKalmanFilterExperimentModel().CreateKalmanFilter();
  QtKalmanFilterExperimentModel().CreateKalmanFilterParameters();
  QtKalmanFilterExperimentModel().CreateWhiteNoiseSystem();
  QtKalmanFilterExperimentModel().CreateFixedLagSmootherKalmanFilterParameters();
  QtKalmanFilterExperimentModel().CreateGapsFilledWhiteNoiseSystemParameters();
  QtKalmanFilterExperimentModel().CreateLaggedWhiteNoiseSystemParameters();
  QtKalmanFilterExperimentModel().CreateMap();
  QtKalmanFilterExperimentModel().CreateLaggedWhiteNoiseSystemParameters();
  ribi::Regex();
  const TestTimer test_timer(__func__,__FILE__,1.0);

  //Test some regexes
  /*
  {
    const std::string s
      =
      "* Kalman filter type: discrete\n"
      "* Lag estimated: 0\n"
      "* Lag real: 0\n"
      "* Number of timesteps: 1500\n"
      "* White noise system type: standard\n"
      "\n"
      "^ Control ^^\n"
      "^ V | 0 |\n"
      "\n"
      "^ Estimated measurement error covariance ^^\n"
      "^ V | 0.10000000000000001 |\n"
      "\n"
      "^ Estimated optimal Kalman gain ^^\n"
      "^ V | 0 |\n"
      "\n"
      "^ Estimated process noise covariance ^^\n"
      "^ V | 0.0001 |\n"
      "\n"
      "^ Initial covariance estimate ^^\n"
      "^ V | 1 |\n"
      "\n"
      "^ Initial state estimate ^^\n"
      "^ V | 3 |\n"
      "\n"
      "^ Real initial state ^^\n"
      "^ V | 1.25 |\n"
      "\n"
      "^ Real measurement noise ^^\n"
      "^ V | 0.10000000000000001 |\n"
      "\n"
      "^ Real process noise ^^\n"
      "^ V | 1.0000000000000001e-005 |\n"
      "\n"
      "^ Input ^^\n"
      "^ V | 0.0 |\n"
      "\n"
      "^ Observation ^^\n"
      "^ V | 1 |\n"
      "\n"
      "^ State names ^^\n"
      "^ V | V |\n"
      "\n"
      "^ State transition ^^\n"
      "^ V | 1 |\n";
    boost::shared_ptr<QtKalmanFilterExperimentModel> m(new QtKalmanFilterExperimentModel);
    m->FromDokuWiki(s);
    const std::string t = m->ToDokuWiki();
    boost::shared_ptr<QtKalmanFilterExperimentModel> n(new QtKalmanFilterExperimentModel);
    n->FromDokuWiki(t);
    assert(*m == *n);
  }
  */
}
#endif

std::string ribi::kalman::QtKalmanFilterExperimentModel::ToDokuWiki() const noexcept
{
  assert(m_version == m_version_current);

  //TempLocale temp_english_locale("en_US.UTF-8");

  assert(std::to_string(1234) == "1234" && "No digit seperators");
  //assert(boost::lexical_cast<std::string>(1234) == "1234" && "No digit seperators"); //FAILS!
  {
    //std::stringstream s; s << 1234;
    //assert(s.str() == "1234" && "No digit seperators in std::stringstream please"); //FAILS!
  }

  const auto lag_estimated_str = std::to_string(m_lag_estimated);
  const auto lag_real_str = std::to_string(m_lag_real);
  const auto number_of_timesteps_str = std::to_string(m_number_of_timesteps);

  assert(std::count(std::begin(lag_estimated_str),std::end(lag_estimated_str),',') == 0
    && "No decimal seperators please"
  );
  assert(std::count(std::begin(lag_real_str),std::end(lag_real_str),',') == 0
    && "No decimal seperators please"
  );
  assert(std::count(std::begin(number_of_timesteps_str),std::end(number_of_timesteps_str),',') == 0
    && "No decimal seperators please"
  );

  std::stringstream s;
  s << "  * Kalman filter type: " << KalmanFilterTypes().ToStr(m_kalman_filter_type) << "\n"
    << "  * Lag estimated: " << lag_estimated_str << "\n"
    << "  * Lag real: " << lag_real_str << "\n"
    << "  * Number of timesteps: " << number_of_timesteps_str << "\n"
    << "  * Version: " << boost::lexical_cast<std::string>(m_version) << "\n"
    << "  * White noise system type: " << WhiteNoiseSystemTypes().ToStr(m_white_noise_system_type) << "\n"
    << " \n"
    << "<html>\n"   //HTML opening tag must have its own line
    << this->GetContext() << '\n'
    << "</html>\n" //HTML closing tag must have its own line
    << " \n";
  //Go through all m_models
  {
    typedef std::map<KalmanFilterExperimentParameterType,QAbstractTableModel *>::const_iterator Iterator;
    const Iterator j = m_models.end();
    for (Iterator i = m_models.begin(); i!=j; ++i)
    {
      const std::pair<KalmanFilterExperimentParameterType,QAbstractTableModel *> p = *i;
      KalmanFilterExperimentParameterType type = p.first;
      const QAbstractTableModel * const model = p.second;
      assert(type != KalmanFilterExperimentParameterType::n_parameters);
      assert(model);
      const std::string name = KalmanFilterExperimentParameter().ToName(type);
      const int n_cols = model->columnCount();
      const int n_rows = model->rowCount();

      assert(n_cols >= 0);
      assert(n_rows >= 0);
      assert(std::string(0,'^') == "");
      s << "^ " << name << " " << std::string(n_cols,'^') << "^ \n";
      for (int row = 0; row!=n_rows; ++row)
      {
        s  << "^ " << model->headerData(row,Qt::Vertical).toString().toStdString() << " | ";
        for (int col = 0; col!=n_cols; ++col)
        {
          const QModelIndex index = model->index(row,col);
          const QString q = model->data(index).toString();
          std::string str{q.toStdString()};
          std::replace(std::begin(str),std::end(str),',','.');
          const ribi::Regex r;
          assert(r.GetRegexMatches(str,r.GetRegexDutchFloat()).empty() && "No Dutch please"
          );
          s << str << " | ";
        }
        s << "\n";
      }
      s << " \n"; //Empty line after every table, space is really needed
    }
  }
  const std::string text = s.str();
  return text;
}


std::string ribi::kalman::QtKalmanFilterExperimentModel::ToHtml() const noexcept
{
  std::string s =

  "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\""
  "  \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">"
  "<html xmlns=\"http://www.w3.org/1999/xhtml\" lang=\"en\" xml:lang=\"en\">"
  "<head>"
  "<meta http-equiv=\"Content-Type\" content=\"text/html;charset=utf-8\"/>"
  "<title>KalmanFilterer parameters</title>"
  "<meta name=\"description\" content=\"KalmanFilterer parameters\"/>"
  "<meta name=\"keywords\" content=\"KalmanFilterer parameters\"/>"
  "<link rel=\"stylesheet\" href=\"Richelbilderbeek.css\" type=\"text/css\"/>"
  "</head>"
  "<!-- End of head, start of body -->"
  "<body>";


  s+="<h1>KalmanFilterer parameters</h1>";
  s+="<p>&nbsp</p>";
  s+="<ul>";
  s+="  <li>Kalman filter type: " + KalmanFilterTypes().ToStr(m_kalman_filter_type) + "</li>";
  s+="  <li>Lag estimated: " + boost::lexical_cast<std::string>(m_lag_estimated) + "</li>";
  s+="  <li>Lag real: " + boost::lexical_cast<std::string>(m_lag_real) + "</li>";
  s+="  <li>Number of timesteps: " + boost::lexical_cast<std::string>(m_number_of_timesteps) + "</li>";
  s+="  <li>Version: " + boost::lexical_cast<std::string>(m_version) + "</li>";
  s+="  <li>White noise system type: " + WhiteNoiseSystemTypes().ToStr(m_white_noise_system_type) + "</li>";
  s+="</ul>";
  s+="<p>&nbsp</p>";
  s+="<!-- <context> -->";
  s+=m_context;
  s+="<!-- </context> -->";

  //Go through all m_models
  {
    typedef std::map<KalmanFilterExperimentParameterType,QAbstractTableModel *>::const_iterator Iterator;
    const Iterator j = m_models.end();
    for (Iterator i = m_models.begin(); i!=j; ++i)
    {
      const std::pair<KalmanFilterExperimentParameterType,QAbstractTableModel *> p = *i;
      KalmanFilterExperimentParameterType type = p.first;
      const QAbstractTableModel * const model = p.second;
      assert(type != KalmanFilterExperimentParameterType::n_parameters);
      assert(model);
      const std::string name = KalmanFilterExperimentParameter().ToName(type);
      s+="<h2>" + name + "</h2S>";
      s+="<table summary=\"" + name + "\" border=\"1\">";
      const int n_cols = model->columnCount();
      const int n_rows = model->rowCount();
      for (int row = 0; row!=n_rows; ++row)
      {
        s +="<tr>";
        for (int col = 0; col!=n_cols; ++col)
        {
          s +="<td>";
          const QModelIndex index = model->index(row,col);
          const QString q = model->data(index).toString();
          s += q.toStdString();
          s +="</td>";
        }
        s +="</tr>";
      }
      s += "</table>";
    }
  }
  s+="</body>";
  s+="</html>";
  return s;
}

bool ribi::kalman::operator==(const QtKalmanFilterExperimentModel& lhs, const QtKalmanFilterExperimentModel& rhs) noexcept
{
  return lhs.ToDokuWiki() == rhs.ToDokuWiki();
}
