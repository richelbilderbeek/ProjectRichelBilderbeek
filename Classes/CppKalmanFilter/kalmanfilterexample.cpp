#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "kalmanfilterexample.h"

#include <cassert>
#include <memory>
#include <boost/lexical_cast.hpp>
#include <boost/numeric/ublas/io.hpp>
#include "matrix.h"
#include "trace.h"

KalmanFilterExample::KalmanFilterExample(
  const std::string& title,
  const std::string& context,
  const std::vector<std::string>& inputs,
  const boost::shared_ptr<const StandardKalmanFilterParameters>& kalman_filter_parameters,
  const std::vector<std::string>& state_names,
  const boost::shared_ptr<const StandardWhiteNoiseSystemParameters>& white_noise_system_parameters)
  : m_context(context),
    m_inputs(inputs),
    m_kalman_filter_parameters(kalman_filter_parameters),
    m_state_names(state_names),
    m_title(title),
    m_white_noise_system_parameters(white_noise_system_parameters)
{
  assert(!m_state_names.empty());
  assert(m_state_names.size() == m_inputs.size());
  assert(m_state_names.size() == m_kalman_filter_parameters->GetInitialStateEstimate().size());
  assert(m_state_names.size() == m_white_noise_system_parameters->GetInitialState().size());

}

const std::vector<boost::shared_ptr<KalmanFilterExample> > KalmanFilterExample::CreateExamples()
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

std::unique_ptr<KalmanFilterExample> KalmanFilterExample::CreateExample(const int i)
{
  std::unique_ptr<KalmanFilterExample> p;
  switch (i)
  {
    case  0: p = CreateExample1(); break;
    case  1: p = CreateExample1(); break;
    case  2: p = CreateExample2(); break;
    case  3: p = CreateExample3(); break;
    case  4: p = CreateExample4(); break;
    case  5: p = CreateExample5(); break;
    case  6: p = CreateExample6(); break;
    case  7: p = CreateExample7(); break;
    default: break;
  }
  //When p is nullptr, this indicates that there are no more examples

  return p;
}



std::unique_ptr<KalmanFilterExample> KalmanFilterExample::CreateExample1()
{
  const std::string title = "Constant voltage";

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
    << "  <li>State names: [1](" << state_names[0] << "): the voltage</li>" << '\n'
    << "  <li>Initial state estimate: " << initial_state_estimate << ": set this value off on purpose, to see the Kalman filter converge</li>" << '\n'
    << "  <li>Input: [1](" << inputs[0] << "): the state (that is, the voltage) will not be changed</li>" << '\n'
    << "  <li>Control: " << control << ": any input (albeit none) will have no effect</li>" << '\n'
    << "  <li>Estimated measurement noise: " << estimated_measurement_noise << ": just some value</li>" << '\n'
    << "</ul>";
  const std::string context = context_stream.str();

  std::unique_ptr<KalmanFilterExample> example(
    new KalmanFilterExample(
      title,
      context,
      inputs,
      kalman_filter_parameters,
      state_names,
      white_noise_system_parameters
    )
  );
  assert(example);
  
  return example;
}

