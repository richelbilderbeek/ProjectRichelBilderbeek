#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

/*

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "pvdbhints.h"

#include <cassert>
#include "trace.h"

#ifdef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
namespace pvdb {
#endif


pvdb::Hints::Hints()
  : m_m(CreateMap())
{
  #ifndef NDEBUG
  Test();
  #endif

}

const std::map<pvdb::Hint,std::pair<bool,std::string> > pvdb::Hints::CreateMap()
{
  std::map<Hint,std::pair<bool,std::string> > m;
  m[Hint::create_concept]
    = std::make_pair(false,"Dubbelklik op leeg gebied om een nieuw concept te maken");
  m[Hint::edit_concept]
    = std::make_pair(false,"Druk op F2 om een concept te bewerken");
  m[Hint::edit_arrow]
    = std::make_pair(false,"Druk op '1' of '2' om pijlpunten te wijzigen");

  return m;
}

const std::string& pvdb::Hints::GetText(const pvdb::Hint hint) const
{
  assert(!IsDone(hint));
  return (*m_m.find(hint)).second.second;
}


bool pvdb::Hints::IsDone(const pvdb::Hint hint) const
{
  assert(m_m.find(hint) != m_m.end());
  return (*m_m.find(hint)).second.first;
}

void pvdb::Hints::SetDone(const pvdb::Hint hint)
{
  assert(m_m.find(hint) != m_m.end());
  //Can always set done, even when already done so
  //assert((*m_m.find(hint)).second.first == false);
  //assert(!IsDone((hint)));
  m_m[hint].first = true;

  assert(IsDone((hint)));
}

void pvdb::Hints::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  {
    pvdb::Hints h;
    assert(!h.IsDone(Hint::create_concept));
    assert(!h.IsDone(Hint::edit_concept));
    assert(!h.IsDone(Hint::edit_arrow));
    assert(!h.GetText(Hint::create_concept).empty());
    assert(!h.GetText(Hint::edit_concept).empty());
    assert(!h.GetText(Hint::edit_arrow).empty());
    h.SetDone(Hint::create_concept);
    h.SetDone(Hint::edit_concept);
    h.SetDone(Hint::edit_arrow);
    assert(h.IsDone(Hint::create_concept));
    assert(h.IsDone(Hint::edit_concept));
    assert(h.IsDone(Hint::edit_arrow));
  }
}


#ifdef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
} //~namespace pvdb
#endif

*/
