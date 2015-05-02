#include <algorithm>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <vector>

#include <boost/units/systems/si/prefixes.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/io.hpp>
#include <boost/units/physical_dimensions/area.hpp>

struct Distance
{
  typedef boost::units::quantity<boost::units::si::length> Distance_type;
  Distance(const Distance_type& distance) : m_distance(distance)
  {
    assert(m_distance >= Distance_type(0));
  }

  const Distance_type& GetDistance() const { return m_distance; }

  private:
  Distance_type m_distance;
};

const Distance operator+(const Distance& lhs, const Distance& rhs)
{
  return Distance( lhs.GetDistance() + rhs.GetDistance() );
}

const Distance operator/(const Distance& numerator, const double denominator)
{
  return Distance(numerator.GetDistance() / denominator);
}

std::ostream& operator<<(std::ostream& os, const Distance& l)
{
  os << l.GetDistance(); return os;
}

const Distance GetAverageDistance(const std::vector<Distance>& v)
{
  return std::accumulate(v.begin(),v.end(),Distance(Distance::Distance_type(0.0 * boost::units::si::meter)))
    / static_cast<double>(v.size());
}

int main()
{
  using namespace boost::units;
  using namespace boost::units::si;
  const std::vector<Distance> v
    =
    {
      Distance(Distance::Distance_type(2.34 * micro * meter)),
      Distance(Distance::Distance_type(3.00 * milli * meter)),
      Distance(Distance::Distance_type(5.00         * meter)),
      Distance(Distance::Distance_type(7.00 * kilo  * meter))
    };
  const Distance distance = GetAverageDistance(v);

  std::cout << std::setprecision(20) << "Distances:\n";
  std::copy(v.begin(),v.end(),std::ostream_iterator<Distance>(std::cout,"\n"));
  std::cout << "Average distance: " << distance << '\n';
}
