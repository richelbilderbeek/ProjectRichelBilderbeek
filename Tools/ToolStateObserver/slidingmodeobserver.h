#ifndef SLIDINGMODEOBSERVER_H
#define SLIDINGMODEOBSERVER_H

#ifdef TRY_GETTING_SLIDINGMODEOBSERVER_RIGHT_ONCE_8234752798253978650738

#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>

struct SteadyStateKalmanFilter;

///Keeps two states only
struct SlidingModeObserver
{
  SlidingModeObserver(const double d);

  double Estimate(const double measurement);

  private:

  const boost::shared_ptr<SteadyStateKalmanFilter> m_filter;

  static const boost::shared_ptr<SteadyStateKalmanFilter> CreateFilter(const int size, const double d);

  ///Create the control matrix
  static const boost::numeric::ublas::matrix<double> CreateControl(const int size);

  ///Create the initial covariance matrix
  static const boost::numeric::ublas::matrix<double> CreateInitialCovariance(const int size);

  ///Create the observation matrix
  static const boost::numeric::ublas::matrix<double> CreateObservation(const int size);

  ///Create the state transition matrix
  static const boost::numeric::ublas::matrix<double> CreateStateTransition(const int size, const double d);
};

#endif

#endif // SLIDINGMODEOBSERVER_H
