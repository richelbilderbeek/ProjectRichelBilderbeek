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
#include "matrix.h"
#include "trace.h"

KalmanFilterExample::KalmanFilterExample(
  const std::string& description,
  const std::vector<std::string>& inputs,
  const boost::shared_ptr<const StandardKalmanFilterParameters>& kalman_filter_parameters,
  const std::vector<std::string>& state_names,
  const boost::shared_ptr<const StandardWhiteNoiseSystemParameters>& white_noise_system_parameters)
  : m_description(description),
    m_inputs(inputs),
    m_kalman_filter_parameters(kalman_filter_parameters),
    m_state_names(state_names),
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
  for (int i=1; ; ++i)
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
    case  0: break;
    case  1:
      p = CreateExample1();
      break;
    case  2:
      p = CreateExample2();
      break;
    case  3:
      p = CreateExample3();
      break;
    case  4:
      p = CreateExample4();
      break;
    case  5:
      p = CreateExample5(); break;
    case  6:
      p = CreateExample6(); break;
    case  7:
      p = CreateExample7(); break;
    case  8:
      p = CreateExample8(); break;
    case  9:
      p = CreateExample9();
      break;
    case 10:
      p = CreateExample10();
      assert(p);
      break;
    default: break;
  }
  //When p is nullptr, this indicates that there are no more examples

  return p;
}

