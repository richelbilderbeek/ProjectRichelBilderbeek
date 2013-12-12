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
  static const std::vector<KalmanFilterType> GetAllTypes();
  static const std::string ToStr(const KalmanFilterType type);
  static KalmanFilterType ToType(const std::string& s);

  private:
  static boost::bimap<KalmanFilterType,std::string> m_map;
  static const boost::bimap<KalmanFilterType,std::string> CreateMap();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace kalman
} //~namespace ribi

#endif // KALMANFILTERTYPES_H
