#include <cassert>
#include <iostream>

#include <boost/units/systems/si/prefixes.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/io.hpp>
#include <boost/units/physical_dimensions/area.hpp>

struct Length
{
  Length(const boost::units::quantity<boost::units::si::length>& length) : m_length(length)
  {
    const boost::units::quantity<boost::units::si::length> zero(0);
    assert(m_length >= zero);
  }
  const boost::units::quantity<boost::units::si::length> m_length;
};

struct Width
{
  Width(const boost::units::quantity<boost::units::si::length>& width) : m_width(width)
  {
    const boost::units::quantity<boost::units::si::length> zero(0);
    assert(m_width >= zero);
  }
  const boost::units::quantity<boost::units::si::length> m_width;
};

struct Area
{
  Area(const Length& length, const Width& width)
    : m_area(length.m_length * width.m_width)
  {
    assert(length.m_length >= width.m_width);
  }
  const boost::units::quantity<boost::units::si::area> m_area;
};

int main()
{
  using namespace boost::units;
  using namespace boost::units::si;
  const Length my_length( quantity<length>(1.23456789*micro*meter) );
  const Width my_width( quantity<length>(2.3456789*nano*meter) );
  const Area my_area(my_length,my_width);
  std::cout
    << "Length: " << my_length.m_length << '\n'
    << "Width: "  << my_width.m_width << '\n'
    << "Area: "   << my_area.m_area << '\n'
  ;
}
