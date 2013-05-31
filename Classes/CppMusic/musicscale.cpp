#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "musicscale.h"

#include <stdexcept>
#include "musicchord.h"
#include "trace.h"

namespace Music {

Scale::Scale(const Note root, const std::vector<int>& intervals)
  : m_root(root),
    m_intervals(intervals)
{
  #ifndef NDEBUG
  Test();
  #endif

}

boost::shared_ptr<Scale> Scale::CreateScale(
    const std::string& scale_name,
    const Note root)
{
  const std::vector<boost::shared_ptr<Scale> > v = CreateScales(root);
  const auto i = std::find_if(v.begin(),v.end(),
    [scale_name](const boost::shared_ptr<Scale>& scale)
    {
      return scale->GetName() == scale_name;
    }
  );
  if (i == v.end())
  {
    TRACE(scale_name);
    throw std::logic_error("Scale name is not found");
  }
  return *i;
}

std::vector<boost::shared_ptr<Scale> > Scale::CreateScales(const Note root)
{
  return
  {
    boost::shared_ptr<Scale>(new ScaleBlues(root)),
    boost::shared_ptr<Scale>(new ScaleHarmonicMinor(root)),
    boost::shared_ptr<Scale>(new ScaleHexatonic(root)),
    boost::shared_ptr<Scale>(new ScaleHyperMajor(root)),
    boost::shared_ptr<Scale>(new ScaleMajor(root)),
    boost::shared_ptr<Scale>(new ScaleMajorPentatonic(root)),
    boost::shared_ptr<Scale>(new ScaleMinorPentatonic(root)),
    boost::shared_ptr<Scale>(new ScaleMollDurDominant(root)),
    boost::shared_ptr<Scale>(new ScaleMollDurSubdominant(root)),
  };
}

bool Scale::Fits(const boost::shared_ptr<Chord>& chord) const
{
  const std::vector<Note> notes_chord = chord->GetNotes();
  const std::vector<Note> notes_scale = this->GetNotes();

  //Count mismatches
  const int n_mismatch
    = std::count_if(notes_chord.begin(),notes_chord.end(),
    [notes_scale](const Note& note)
    {
      //If note from chord cannot be found in scale, return true
      return std::find(notes_scale.begin(),notes_scale.end(),note) == notes_scale.end();
    }
  );
  return n_mismatch == 0;
}


const std::vector<Note> Scale::GetNotes() const
{
  std::vector<Note> notes;
  Note cur = m_root;
  notes.push_back(cur);
  std::for_each(m_intervals.begin(),m_intervals.end(),
    [&cur,&notes](const int interval)
    {
      cur = Note( (cur.ToInt() + interval) % 12);
      notes.push_back(cur);
    }
  );
  return notes;
}

const std::string Scale::GetVersion()
{
  return "1.1";
}

const std::vector<std::string> Scale::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2012-08-10: version 1.0: initial version with five different scales");
  v.push_back("2012-08-11: version 1.1: added four scales");
  return v;
}

void Scale::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
}

ScaleBlues::ScaleBlues(const Note root)
  : Scale(root, {3,2,1,1,3} )
{

}

//C-D-Eb-F-G-Ab-B
// 2 1  2 2 1  3
ScaleHarmonicMinor::ScaleHarmonicMinor(const Note root)
  : Scale(root, {2,1,2,2,1,3} )
{

}

ScaleHexatonic::ScaleHexatonic(const Note root)
  : Scale(root, {2,2,2,2,2} )
{

}

ScaleHyperMajor::ScaleHyperMajor(const Note root)
  : Scale(root, {1,3,1,3,1} )
{

}


ScaleMajor::ScaleMajor(const Note root)
  : Scale(root, {2,2,1,2,2,2} )
{

}

//C-D-E-G-A
// 2 2 3 2
ScaleMajorPentatonic::ScaleMajorPentatonic(const Note root)
  : Scale(root, {2,2,3,2} )
{

}

//C-Eb-F-G_Bb
// 3  2 2 3
ScaleMinorPentatonic::ScaleMinorPentatonic(const Note root)
  : Scale(root, {3,2,2,3} )
{

}

ScaleMollDurDominant::ScaleMollDurDominant(const Note root)
  : Scale(root, {2,2,1,2,1,3} )
{

}

ScaleMollDurSubdominant::ScaleMollDurSubdominant(const Note root)
  : Scale(root, {2,2,1,2,1,2} )
{

}

} //~namespace Music

