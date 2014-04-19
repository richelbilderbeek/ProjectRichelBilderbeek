#ifndef MUSICNOTE_H
#define MUSICNOTE_H

#include <string>
#include <vector>

namespace ribi {

namespace Music {

///Note class, e.g. 'C with length 1/1'
struct Note
{
  enum class Letter { A,B,C,D,E,F,G };
  enum class Accidental { none, flat, sharp };

  ///Create a Note from an integer, always uses the sharp for an accidental
  ///Examples: 0 = C, 1 = C#, 2 = D, 3 = D#
  ///Throws an exception when i is out of range
  explicit Note(const int i, const std::pair<int,int>& length = {0,1} );

  ///Create a Note from a std::string.
  ///Throws an exception when string is invalid
  explicit Note(const std::string& s, const std::pair<int,int>& length = {0,1} );

  ///Create a Note from a Letter and Accidental, will always succeed
  explicit Note(
    const Letter letter = Letter::C,
    const Accidental accidental = Accidental::none,
    const std::pair<int,int>& length = {0,1}
  ) noexcept;

  ///A Factory method to create all notes
  static const std::vector<Note> GetAllNotes() noexcept;

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  #ifndef NDEBUG
  ///Test this class
  static void Test() noexcept;
  #endif

  ///Convert a note to an integer
  ///Examples: C = 0, C# = 1, Db = 1, D = 2
  int ToInt() const noexcept;

  ///Convert a note to a string
  std::string ToStr() const noexcept;


  private:
  Accidental m_accidental;

  ///An x/yth note, e.g 1/4th
  std::pair<int,int> m_length;


  Letter m_letter;
};

bool operator==(const Note& lhs, const Note& rhs) noexcept;
bool operator<(const Note& lhs, const Note& rhs) noexcept;

} //~namespace Music

} //~namespace ribi

#endif // MUSICNOTE_H
