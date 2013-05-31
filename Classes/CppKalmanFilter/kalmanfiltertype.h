#ifndef KALMANFILTERTYPE_H
#define KALMANFILTERTYPE_H


enum class KalmanFilterType
{
  fixed_lag_smoother,
  standard,
  steady_state,
  n_types //Must be last value, used in debugging
};

bool operator==(const KalmanFilterType lhs, const KalmanFilterType rhs);
bool operator!=(const KalmanFilterType lhs, const KalmanFilterType rhs);
bool operator<(const KalmanFilterType lhs, const KalmanFilterType rhs);


#endif // KALMANFILTERTYPE_H
