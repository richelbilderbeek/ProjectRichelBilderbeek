//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "musicchord.h"

#include <set>

namespace Music {

Chord::Chord(
  const Note root,
  const std::string& postfix,
  const std::vector<int>& intervals)
  : m_root(root), m_postfix(postfix), m_intervals(intervals)
{
  #ifndef NDEBUG
  Test();
  #endif

}

int Chord::CountSameNotes(const boost::shared_ptr<Chord>& lhs, const boost::shared_ptr<Chord>& rhs)
{
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


std::vector<boost::shared_ptr<Chord> > Chord::CreateAllChords()
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

std::vector<boost::shared_ptr<Chord> > Chord::CreateChords(const Note root)
{
  return
  {
    boost::shared_ptr<Chord>(new ChordAug(root)),
    boost::shared_ptr<Chord>(new ChordDim(root)),
    boost::shared_ptr<Chord>(new ChordMajor(root)),
    boost::shared_ptr<Chord>(new ChordMinor(root)),
    boost::shared_ptr<Chord>(new Chord6(root)),
    boost::shared_ptr<Chord>(new ChordMinor6(root)),
    boost::shared_ptr<Chord>(new Chord7(root)),
    boost::shared_ptr<Chord>(new ChordMinor7(root))
  };
}

boost::shared_ptr<Chord> Chord::CreateChord(const std::string& chord_name)
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

const std::vector<Note> Chord::GetNotes() const
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

const std::string Chord::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> Chord::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2012-08-10: version 1.0: initial version");
  return v;
}

void Chord::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
}

const std::string Chord::ToStr() const
{
  return m_root.ToStr() + m_postfix;
}

ChordAug::ChordAug(const Note root)
  : Chord(root,"+",{4,4})
{

}

ChordDim::ChordDim(const Note root)
  : Chord(Note(root.ToInt() + 3),"dim",{3,3})
{

}

ChordMajor::ChordMajor(const Note root)
  : Chord(root,"",{4,3})
{

}

ChordMinor::ChordMinor(const Note root)
  : Chord(root,"m",{3,4})
{

}

Chord6::Chord6(const Note root)
  : Chord(root,"6",{4,3,2})
{

}

ChordMinor6::ChordMinor6(const Note root)
  : Chord(root,"m6",{3,4,2})
{

}

Chord7::Chord7(const Note root)
  : Chord(Note(root.ToInt() + 4),"7",{3,3})
{

}

ChordMinor7::ChordMinor7(const Note root)
  : Chord(Note(root.ToInt() + 3),"m7",{4,3})
{

}

} //~namespace Music


