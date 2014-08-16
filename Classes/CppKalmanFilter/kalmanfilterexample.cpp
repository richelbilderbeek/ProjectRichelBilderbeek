#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "kalmanfilterexample.h"

#include <cassert>

#include <boost/math/constants/constants.hpp>

#include <memory>


#include <boost/lexical_cast.hpp>
#include <boost/numeric/ublas/io.hpp>
#include "matrix.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::kalman::KalmanFilterExample::KalmanFilterExample(
  const std::string& title,
  const std::string& context,
  const std::vector<std::string>& inputs,
  const boost::shared_ptr<const StandardKalmanFilterParameters>& kalman_filter_parameters,
  const int number_of_timesteps,
  const std::vector<std::string>& state_names,
  const boost::shared_ptr<const StandardWhiteNoiseSystemParameters>& white_noise_system_parameters)
  : m_context{context},
    m_inputs{inputs},
    m_kalman_filter_parameters{kalman_filter_parameters},
    m_number_of_timesteps{number_of_timesteps},
    m_state_names{state_names},
    m_title{title},
    m_white_noise_system_parameters{white_noise_system_parameters}
{
  assert(!m_state_names.empty());
  assert(m_state_names.size() == m_inputs.size());
  assert(m_state_names.size() == m_kalman_filter_parameters->GetInitialStateEstimate().size());
  assert(m_state_names.size() == m_white_noise_system_parameters->GetInitialState().size());
  assert(number_of_timesteps >= 0);

}

std::vector<boost::shared_ptr<ribi::kalman::KalmanFilterExample> > ribi::kalman::KalmanFilterExample::CreateExamples() noexcept
{
  std::vector<boost::shared_ptr<KalmanFilterExample> > v;
  for (int i=0; ; ++i)
  {
    std::unique_ptr<KalmanFilterExample> p(CreateExample(i));
    if (!p) return v;
    const boost::shared_ptr<KalmanFilterExample> q(p.release());
    assert(q);
    assert(q.use_count() == 1);
    assert(!p);
    v.push_back(q);
  }
  assert(!"Cannot get here: must return in for loop above");
}

std::unique_ptr<ribi::kalman::KalmanFilterExample> ribi::kalman::KalmanFilterExample::CreateExample(const int i)
{
  std::unique_ptr<KalmanFilterExample> p;
  switch (i)
  {
    case 0: p = CreateExample0(); break;
    case 1: p = CreateExample1(); break;
    case 2: p = CreateExample2(); break;
    case 3: p = CreateExample3(); break;
    case 4: p = CreateExample4(); break;
    case 5: p = CreateExample5(); break;
    case 6: p = CreateExample6(); break;
    case 7: p = CreateExample7(); break;
    case 8: p = CreateExample8(); break;
    default: break;
  }
  //When p is nullptr, this indicates that there are no more examples

  return p;
}



std::unique_ptr<ribi::kalman::KalmanFilterExample> ribi::kalman::KalmanFilterExample::CreateExample0()
{
  const std::string title = "Constant voltage";

  const int number_of_timesteps = 1000;

  const boost::numeric::ublas::matrix<double> control
    = Matrix::CreateMatrix(1,1, { 0.0 } );
  const boost::numeric::ublas::matrix<double> estimated_measurement_noise
    = Matrix::CreateMatrix(1,1, { 0.1 } );
  const boost::numeric::ublas::matrix<double> estimated_process_noise_covariance
    = Matrix::CreateMatrix(1,1, { 0.0001 } );
  const boost::numeric::ublas::matrix<double> initial_covariance_estimate
    = Matrix::CreateMatrix(1,1, { 1.0 } );
  const boost::numeric::ublas::vector<double> initial_state_estimate
    = Matrix::CreateVector( { 3.0 } );
  const boost::numeric::ublas::matrix<double> observation
    = Matrix::CreateMatrix(1,1, { 1.0 } );
  const boost::numeric::ublas::matrix<double> state_transition
    = Matrix::CreateMatrix(1,1, {1.0} );
  const boost::numeric::ublas::vector<double> initial_state
    = Matrix::CreateVector( { 1.25 } );
  const boost::numeric::ublas::vector<double> real_measurement_noise
    = Matrix::CreateVector( { 0.1 } );
  const boost::numeric::ublas::vector<double> real_process_noise
    = Matrix::CreateVector( { 0.00001 } );


  const std::vector<std::string> inputs = { "0.0" };

  const boost::shared_ptr<const StandardKalmanFilterParameters> kalman_filter_parameters(
    new StandardKalmanFilterParameters(
    control,
    estimated_measurement_noise,
    estimated_process_noise_covariance,
    initial_covariance_estimate,
    initial_state_estimate,
    observation,
    state_transition)
  );

  const std::vector<std::string> state_names = { "V" };

  const boost::shared_ptr<const StandardWhiteNoiseSystemParameters> white_noise_system_parameters(
    new StandardWhiteNoiseSystemParameters(
    control,
    initial_state,
    real_measurement_noise,
    real_process_noise,
    state_transition)
  );

  assert(state_names.size() == inputs.size());
  assert(state_names.size() == kalman_filter_parameters->GetInitialStateEstimate().size());
  assert(state_names.size() == white_noise_system_parameters->GetInitialState().size());

  std::stringstream context_stream;
  context_stream
    << "<h1>" << title << "</h1>" << '\n'
    << "<p>This is an example from <a href=\"http://greg.czerniak.info/guides/kalman1\">Greg Czerniak's tutorial</a></p>" << '\n'
    << "<p>The context is the noisy measurement of a constant voltage.<p>" << '\n'
    << "<ul>" << '\n'
    << "  <li>State names: " << DisplayAsUblasVector(state_names) << ": the voltage</li>" << '\n'
    << "  <li>Initial state, real: " << initial_state << ": just some voltage</li>" << '\n'
    << "  <li>Initial state, estimate: " << initial_state_estimate << ": set this value off on purpose, to see the Kalman filter converge</li>" << '\n'
    << "  <li>Input: " << DisplayAsUblasVector(inputs) << ": the state (that is, the voltage) will not be changed</li>" << '\n'
    << "  <li>Control: " << control << ": any input (albeit none) will have no effect</li>" << '\n'
    << "  <li>Observation: " << observation << ": the voltage is measured directly (that is: as a voltage)</li>" << '\n'
    << "  <li>State transition: " << state_transition << ": the voltage remains constant</li>" << '\n'
    << "  <li>Measurement noise, real: " << real_measurement_noise << ": just some low value</li>" << '\n'
    << "  <li>Measurement noise, estimate: " << estimated_measurement_noise << ": just some low value</li>" << '\n'
    << "  <li>Process noise, real: " << real_process_noise << ": just some low value</li>" << '\n'
    << "  <li>Process noise, estimated covariance: " << estimated_process_noise_covariance << ": just some low value</li>" << '\n'
    << "  <li>Initial covariance estimate: " << initial_covariance_estimate << ": just some low value</li>" << '\n'
    << "</ul>";
  const std::string context = context_stream.str();


  std::unique_ptr<KalmanFilterExample> example(
    new KalmanFilterExample(
      title,
      context,
      inputs,
      kalman_filter_parameters,
      number_of_timesteps,
      state_names,
      white_noise_system_parameters
    )
  );
  assert(example);
  
  return example;
}