std::unique_ptr<KalmanFilterExample> KalmanFilterExample::CreateExample1()
{
  
  //Use examples and variables as http://greg.czerniak.info/guides/kalman1
  //Context: measuring a voltage
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

  std::unique_ptr<KalmanFilterExample> example(
    new KalmanFilterExample(
      "Voltage",
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
      "Accelerating car (two states)",
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
      "Cannonball",
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
        2.0, 2.0,
        2.0, 2.0
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
    = Matrix::CreateMatrix(n,n,
      { //Beware: appears as transposition of real matrix
        1.0       ,   dt,
        -dt*k/mass, 0.99
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
      "Spring",
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
      "Airhockey puck",
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
  //System under inspection
  const int n = 6; //Size of all vectors and matrices
  //const double e = 0.001; //Small value

  const double xv = 2.3230447219468875E-6f;
  const double xa = 0.0002043072189142625f;
  const double xi = 0.11015678581090188f;
  //const double xi_prev = -0.0662404026536986f;
  const double yv = -2.3115486099678506E-6f;
  const double ya = -0.00030203734833222917f;
  const double yi = -0.05269666456255229f;


  const boost::numeric::ublas::matrix<double> control
    = boost::numeric::ublas::trans(Matrix::CreateMatrix(n,n,
      { //Seen as normal
         1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
         1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
         1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
         0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
         0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
         0.0, 0.0, 0.0, 0.0, 0.0, 0.0
      }
    ));

  //Just a guess
  const boost::numeric::ublas::matrix<double> initial_covariance_estimate
    = Matrix::CreateMatrix(n,n,
      {
         1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
         0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
         0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
         0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
         0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
         0.0, 0.0, 0.0, 0.0, 0.0, 1.0
      }
    );

  //Initial state estimates are a bit off on purpose
  const boost::numeric::ublas::vector<double> initial_state_estimate
    = Matrix::CreateVector( std::vector<double>(n,0.0) );

  //Shot from the cannon with velocity 100.0 at an angle
  const boost::numeric::ublas::vector<double> initial_state
    = Matrix::CreateVector( std::vector<double>(n,0.0) );

  //All inputs are identical
  const std::vector<std::string> inputs(n,"t>10");

  //Just an estimation
  const double f = 0.001;
  const boost::numeric::ublas::matrix<double> estimated_measurement_noise
    = Matrix::CreateMatrix(n,n,
      {
          f, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0,   f, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0,   f, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,   f, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0,   f, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,   f
      }
    );

  //Can observe all positions and speeds
  const boost::numeric::ublas::matrix<double> observation
    = Matrix::CreateMatrix(n,n,
      {
        1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 1.0
      }
    );

  //Due to this being a simulation, one can safely assume no process noise
  const boost::numeric::ublas::matrix<double> estimated_process_noise_covariance
    = Matrix::CreateMatrix(n,n,
      {
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0
      }
    );

  const boost::numeric::ublas::vector<double> real_measurement_noise
    = Matrix::CreateVector( std::vector<double>(n,f) );

  const boost::numeric::ublas::vector<double> real_process_noise
    = Matrix::CreateVector( std::vector<double>(n,f) );


  //Velocities influence positions
  const boost::numeric::ublas::matrix<double> state_transition
    = boost::numeric::ublas::trans(Matrix::CreateMatrix(n,n,
      { //Seen as normal
         0.0,  0.0, 0.0, 0.0     , 0.0  ,    0.0     ,
        -1.0,  0.0, 0.0, 0.0     , 0.0  ,    0.0     ,
        -1.0, -1.0, 0.0, 0.0     , 0.0  ,    0.0     ,
          xv,   xa,  xi, 1.0 + yv, 1.0 + ya, 1.0 + yi,
          xv,   xa,  xi,     - yv, 1.0 + ya, 1.0 + yi,
          xv,   xa,  xi,     - yv,     - ya, 1.0 + yi
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

  const std::vector<std::string> state_names = { "xv", "xa", "xi", "yv", "ya", "yi" };

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
      "6",
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
  //System under inspection
  const int n = 6; //Size of all vectors and matrices

  const double xv = 0.001;
  const double xa = 0.01;
  const double xi = 0.1;
  const double yv = -0.001;
  const double ya = -0.01;
  const double yi = -0.1;

  const boost::numeric::ublas::matrix<double> control
    = boost::numeric::ublas::trans(Matrix::CreateMatrix(n,n,
      { //Seen as normal
         1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
         1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
         1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
         0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
         0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
         0.0, 0.0, 0.0, 0.0, 0.0, 0.0
      }
    ));

  const boost::numeric::ublas::matrix<double> initial_covariance_estimate
    = Matrix::CreateMatrix(n,n,
      {
         1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
         0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
         0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
         0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
         0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
         0.0, 0.0, 0.0, 0.0, 0.0, 1.0
      }
    );

  const boost::numeric::ublas::vector<double> initial_state_estimate
    = Matrix::CreateVector( { 2.0, 3.0, 5.0, 7.0, 11.0, 13.0 } );

  const boost::numeric::ublas::vector<double> initial_state
    = Matrix::CreateVector( { 2.0, 3.0, 5.0, 7.0, 11.0, 13.0 } );

  //All inputs are identical
  const std::vector<std::string> inputs(n,"17.0 + (t>10)");

  //Just an estimation
  const double f = 0.001;
  const boost::numeric::ublas::matrix<double> estimated_measurement_noise
    = Matrix::CreateMatrix(n,n,
      {
          f, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0,   f, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0,   f, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,   f, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0,   f, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,   f
      }
    );

  const boost::numeric::ublas::matrix<double> observation
    = Matrix::CreateMatrix(n,n,
      {
        1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 1.0
      }
    );

  const boost::numeric::ublas::matrix<double> estimated_process_noise_covariance
    = Matrix::CreateMatrix(n,n,
      {
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0
      }
    );

  const boost::numeric::ublas::vector<double> real_measurement_noise
    = Matrix::CreateVector( std::vector<double>(n,f) );

  const boost::numeric::ublas::vector<double> real_process_noise
    = Matrix::CreateVector( std::vector<double>(n,f) );


  //Velocities influence positions
  const boost::numeric::ublas::matrix<double> state_transition
    = boost::numeric::ublas::trans(Matrix::CreateMatrix(n,n,
      { //Seen as normal
         0.0        ,  0.0        , 0.0        , 0.0     , 0.0  ,    0.0     ,
        -1.0        ,  0.0        , 0.0        , 0.0     , 0.0  ,    0.0     ,
        -1.0        , -1.0        , 0.0        , 0.0     , 0.0  ,    0.0     ,
          xv        ,   xa        ,  xi        , 1.0 + yv, 1.0 + ya, 1.0 + yi,
          xv        ,   xa        ,  xi        ,       yv, 1.0 + ya, 1.0 + yi,
          xv        ,   xa        ,  xi        ,       yv,       ya, 1.0 + yi
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

  const std::vector<std::string> state_names = { "xv", "xa", "xi", "yv", "ya", "yi" };

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
      "7",
      inputs,
      kalman_filter_parameters,
      state_names,
      white_noise_system_parameters
    )
  );
  assert(example);
  return example;
}

std::unique_ptr<KalmanFilterExample> KalmanFilterExample::CreateExample8()
{
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

  const boost::numeric::ublas::matrix<double> state_transition
    = boost::numeric::ublas::trans(Matrix::CreateMatrix(n,n,
      { //Shown as on paper
        1.0,  dt, 0.0,
        0.0, 1.0,  dt,
        0.0, 0.0, 1.0
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
      "Accelerating car (3 states)",
      inputs,
      kalman_filter_parameters,
      state_names,
      white_noise_system_parameters
    )
  );
  assert(example);
  return example;
}

std::unique_ptr<KalmanFilterExample> KalmanFilterExample::CreateExample9()
{
  const int n = 2;
  const double x = 2.0 / boost::numeric_cast<double>(2 << 4);
  assert(x > 0.0);

  const boost::numeric::ublas::matrix<double> control
    = Matrix::CreateMatrix(n,n, { x,0.0,0.0,0.0 } );

  //Just a guess
  const boost::numeric::ublas::matrix<double> initial_covariance_estimate
    = Matrix::CreateMatrix(n,n, { 1.0,0.0,0.0,1.0 } );

  //Initial state estimates are a bit off on purpose
  const boost::numeric::ublas::vector<double> initial_state_estimate
    = Matrix::CreateVector( std::vector<double>(n,0.0) );

  //From exact standstill
  const boost::numeric::ublas::vector<double> initial_state
    = Matrix::CreateVector( std::vector<double>(n,0.0) );

  const boost::numeric::ublas::matrix<double> estimated_measurement_noise
    = Matrix::CreateMatrix(n,n,std::vector<double>(n*n,0.00001));

  const boost::numeric::ublas::matrix<double> observation
    = Matrix::CreateMatrix(n,n, { 1.0, 0.0, 0.0, 1.0 } );

  const boost::numeric::ublas::matrix<double> estimated_process_noise_covariance
    = Matrix::CreateMatrix(n,n, std::vector<double>(n*n,0.00001));

  //Only normal noise in GPS, speedometer has enormous noise as if defect (yet cannot be 0.0)
  const boost::numeric::ublas::vector<double> real_measurement_noise
    = Matrix::CreateVector( std::vector<double>(n,0.00001) );

  const boost::numeric::ublas::vector<double> real_process_noise
    = Matrix::CreateVector( std::vector<double>(n,0.00001) );

  const boost::numeric::ublas::matrix<double> state_transition
    = boost::numeric::ublas::trans(
      Matrix::CreateMatrix(n,n, //View as on paper
      {
        1.0 - x, 0.0    ,
        0.0 + x, 1.0 - x
      }
    )
  );

  const std::vector<std::string> inputs = { "(t<1)*(2^23)", "0.0" };

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

  const std::vector<std::string> state_names = { "1", "2" };

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
      "Second order low-pass filter",
      inputs,
      kalman_filter_parameters,
      state_names,
      white_noise_system_parameters
    )
  );
  assert(example);
  return example;
}

std::unique_ptr<KalmanFilterExample> KalmanFilterExample::CreateExample10()
{
  //System under inspection with LSQ
  const int n = 8; //Size of all vectors and matrices

  const double pxv = 2.3230447219468875E-6;
  const double pxa = 0.0002043072189142625;
  const double pxi = 0.11015678581090188;
  const double pxi_prev = -0.0662404026536986;
  const double pyv = -2.3115486099678506E-6;
  const double pya = -0.00030203734833222917;
  const double pyi = -0.05269666456255229;

  const double d = 1.0 / std::pow(2.0,4.0);

  const boost::numeric::ublas::matrix<double> control
    = boost::numeric::ublas::trans(Matrix::CreateMatrix(n,n,
      { //Seen as normal
     //input,   -,   -,   -,   -,   -, in1, in2
         1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, //xv
         1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, //xa
         1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, //xi
 pxv+pxa+pxi, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, //yv
 pxv+pxa+pxi, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, //ya
 pxv+pxa+pxi, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, //yi
         0.0, 0.0, 0.0, 0.0, 0.0, 0.0,   d, 0.0, //alpha_hidden
         0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0  //alpha-active
      }
    )
  );

  const boost::numeric::ublas::matrix<double> initial_covariance_estimate
    = Matrix::CreateMatrix(n,n,
      {
         1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
         0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
         0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
         0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
         0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
         0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
         0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
         0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0
      }
    );

  const boost::numeric::ublas::vector<double> initial_state_estimate
    = Matrix::CreateVector( std::vector<double>(n,0.0) );

  const boost::numeric::ublas::vector<double> initial_state
    = Matrix::CreateVector( std::vector<double>(n,0.0) );

  const std::vector<std::string> inputs
    =
    {
      "0.0",
      "0.0",
      "0.0",
      "0.0",
      "0.0",
      "0.0",
      "(2^40)*(t<1)",
      "0.0"
    };

  //Just an estimation
  const double f = 0.001;
  const boost::numeric::ublas::matrix<double> estimated_measurement_noise
    = Matrix::CreateMatrix(n,n,
      {
          f, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0,   f, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0,   f, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,   f, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0,   f, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0,   f, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0,   f, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,   f
      }
    );

  const boost::numeric::ublas::matrix<double> observation
    = Matrix::CreateMatrix(n,n,
      {
        1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
      }
    );
  assert(observation(2,2) == 1.0);
  assert(observation(5,5) == 1.0);

  const boost::numeric::ublas::matrix<double> estimated_process_noise_covariance
    = Matrix::CreateMatrix(n,n,std::vector<double>(n*n,0.0));

  const boost::numeric::ublas::vector<double> real_measurement_noise
    = Matrix::CreateVector( std::vector<double>(n,f) );

  const boost::numeric::ublas::vector<double> real_process_noise
    = Matrix::CreateVector( std::vector<double>(n,f) );


  //Velocities influence positions
  const boost::numeric::ublas::matrix<double> state_transition
    = boost::numeric::ublas::trans(Matrix::CreateMatrix(n,n,
      { //Seen as normal
       // xv,  xa ,    xi   ,    yv    ,    ya    ,    yi    ,   in1  ,   in2
         0.0,  0.0,      0.0, 0.0      , 0.0      , 0.0      , 0.0    , 1.0/**/, //xv
        -1.0,  0.0,      0.0, 0.0      , 0.0      , 0.0      , 0.0    , 0.0    , //xa
        -1.0, -1.0,      0.0, 0.0      , 0.0      , 0.0      , 0.0    , 0.0    , //xi
    -pxa-pxi, -pxi, pxi_prev, 1.0 + pyv, 1.0 + pya, 1.0 + pyi, 0.0    , 0.0    , //yv
    -pxa-pxi, -pxi, pxi_prev,       pyv, 1.0 + pya, 1.0 + pyi, 0.0    , 0.0    , //ya
    -pxa-pxi, -pxi, pxi_prev,       pyv,       pya, 1.0 + pyi, 0.0    , 0.0    , //yi
         0.0,  0.0,      0.0, 0.0      , 0.0      , 0.0      , 1.0 - d, 0.0    , //alpha_hidden
         0.0,  0.0,      0.0, 0.0      , 0.0      , 0.0      ,       d, 1.0 - d  //alpha_active
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

  const std::vector<std::string> state_names = { "xv", "xa", "xi", "yv", "ya", "yi", "in1", "in2" };

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
      "10",
      inputs,
      kalman_filter_parameters,
      state_names,
      white_noise_system_parameters
    )
  );
  assert(example);
  assert(example->GetKalmanFilterParameters()->GetObservation().size1() == 8);
  assert(example->GetKalmanFilterParameters()->GetObservation().size2() == 8);
  assert(example->GetKalmanFilterParameters()->GetObservation()(5,5) == 1.0);
  return example;
}
