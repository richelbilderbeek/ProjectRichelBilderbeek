#ifndef KALMANFILTEREXAMPLE_H
#define KALMANFILTEREXAMPLE_H

#include <vector>
#include <boost/checked_delete.hpp>
#include <boost/shared_ptr.hpp>
#include "standardkalmanfilterparameters.h"
#include "standardwhitenoisesystemparameters.h"

///KalmanFilterExample contains an example set of variables
struct KalmanFilterExample
{
  KalmanFilterExample(
    const std::vector<std::string>& inputs,
    const boost::shared_ptr<const StandardKalmanFilterParameters>& kalman_filter_parameters,
    const std::vector<std::string>& state_names,
    const boost::shared_ptr<const StandardWhiteNoiseSystemParameters>& white_noise_system_parameters);

  static const std::vector<boost::shared_ptr<KalmanFilterExample> > CreateExamples();
  static const boost::shared_ptr<KalmanFilterExample> CreateExample(const int i);

  const std::vector<std::string>& GetInputs() const
    { return m_inputs; }
  const boost::shared_ptr<const StandardKalmanFilterParameters>& GetKalmanFilterParameters() const
    { return m_kalman_filter_parameters; }
  const std::vector<std::string>& GetStateNames() const
    { return m_state_names; }
  const boost::shared_ptr<const StandardWhiteNoiseSystemParameters>& GetWhiteNoiseSystemParameters() const
    { return  m_white_noise_system_parameters; }

  private:
  ///Can only be deleted by boost::checked_delete
  ~KalmanFilterExample() {}
  friend void boost::checked_delete<>(KalmanFilterExample*);

  const std::vector<std::string> m_inputs;
  const boost::shared_ptr<const StandardKalmanFilterParameters> m_kalman_filter_parameters;
  const std::vector<std::string> m_state_names;
  const boost::shared_ptr<const StandardWhiteNoiseSystemParameters> m_white_noise_system_parameters;

  static const boost::shared_ptr<KalmanFilterExample> CreateExample1();
  static const boost::shared_ptr<KalmanFilterExample> CreateExample2();
  static const boost::shared_ptr<KalmanFilterExample> CreateExample3();
  static const boost::shared_ptr<KalmanFilterExample> CreateExample4();
  static const boost::shared_ptr<KalmanFilterExample> CreateExample5();
  static const boost::shared_ptr<KalmanFilterExample> CreateExample6();
  static const boost::shared_ptr<KalmanFilterExample> CreateExample7();
  static const boost::shared_ptr<KalmanFilterExample> CreateExample8();
  static const boost::shared_ptr<KalmanFilterExample> CreateExample9();
  static const boost::shared_ptr<KalmanFilterExample> CreateExample10();
};

#endif // KALMANFILTEREXAMPLE_H