std::unique_ptr<ribi::kalman::KalmanFilterExample> ribi::kalman::KalmanFilterExample::CreateExample1()
{
  const std::string title = "Accelerating car (two states)";
  const int n = 2;
  const double acceleration = 1.0;
  const double measurement_noise = 10.0; //Called 'measnoise'
  const double accelnoise = 0.2; //Called 'accelnoise'
  const double dt = 0.1; //Timestep

  const int number_of_timesteps = 1000;

  const boost::numeric::ublas::matrix<double> control
    = Matrix::CreateMatrix(n,n, { 0.0,0.0,0.0,dt } );

  const boost::numeric::ublas::matrix<double> initial_covariance_estimate
    = Matrix::CreateMatrix(n,n, { 1.0,0.0,0.0,1.0 } );

  const boost::numeric::ublas::vector<double> initial_state_estimate
    = Matrix::CreateVector( { 10.0,1.0 } );

  const boost::numeric::ublas::vector<double> initial_state
    = Matrix::CreateVector( { 0.0,0.0 } );

  const boost::numeric::ublas::matrix<double> estimated_measurement_noise
    = Matrix::CreateMatrix(n,n, { 10.0 * measurement_noise,0.0,0.0,1000000.0 } );

  const boost::numeric::ublas::matrix<double> observation
    = Matrix::CreateMatrix(n,n, { 1.0,0.0,0.0,0.0 } );

  const boost::numeric::ublas::matrix<double> estimated_process_noise_covariance
    = Matrix::CreateMatrix(n,n, {
      10.0 * accelnoise,
      10.0 * accelnoise,
      10.0 * accelnoise,
      10.0 * accelnoise
    } );

  const boost::numeric::ublas::vector<double> real_measurement_noise
    = Matrix::CreateVector( { measurement_noise, 1000000.0 } );

  const boost::numeric::ublas::vector<double> real_process_noise
    = Matrix::CreateVector( { 0.5  * accelnoise * dt * dt, accelnoise * dt} );

  const boost::numeric::ublas::matrix<double> state_transition
    = Matrix::CreateMatrix(n,n, { 1.0, 0.0, dt, 1.0 } );

  const std::vector<std::string> inputs = { "0.0", boost::lexical_cast<std::string>(acceleration) };

  const boost::shared_ptr<const StandardKalmanFilterParameters> kalman_filter_parameters(
    new StandardKalmanFilterParameters(
    control,
    estimated_measurement_noise,
    estimated_process_noise_covariance,
    initial_covariance_estimate,
    initial_state_estimate,
    observation,
    state_transition)
  );

  const std::vector<std::string> state_names = { "x", "v" };

  const boost::shared_ptr<const StandardWhiteNoiseSystemParameters> white_noise_system_parameters(
    new StandardWhiteNoiseSystemParameters(
    control,
    initial_state,
    real_measurement_noise,
    real_process_noise,
    state_transition)
  );

  assert(control.size1() > 0);
  assert(control.size2() > 0);
  assert(state_names.size() == inputs.size());
  assert(state_names.size() == kalman_filter_parameters->GetInitialStateEstimate().size());
  assert(state_names.size() == white_noise_system_parameters->GetInitialState().size());
  assert(Matrix::MatricesAreEqual(kalman_filter_parameters->GetControl(),white_noise_system_parameters->GetControl()));
  assert(Matrix::MatricesAreEqual(kalman_filter_parameters->GetStateTransition(),white_noise_system_parameters->GetStateTransition()));

  std::stringstream context_stream;
  context_stream
    << "<h1>" << title << "</h1>" << '\n'
    << "<p>This is an example from D. Simon's article 'Kalman Filtering', published in 'Embedded Systems Programming' (June 2001).</p>" << '\n'
    << "<p>The context is an accelerating car with a GPS and a defect speedometer<p>" << '\n'
    << "<ul>" << '\n'
    << "  <li>State names: " << DisplayAsUblasVector(state_names) << ": position (e.g. meter) and velocity (e.g. meter per second)</li>" << '\n'
    << "  <li>Initial state, real: " << initial_state << ": car starts from standstill</li>" << '\n'
    << "  <li>Initial state, estimate: " << initial_state_estimate << ": set this value off on purpose, to see the Kalman filter converge</li>" << '\n'
    << "  <li>Input: " << DisplayAsUblasVector(inputs) << ": a gas pedal is pushed to a certain acceleration value</li>" << '\n'
    << "  <li>Control: " << control << ": a gas pedal has an influence on the velocity</li>" << '\n'
    << "  <li>Observation: " << observation << ": only observe position, which can be observed directly with a GPS</li>" << '\n'
    << "  <li>State transition: " << state_transition << ": the position is increased by a velocity, the velocity stays constant without input</li>" << '\n'
    << "  <li>Measurement noise, real: " << real_measurement_noise << ": GPS works, speedometer does not</li>" << '\n'
    << "  <li>Measurement noise, estimate: " << estimated_measurement_noise << ": just some pessimistic value</li>" << '\n'
    << "  <li>Process noise, real: " << real_process_noise << ": noise caused by acceleration</li>" << '\n'
    << "  <li>Process noise, estimated covariance: " << estimated_process_noise_covariance << ": a more pessimistic value</li>" << '\n'
    << "  <li>Initial covariance estimate: " << initial_covariance_estimate << ": just a guess</li>" << '\n'
    << "</ul>";
  const std::string context = context_stream.str();

  std::unique_ptr<KalmanFilterExample> example(
    new KalmanFilterExample(
      title,
      context,
      inputs,
      kalman_filter_parameters,
      number_of_timesteps,
      state_names,
      white_noise_system_parameters
    )
  );
  assert(example);
  return example;
}