std::unique_ptr<KalmanFilterExample> KalmanFilterExample::CreateExample2()
{
  const std::string title = "Accelerating car (two states)";
  const std::string context
    = "<h1>" + title + "</h1>";
  //Use example from Simon, D. Kalman Filtering. Embedded Systems Programming. June 2001
  const int n = 2;
  const double acceleration = 1.0;
  const double measurement_noise = 10.0; //Called 'measnoise'
  const double accelnoise = 0.2; //Called 'accelnoise'
  const double dt = 0.1; //Timestep

  //A gas pedal only influences speed
  const boost::numeric::ublas::matrix<double> control
    = Matrix::CreateMatrix(n,n, { 0.0,0.0,0.0,dt } );

  //Just a guess
  const boost::numeric::ublas::matrix<double> initial_covariance_estimate
    = Matrix::CreateMatrix(n,n, { 1.0,0.0,0.0,1.0 } );

  //Initial state estimates are a bit off on purpose
  const boost::numeric::ublas::vector<double> initial_state_estimate
    = Matrix::CreateVector( { 10.0,1.0 } );

  //From exact standstill
  const boost::numeric::ublas::vector<double> initial_state
    = Matrix::CreateVector( { 0.0,0.0 } );

  //Only (pessimistic) normal noise in GPS, speedometer has enormous noise as if defect (yet cannot be 0.0)
  const boost::numeric::ublas::matrix<double> estimated_measurement_noise
    = Matrix::CreateMatrix(n,n, { 10.0 * measurement_noise,0.0,0.0,1000000.0 } );

  const boost::numeric::ublas::matrix<double> observation
    = Matrix::CreateMatrix(n,n, { 1.0,0.0,0.0,0.0 } ); //Only use GPS, no speedometer

  const boost::numeric::ublas::matrix<double> estimated_process_noise_covariance
    = Matrix::CreateMatrix(n,n, {
      10.0 * accelnoise,
      10.0 * accelnoise,
      10.0 * accelnoise,
      10.0 * accelnoise
    } ); //Pessimistic estimate

  //Only normal noise in GPS, speedometer has enormous noise as if defect (yet cannot be 0.0)
  const boost::numeric::ublas::vector<double> real_measurement_noise
    = Matrix::CreateVector( { measurement_noise, 1000000.0 } );

  const boost::numeric::ublas::vector<double> real_process_noise
    = Matrix::CreateVector( { 0.5  * accelnoise * dt * dt, accelnoise * dt} );

  const boost::numeric::ublas::matrix<double> state_transition
    = Matrix::CreateMatrix(n,n, { 1.0, 0.0, dt, 1.0 } );

  //A gas pedal only influences speed
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

  std::unique_ptr<KalmanFilterExample> example(
    new KalmanFilterExample(
      title,
      context,
      inputs,
      kalman_filter_parameters,
      state_names,
      white_noise_system_parameters
    )
  );
  assert(example);
  return example;
}

std::unique_ptr<KalmanFilterExample> KalmanFilterExample::CreateExample3()
{
  const std::string title = "Cannonball";
  std::stringstream context_stream;
  context_stream
    << "<h1>" << title << "</h1>";
  const std::string context = context_stream.str();

  //Use examples and variables as http://greg.czerniak.info/guides/kalman1
  //Context: cannonball lauched from a cannon
  const int n = 4; //Size of all vectors and matrices
  const double dt = 0.1; //Timestep
  const double g = 9.81; //Gravity
  const double angle = M_PI / 4.0; //Radians. 45 degrees = M_PI / 4.0 radians

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

  std::unique_ptr<KalmanFilterExample> example(
    new KalmanFilterExample(
      title,
      context,
      inputs,
      kalman_filter_parameters,
      state_names,
      white_noise_system_parameters
    )
  );
  assert(example);
  return example;
}

std::unique_ptr<KalmanFilterExample> KalmanFilterExample::CreateExample4()
{
  const std::string title = "Spring";
  const std::string context
    = "<h1>" + title + "</h1>";

  //Use spring system: a mass is lying on a frictionless surface and is connected to two horizontal springs
  const int n = 2; //Size of vectors and matrices
  const double dt = 0.1; //Timestep
  const double k = 1.0; //Spring constant
  const double mass = 1.0; //Mass

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
      state_names,
      white_noise_system_parameters
    )
  );
  assert(example);
  return example;
}

std::unique_ptr<KalmanFilterExample> KalmanFilterExample::CreateExample5()
{
  const std::string title = "Airhockey puck";
  const std::string context
    = "<h1>" + title + "</h1>";

  //Context: airhockey puck with a constant speed
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
      state_names,
      white_noise_system_parameters
    )
  );
  assert(example);
  return example;
}



