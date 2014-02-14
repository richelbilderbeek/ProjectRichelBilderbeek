#include <algorithm>
#include <cassert>
#include <set>

struct Coordinat
{
  explicit Coordinat(const double x = 0.0,const double y = 0.0)
    : m_x{x}, m_y{y}
  {

  }
  double GetX() const noexcept { return m_x; }
  double GetY() const noexcept { return m_y; }

  private:
  const double m_x;
  const double m_y;
};

bool operator<(const Coordinat& lhs, const Coordinat& rhs)
{
  if (lhs.GetX() < rhs.GetX()) return true;
  if (lhs.GetX() > rhs.GetX()) return false;
  return lhs.GetY() < rhs.GetY();
}

int main()
{
  std::set<Coordinat> s;
  s.insert(s.begin(),Coordinat( 2.0,-5.0));
  s.insert(s.begin(),Coordinat(-1.0,-1.0));
  s.insert(s.begin(),Coordinat( 0.0, 8.0));
  s.insert(s.begin(),Coordinat(-2.0,-4.0));
  s.insert(s.begin(),Coordinat( 1.0,-1.0));

  const auto xs {
    std::minmax_element(s.begin(),s.end(),
      [](const Coordinat& lhs, const Coordinat& rhs)
      {
        return lhs.GetX() < rhs.GetX();
      }
    )
  };
  const double minx = (std::get<0>(xs)).GetX();
  const double maxx = (*xs.second).GetX();
  assert(minx == -2.0);
  assert(maxx ==  2.0);

  const auto ys {
    std::minmax_element(s.begin(),s.end(),
      [](const Coordinat& lhs, const Coordinat& rhs)
      {
        return lhs.GetY() < rhs.GetY();
      }
    )
  };

  const double miny = (*ys.first).GetY();
  const double maxy = (*ys.second).GetY();
  assert(miny == -5.0);
  assert(maxy ==  8.0);
}