std::unique_ptr<ribi::kalman::KalmanFilterExample> ribi::kalman::KalmanFilterExample::CreateExample2()
{
  const std::string title = "Cannonball";
  const int number_of_timesteps = 1000;

  const int n = 4; //Size of all vectors and matrices
  const double dt = 0.1; //Timestep
  const double g = 9.81; //Gravity

  const double pi = boost::math::constants::pi<double>();
  const double angle = pi / 4.0; //Radians. 45 degrees = pi / 4.0 radians


  //Gravity influences y and Vy
  const boost::numeric::ublas::matrix<double> control
    = Matrix::CreateMatrix(n,n,
      {
        0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
      }
    );

  //Just a guess
  const boost::numeric::ublas::matrix<double> initial_covariance_estimate
    = Matrix::CreateMatrix(n,n,
      {
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
      }
    );

  //Initial state estimates are a bit off on purpose
  const boost::numeric::ublas::vector<double> initial_state_estimate
    = Matrix::CreateVector( { 0.0, 100.0 * std::cos(angle), 500.0, 100.0 * sin(angle) } );

  //Shot from the cannon with velocity 100.0 at an angle
  const boost::numeric::ublas::vector<double> initial_state
    = Matrix::CreateVector( { 0.0, 100.0 * std::cos(angle), 0.0, 100.0 * sin(angle) } );

  //Gravity influences position and velocity in the vertical direction
  const std::vector<std::string> inputs
    = {
      boost::lexical_cast<std::string>( 0.0 ),
      boost::lexical_cast<std::string>( 0.0 ),
      boost::lexical_cast<std::string>( -0.5*g*dt*dt ),
      boost::lexical_cast<std::string>( -    g*dt    )
    };

  //ust an estimation
  const boost::numeric::ublas::matrix<double> estimated_measurement_noise
    = Matrix::CreateMatrix(n,n,
      {
        0.2, 0.0, 0.0, 0.0,
        0.0, 0.2, 0.0, 0.0,
        0.0, 0.0, 0.2, 0.0,
        0.0, 0.0, 0.0, 0.2
      }
    );

  //Can observe all positions and speeds
  const boost::numeric::ublas::matrix<double> observation
    = Matrix::CreateMatrix(n,n,
      {
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
      }
    );

  //Due to this being a simulation, one can safely assume no process noise
  const boost::numeric::ublas::matrix<double> estimated_process_noise_covariance
    = Matrix::CreateMatrix(n,n,
      {
        0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0
      }
    );

  //Noise in GPS and speedometer in cannonball
  const boost::numeric::ublas::vector<double> real_measurement_noise
    = Matrix::CreateVector( { 30.0, 30.0, 30.0, 30.0 } );

  //Due to this being a simulation, put in no process noise
  const boost::numeric::ublas::vector<double> real_process_noise
    = Matrix::CreateVector( { 0.0, 0.0, 0.0, 0.0 } );


  //Velocities influence positions
  const boost::numeric::ublas::matrix<double> state_transition
    = Matrix::CreateMatrix(n,n,
      { //Beware: appears as transposition of real matrix
        1.0, 0.0, 0.0, 0.0,
         dt, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, dt , 1.0
      }
    );

  const boost::shared_ptr<const StandardKalmanFilterParameters> kalman_filter_parameters(
    new StandardKalmanFilterParameters(
    control,
    estimated_measurement_noise,
    estimated_process_noise_covariance,
    initial_covariance_estimate,
    initial_state_estimate,
    observation,
    state_transition)
  );

  const std::vector<std::string> state_names = { "x", "Vx", "y", "Vy" };

  const boost::shared_ptr<const StandardWhiteNoiseSystemParameters> white_noise_system_parameters(
    new StandardWhiteNoiseSystemParameters(
    control,
    initial_state,
    real_measurement_noise,
    real_process_noise,
    state_transition)
  );

  assert(state_names.size() == inputs.size());
  assert(state_names.size() == kalman_filter_parameters->GetInitialStateEstimate().size());
  assert(state_names.size() == white_noise_system_parameters->GetInitialState().size());

  std::stringstream context_stream;
  context_stream
    << "<h1>" << title << "</h1>" << '\n'
    << "<p>This is an example from <a href=\"http://greg.czerniak.info/guides/kalman1\">Greg Czerniak's tutorial</a></p>" << '\n'
    << "<p>The context is a cannonball lauched from a cannon.<p>" << '\n'
    << "<ul>" << '\n'
    << "  <li>State names: " << DisplayAsUblasVector(state_names) << ": horizontal position (m), horizontal velocity (m/s), vertical position (m), vertical velocity (m)</li>" << '\n'
    << "  <li>Initial state, real: " << initial_state << ": the cannon shoots the ball from an angle of 45 degrees at an initial speed of 100 m/s</li>" << '\n'
    << "  <li>Initial state, estimate: " << initial_state_estimate << ": set this value off on purpose, to see the Kalman filter converge</li>" << '\n'
    << "  <li>Input: " << DisplayAsUblasVector(inputs) << ": gravity will change the vertical velocity by 9.81 m/(s^2)</li>" << '\n'
    << "  <li>Control: " << control << ": gravity influences the vertical velocity only</li>" << '\n'
    << "  <li>Observation: " << observation << ": all states are observed directly with a GPS and an internal speedometer</li>" << '\n'
    << "  <li>State transition: " << state_transition << ": positions are increased by their velocities. Velocities remain constant without input</li>" << '\n'
    << "  <li>Measurement noise, real: " << real_measurement_noise << ": just some low value</li>" << '\n'
    << "  <li>Measurement noise, estimate: " << estimated_measurement_noise << ": just some low value</li>" << '\n'
    << "  <li>Process noise, real: " << real_process_noise << ": just some low value</li>" << '\n'
    << "  <li>Process noise, estimated covariance: " << estimated_process_noise_covariance << ": just some low value</li>" << '\n'
    << "  <li>Initial covariance estimate: " << initial_covariance_estimate << ": just some low value</li>" << '\n'
    << "</ul>";
  const std::string context = context_stream.str();

  std::unique_ptr<KalmanFilterExample> example(
    new KalmanFilterExample(
      title,
      context,
      inputs,
      kalman_filter_parameters,
      number_of_timesteps,
      state_names,
      white_noise_system_parameters
    )
  );
  assert(example);
  return example;
}

