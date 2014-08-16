#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "fixedlagsmootherkalmanfilter.h"

#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>

#include "matrix.h"
#include "testtimer.h"
#include "trace.h"
#include "standardkalmanfilterfactory.h"
#pragma GCC diagnostic pop

ribi::kalman::FixedLagSmootherKalmanFilter::FixedLagSmootherKalmanFilter(
  const boost::shared_ptr<FixedLagSmootherKalmanFilterCalculationElements>& calculation,
  const boost::shared_ptr<const KalmanFilterParameters>& parameters)
  : KalmanFilter{},
    m_last_calculation{calculation},
    m_last_fixed_lag_smoother_calculation{boost::dynamic_pointer_cast<FixedLagSmootherKalmanFilterCalculationElements>(calculation)},
    m_standard_filter{StandardKalmanFilterFactory().Create(DownCast(parameters)->GetStandardParameters())},
    m_parameters{DownCast(parameters)},
    m_state_estimates{CreateInitialStates(DownCast(parameters))}
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(m_last_fixed_lag_smoother_calculation);
  assert(m_parameters);
  assert(boost::numeric_cast<int>(m_state_estimates.size()) == m_parameters->GetLag() * m_standard_filter->GetStateSize());
}


boost::numeric::ublas::vector<boost::numeric::ublas::matrix<double> > ribi::kalman::FixedLagSmootherKalmanFilter::CreateInitialGains(
  const int lag,
  const StandardKalmanFilter& filter)
{

  assert(filter.GetStateSize() == boost::numeric_cast<int>(filter.GetLastStandardCalculation()->GetKalmanGain().size1()));
  assert(filter.GetLastStandardCalculation()->GetKalmanGain().size1() == filter.GetLastStandardCalculation()->GetKalmanGain().size2());
  boost::numeric::ublas::vector<boost::numeric::ublas::matrix<double> > v(lag,filter.GetLastStandardCalculation()->GetKalmanGain());
  return v;
}

boost::numeric::ublas::vector<boost::numeric::ublas::vector<double> > ribi::kalman::FixedLagSmootherKalmanFilter::CreateComplexInitialStates(
  const boost::shared_ptr<const FixedLagSmootherKalmanFilterParameters>& parameters)
{
  assert(parameters);
  boost::numeric::ublas::vector<boost::numeric::ublas::vector<double> > v(
    parameters->GetLag(),
    parameters->GetStandardParameters()->GetInitialStateEstimate());
  return v;
}

boost::numeric::ublas::vector<boost::numeric::ublas::matrix<double> >
  ribi::kalman::FixedLagSmootherKalmanFilter::CreateComplexTermA(
  const int lag,
  const int state_size)
{
  //
  assert(lag > 0 && "Term A is not needed for a lag of zero");
  boost::numeric::ublas::vector<boost::numeric::ublas::matrix<double> > v(lag);

  v[0] = boost::numeric::ublas::identity_matrix<double>(state_size);
  for (int i=1; i!=lag; ++i)
  {
    assert(i < boost::numeric_cast<int>(v.size()));
    v[i] = boost::numeric::ublas::zero_matrix<double>(state_size);
  }
  return v;
}

boost::numeric::ublas::matrix<double>
  ribi::kalman::FixedLagSmootherKalmanFilter::CreateTermA(
  const int lag,
  const int state_size)
{
  //
  assert(lag > 0 && "Term A is not needed for a lag of zero");
  const boost::numeric::ublas::matrix<double> v
    = Matrix::SimplifyVectorOfMatrix(CreateComplexTermA(lag,state_size));
  assert(lag * state_size == boost::numeric_cast<int>(v.size1()));
  assert(  1 * state_size == boost::numeric_cast<int>(v.size2()));
  return v;
}

boost::numeric::ublas::matrix<double >
  ribi::kalman::FixedLagSmootherKalmanFilter::CreateTermB(
    const int lag,
    const int state_size)
{
  //
  boost::numeric::ublas::matrix<double> v
    = Matrix::SimplifyMatrixOfMatrix(CreateComplexTermB(lag,state_size));
  //
  assert(lag > 0 && "Term B is not needed for a lag of zero");
  assert(lag > 1 && "Term B cannot be calculated for a lag of one");
  assert((lag - 0) * state_size == boost::numeric_cast<int>(v.size1()));
  assert((lag - 1) * state_size == boost::numeric_cast<int>(v.size2()));
  return v;
}


