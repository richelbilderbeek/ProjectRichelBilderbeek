#ifndef KALMANFILTERTYPES_H
#define KALMANFILTERTYPES_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/bimap.hpp>
#pragma GCC diagnostic pop

#include "kalmanfiltertype.h"


namespace ribi {
namespace kalman {

///Class to work on one or more KalmanFilterType instances
struct KalmanFilterTypes
{
  static std::vector<KalmanFilterType> GetAllTypes() noexcept;
  static std::string ToStr(const KalmanFilterType type) noexcept;
  static KalmanFilterType ToType(const std::string& s);

  private:
  static boost::bimap<KalmanFilterType,std::string> m_map;
  static boost::bimap<KalmanFilterType,std::string> CreateMap() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace kalman
} //~namespace ribi

#endif // KALMANFILTERTYPES_H