std::unique_ptr<ribi::kalman::KalmanFilterExample> ribi::kalman::KalmanFilterExample::CreateExample3()
{
  const std::string title = "Spring";
  const std::string context
    = "<h1>" + title + "</h1>";

  //Use spring system: a mass is lying on a frictionless surface and is connected to two horizontal springs
  const int n = 2; //Size of vectors and matrices
  const double dt = 0.1; //Timestep
  const double k = 1.0; //Spring constant
  const double mass = 1.0; //Mass

  const int number_of_timesteps = 1000;

  //No input used, so control matrix can be zeroes only
  const boost::numeric::ublas::matrix<double> control
    = Matrix::CreateMatrix(n,n,
      {
        0.0, 0.0,
        0.0, 0.0
      }
    );

  //Just a guess
  const boost::numeric::ublas::matrix<double> initial_covariance_estimate
    = Matrix::CreateMatrix(n,n,
      {
        1.0, 0.0,
        0.0, 1.0
      }
    );

  //Initial state estimates are a bit off on purpose
  const boost::numeric::ublas::vector<double> initial_state_estimate
    = Matrix::CreateVector( { -10.0, -1.0 } );

  //From a perfect standstill at a certain position
  const boost::numeric::ublas::vector<double> initial_state
    = Matrix::CreateVector( { 10.0, 0.0 } );

  //There is no input supplied
  const std::vector<std::string> inputs
    = {
      boost::lexical_cast<std::string>( 0.0 ),
      boost::lexical_cast<std::string>( 0.0 )
    };

  const boost::numeric::ublas::matrix<double> estimated_measurement_noise
    = Matrix::CreateMatrix(n,n,
      {
        1.0, 0.0,
        0.0, 1.0
      }
    );

  //Observe the position of the spring only
  const boost::numeric::ublas::matrix<double> observation
    = Matrix::CreateMatrix(n,n,
      {
        1.0, 0.0,
        0.0, 0.0
      }
    );

  const boost::numeric::ublas::matrix<double> estimated_process_noise_covariance
    = Matrix::CreateMatrix(n,n,
      {
        1.0, 0.0,
        0.0, 1.0
      }
    );

  //Some noise
  const boost::numeric::ublas::vector<double> real_measurement_noise
    = Matrix::CreateVector( { 1.0, 1.0 } );

  //Simulation, so process noise is zero
  const boost::numeric::ublas::vector<double> real_process_noise
    = Matrix::CreateVector( { 0.0, 0.0 } );

  const std::vector<std::string> state_names = { "x", "v" };

  const boost::numeric::ublas::matrix<double> state_transition
    = boost::numeric::ublas::trans(Matrix::CreateMatrix(n,n,
      { //As on paper
        1.0,   -dt*k/mass,
        dt , 0.99
      }
    ));


  const boost::shared_ptr<const StandardKalmanFilterParameters> kalman_filter_parameters(
    new StandardKalmanFilterParameters(
    control,
    estimated_measurement_noise,
    estimated_process_noise_covariance,
    initial_covariance_estimate,
    initial_state_estimate,
    observation,
    state_transition)
  );

  const boost::shared_ptr<const StandardWhiteNoiseSystemParameters> white_noise_system_parameters(
    new StandardWhiteNoiseSystemParameters(
    control,
    initial_state,
    real_measurement_noise,
    real_process_noise,
    state_transition)
  );

  assert(state_names.size() == inputs.size());
  assert(state_names.size() == kalman_filter_parameters->GetInitialStateEstimate().size());
  assert(state_names.size() == white_noise_system_parameters->GetInitialState().size());

  std::unique_ptr<KalmanFilterExample> example(
    new KalmanFilterExample(
      title,
      context,
      inputs,
      kalman_filter_parameters,
      number_of_timesteps,
      state_names,
      white_noise_system_parameters
    )
  );
  assert(example);
  return example;
}

std::unique_ptr<ribi::kalman::KalmanFilterExample> ribi::kalman::KalmanFilterExample::CreateExample4()
{
  const std::string title = "Airhockey puck";
  const std::string context
    = "<h1>" + title + "</h1>";

  //Context: airhockey puck with a constant speed
  const int number_of_timesteps = 1000;

  const boost::numeric::ublas::matrix<double> control
    = Matrix::CreateMatrix(1,1, { 1.0 } );
  const boost::numeric::ublas::matrix<double> estimated_measurement_noise
    = Matrix::CreateMatrix(1,1, { 0.0000001 } );
  const boost::numeric::ublas::matrix<double> estimated_process_noise_covariance
    = Matrix::CreateMatrix(1,1, { 0.0 } );
  const boost::numeric::ublas::matrix<double> initial_covariance_estimate
    = Matrix::CreateMatrix(1,1, { 0.0 } );
  const boost::numeric::ublas::vector<double> initial_state_estimate
    = Matrix::CreateVector( { 0.0 } );
  const boost::numeric::ublas::matrix<double> observation
    = Matrix::CreateMatrix(1,1, { 1.0 } );
  const boost::numeric::ublas::matrix<double> state_transition
    = Matrix::CreateMatrix(1,1, {1.0} );
  const boost::numeric::ublas::vector<double> initial_state
    = Matrix::CreateVector( { 0.0 } );
  const boost::numeric::ublas::vector<double> real_measurement_noise
    = Matrix::CreateVector( { 0.0 } );
  const boost::numeric::ublas::vector<double> real_process_noise
    = Matrix::CreateVector( { 0.0 } );


  const std::vector<std::string> inputs
    = {
      boost::lexical_cast<std::string>( 1.0 )
    };

  const boost::shared_ptr<const StandardKalmanFilterParameters> kalman_filter_parameters(
    new StandardKalmanFilterParameters(
    control,
    estimated_measurement_noise,
    estimated_process_noise_covariance,
    initial_covariance_estimate,
    initial_state_estimate,
    observation,
    state_transition)
  );

  const std::vector<std::string> state_names = { "x" };

  const boost::shared_ptr<const StandardWhiteNoiseSystemParameters> white_noise_system_parameters(
    new StandardWhiteNoiseSystemParameters(
    control,
    initial_state,
    real_measurement_noise,
    real_process_noise,
    state_transition)
  );

  assert(state_names.size() == inputs.size());
  assert(state_names.size() == kalman_filter_parameters->GetInitialStateEstimate().size());
  assert(state_names.size() == white_noise_system_parameters->GetInitialState().size());

  std::unique_ptr<KalmanFilterExample> example(
    new KalmanFilterExample(
      title,
      context,
      inputs,
      kalman_filter_parameters,
      number_of_timesteps,
      state_names,
      white_noise_system_parameters
    )
  );
  assert(example);
  return example;
}



