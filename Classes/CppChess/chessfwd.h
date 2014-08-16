#ifndef RIBI_CHESSFWD_H
#define RIBI_CHESSFWD_H

///Contains the CppChess forward declarations
namespace ribi {
namespace Chess {

struct BitBoard;
struct Board;
struct BoardFactory;
struct BoardWidget;
//enum class Castling;
//enum class Color;
struct File;
struct Game;
struct GameWidget;
struct Move;
struct MoveFactory;
struct Piece;
struct PieceBishop;
struct PieceFactory;
struct PieceKing;
struct PieceKnight;
struct PiecePawn;
struct PieceQueen;
struct PieceRook;
//enum class Player;
struct Rank;
struct Score;
struct Square;
struct SquareFactory;
struct SquareSelector;

} //~namespace Chess

struct Widget;

} //~namespace ribi

#endif // RIBI_CHESSFWD_H
