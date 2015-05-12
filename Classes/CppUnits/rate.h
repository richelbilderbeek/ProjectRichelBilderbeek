#ifndef RATE_H
#define RATE_H

//Rate
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
    typedef derived_dimension<
      time_base_dimension,-1
    >::type rate_dimension;
  } // namespace units
} // namespace boost

namespace boost {
  namespace units {
    namespace si {
      typedef unit<rate_dimension,si::system> rate;
      BOOST_UNITS_STATIC_CONSTANT(per_second,rate);

      using Rate = boost::units::quantity<boost::units::si::rate>;
      std::istream& operator>>(std::istream& is,Rate& sd);

    } // namespace si
  } // namespace units
} //namespace boost

#ifndef NDEBUG
namespace ribi {
  namespace units {

    using Rate = boost::units::quantity<boost::units::si::rate>;

    ///All I can do on them, is test them
    void TestRate() noexcept;
  } //~namespace units
} //~namespace ribi
#endif

#endif // RATE_H
