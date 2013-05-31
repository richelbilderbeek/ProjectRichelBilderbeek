#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "pvdbcompetency.h"

#include <cassert>
#include <stdexcept>

#ifdef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
namespace pvdb {
#endif

const std::vector<pvdb::Competency> pvdb::GetAllCompetencies()
{
  return
  {
    pvdb::Competency::uninitialized,
    pvdb::Competency::profession,
    pvdb::Competency::organisations,
    pvdb::Competency::social_surroundings,
    pvdb::Competency::target_audience,
    pvdb::Competency::ti_knowledge,
    pvdb::Competency::prof_growth,
    pvdb::Competency::misc
  };

}

const std::string pvdb::CompetencyToDutchStr(const pvdb::Competency type)
{
  switch (type)
  {
    case pvdb::Competency::uninitialized: return "[Ongeinitialiseerd]";
    case pvdb::Competency::profession: return "Kennis van het beroepsdomein";
    case pvdb::Competency::organisations: return "Kennis van de organisatie";
    case pvdb::Competency::social_surroundings: return "Kennis van de sociale omgeving";
    case pvdb::Competency::target_audience: return "Kennis van de doelgroep";
    case pvdb::Competency::ti_knowledge: return "Technisch instrumentele kennis";
    case pvdb::Competency::prof_growth: return "Kennis van de eigen persoon";
    case pvdb::Competency::misc: return "Overige";
  }
  assert(!"Should not get here");
  throw std::logic_error("Unknown pvdb::Competency");
}

#ifdef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
} //~namespace pvdb
#endif
