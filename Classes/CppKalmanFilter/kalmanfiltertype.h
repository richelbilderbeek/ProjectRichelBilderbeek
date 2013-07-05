#ifndef KALMANFILTERTYPE_H
#define KALMANFILTERTYPE_H


enum class KalmanFilterType
{
  //ensemble,
  //extended,
  fixed_lag_smoother,
  //hybrid
  //kalman_bucy
  //minimum_variance_smoother
  //modified_Bryson_Frazier_smoother
  //rauch_tung_striebel_smoother
  standard, //Also called: 'steady state'
  steady_state,
  //unscented,
  n_types //Must be last value, used in debugging
};


bool operator==(const KalmanFilterType lhs, const KalmanFilterType rhs);
bool operator!=(const KalmanFilterType lhs, const KalmanFilterType rhs);
bool operator<(const KalmanFilterType lhs, const KalmanFilterType rhs);


#endif // KALMANFILTERTYPE_H
