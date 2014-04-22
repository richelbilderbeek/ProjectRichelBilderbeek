
#ifndef CHESSRANK_H
#define CHESSRANK_H

#include <string>
#include <vector>

namespace ribi {
namespace Chess {

///Rank is the y coordinat on the Board
struct Rank
{
  ///Create a Rank from a single-character std::string
  ///Use std::string instead of char to prevent implicit typecasts
  explicit Rank(const std::string& rank);

  ///Create a Rank from its y coordinat
  explicit Rank(const int y);

  ///Obtain the version of this class
  static std::string GetVersion();

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory();

  ///Test this class
  static void Test() noexcept;

  ///Convert the Rank to its y coordinat on the Board, for example 0 for square h1
  int ToInt() const;

  ///Convert the Rank to its single-character string, for example "1" for square h1
  const std::string& ToStr() const;

  //Increment rank, e.g. from '1' to'2'
  //Rank& operator++();

  //Decrement rank, e.g. from '2' to'1'
  //Rank& operator--();

  private:
  ///The Rank as a single-character std::string, for example "1"
  ///Use std::string instead of char to prevent implicit typecasts
  const std::string m_rank;
};

bool operator==(const Rank& lhs, const Rank& rhs);

} //~namespace Chess
} //~namespace ribi

#endif // CHESSRANK_H
