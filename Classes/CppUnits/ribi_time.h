#ifndef RIBI_TIME_H
#define RIBI_TIME_H

//Time
// The relative (unitless) change of something in time

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/units/io.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/prefixes.hpp>
#pragma GCC diagnostic pop

namespace boost {
  namespace units {
    namespace si {
      using Time = boost::units::quantity<boost::units::si::time>;
      std::istream& operator>>(std::istream& is,Time& sd);

    } // namespace si
  } // namespace units
} //namespace boost

namespace ribi {
  namespace units {

    using Time = boost::units::quantity<boost::units::si::time>;

    #ifndef NDEBUG
    void TestTime() noexcept;
    #endif
  } //~namespace units
} //~namespace ribi

#endif // RIBI_TIME_H