std::unique_ptr<ribi::kalman::KalmanFilterExample> ribi::kalman::KalmanFilterExample::CreateExample5()
{
  const std::string title = "Accelerating car (3 states)";
  const std::string context
    = "<h1>" + title + "</h1>";

  //Another accelerating car
  const int n = 3;
  const double force =  1000.0; //Newton
  const double mass  = 10000.0; //kilogram
  const double dt = 0.1; //Timestep
  const double acc = dt * force / mass;

  const int number_of_timesteps = 1000;

  //A gas pedal only influences acceleration
  const boost::numeric::ublas::matrix<double> control
    = Matrix::CreateMatrix(n,n,
    {
      0.0,0.0,0.0,
      0.0,0.0,0.0,
      0.0,0.0,acc
    } );

  //Just a guess
  const boost::numeric::ublas::matrix<double> initial_covariance_estimate
    = Matrix::CreateMatrix(n,n,
      {
        1.0,0.0,0.0,
        0.0,1.0,0.0,
        0.0,0.0,1.0
      } );

  //Initial state estimates are a bit off on purpose
  const boost::numeric::ublas::vector<double> initial_state_estimate
    = Matrix::CreateVector( { 10.0,1.0,-1.0 } );

  //From exact standstill
  const boost::numeric::ublas::vector<double> initial_state
    = Matrix::CreateVector( { 0.0,0.0,0.0 } );

  //Only (pessimistic) normal noise in GPS, speedometer and accelerometer
  const boost::numeric::ublas::matrix<double> estimated_measurement_noise
    = Matrix::CreateMatrix(n,n,
    {
      100.0,  0.0,  0.0,
        0.0,100.0,  0.0,
        0.0,  0.0,100.0
    } );

  //Observe all: GPS, speedometer, accelerometer
  const boost::numeric::ublas::matrix<double> observation
    = Matrix::CreateMatrix(n,n,
    {
      1.0,0.0,0.0,
      0.0,1.0,0.0,
      0.0,0.0,1.0
    } );

  const boost::numeric::ublas::matrix<double> estimated_process_noise_covariance
    = Matrix::CreateMatrix(n,n, {
      0.1,0.0,0.0,
      0.0,0.1,0.0,
      0.0,0.0,0.1,
    } ); //Pessimistic estimate

  //Only normal noise in GPS, speedometer has enormous noise as if defect (yet cannot be 0.0)
  const boost::numeric::ublas::vector<double> real_measurement_noise
    = Matrix::CreateVector( { 10.0, 10.0, 10.0 } );

  const boost::numeric::ublas::vector<double> real_process_noise
    = Matrix::CreateVector( { 0.01, 0.01, 0.01 } );

  //x(t+1) = x(t) + dt*v(t) + 0.5*(dt^2)*a(t)
  //v(t+1) =           v(t) +     (dt  )*a(t)
  //a(t+1) =                             a(t)
  const boost::numeric::ublas::matrix<double> state_transition
    = boost::numeric::ublas::trans(Matrix::CreateMatrix(n,n,
      { //Shown as on paper
        1.0,  dt, 0.5*dt*dt,
        0.0, 1.0,        dt,
        0.0, 0.0,       1.0
      } ));

  //A gas pedal only influences acceleration
  const std::vector<std::string> inputs = { "0.0", "0.0", "1.0" };

  const boost::shared_ptr<const StandardKalmanFilterParameters> kalman_filter_parameters(
    new StandardKalmanFilterParameters(
    control,
    estimated_measurement_noise,
    estimated_process_noise_covariance,
    initial_covariance_estimate,
    initial_state_estimate,
    observation,
    state_transition)
  );

  const std::vector<std::string> state_names = { "x", "v", "a" };

  const boost::shared_ptr<const StandardWhiteNoiseSystemParameters> white_noise_system_parameters(
    new StandardWhiteNoiseSystemParameters(
    control,
    initial_state,
    real_measurement_noise,
    real_process_noise,
    state_transition)
  );

  assert(control.size1() > 0);
  assert(control.size2() > 0);
  assert(state_names.size() == inputs.size());
  assert(state_names.size() == kalman_filter_parameters->GetInitialStateEstimate().size());
  assert(state_names.size() == white_noise_system_parameters->GetInitialState().size());
  assert(Matrix::MatricesAreEqual(kalman_filter_parameters->GetControl(),white_noise_system_parameters->GetControl()));
  assert(Matrix::MatricesAreEqual(kalman_filter_parameters->GetStateTransition(),white_noise_system_parameters->GetStateTransition()));

  std::unique_ptr<KalmanFilterExample> example(
    new KalmanFilterExample(
      title,
      context,
      inputs,
      kalman_filter_parameters,
      number_of_timesteps,
      state_names,
      white_noise_system_parameters
    )
  );
  assert(example);
  return example;
}

