#ifndef RIBI_CHESSSQUARE_H
#define RIBI_CHESSSQUARE_H

#include <iosfwd>
#include <string>
#include <boost/checked_delete.hpp>
#include "chesscolor.h"
#include "chessfile.h"
#include "chessrank.h"
#include "chessfwd.h"

namespace ribi {
namespace Chess {

///Square is the square on a Board, for example 'a1'
///ToInt can be used to derive the coordinat of the square on a chessboard
struct Square
{
  ///Obtain a Square from its notational form
  ///Note that s is checked for validity after contruction
  //Square(const char * const s);

  ///Conclude the color of the square
  Chess::Color GetColor() const;

  ///Obtain the File (X direction) of the Square
  const Chess::File& GetFile() const { return m_file; }

  ///Obtain the Rank (Y direction) of the Square
  const Chess::Rank& GetRank() const { return m_rank; }

  ///Obtain the version of this class
  static std::string GetVersion();

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory();

  ///Test the correct working of Square
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  ///Convert the Square to a string
  std::string ToStr() const noexcept;

  private:
  ///Obtain a Square from its coordinats
  explicit Square(const Chess::File& x, const Chess::Rank& y);

  ///Obtain a Square from its notational form
  explicit Square(const std::string& s);

  ///the file or x-coordinat of the square, a2 has m_file of 0
  const Chess::File m_file; //X

  ///the rank or y-coordinat of the square, a2 has m_file of 1
  const Chess::Rank m_rank; //Y

  ~Square() {}
  friend void boost::checked_delete<>(Square *);
  friend class SquareFactory;
};

std::ostream& operator<<(std::ostream& os, const Chess::Square& s) noexcept;
bool operator==(const Chess::Square& lhs, const Chess::Square& rhs) noexcept;
bool operator!=(const Chess::Square& lhs, const Chess::Square& rhs) noexcept;

} //~namespace Chess
} //~namespace ribi

#endif // RIBI_CHESSSQUARE_H
