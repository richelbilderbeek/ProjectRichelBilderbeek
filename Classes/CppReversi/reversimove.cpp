#include "reversimove.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>
#pragma GCC diagnostic pop

std::string ribi::reversi::MovePlacePiece::ToStr() const noexcept
{
  std::stringstream s;
  s << this->GetX() << ',' << this->GetY();
  return s.str();
}

boost::shared_ptr<ribi::reversi::Move> ribi::reversi::Move::Parse(
  const std::string& s) noexcept
{
  boost::shared_ptr<ribi::reversi::Move> move;

  if (s.empty()) return move;
  if (s == "p" || s == "P" || s == "pass" || s == "Pass" || s == "PASS")
  {
    move.reset(new MovePass);
    return move;
  }
  const std::size_t i = s.find(',');
  if (
       i != std::string::npos
    && i != 0
    && i != s.size() - 1
    && std::count(s.begin(),s.end(),',') == 1
  )
  {
    const std::string a = s.substr(0,i);
    const std::string b = s.substr(i + 1,s.size() - i - 1);
    assert(std::count(a.begin(),a.end(),',') == 0);
    assert(std::count(b.begin(),b.end(),',') == 0);
    const int x = boost::lexical_cast<int>(a);
    const int y = boost::lexical_cast<int>(b);
    move.reset(new MovePlacePiece(x,y));
    return move;
  }

  assert(move || !move);
  return move;
}

