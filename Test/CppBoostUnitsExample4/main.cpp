#include <cassert>
#include <iostream>
#include <iomanip>

#include <boost/units/systems/si/prefixes.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/io.hpp>
#include <boost/units/physical_dimensions/area.hpp>

struct Length
{
  typedef boost::units::quantity<boost::units::si::length> Length_type;
  Length(const Length_type& length) : m_length(length)
  {
    assert(m_length >= Length_type(0));
  }

  const Length_type& GetLength() const { return m_length; }

  private:
  const Length_type m_length;
};

std::ostream& operator<<(std::ostream& os, const Length& l)
{
  os << l.GetLength(); return os;
}

struct Width
{
  typedef boost::units::quantity<boost::units::si::length> Length_type;
  Width(const Length_type& width) : m_width(width)
  {
    assert(m_width >= Length_type(0));
  }
  const Length_type& GetWidth() const { return m_width; }
  private:
  const Length_type m_width;
};

std::ostream& operator<<(std::ostream& os, const Width& w)
{
  os << w.GetWidth(); return os;
}

struct Area
{
  typedef boost::units::quantity<boost::units::si::area> Area_type;
  Area(const Length& length, const Width& width)
    : m_area(length.GetLength() * width.GetWidth())
  {
    assert(length.GetLength() >= width.GetWidth() );
  }
  const Area_type& GetArea() const { return m_area; }
  private:
  const Area_type m_area;
};

std::ostream& operator<<(std::ostream& os, const Area& a)
{
  os << a.GetArea(); return os;
}

int main()
{
  using namespace boost::units;
  using namespace boost::units::si;
  const Length my_length(quantity<length>(1.23456789*micro*meter) );
  const Width my_width(quantity<length>(2.3456789*nano*meter) );
  const Area my_area(my_length,my_width);
  std::cout
    << std::setprecision(20)
    << "Length: " << my_length << '\n'
    << "Width: "  << my_width << '\n'
    << "Area: "   << my_area << '\n'
  ;
}