std::unique_ptr<KalmanFilterExample> KalmanFilterExample::CreateExample6()
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
      state_names,
      white_noise_system_parameters
    )
  );
  assert(example);
  return example;
}

std::unique_ptr<KalmanFilterExample> KalmanFilterExample::CreateExample7()
{
  const std::string title = "Exponential decay";
  const std::string context
    = "<h1>" + title + "</h1>"
      "<p>&nbsp;</p>"
      "<p>"
      "  This is more of a mathematical example. It shows that"
      "  a recurrence equation and its closed-form solution for exponential"
      "  decay are equivalent"
      "</p>"
      "<p>"
      "  The closed-form solution of exponential decay is:"
      "</p>"
      "<p>"
      "  f(t) = e^(-gamma*t)"
      "</p>"
      "<p>"
      "  Where t is the time step and gamma a constant, which is equal to -ln(0.1)/1000 = 0.0023025850929940454."
      "  This value of gamma lets the exponential decay reach 10% after 1000 timesteps."
      "</p>"
      "<p>"
      "  The recurrence equation of exponential decay is:"
      "</p>"
      "<p>"
      "  f(t+1) = tau * f(t)"
      "</p>"
      "<p>"
      "  Where t is the time step and tau a constant, which is equal to e^(ln(0.1)/1000) = 0.99770006382255327."
      "  This value of tau lets the exponential decay reach 10% after 1000 timesteps."
      "</p>"
      "<p>"
      "  The closed-form solution is plotted as the input, the recurrence equation as the state."
      "  Because the control matrix contains a zero only, the input has no influence on the state."
      "  For the cleanest look, all noise was set to a low value."
      "</p>"
      ;
  const int n = 1;
  const double e = 0.000000001;
  const double gamma = -std::log(0.1)/1000.0;
  const double tau = std::pow(M_E,std::log(0.1) / 1000.0);
  const boost::numeric::ublas::matrix<double> control
    = Matrix::CreateMatrix(n,n,
    {
      0.0
    } );

  //Just a guess
  const boost::numeric::ublas::matrix<double> initial_covariance_estimate
    = Matrix::CreateMatrix(n,n,
      {
        0.0,
      } );

  //Initial state estimate is correct on purpose
  const boost::numeric::ublas::vector<double> initial_state_estimate
    = Matrix::CreateVector( { 1.0 } );

  //From 100%
  const boost::numeric::ublas::vector<double> initial_state
    = Matrix::CreateVector( { 1.0 } );

  //Only (pessimistic) normal noise in GPS, speedometer and accelerometer
  const boost::numeric::ublas::matrix<double> estimated_measurement_noise
    = Matrix::CreateMatrix(n,n,
    {
      e
    } );

  //Observe all: GPS, speedometer, accelerometer
  const boost::numeric::ublas::matrix<double> observation
    = Matrix::CreateMatrix(n,n,
    {
      1.0
    } );

  const boost::numeric::ublas::matrix<double> estimated_process_noise_covariance
    = Matrix::CreateMatrix(n,n, {
      e
    } );

  const boost::numeric::ublas::vector<double> real_measurement_noise
    = Matrix::CreateVector( { e } );

  const boost::numeric::ublas::vector<double> real_process_noise
    = Matrix::CreateVector( { e } );

  //Reach a 10% value after 1000 timesteps
  const boost::numeric::ublas::matrix<double> state_transition
    = boost::numeric::ublas::trans(Matrix::CreateMatrix(n,n,
      { //Shown as on paper
        tau
      } ));

  const std::string input = std::string("exp(-") + boost::lexical_cast<std::string>(gamma) + "*t)";
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

  const std::vector<std::string> state_names = { "x" };

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
      state_names,
      white_noise_system_parameters
    )
  );
  assert(example);
  return example;
}
