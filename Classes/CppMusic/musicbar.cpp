#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "musicbar.h"

#include <cassert>

namespace Music {

Bar::Bar(
  const std::pair<int,int> time_signature,
  const std::vector<Note>& notes)
  : m_notes(notes),
    m_time_signature(time_signature)
{
  assert(!"TODO: Check that the num of lengths of the notes equals the time signature");
}

} //~namespace Music
