#ifndef CHESSFILE_H
#define CHESSFILE_H

#include <string>
#include <vector>

namespace ribi {
namespace Chess {

///A File is the x-coordinat on a Board
struct File
{
  ///Create a file from its single-character string, e.g. "b" for file b
  explicit File(const std::string& x);

  ///Create a file from its x-coordinat, e.g. 1 for file b
  explicit File(const int x);

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  ///Test this class
  static void Test() noexcept;

  ///Convert a File to its single-character string.
  ///For example, file "a" has x-coordinat 0
  const std::string& ToStr() const { return m_s; }

  ///Convert a File to its x-coordinat.
  ///For example, file 'a' has x-coordinat 0
  int ToInt() const;

  //Increment file, e.g. from 'a' to'b'
  //File& operator++();

  //Decrement file, e.g. from 'b' to'a'
  //File& operator--();

  private:
  const std::string m_s;


  ///Convert 0 to 'a', 1 to 'b', etc...
  static std::string IntToCharToStr(const int x);
};

bool operator==(const File& lhs, const File& rhs);

} //~namespace Chess
} //~namespace ribi

#endif // CHESSFILE_H