std::unique_ptr<ribi::kalman::KalmanFilterExample> ribi::kalman::KalmanFilterExample::CreateExample6()
{
  const std::string title = "Exponential decay";
  //One state
  const int n = 1;
  //As small as possible
  const double epsilon = 0.00000000001;
  //Reach a 10% value after 1000 timesteps with the closed-form solution
  const double gamma = -std::log(0.1)/1000.0;
  //Reach a 10% value after 1000 timesteps with the recurrence equation

  const double e = boost::math::constants::e<double>();
  const double tau = std::pow(e,std::log(0.1) / 1000.0);

  const int number_of_timesteps = 1000;

  //Just a variable name
  const std::vector<std::string> state_names = { "x" };

  //Input does not change state
  const boost::numeric::ublas::matrix<double> control
    = Matrix::CreateMatrix(n,n, { 0.0 } );

  //As small as possible
  const boost::numeric::ublas::matrix<double> initial_covariance_estimate
    = Matrix::CreateMatrix(n,n, { epsilon } );

  //From 100%
  const boost::numeric::ublas::vector<double> initial_state
    = Matrix::CreateVector( { 1.0 } );

  //Initial state estimate is correct on purpose
  const boost::numeric::ublas::vector<double> initial_state_estimate = initial_state;

  //As small as possible
  const boost::numeric::ublas::matrix<double> estimated_measurement_noise
    = Matrix::CreateMatrix(n,n, { epsilon } );

  //Observe directly
  const boost::numeric::ublas::matrix<double> observation
    = Matrix::CreateMatrix(n,n, { 1.0 } );

  //As small as possible
  const boost::numeric::ublas::matrix<double> estimated_process_noise_covariance
    = Matrix::CreateMatrix(n,n, { epsilon } );

  //As small as possible
  const boost::numeric::ublas::vector<double> real_measurement_noise
    = Matrix::CreateVector( { epsilon } );

  //As small as possible
  const boost::numeric::ublas::vector<double> real_process_noise
    = Matrix::CreateVector( { epsilon } );

  //Reach a 10% value after 1000 timesteps with the recurrence equation
  const boost::numeric::ublas::matrix<double> state_transition
    = boost::numeric::ublas::trans(Matrix::CreateMatrix(n,n, { tau } ));

  //Reach a 10% value after 1000 timesteps with the closed-form solution
  const std::string input = "exp(-" + boost::lexical_cast<std::string>(gamma) + "*(t+1))";
  const std::vector<std::string> inputs = { input };

  const boost::shared_ptr<const StandardKalmanFilterParameters> kalman_filter_parameters(
    new StandardKalmanFilterParameters(
    control,
    estimated_measurement_noise,
    estimated_process_noise_covariance,
    initial_covariance_estimate,
    initial_state_estimate,
    observation,
    state_transition)
  );

  const boost::shared_ptr<const StandardWhiteNoiseSystemParameters> white_noise_system_parameters(
    new StandardWhiteNoiseSystemParameters(
    control,
    initial_state,
    real_measurement_noise,
    real_process_noise,
    state_transition)
  );

  assert(control.size1() > 0);
  assert(control.size2() > 0);
  assert(state_names.size() == inputs.size());
  assert(state_names.size() == kalman_filter_parameters->GetInitialStateEstimate().size());
  assert(state_names.size() == white_noise_system_parameters->GetInitialState().size());
  assert(Matrix::MatricesAreEqual(kalman_filter_parameters->GetControl(),white_noise_system_parameters->GetControl()));
  assert(Matrix::MatricesAreEqual(kalman_filter_parameters->GetStateTransition(),white_noise_system_parameters->GetStateTransition()));

  std::stringstream context_stream;
  context_stream
    << "<h1>" << title << "</h1>" << '\n'
    << "<p>&nbsp;</p>" << '\n'
    << "<p>" << '\n'
    << "  This is more of a mathematical example. It shows that" << '\n'
    << "  a recurrence equation and its closed-form solution for exponential" << '\n'
    << "  decay are equivalent" << '\n'
    << "</p>" << '\n'
    << "<p>" << '\n'
    << "  The closed-form solution of exponential decay is:" << '\n'
    << "</p>" << '\n'
    << "<p>" << '\n'
    << "  f(t) = e^(-gamma*t)" << '\n'
    << "</p>" << '\n'
    << "<p>" << '\n'
    << "  Where t is the time step and gamma a constant, which is equal to -ln(0.1)/1000 = 0.0023025850929940454." << '\n'
    << "  This value of gamma lets the exponential decay reach 10% after 1000 timesteps." << '\n'
    << "</p>" << '\n'
    << "<p>" << '\n'
    << "  The recurrence equation of exponential decay is:" << '\n'
    << "</p>" << '\n'
    << "<p>" << '\n'
    << "  f(t+1) = tau * f(t)" << '\n'
    << "</p>" << '\n'
    << "<p>" << '\n'
    << "  Where t is the time step and tau a constant, which is equal to e^(ln(0.1)/1000) = 0.99770006382255327." << '\n'
    << "  This value of tau lets the exponential decay reach 10% after 1000 timesteps." << '\n'
    << "</p>" << '\n'
    << "<p>" << '\n'
    << "  The closed-form solution is plotted as the input, the recurrence equation as the state." << '\n'
    << "  Because the control matrix contains a zero only, the input has no influence on the state." << '\n'
    << "  For the cleanest look, all noise was set to a low value." << '\n'
    << "</p>" << '\n'
    << "<p>&nbsp;</p>" << '\n'
    << "<ul>" << '\n'
    << "  <li>State names: " << DisplayAsUblasVector(state_names) << ": just a variable without meaning</li>" << '\n'
    << "  <li>Initial state, real: " << initial_state << ": decay starting from 1.0</li>" << '\n'
    << "  <li>Initial state, estimate: " << initial_state_estimate << ": set this value to the real value, there is no need to do estimation</li>" << '\n'
    << "  <li>Input: " << DisplayAsUblasVector(inputs) << ": the closed-form solution of exponential decay. t must be increased by one timestep, because a Kalman Filter estimates after an update</li>" << '\n'
    << "  <li>Control: " << control << ": input must have no effect in changing the state to do a valid comparison</li>" << '\n'
    << "  <li>Observation: " << observation << ": the value is observed directly</li>" << '\n'
    << "  <li>State transition: " << state_transition << ": the recurrence equation of exponential decay</li>" << '\n'
    << "  <li>Measurement noise, real: " << real_measurement_noise << ": some very low value</li>" << '\n'
    << "  <li>Measurement noise, estimate: " << estimated_measurement_noise << ": some very low value</li>" << '\n'
    << "  <li>Process noise, real: " << real_process_noise << ": some very low value</li>" << '\n'
    << "  <li>Process noise, estimated covariance: " << estimated_process_noise_covariance << ": some very low value</li>" << '\n'
    << "  <li>Initial covariance estimate: " << initial_covariance_estimate << ": some very low value</li>" << '\n'
    << "</ul>"
    ;
  const std::string context = context_stream.str();

  std::unique_ptr<KalmanFilterExample> example(
    new KalmanFilterExample(
      title,
      context,
      inputs,
      kalman_filter_parameters,
      number_of_timesteps,
      state_names,
      white_noise_system_parameters
    )
  );
  assert(example);
  return example;
}

