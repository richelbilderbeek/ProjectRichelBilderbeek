#include "musicbar.h"

#include <cassert>


ribi::Music::Bar::Bar(
  const std::pair<int,int> time_signature,
  const std::vector<Note>& notes)
  : m_notes(notes),
    m_time_signature(time_signature)
{
  assert(!"TODO: Check that the num of lengths of the notes equals the time signature");
}
