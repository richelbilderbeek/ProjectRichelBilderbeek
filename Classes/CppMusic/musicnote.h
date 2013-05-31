#ifndef MUSICNOTE_H
#define MUSICNOTE_H

#include <string>
#include <vector>

namespace Music {

///Note class, e.g. 'C with length 1/1'
struct Note
{
  enum class Letter { A,B,C,D,E,F,G };
  enum class Accidental { none, flat, sharp };

  ///Create a Note from an integer, always uses the sharp for an accidental
  ///Examples: 0 = C, 1 = C#, 2 = D, 3 = D#
  explicit Note(const int i, const std::pair<int,int>& length = {1,1} );

  ///Create a Note from a std::string.
  ///Throws an exception when string is invalid
  explicit Note(const std::string& s, const std::pair<int,int>& length = {1,1} );

  ///Create a Note from a Letter and Accidental, will always succeed
  explicit Note(
    const Letter letter = Letter::C,
    const Accidental accidental = Accidental::none,
    const std::pair<int,int>& length = {1,1}
  );

  ///A Factory method to create all notes
  static const std::vector<Note> GetAllNotes();

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  ///Test this class
  static void Test();

  ///Convert a note to an integer
  ///Examples: C = 0, C# = 1, Db = 1, D = 2
  int ToInt() const;

  ///Convert a note to a string
  const std::string ToStr() const;


  private:
  Accidental m_accidental;
  std::pair<int,int> m_length;
  Letter m_letter;
};

bool operator==(const Note& lhs, const Note& rhs);
bool operator<(const Note& lhs, const Note& rhs);

} //~namespace Music

#endif // MUSICNOTE_H