std::unique_ptr<ribi::kalman::KalmanFilterExample> ribi::kalman::KalmanFilterExample::CreateExample7()
{
  const std::string title = "Harmonic oscillation (two states)";
  //Two states
  const int n = 2;
  //As small as possible
  const double e = 0.00000000001;
  //Period of 100 timesteps

  const double pi = boost::math::constants::pi<double>();
  const double angular_frequency = 2.0 * pi / 100.0;

  //Correct for floating point rounding errors that will increase the amplitude.
  //This value is found by experimenting
  const double correction = 0.998026148;

  const int number_of_timesteps = 1000;

  //Name of the functions
  const std::vector<std::string> state_names = { "sin", "cos" };

  //Input does not change state
  const boost::numeric::ublas::matrix<double> control
    = Matrix::CreateMatrix(n,n, { 0.0, 0.0, 0.0, 0.0 } );

  //As small as possible
  const boost::numeric::ublas::matrix<double> initial_covariance_estimate
    = Matrix::CreateMatrix(n,n, { e,0.0,0.0,e } );

  //Correct
  const boost::numeric::ublas::vector<double> initial_state
    = Matrix::CreateVector( { 0.0, 1.0 } );

  //Initial state estimate is correct on purpose
  const boost::numeric::ublas::vector<double> initial_state_estimate = initial_state;

  //As small as possible
  const boost::numeric::ublas::matrix<double> estimated_measurement_noise
    = Matrix::CreateMatrix(n,n, { e,0.0,0.0,e } );

  //Observe directly
  const boost::numeric::ublas::matrix<double> observation
    = Matrix::CreateMatrix(n,n, { 1.0,0.0,0.0,1.0 } );

  //As small as possible
  const boost::numeric::ublas::matrix<double> estimated_process_noise_covariance
    = Matrix::CreateMatrix(n,n, { e,0.0,0.0,e } );

  //As small as possible
  const boost::numeric::ublas::vector<double> real_measurement_noise
    = Matrix::CreateVector( { e,e } );

  //As small as possible
  const boost::numeric::ublas::vector<double> real_process_noise
    = Matrix::CreateVector( { e,e } );

  //Reach a 10% value after 1000 timesteps with the recurrence equation
  const boost::numeric::ublas::matrix<double> state_transition
    = boost::numeric::ublas::trans(Matrix::CreateMatrix(n,n,
      {
                correction, angular_frequency,
        -angular_frequency,        correction
      } ));

  //Reach a 10% value after 1000 timesteps with the closed-form solution
  const std::string input1 = "sin(" + boost::lexical_cast<std::string>(angular_frequency) + "*(t+1))";
  const std::string input2 = "cos(" + boost::lexical_cast<std::string>(angular_frequency) + "*(t+1))";
  const std::vector<std::string> inputs = { input1, input2 };

  const boost::shared_ptr<const StandardKalmanFilterParameters> kalman_filter_parameters(
    new StandardKalmanFilterParameters(
    control,
    estimated_measurement_noise,
    estimated_process_noise_covariance,
    initial_covariance_estimate,
    initial_state_estimate,
    observation,
    state_transition)
  );

  const boost::shared_ptr<const StandardWhiteNoiseSystemParameters> white_noise_system_parameters(
    new StandardWhiteNoiseSystemParameters(
    control,
    initial_state,
    real_measurement_noise,
    real_process_noise,
    state_transition)
  );

  assert(control.size1() > 0);
  assert(control.size2() > 0);
  assert(state_names.size() == inputs.size());
  assert(state_names.size() == kalman_filter_parameters->GetInitialStateEstimate().size());
  assert(state_names.size() == white_noise_system_parameters->GetInitialState().size());
  assert(Matrix::MatricesAreEqual(kalman_filter_parameters->GetControl(),white_noise_system_parameters->GetControl()));
  assert(Matrix::MatricesAreEqual(kalman_filter_parameters->GetStateTransition(),white_noise_system_parameters->GetStateTransition()));

  std::stringstream context_stream;
  context_stream
    << "<h1>" << title << "</h1>" << '\n'
    << "<p>&nbsp;</p>" << '\n'
    << "<p>" << '\n'
    << "  This is more of a mathematical example. It shows that" << '\n'
    << "  a recurrence equation and its closed-form solution for a harmonic" << '\n'
    << "  oscillation are equivalent" << '\n'
    << "</p>" << '\n'
    << "<p>" << '\n'
    << "  The closed-form solution of a harmonic oscillation is:" << '\n'
    << "</p>" << '\n'
    << "<code>" << '\n'
    << "x(t) = sin(angular_frequency*t)<br/>" << '\n'
    << "v(t) = cos(angular_frequency*t)<br/>" << '\n'
    << "</code>" << '\n'
    << "<p>" << '\n'
    << "  The period is set to 100 timesteps," << '\n'
    << "  so the angular frequency equals 2*pi radian per period = 2 * pi / 100 = 0.0628." << '\n'
    << "</p>" << '\n'
    << "<p>" << '\n'
    << "  The recurrence equation of a harmonic oscillation is" << '\n'
    << "</p>" << '\n'
    << "<code>" << '\n'
    << "x(t+1) = c * x(t) + angular_frequency * v(t)<br/>" << '\n'
    << "v(t+1) = c * v(t) - angular_frequency * x(t)<br/>" << '\n'
    << "</code>" << '\n'
    << "<p>" << '\n'
    << "  Where c is a correction close to 1.0, to prevent the amplitude from increasing beyond 1" << '\n'
    << "  (probably due to rounding errors)" << '\n'
    << "</p>" << '\n'
    << "<p>" << '\n'
    << "  The closed-form solution is plotted as the input, the recurrence equation as the state." << '\n'
    << "  Because the control matrix contains a zero only, the input has no influence on the state." << '\n'
    << "  For the cleanest look, all noise was set to a low value." << '\n'
    << "</p>" << '\n'
    << "<p>&nbsp;</p>" << '\n'
    << "<ul>" << '\n'
    << "  <li>State names: " << DisplayAsUblasVector(state_names) << ": position (e.g. meters) and velocity (e.g. meters per second)</li>" << '\n'
    << "  <li>Initial state, real: " << initial_state << ": a sine starts at 0.0, a cosine starts at 1.0</li>" << '\n'
    << "  <li>Initial state, estimate: " << initial_state_estimate << ": set this value to the real value, there is no need to do estimation</li>" << '\n'
    << "  <li>Input: " << DisplayAsUblasVector(inputs) << ": the closed-form solution of a harmonic oscillation. t must be increased by one timestep, because a Kalman Filter estimates after an update</li>" << '\n'
    << "  <li>Control: " << control << ": input must have no effect in changing the state to do a valid comparison</li>" << '\n'
    << "  <li>Observation: " << observation << ": the value is observed directly</li>" << '\n'
    << "  <li>State transition: " << state_transition << ": the recurrence equation of a harmonic oscillation</li>" << '\n'
    << "  <li>Measurement noise, real: " << real_measurement_noise << ": some very low value</li>" << '\n'
    << "  <li>Measurement noise, estimate: " << estimated_measurement_noise << ": some very low value</li>" << '\n'
    << "  <li>Process noise, real: " << real_process_noise << ": some very low value</li>" << '\n'
    << "  <li>Process noise, estimated covariance: " << estimated_process_noise_covariance << ": some very low value</li>" << '\n'
    << "  <li>Initial covariance estimate: " << initial_covariance_estimate << ": some very low value</li>" << '\n'
    << "</ul>"
    ;
  const std::string context = context_stream.str();

  std::unique_ptr<KalmanFilterExample> example(
    new KalmanFilterExample(
      title,
      context,
      inputs,
      kalman_filter_parameters,
      number_of_timesteps,
      state_names,
      white_noise_system_parameters
    )
  );
  assert(example);
  return example;
}

