#include "abcfile.h"

#include <sstream>

AbcFile::AbcFile()
  : m_composer(""),
    m_index(0),
    m_note(0),
    m_note_length { 1,4 },
    m_tempo { 1,4,120 } ,
    m_time_signature { 3,4 } ,
    m_title("")
{

}

const std::string AbcFile::ToStr() const
{
  std::stringstream s;
  s << "X:" << this->GetIndex() << '\n'
    << "T:" << this->GetTitle() << '\n'
    << "C:" << this->GetComposer() << '\n'
    << "L:" << m_note_length.first << "/" << m_note_length.second << '\n'
    << "M:" << m_time_signature.first << "/" << m_time_signature.second << '\n'
    << "T"  << std::get<0>(m_tempo) << "/" << std::get<1>(m_tempo) << "=" << std::get<2>(m_tempo) << '\n'
    << "V:V1 clef=treble" << '\n'
    << "V:V2 clef=bass" << '\n';

}


std::ostream& operator<<(std::ostream& os, const AbcFile& file)
{
  os << file.ToStr();
  return os;
}

/*
[V:V1] [FBd]2 d  B   | [FBd]2 d B   | [GBd]2 B d   | [GBd]2 B d    |
w:     dot    se-ven | zip    ~ ex- | tract in the | mor-     ning |
[V:V2] B,,4          | B,4          | G,,4         | G,4           |
%      B             |              | G#m          |               |
%
% Verse 1, 13-16
%
[V:V1] [GBe]2  e B   | [GBe]2  e B  | [FAc]2 c A  | [FAc]2 c   A  |
w:     gotta have my | tools, gotta | have ~ mer- | cu-    ri- al |
[V:V2] E,4           | E4           | F,,4        | F,4           |
%      E             |              | F#          |               |

*/
