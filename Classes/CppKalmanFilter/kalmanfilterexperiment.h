#ifndef KALMANFILTEREXPERIMENT_H
#define KALMANFILTEREXPERIMENT_H

#include <vector>

#include <boost/checked_delete.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/noncopyable.hpp>

#include "steadystatekalmanfilterparameters.h"
#include "steadystatekalmanfiltercalculationelements.h"
//#include "standardwhitenoisesystemparameters.h"
#include "kalmanfilter.h"
#include "whitenoisesystem.h"


///A KalmanFilterExperiment
struct KalmanFilterExperiment : public boost::noncopyable
{
  KalmanFilterExperiment(
    const int time,
    const std::vector<std::string>& input,
    const boost::shared_ptr<KalmanFilter> kalman_filter,
    const std::vector<std::string>& state_names,
    const boost::shared_ptr<WhiteNoiseSystem>& white_noise_system,
    const std::string& context = ""
  );

  ///Obtain the calculation elements of each timestep
  const std::vector<boost::shared_ptr<KalmanFilterCalculationElements> >& GetCalculationElements() const
    { return m_calculation_elements; }

  ///Obtain the HTML description of the context of this experiment
  const std::string& GetContext() const { return m_context; }

  ///Obtain the predicted states
  const std::vector<boost::numeric::ublas::vector<double> > GetPredictedStates() const;

  ///Obtain the inputs of each timestep
  const std::vector<boost::numeric::ublas::vector<double> >& GetInputs() const
    { return m_inputs; }

  ///Obtain the Kalman filter
  const boost::shared_ptr<KalmanFilter>& GetKalmanFilter() const { return m_kalman_filter; }

  ///Obtain the measured states, that is, measured with noise
  const std::vector<boost::numeric::ublas::vector<double> > GetMeasuredStates() const;

  ///Obtain the real state, that is, the values that would be measured without noise
  const std::vector<boost::numeric::ublas::vector<double> >& GetRealStates() const
    { return m_real_states; }

  ///Obtain the state names
  const std::vector<std::string>& GetStateNames() const
    { return m_state_names; }

  ///The white noise system
  const boost::shared_ptr<WhiteNoiseSystem>& GetWhiteNoiseSystem() const
    { return m_white_noise_system; }

  ///Check if the state of the class is valid
  bool IsValid() const;

  protected:

  ///Append a real state
  void AppendRealState(const boost::numeric::ublas::vector<double>& real_state);

  private:
  ///Can only be deleted by boost::checked_delete
  ~KalmanFilterExperiment() {}
  friend void boost::checked_delete<>(KalmanFilterExperiment*);

  static const std::vector<boost::numeric::ublas::vector<double> > ParseInput(
    const std::vector<std::string>& input,
    const int n_timesteps);

  ///The calculation elements of each timestep
  std::vector<boost::shared_ptr<KalmanFilterCalculationElements> > m_calculation_elements;

  ///The HTML description of the context of this experiment
  const std::string m_context;

  ///The inputs of each timestep
  const std::vector<boost::numeric::ublas::vector<double> > m_inputs;

  ///The Kalman filter
  const boost::shared_ptr<KalmanFilter> m_kalman_filter;

  ///The real state, that is, the values that would be measured without noise
  std::vector<boost::numeric::ublas::vector<double> > m_real_states;

  ///State names
  const std::vector<std::string> m_state_names;

  ///The white noise system
  const boost::shared_ptr<WhiteNoiseSystem> m_white_noise_system;
};


#endif // KALMANFILTEREXPERIMENT_H
