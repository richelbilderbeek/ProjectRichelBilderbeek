#ifndef CPPREVERSIMOVE_H
#define CPPREVERSIMOVE_H


namespace ribi {
namespace reversi {

struct Move
{
  virtual ~Move() {}
};

struct MovePlacePiece : public Move
{
  MovePlacePiece(const int x, const int y);
};

struct MovePass : public Move
{
  MovePass();
};


} //~namespace reversi
} //~namespace ribi

#endif // CPPREVERSIMOVE_H