std::unique_ptr<ribi::kalman::KalmanFilterExample> ribi::kalman::KalmanFilterExample::CreateExample8()
{
  const std::string title = "Harmonic oscillation (three states)";
  //Two states
  const int n = 3;
  //As small as possible
  const double e = 0.00000000001;
  //Period of 100 timesteps

  const double pi = boost::math::constants::pi<double>();
  const double angular_frequency = 2.0 * pi / 100.0;
  //Correct for floating point rounding errors that will increase the amplitude.
  //This value is found by experimenting
  const double correction = 0.998026148;

  const int number_of_timesteps = 1000;

  //Name of the functions
  const std::vector<std::string> state_names = { "x", "v", "a" };

  //Input does not change state
  const boost::numeric::ublas::matrix<double> control
    = Matrix::CreateMatrix(n,n,std::vector<double>(n*n,0.0));

  //As small as possible
  const boost::numeric::ublas::matrix<double> initial_covariance_estimate
    = Matrix::CreateMatrix(n,n, { e,0.0,0.0,0.0,e,0.0,0.0,0.0,e } );

  //Correct
  const boost::numeric::ublas::vector<double> initial_state
    = Matrix::CreateVector( { 0.0, angular_frequency, -angular_frequency*angular_frequency } );

  //Initial state estimate is correct on purpose
  const boost::numeric::ublas::vector<double> initial_state_estimate = initial_state;

  //As small as possible
  const boost::numeric::ublas::matrix<double> estimated_measurement_noise
    = Matrix::CreateMatrix(n,n, { e,0.0,0.0,0.0,e,0.0,0.0,0.0,e } );

  //Observe directly
  const boost::numeric::ublas::matrix<double> observation
    = Matrix::CreateMatrix(n,n, { 1.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,1.0 } );

  //As small as possible
  const boost::numeric::ublas::matrix<double> estimated_process_noise_covariance
    = Matrix::CreateMatrix(n,n, { e,0.0,0.0,0.0,e,0.0,0.0,0.0,e } );

  //As small as possible
  const boost::numeric::ublas::vector<double> real_measurement_noise
    = Matrix::CreateVector( { e,e,e } );

  //As small as possible
  const boost::numeric::ublas::vector<double> real_process_noise
    = Matrix::CreateVector( { e,e,e } );

  //Reach a 10% value after 1000 timesteps with the recurrence equation
  const boost::numeric::ublas::matrix<double> state_transition
    = boost::numeric::ublas::trans(Matrix::CreateMatrix(n,n,
      {
                                  correction, angular_frequency,angular_frequency*angular_frequency,
                          -angular_frequency,        correction,                  angular_frequency,
        -angular_frequency*angular_frequency,               0.0,                                0.0
      } ));

  //Reach a 10% value after 1000 timesteps with the closed-form solution
  const std::string input1
    = "sin(" + boost::lexical_cast<std::string>(angular_frequency) + "*(t+1))";
  const std::string input2
    = boost::lexical_cast<std::string>(angular_frequency)
    + "*cos(" + boost::lexical_cast<std::string>(angular_frequency)
    + "*(t+1))";
  const std::string input3
    = "-"
    + boost::lexical_cast<std::string>(angular_frequency)
    + "*"
    + boost::lexical_cast<std::string>(angular_frequency)
    + "*sin(" + boost::lexical_cast<std::string>(angular_frequency) + "*(t+1))";
  const std::vector<std::string> inputs = { input1, input2, input3 };

  const boost::shared_ptr<const StandardKalmanFilterParameters> kalman_filter_parameters(
    new StandardKalmanFilterParameters(
    control,
    estimated_measurement_noise,
    estimated_process_noise_covariance,
    initial_covariance_estimate,
    initial_state_estimate,
    observation,
    state_transition)
  );

  const boost::shared_ptr<const StandardWhiteNoiseSystemParameters> white_noise_system_parameters(
    new StandardWhiteNoiseSystemParameters(
    control,
    initial_state,
    real_measurement_noise,
    real_process_noise,
    state_transition)
  );

  assert(control.size1() > 0);
  assert(control.size2() > 0);
  assert(state_names.size() == inputs.size());
  assert(state_names.size() == kalman_filter_parameters->GetInitialStateEstimate().size());
  assert(state_names.size() == white_noise_system_parameters->GetInitialState().size());
  assert(Matrix::MatricesAreEqual(kalman_filter_parameters->GetControl(),white_noise_system_parameters->GetControl()));
  assert(Matrix::MatricesAreEqual(kalman_filter_parameters->GetStateTransition(),white_noise_system_parameters->GetStateTransition()));

  std::stringstream context_stream;
  context_stream
    << "<h1>" << title << "</h1>" << '\n'
    << "<p>&nbsp;</p>" << '\n'
    << "<p>" << '\n'
    << "  This is more of a mathematical example. It shows that" << '\n'
    << "  a recurrence equation and its closed-form solution for a harmonic" << '\n'
    << "  oscillation (three states) are equivalent" << '\n'
    << "</p>" << '\n'
    << "<p>" << '\n'
    << "  The closed-form solution of a harmonic oscillation is:" << '\n'
    << "</p>" << '\n'
    << "<code>" << '\n'
    << "x(t) = sin(angular_frequency*t)<br/>" << '\n'
    << "v(t) = cos(angular_frequency*t)<br/>" << '\n'
    << "</code>" << '\n'
    << "<p>" << '\n'
    << "  The period is set to 100 timesteps," << '\n'
    << "  so the angular frequency equals 2*pi radian per period = 2 * pi / 100 = 0.0628." << '\n'
    << "</p>" << '\n'
    << "<p>" << '\n'
    << "  The recurrence equation of a harmonic oscillation is" << '\n'
    << "</p>" << '\n'
    << "<code>" << '\n'
    << "x(t+1) = c * x(t) + angular_frequency * v(t)<br/>" << '\n'
    << "v(t+1) = c * v(t) - angular_frequency * x(t)<br/>" << '\n'
    << "</code>" << '\n'
    << "<p>" << '\n'
    << "  Where c is a correction close to 1.0, to prevent the amplitude from increasing beyond 1" << '\n'
    << "  (probably due to rounding errors)" << '\n'
    << "</p>" << '\n'
    << "<p>" << '\n'
    << "  The closed-form solution is plotted as the input, the recurrence equation as the state." << '\n'
    << "  Because the control matrix contains a zero only, the input has no influence on the state." << '\n'
    << "  For the cleanest look, all noise was set to a low value." << '\n'
    << "</p>" << '\n'
    << "<p>&nbsp;</p>" << '\n'
    << "<ul>" << '\n'
    << "  <li>State names: " << DisplayAsUblasVector(state_names) << ": position (e.g. meters) and velocity (e.g. meters per second)</li>" << '\n'
    << "  <li>Initial state, real: " << initial_state << ": a sine starts at 0.0, a cosine starts at 1.0</li>" << '\n'
    << "  <li>Initial state, estimate: " << initial_state_estimate << ": set this value to the real value, there is no need to do estimation</li>" << '\n'
    << "  <li>Input: " << DisplayAsUblasVector(inputs) << ": the closed-form solution of a harmonic oscillation. t must be increased by one timestep, because a Kalman Filter estimates after an update</li>" << '\n'
    << "  <li>Control: " << control << ": input must have no effect in changing the state to do a valid comparison</li>" << '\n'
    << "  <li>Observation: " << observation << ": the value is observed directly</li>" << '\n'
    << "  <li>State transition: " << state_transition << ": the recurrence equation of a harmonic oscillation</li>" << '\n'
    << "  <li>Measurement noise, real: " << real_measurement_noise << ": some very low value</li>" << '\n'
    << "  <li>Measurement noise, estimate: " << estimated_measurement_noise << ": some very low value</li>" << '\n'
    << "  <li>Process noise, real: " << real_process_noise << ": some very low value</li>" << '\n'
    << "  <li>Process noise, estimated covariance: " << estimated_process_noise_covariance << ": some very low value</li>" << '\n'
    << "  <li>Initial covariance estimate: " << initial_covariance_estimate << ": some very low value</li>" << '\n'
    << "</ul>"
    ;
  const std::string context = context_stream.str();

  std::unique_ptr<KalmanFilterExample> example(
    new KalmanFilterExample(
      title,
      context,
      inputs,
      kalman_filter_parameters,
      number_of_timesteps,
      state_names,
      white_noise_system_parameters
    )
  );
  assert(example);
  return example;
}

std::string ribi::kalman::KalmanFilterExample::DisplayAsUblasVector(const std::vector<std::string>& v)
{
  std::stringstream s;
  s << "[" << v.size() << "](";
  for(const std::string& str: v) { s << str << ","; }
  //Replace trailing comma with a closing bracket
  std::string str = s.str();
  str[str.size() - 1] = ')';
  return str;
}
