#include "pvdbcompetency.h"

#include <cassert>
#include <stdexcept>

const std::vector<ribi::pvdb::Competency> ribi::pvdb::GetAllCompetencies()
{
  return
  {
    ribi::pvdb::Competency::uninitialized,
    ribi::pvdb::Competency::profession,
    ribi::pvdb::Competency::organisations,
    ribi::pvdb::Competency::social_surroundings,
    ribi::pvdb::Competency::target_audience,
    ribi::pvdb::Competency::ti_knowledge,
    ribi::pvdb::Competency::prof_growth,
    ribi::pvdb::Competency::misc
  };

}

const std::string ribi::pvdb::CompetencyToDutchStr(const ribi::pvdb::Competency type)
{
  switch (type)
  {
    case ribi::pvdb::Competency::uninitialized: return "[Ongeinitialiseerd]";
    case ribi::pvdb::Competency::profession: return "Kennis van het beroepsdomein";
    case ribi::pvdb::Competency::organisations: return "Kennis van de organisatie";
    case ribi::pvdb::Competency::social_surroundings: return "Kennis van de sociale omgeving";
    case ribi::pvdb::Competency::target_audience: return "Kennis van de doelgroep";
    case ribi::pvdb::Competency::ti_knowledge: return "Technisch instrumentele kennis";
    case ribi::pvdb::Competency::prof_growth: return "Kennis van de eigen persoon";
    case ribi::pvdb::Competency::misc: return "Overige";
  }
  assert(!"Should not get here");
  throw std::logic_error("Unknown ribi::pvdb::Competency");
}
