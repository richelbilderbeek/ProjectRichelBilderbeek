#include "geometry.h"

#include "apcplx.h"

template <class T> T Atan2Impl(const T& a, const T& b) noexcept;
template <> double Atan2Impl(const double& a, const double& b) noexcept { return std::atan2(a,b); }
template <> apfloat Atan2Impl(const apfloat& a, const apfloat& b) noexcept { return ribi::Geometry().Atan2(a,b); }

template <class T>
T GetAngleClockCartesianImpl(const T& dx, const T& dy) noexcept
{
  const T pi = boost::math::constants::pi<double>();
  const T tau = boost::math::constants::two_pi<double>();
  const T angle = ribi::Geometry().Fmod(pi - Atan2Impl(dx,-dy),tau);
  assert(angle >= 0.0 && "GetAngle must return a value between zero and two pi");
  assert(angle < tau  && "GetAngle must return a value between zero and two pi");
  return angle;
}

double ribi::Geometry::GetAngleClockCartesian(const double dx, const double dy) const noexcept
{
  return GetAngleClockCartesianImpl(dx,dy);
}

ribi::Geometry::Apfloat ribi::Geometry::GetAngleClockCartesian(const Apfloat& dx, const Apfloat& dy) const noexcept
{
  return GetAngleClockCartesianImpl(dx,dy);
}

double ribi::Geometry::GetAngleClockCartesian(const Coordinat2D& p) const noexcept
{
  return GetAngleClockCartesianImpl(boost::geometry::get<0>(p),boost::geometry::get<1>(p));
}

ribi::Geometry::Apfloat ribi::Geometry::GetAngleClockCartesian(const ApCoordinat2D& p) const noexcept
{
  return GetAngleClockCartesianImpl(boost::geometry::get<0>(p),boost::geometry::get<1>(p));
}


template <class T>
T GetAngleClockScreenImpl(const T& dx, const T& dy) noexcept
{
  const T pi = boost::math::constants::pi<double>();
  const T tau = boost::math::constants::two_pi<double>();
  const T angle = ribi::Geometry().Fmod(pi - Atan2Impl(dx,dy),tau);
  assert(angle >= 0.0 && "GetAngle must return a value between zero and two pi");
  assert(angle < tau  && "GetAngle must return a value between zero and two pi");
  return angle;
}

double ribi::Geometry::GetAngleClockScreen(const double dx, const double dy) const noexcept
{
  //const double pi = boost::math::constants::pi<double>();
  //const double tau = boost::math::constants::two_pi<double>();
  //const double angle = Fmod(pi - (std::atan2(dx,dy)),tau);
  //assert(angle >= 0.0 && "GetAngle must return a value between zero and two pi");
  //assert(angle < tau  && "GetAngle must return a value between zero and two pi");
  //return angle;
  //return ToDoubleSafe(GetAngle(Apfloat(dx),Apfloat(dy)));
  return GetAngleClockScreenImpl(dx,dy);
}

ribi::Geometry::Apfloat ribi::Geometry::GetAngleClockScreen(const Apfloat& dx, const Apfloat& dy) const noexcept
{
  return GetAngleClockScreenImpl(dx,dy);
  //return GetAngle(ApCoordinat2D(dx,dy));
}

double ribi::Geometry::GetAngleClockScreen(const Coordinat2D& p) const noexcept
{
  return GetAngleClockScreenImpl(boost::geometry::get<0>(p),boost::geometry::get<1>(p));

  //return ToDoubleSafe(GetAngle(ToApfloat(p)));
}

ribi::Geometry::Apfloat ribi::Geometry::GetAngleClockScreen(const ApCoordinat2D& p) const noexcept
{
  return GetAngleClockScreenImpl(boost::geometry::get<0>(p),boost::geometry::get<1>(p));
  /*
  const Apfloat pi = boost::math::constants::pi<double>();
  const Apfloat tau = boost::math::constants::two_pi<double>();
  const Apfloat dx = boost::geometry::get<0>(p);
  const Apfloat dy = boost::geometry::get<1>(p);
  const Apfloat part = ::atan2(dx,dy);
  const Apfloat angle = Fmod(pi - ::atan2(dx,dy),tau);
  assert(angle >= 0.0 && "GetAngle must return a value between zero and two pi");
  assert(angle < tau  && "GetAngle must return a value between zero and two pi");
  return angle;
  */
}
