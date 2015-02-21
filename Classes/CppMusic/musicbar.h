#ifndef MUSICBAR_H
#define MUSICBAR_H

#include "musicnote.h"

namespace ribi {
namespace Music {

///A Bar is a collection of Note instances ensuring that
///the sum of the length of the Notes equals the time signature of the bar.
///Note that rests are not supported
struct Bar
{
  Bar(
    const std::pair<int,int> time_signature,
    const std::vector<Note>& notes);

  private:
  const std::vector<Note> m_notes;
  const std::pair<int,int> m_time_signature;
};

} //~namespace Music
} //~namespace ribi

#endif // MUSICBAR_H
