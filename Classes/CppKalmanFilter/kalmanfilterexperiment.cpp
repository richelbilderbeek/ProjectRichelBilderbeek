#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "kalmanfilterexperiment.h"

#include <cassert>
#include <boost/numeric/conversion/cast.hpp>

#include "kalmanfiltercalculationelementsfactory.h"
#include "modelfunctionparser.h"
#include "matrix.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::kalman::KalmanFilterExperiment::KalmanFilterExperiment(
  const int time,
  const std::vector<std::string>& input_functions,
  const boost::shared_ptr<KalmanFilter> m_kalman_filter,
  const std::vector<std::string>& state_names,
  const boost::shared_ptr<WhiteNoiseSystem>& m_white_noise_system,
  const std::string& context
  )
  : m_calculation_elements{},
    m_context{context},
    m_inputs{ribi::kalman::KalmanFilterExperiment::ParseInput(input_functions,time)},
    m_kalman_filter{m_kalman_filter},
    m_real_states{},
    m_state_names{state_names},
    m_white_noise_system{m_white_noise_system}
{
  assert(m_kalman_filter);
  assert(this->GetKalmanFilter());
  assert(this->GetKalmanFilter()->GetParameters());
  assert(m_white_noise_system);
  assert(this->GetWhiteNoiseSystem());
  assert(this->GetWhiteNoiseSystem()->GetParameters());
  #ifndef NDEBUG
  {
    const std::size_t sz = state_names.size();
    assert(sz == state_names.size());
    assert(sz == this->GetKalmanFilter()->GetParameters()->GetControl().size1());
    assert(sz == this->GetKalmanFilter()->GetParameters()->GetControl().size2());
    assert(sz == this->GetKalmanFilter()->GetParameters()->GetInitialStateEstimate().size());
    assert(sz == this->GetKalmanFilter()->GetParameters()->GetObservation().size1());
    assert(sz == this->GetKalmanFilter()->GetParameters()->GetObservation().size2());
    assert(sz == this->GetKalmanFilter()->GetParameters()->GetStateTransition().size1());
    assert(sz == this->GetKalmanFilter()->GetParameters()->GetStateTransition().size2());
    assert(sz == GetWhiteNoiseSystem()->GetParameters()->GetControl().size1());
    assert(sz == GetWhiteNoiseSystem()->GetParameters()->GetControl().size2());
    assert(sz == GetWhiteNoiseSystem()->GetParameters()->GetInitialState().size());
    assert(sz == GetWhiteNoiseSystem()->GetParameters()->GetMeasurementNoise().size());
    assert(sz == GetWhiteNoiseSystem()->GetParameters()->GetProcessNoise().size());
    assert(sz == GetWhiteNoiseSystem()->GetParameters()->GetStateTransition().size1());
    assert(sz == GetWhiteNoiseSystem()->PeekAtRealState().size());
    assert(sz == input_functions.size());
  }
  #endif

  

  assert(Matrix::MatricesAreAboutEqual(
    m_kalman_filter->GetParameters()->GetControl(),
    m_white_noise_system->GetParameters()->GetControl()));
  assert(Matrix::MatricesAreAboutEqual(
    m_kalman_filter->GetParameters()->GetStateTransition(),
    m_white_noise_system->GetParameters()->GetStateTransition()));

  
  for (int i=0;i!=time;++i)
  {
    //Update reality, that is, let the real system (i.e. reality) go to its next state
    assert(i < boost::numeric_cast<int>(GetInputs().size()));
    const boost::numeric::ublas::vector<double>& input = GetInputs()[i];

    //assert(m_white_noise_system->GetCurrentState().size() == input.size());

    
    m_white_noise_system->GoToNextState(input);
    

    //Perform a noisy measurement
    const boost::numeric::ublas::vector<double> z_measured = m_white_noise_system->Measure();
    

    //Pass this measurement to the filter
    try
    {
      
      m_kalman_filter->SupplyMeasurementAndInput(z_measured,input);
      
    }
    catch (std::runtime_error& e)
    {
      //Happens when innovation covariance becomes degenerate
      //(that is, its determinant is zero)
      assert(this->IsValid() && "The experiment must end in a valid state");
      return;
    }
    catch (...)
    {
      assert(!"Should never get here");
    }

    this->AppendRealState(m_white_noise_system->PeekAtRealState());

    //Store
    const boost::shared_ptr<KalmanFilterCalculationElements> last_calculation
      = KalmanFilterCalculationElementsFactory().DeepCopy(m_kalman_filter->GetLastCalculation());
    m_calculation_elements.push_back(last_calculation);
  }
  assert(time == boost::numeric_cast<int>(m_calculation_elements.size()));
  assert(this->IsValid() && "The experiment must end in a valid state");
}

