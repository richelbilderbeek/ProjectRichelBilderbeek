#ifndef REVERSIMOVE_H
#define REVERSIMOVE_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

namespace ribi {
namespace reversi {

struct Move
{
  virtual ~Move() noexcept {}

  ///Create a Move from a std::string
  ///Returns a nullptr if the Move cannot be parsed
  ///
  ///Notation:
  ///- x,y -> MovePlacePiece
  ///- [empty] -> MovePass
  static boost::shared_ptr<Move> Parse(const std::string& s) noexcept;

  virtual std::string ToStr() const noexcept = 0;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

struct MovePlacePiece : public Move
{
  MovePlacePiece(const int x, const int y) : m_x(x), m_y(y) {}

  int GetX() const noexcept { return m_x; }
  int GetY() const noexcept { return m_y; }

  std::string ToStr() const noexcept;

  private:
  const int m_x;
  const int m_y;
};

struct MovePass : public Move
{
  MovePass() {}

  std::string ToStr() const noexcept { return "pass"; }
};


} //~namespace reversi
} //~namespace ribi

#endif // REVERSIMOVE_H