boost::numeric::ublas::matrix<boost::numeric::ublas::matrix<double> >
  ribi::kalman::FixedLagSmootherKalmanFilter::CreateComplexTermB(
    const int lag,
    const int state_size)
{
  //
  assert(lag > 0 && "Term B is not needed for a lag of zero");
  const int n_cols = lag - 1;
  const int n_rows = lag;
  boost::numeric::ublas::matrix<boost::numeric::ublas::matrix<double> > v(n_rows,n_cols);
  for (int y=0; y!=n_rows; ++y)
  {
    for (int x=0; x!=n_cols; ++x)
    {
      if (y - 1 == x)
      {
        assert(y < boost::numeric_cast<int>(v.size1()));
        assert(x < boost::numeric_cast<int>(v.size2()));
        v(y,x) = boost::numeric::ublas::identity_matrix<double>(state_size);
      }
      else
      {
        assert(y < boost::numeric_cast<int>(v.size1()));
        assert(x < boost::numeric_cast<int>(v.size2()));
        v(y,x) = boost::numeric::ublas::zero_matrix<double>(state_size);
      }
    }
  }
  return v;
}

boost::numeric::ublas::vector<double> ribi::kalman::FixedLagSmootherKalmanFilter::CreateInitialStates(
  const boost::shared_ptr<const FixedLagSmootherKalmanFilterParameters>& parameters)
{
  assert(parameters);
  //
  //if (lag == 0) return boost::numeric::ublas::vector<double>();
  boost::numeric::ublas::vector<double> v = Matrix::SimplifyVectorOfVector(
    CreateComplexInitialStates(parameters));
  return v;
}

boost::shared_ptr<const ribi::kalman::FixedLagSmootherKalmanFilterParameters> ribi::kalman::FixedLagSmootherKalmanFilter::DownCast(
  const boost::shared_ptr<const KalmanFilterParameters>& parameters)
{
  #ifndef NDEBUG
  const auto i = parameters.use_count();
  #endif

  const boost::shared_ptr<const FixedLagSmootherKalmanFilterParameters> p
    = boost::dynamic_pointer_cast<const FixedLagSmootherKalmanFilterParameters>(parameters);
  assert(p);

  #ifndef NDEBUG
  const auto j = parameters.use_count();
  assert(i + 1 == j);
  #endif
  return p;
}


std::string ribi::kalman::FixedLagSmootherKalmanFilter::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::kalman::FixedLagSmootherKalmanFilter::GetVersionHistory() noexcept
{
  return {
    "2013-05-03: version 1.0: initial version"
  };
}

boost::numeric::ublas::vector<double> ribi::kalman::FixedLagSmootherKalmanFilter::PredictState(
  const boost::numeric::ublas::vector<double>& input) const
{
  //
  using boost::numeric::ublas::range;
  using boost::numeric::ublas::vector;
  using boost::numeric::ublas::vector_range;

  if (m_parameters->GetLag() == 0) return m_standard_filter->PredictState(input);
  assert(!m_state_estimates.empty());
  const std::size_t state_size = m_standard_filter->GetStateSize();
  assert(state_size <= m_state_estimates.size());
  const vector_range<const vector<double> > state(m_state_estimates,range(0,state_size));
  return vector<double>(state);
}