void ribi::kalman::KalmanFilterExperiment::AppendRealState(const boost::numeric::ublas::vector<double>& real_state)
{
  this->m_real_states.push_back(real_state);
}

std::vector<boost::numeric::ublas::vector<double> > ribi::kalman::KalmanFilterExperiment::GetMeasuredStates() const
{
  std::vector<boost::numeric::ublas::vector<double> > v;
  v.reserve(m_calculation_elements.size());
  const auto j = m_calculation_elements.end();
  for (auto i = m_calculation_elements.begin(); i!=j; ++i)
  {
    v.push_back( (*i)->GetMeasurement() );
  }
  return v;
}

std::vector<boost::numeric::ublas::vector<double> > ribi::kalman::KalmanFilterExperiment::GetPredictedStates() const
{
  std::vector<boost::numeric::ublas::vector<double> > v;
  v.reserve(m_calculation_elements.size());
  const auto j = m_calculation_elements.end();
  for (auto i = m_calculation_elements.begin(); i!=j; ++i)
  {
    const boost::shared_ptr<KalmanFilterCalculationElements> element = *i;
    v.push_back( element->GetPredictedState() );
  }
  return v;
}

bool ribi::kalman::KalmanFilterExperiment::IsValid() const
{
  //Do not count the inputs: these are created at startup of the experiment
  //and always have the maximum size (of n_timesteps)
  //const int n_inputs = boost::numeric_cast<int>(GetInputs().size());
  const int n_real_states = boost::numeric_cast<int>(GetRealStates().size());
  const int n_predicted_states = boost::numeric_cast<int>(GetPredictedStates().size());
  const int n_measured_states = boost::numeric_cast<int>(GetMeasuredStates().size());
  //Does the experiment produce an equal amount of real, estimated and measured states?
  return n_real_states == n_predicted_states
      && n_real_states == n_measured_states;
}

std::vector<boost::numeric::ublas::vector<double> > ribi::kalman::KalmanFilterExperiment::ParseInput(
  const std::vector<std::string>& input,
  const int n_timesteps)
{
  const int n_rows = n_timesteps;
  const int n_cols = input.size();
  std::vector<boost::numeric::ublas::vector<double> > m(n_rows,
    boost::numeric::ublas::vector<double>(n_cols));

  for (int row=0; row!=n_rows; ++row)
  {
    for (int col=0; col!=n_cols; ++col)
    {
      assert(col < boost::numeric_cast<int>(input.size()));
      const std::string& s = input[col];
      try
      {
        const std::string zero{std::to_string(0.0)}; //For locale
        const ModelFunctionParser f(s.empty() ? zero : s, "t");
        const double y = f.Evaluate( boost::numeric_cast<double>(row) );
        assert(row < boost::numeric_cast<int>(m.size()));
        assert(col < boost::numeric_cast<int>(m[row].size()));
        m[row](col) = y;
      }
      catch (std::runtime_error& e)
      {
        TRACE(e.what());
        TRACE("Unparsable function (will be parsed against 't'):");
        TRACE(s);
        assert(!"Parsing the function should have succeeded, as the GUI takes this out");
        throw;
      }
    }
  }
  assert(n_timesteps == boost::numeric_cast<int>(m.size()));
  assert(m.empty() || input.size() == m[0].size());
  return m;

}
