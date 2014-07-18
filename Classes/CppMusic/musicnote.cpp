

#include "musicnote.h"

#include <cassert>
#include <stdexcept>
#include <vector>

#include "trace.h"

ribi::Music::Note::Note(const int i, const std::pair<int,int>& length)
  : m_accidental(ribi::Music::Note::Accidental::none),
    m_length(length),
    m_letter(ribi::Music::Note::Letter::C)
{
  #ifndef NDEBUG
  Test();
  #endif

  switch (i % 12)
  {
    case  0: m_letter = Letter::C; m_accidental = Accidental::none ; break;
    case  1: m_letter = Letter::C; m_accidental = Accidental::sharp; break;
    case  2: m_letter = Letter::D; m_accidental = Accidental::none ; break;
    case  3: m_letter = Letter::D; m_accidental = Accidental::sharp; break;
    case  4: m_letter = Letter::E; m_accidental = Accidental::none ; break;
    case  5: m_letter = Letter::F; m_accidental = Accidental::none ; break;
    case  6: m_letter = Letter::F; m_accidental = Accidental::sharp; break;
    case  7: m_letter = Letter::G; m_accidental = Accidental::none ; break;
    case  8: m_letter = Letter::G; m_accidental = Accidental::sharp; break;
    case  9: m_letter = Letter::A; m_accidental = Accidental::none ; break;
    case 10: m_letter = Letter::A; m_accidental = Accidental::sharp; break;
    case 11: m_letter = Letter::B; m_accidental = Accidental::none ; break;
    default:
      TRACE(i);
      assert(!"Should not get here");
      throw std::logic_error("Invalid value for note; must be in range [0,12>");
  }
}

ribi::Music::Note::Note(const std::string& s, const std::pair<int,int>& length)
  : m_accidental(ribi::Music::Note::Accidental::none),
    m_length(length),
    m_letter(ribi::Music::Note::Letter::C)
{
  #ifndef NDEBUG
  Test();
  #endif
  if (s.empty()) throw std::logic_error("A music note must not be empty");
  if (s[0] < 'A' || s[0] > 'G') throw std::logic_error("A music note must start with a capital letter from A to and including G");
  if (s.size() > 2) throw std::logic_error("A music note cannot consist of more than two character");
  if (s.size() == 2 && (s[1] != '#' && s[1] != 'b'))
  {
    TRACE(s);
    throw std::logic_error("A music note's second character must be either absent, '#' or 'b'");
  }
  switch (s[0])
  {
    case 'C': m_letter = Letter::C; break;
    case 'D': m_letter = Letter::D; break;
    case 'E': m_letter = Letter::E; break;
    case 'F': m_letter = Letter::F; break;
    case 'G': m_letter = Letter::G; break;
    case 'A': m_letter = Letter::A; break;
    case 'B': m_letter = Letter::B; break;
  }
  if (s.size() == 2)
  {
    switch (s[1])
    {
      case '#': m_accidental = Accidental::sharp; break;
      case 'b': m_accidental = Accidental::flat; break;
    }
  }
  else
  {
    m_accidental = Accidental::none;
  }
}

ribi::Music::Note::Note(
  const Letter letter,
  const Accidental accidental,
  const std::pair<int,int>& length) noexcept
  : m_accidental(accidental),
    m_length(length),
    m_letter(letter)

{
  #ifndef NDEBUG
  Test();
  #endif

}

const std::vector<ribi::Music::Note> ribi::Music::Note::GetAllNotes() noexcept
{
  std::vector<Note> v;
  for (int i=0; i!=12; ++i)
  {
    v.push_back(Note(i));
  }
  return v;
}

std::string ribi::Music::Note::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::Music::Note::GetVersionHistory() noexcept
{
  return {
    "2012-08-10: version 1.0: initial version"
  };
}

#ifndef NDEBUG
void ribi::Music::Note::Test() noexcept
{
  //Test exactly once
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  //Test ToInt
  {
    assert(Note(Letter::C).ToInt() == 0);
    assert(Note(0).ToInt() == 0);
    assert(Note(0).ToStr() == "C");
  }
}
#endif

int ribi::Music::Note::ToInt() const noexcept
{
  int x = 0;
  switch (m_letter)
  {
    case Letter::C: x =  0; break;
    case Letter::D: x =  2; break;
    case Letter::E: x =  4; break;
    case Letter::F: x =  5; break;
    case Letter::G: x =  7; break;
    case Letter::A: x =  9; break;
    case Letter::B: x = 11; break;
  }
  switch (m_accidental)
  {
    case Accidental::none : break;
    case Accidental::sharp: ++x; break;
    case Accidental::flat : --x; break;
  }
  x += 12;
  x %= 12;
  assert(x >= 0); assert(x < 12);
  return x;
}

std::string ribi::Music::Note::ToStr() const noexcept
{
  std::string s;
  switch (m_letter)
  {
    case Letter::C: s = "C"; break;
    case Letter::D: s = "D"; break;
    case Letter::E: s = "E"; break;
    case Letter::F: s = "F"; break;
    case Letter::G: s = "G"; break;
    case Letter::A: s = "A"; break;
    case Letter::B: s = "B"; break;
  }
  switch (m_accidental)
  {
    case Accidental::none : break;
    case Accidental::sharp: s+="#"; break;
    case Accidental::flat : s+="b"; break;
  }
  return s;
}

bool ribi::Music::operator==(const Note& lhs, const Note& rhs) noexcept
{
  return lhs.ToInt() == rhs.ToInt();
}

bool ribi::Music::operator<(const Note& lhs, const Note& rhs) noexcept
{
  return lhs.ToInt() < rhs.ToInt();
}