void ribi::kalman::FixedLagSmootherKalmanFilter::SupplyMeasurementAndInput(
  const boost::numeric::ublas::vector<double>& x,
  const boost::numeric::ublas::vector<double>& input)
{
  
  using boost::numeric::ublas::vector;
  using boost::numeric::ublas::vector_range;
  using boost::numeric::ublas::range;
  using boost::numeric::ublas::matrix;
  using boost::numeric::ublas::trans;

  //Store calculation for KalmanFilterExperiment
  m_last_fixed_lag_smoother_calculation->Clear();
  m_last_fixed_lag_smoother_calculation->SetPreviousStateEstimate(this->GetStandardKalmanFilter()->GetStateEstimate()); //1
  //m_last_fixed_lag_smoother_calculation->SetPreviousCovarianceEstimate(this->GetEstimationErrorCovariance()); //2

  const int state_size = m_standard_filter->GetStateSize();
  assert(state_size == boost::numeric_cast<int>(x.size()));
  assert(state_size == boost::numeric_cast<int>(input.size()));
  m_standard_filter->SupplyMeasurementAndInput(x,input);
  if (m_parameters->GetLag() == 0) return;
  const matrix<double> term_a = CreateTermA(m_parameters->GetLag(),state_size);
  const int lag = m_parameters->GetLag();
  assert(lag * state_size == boost::numeric_cast<int>(term_a.size1()));
  assert(  1 * state_size == boost::numeric_cast<int>(term_a.size2()));

  //Get the naive (that is, based on no time lag) prediction
  const vector<double> x_naive = m_standard_filter->PredictState(input);
  const matrix<double> term_b = CreateTermB(lag,state_size);

  //Find P(i) (yes, i can be zero and goes to lag)
  //ps has length lag
  //P(i) has size state_size x state_size
  //P(i) = P . [ [F-KH]^T ]^i (where ^T denotes a transposition, where ^i denotes an exponent to the power of i
  TRACE(m_standard_filter->GetLastStandardCalculation()->GetPreviousCovarianceEstimate());
  TRACE(m_standard_filter->GetLastStandardCalculation()->GetKalmanGain());
  vector<matrix<double> > ps_complex(lag);
  for (int i=0; i!=lag; ++i)
  {
    //
    assert(i < boost::numeric_cast<int>(ps_complex.size()));
    ps_complex[i]
      = Matrix::Prod(
          m_standard_filter->GetEstimationErrorCovariance(),
          Matrix::Power(
            trans(
              m_standard_filter->GetParameters()->GetStateTransition()
                - Matrix::Prod(
                  m_standard_filter->GetLastStandardCalculation()->GetKalmanGain(),
                  m_standard_filter->GetParameters()->GetObservation()
                )
              )
            ,
            i)
        );
  }

  //Find K(i) (yes, i can be zero and goes to lag)
  //ks has length lag
  //K(i) has size state_size x state_size
  //K(i) = P(i) . H^T . [H.P.H^T + R]^-1
  //
  vector<matrix<double> > ks_complex(lag);
  for (int i=0; i!=lag; ++i)
  {
    const boost::numeric::ublas::matrix<double> term
      = Matrix::MultiProd(
          m_standard_filter->GetParameters()->GetObservation(),
          m_standard_filter->GetEstimationErrorCovariance(),
          trans(m_standard_filter->GetParameters()->GetObservation())
        )
        + m_standard_filter->GetStandardParameters()->GetEstimatedMeasurementNoise();
    if (Matrix::CalcDeterminant(term) == 0.0)
    {
      throw std::runtime_error("Determinant of term in K(i) equals zero");
    }
    assert(i < boost::numeric_cast<int>(ks_complex.size()));
    assert(i < boost::numeric_cast<int>(ps_complex.size()));
    //
    ks_complex[i]
      = Matrix::MultiProd(
          ps_complex[i],
          trans(m_standard_filter->GetParameters()->GetObservation()),
          Matrix::Inverse(term)
        );
  }
  //
  matrix<double> ks = Matrix::SimplifyVectorOfMatrix(ks_complex);
  //
  const vector<double> innovation = m_standard_filter->GetLastStandardCalculation()->GetInnovation();
  //

  const vector<double> new_states_term_a
    = Matrix::Prod(term_a,x_naive);
  const vector<double> new_states_term_b
    = Matrix::Prod(term_b,vector_range<const vector<double> >(m_state_estimates,range(0,m_state_estimates.size()- m_standard_filter->GetStateSize())));
  //const vector<double> new_states_term_b
  //  = Matrix::Prod(term_b,vector_range<const vector<double> >(m_states,range(m_standard_filter->GetStateSize(),m_states.size())))
  const vector<double> new_states_term_c
    = Matrix::Prod(ks,innovation);

  m_state_estimates
    = new_states_term_a
    + new_states_term_b
    + new_states_term_c;

  TRACE("Store the calculation hiero");
  m_last_fixed_lag_smoother_calculation->SetStandardCalculationElement(this->m_standard_filter->GetLastStandardCalculation());
}

#ifndef NDEBUG
void ribi::kalman::FixedLagSmootherKalmanFilter::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  try
  {
    boost::numeric_cast<std::size_t>(-1);
    assert(!"Line above must fail, so shouldn't get here");
  }
  catch (boost::numeric::bad_numeric_cast& e)
  {
    //OK!
  }

  //CreateTermA
  {
    const int lag = 13;
    const int state_size = 17;
    const boost::numeric::ublas::matrix<double> v = CreateTermA(lag,state_size);
    const int n_rows = lag * state_size;
    const int n_cols =   1 * state_size;
    assert(boost::numeric_cast<int>(v.size1()) == n_rows);
    assert(boost::numeric_cast<int>(v.size2()) == n_cols);
    for (int row = 0; row!=n_rows; ++row)
    {
      assert(row < boost::numeric_cast<int>(v.size1()));
      for (int col = 0; col!=n_cols; ++col)
      {
        assert(col < boost::numeric_cast<int>(v.size2()));
        const double expected = row == col ? 1.0 : 0.0;
        assert(Matrix::IsAboutEqual(v(row,col),expected));
      }
    }
  }
  //CreateTermB
  {
    const int lag = 3;
    const int state_size = 5;
    const boost::numeric::ublas::matrix<double> v = CreateTermB(lag,state_size);
    const int n_rows = lag * state_size;
    const int n_cols = (lag - 1) * state_size;
    assert(boost::numeric_cast<int>(v.size1()) == n_rows);
    assert(boost::numeric_cast<int>(v.size2()) == n_cols);
    for (int row = 0; row!=n_rows; ++row)
    {
      assert(row < boost::numeric_cast<int>(v.size1()));
      for (int col = 0; col!=n_cols; ++col)
      {
        assert(col < boost::numeric_cast<int>(v.size2()));
        const double expected = row - state_size == col ? 1.0 : 0.0;
        assert(Matrix::IsAboutEqual(v(row,col),expected));
      }
    }
  }
}
#endif
