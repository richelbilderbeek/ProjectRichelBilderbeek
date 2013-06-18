#ifndef ALPHAFILTER_H
#define ALPHAFILTER_H

#include <string>
#include <vector>

#include "floatingpointstateobserver.h"

///An alpha filter as described on [1]
///An alpha filter is equivalant to a low-pass filter (also called high-cut filter, or treble cut filter) [2]
/// [1] http://en.wikipedia.org/wiki/Alpha_beta_filter#The_alpha_filter
/// [2] http://en.wikipedia.org/wiki/Low-pass_filter
struct AlphaFilter : public FloatingPointStateObserver
{
  AlphaFilter(
    const double alpha = 0.1,
    const double dt    = 1.0
  );

  ///Get the current state estimate
  double GetEstimate() const { return m_output; }

  ///Supply a measurement, which will update the state estimate
  void Update(const double measurement);

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  private:
  ///The response to noise measurements
  ///  * m_alpha = 1.0: follow measurements
  ///  * m_alpha = 0.9: low inertia: noise in measurements in decreased only slightly
  ///  * m_alpha = 0.1: high inertia: noise in measurements in decreased considerably
  ///  * m_alpha = 0.0: ignore measurements
  ///
  ///For a low-pass filter:
  ///
  ///  m_alpha = m_dt / (RC + m_dt)
  ///
  ///Where
  ///  * m_dt: time step (sec)
  ///  * R: resistance (ohm)
  ///  * C: capacitance (Farad)
  const double m_alpha;

  ///The time constant
  const double m_dt;

  ///The current estimate of the state observed
  double m_output;
};

///An alpha filter can easily be converted to the following state transition matrix:
///
///[x_new] = [x_current] * [1.0 - alpha] + [ alpha ] [ input ] + [ noise ]
///  #1          #2             #3            #4         #5         #6
///
///#1: The new state vector
///#2: The current state vector
///#3: The state transition matrix
///#4: The control matrix
///#5: The input vector
///#6: The process noise vector
///
///The alpha filter is supplied as an example in the tool KalmanFilterer

#endif // ALPHAFILTER_H
