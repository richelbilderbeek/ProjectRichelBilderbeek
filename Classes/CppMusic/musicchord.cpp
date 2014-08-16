#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "musicchord.h"
#include <set>
#include <boost/make_shared.hpp>
#pragma GCC diagnostic pop

ribi::Music::Chord::Chord(
  const Note root,
  const std::string& postfix,
  const std::vector<int>& intervals)
  : m_root(root), m_postfix(postfix), m_intervals(intervals)
{
  #ifndef NDEBUG
  Test();
  #endif

}

int ribi::Music::Chord::CountSameNotes(const boost::shared_ptr<Chord>& lhs, const boost::shared_ptr<Chord>& rhs)
{
  assert(lhs);
  assert(rhs);
  //The indices of the notes
  std::set<int> x;
  {
    const std::vector<Music::Note> tmp = lhs->GetNotes();
    std::transform(tmp.begin(),tmp.end(),std::inserter(x,x.begin()),
      [](const Music::Note& note) { return note.ToInt(); } );
  }
  std::set<int> y;
  {
    const std::vector<Music::Note> tmp = rhs->GetNotes();
    std::transform(tmp.begin(),tmp.end(),std::inserter(y,y.begin()),
      [](const Music::Note& note) { return note.ToInt(); } );
  }
  std::set<int> z;
  std::set_intersection(x.begin(),x.end(),y.begin(),y.end(),std::inserter(z,z.begin()));
  return static_cast<int>(z.size());
}


std::vector<boost::shared_ptr<ribi::Music::Chord> > ribi::Music::Chord::CreateAllChords() noexcept
{
  std::vector<boost::shared_ptr<Chord> > v;
  std::vector<Note> notes = Note::GetAllNotes();
  std::for_each(notes.begin(),notes.end(),
    [&v](const Note& note)
    {
      const std::vector<boost::shared_ptr<Chord> > w = CreateChords(note);
      v.insert(v.end(),w.begin(),w.end());
    }
  );
  return v;
}

std::vector<boost::shared_ptr<ribi::Music::Chord> > ribi::Music::Chord::CreateChords(const Note root) noexcept
{

  return
  {
    boost::make_shared<ChordAug   >(root),
    boost::make_shared<ChordDim   >(root),
    boost::make_shared<ChordMajor >(root),
    boost::make_shared<ChordMinor >(root),
    boost::make_shared<Chord6     >(root),
    boost::make_shared<ChordMinor6>(root),
    boost::make_shared<Chord7     >(root),
    boost::make_shared<ChordMinor7>(root)
  };
}

boost::shared_ptr<ribi::Music::Chord> ribi::Music::Chord::CreateChord(const std::string& chord_name) noexcept
{
  std::vector<boost::shared_ptr<Chord> > v = CreateAllChords();
  const auto i = std::find_if(v.begin(),v.end(),
    [chord_name](const boost::shared_ptr<Chord>& chord)
    {
      return chord->ToStr() == chord_name;
    }
  );
  assert(i != v.end());
  return *i;

  /*
  assert(!chord_name.empty());
  //Get the root
  Note root = Note(chord_name.substr(0,1);
  try
  {
    //Even if the chord_name was 'C' (so a substring of length 2 is not possible),
    //also this exception is caught
    Note perhaps_root = Note(chord_name.substr(0,2);
    root = perhaps_root;
  }
  catch (std::exception&)
  {
    //No worries
  }
  //Read the chord type
  const std::string chord_type
    = chord_name.substr(
      root.ToStr().size(),
      chord_name.size() - root.ToStr().size());
  if (chord_type.empty()) return boost::shared_ptr<Chord>(new ChordMajor(root));
  */
}

const std::vector<ribi::Music::Note> ribi::Music::Chord::GetNotes() const noexcept
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

std::string ribi::Music::Chord::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::Music::Chord::GetVersionHistory() noexcept
{
  return {
    "2012-08-10: version 1.0: initial version"
  };
}

void ribi::Music::Chord::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
}

std::string ribi::Music::Chord::ToStr() const noexcept
{
  return m_root.ToStr() + m_postfix;
}

ribi::Music::ChordAug::ChordAug(const Note root) noexcept
  : Chord(root,"+",{4,4})
{

}

ribi::Music::ChordDim::ChordDim(const Note root) noexcept
  : Chord(Note(root.ToInt() + 3),"dim",{3,3})
{

}

ribi::Music::ChordMajor::ChordMajor(const Note root) noexcept
  : Chord(root,"",{4,3})
{

}

ribi::Music::ChordMinor::ChordMinor(const Note root) noexcept
  : Chord(root,"m",{3,4})
{

}

ribi::Music::Chord6::Chord6(const Note root) noexcept
  : Chord(root,"6",{4,3,2})
{

}

ribi::Music::ChordMinor6::ChordMinor6(const Note root) noexcept
  : Chord(root,"m6",{3,4,2})
{

}

ribi::Music::Chord7::Chord7(const Note root) noexcept
  : Chord(Note(root.ToInt() + 4),"7",{3,3})
{

}

ribi::Music::ChordMinor7::ChordMinor7(const Note root) noexcept
  : Chord(Note(root.ToInt() + 3),"m7",{4,3})
{

}

