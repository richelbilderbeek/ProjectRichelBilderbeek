#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "musicscale.h"

#include <stdexcept>
#include "musicchord.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::Music::Scale::Scale(const Note root, const std::vector<int>& intervals)
  : m_root(root),
    m_intervals(intervals)
{
  #ifndef NDEBUG
  Test();
  #endif

}

boost::shared_ptr<ribi::Music::Scale> ribi::Music::Scale::CreateScale(
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

std::vector<boost::shared_ptr<ribi::Music::Scale> > ribi::Music::Scale::CreateScales(const Note root) noexcept
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

bool ribi::Music::Scale::Fits(const boost::shared_ptr<Chord>& chord) const noexcept
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


const std::vector<ribi::Music::Note> ribi::Music::Scale::GetNotes() const noexcept
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

std::string ribi::Music::Scale::GetVersion() noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::Music::Scale::GetVersionHistory() noexcept
{
  return {
    "2012-08-10: version 1.0: initial version with five different scales",
    "2012-08-11: version 1.1: added four scales"
  };
}

void ribi::Music::Scale::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
}

ribi::Music::ScaleBlues::ScaleBlues(const Note root) noexcept
  : Scale(root, {3,2,1,1,3} )
{

}

//C-D-Eb-F-G-Ab-B
// 2 1  2 2 1  3
ribi::Music::ScaleHarmonicMinor::ScaleHarmonicMinor(const Note root) noexcept
  : Scale(root, {2,1,2,2,1,3} )
{

}

ribi::Music::ScaleHexatonic::ScaleHexatonic(const Note root) noexcept
  : Scale(root, {2,2,2,2,2} )
{

}

ribi::Music::ScaleHyperMajor::ScaleHyperMajor(const Note root) noexcept
  : Scale(root, {1,3,1,3,1} )
{

}


ribi::Music::ScaleMajor::ScaleMajor(const Note root) noexcept
  : Scale(root, {2,2,1,2,2,2} )
{

}

//C-D-E-G-A
// 2 2 3 2
ribi::Music::ScaleMajorPentatonic::ScaleMajorPentatonic(const Note root) noexcept
  : Scale(root, {2,2,3,2} )
{

}

//C-Eb-F-G_Bb
// 3  2 2 3
ribi::Music::ScaleMinorPentatonic::ScaleMinorPentatonic(const Note root) noexcept
  : Scale(root, {3,2,2,3} )
{

}

ribi::Music::ScaleMollDurDominant::ScaleMollDurDominant(const Note root) noexcept
  : Scale(root, {2,2,1,2,1,3} )
{

}

ribi::Music::ScaleMollDurSubdominant::ScaleMollDurSubdominant(const Note root) noexcept
  : Scale(root, {2,2,1,2,1,2} )
{

}
