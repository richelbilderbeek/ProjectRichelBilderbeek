#include "conceptmapcompetency.h"

#include <cassert>
#include <stdexcept>

const std::vector<ribi::cmap::Competency> ribi::cmap::GetAllCompetencies()
{
  return
  {
    ribi::cmap::Competency::uninitialized,
    ribi::cmap::Competency::profession,
    ribi::cmap::Competency::organisations,
    ribi::cmap::Competency::social_surroundings,
    ribi::cmap::Competency::target_audience,
    ribi::cmap::Competency::ti_knowledge,
    ribi::cmap::Competency::prof_growth,
    ribi::cmap::Competency::misc
  };

}

const std::string ribi::cmap::CompetencyToDutchStr(const ribi::cmap::Competency type)
{
  switch (type)
  {
    case ribi::cmap::Competency::uninitialized: return "[Ongeinitialiseerd]";
    case ribi::cmap::Competency::profession: return "Kennis van het beroepsdomein";
    case ribi::cmap::Competency::organisations: return "Kennis van de organisatie";
    case ribi::cmap::Competency::social_surroundings: return "Kennis van de sociale omgeving";
    case ribi::cmap::Competency::target_audience: return "Kennis van de doelgroep";
    case ribi::cmap::Competency::ti_knowledge: return "Technisch instrumentele kennis";
    case ribi::cmap::Competency::prof_growth: return "Kennis van de eigen persoon";
    case ribi::cmap::Competency::misc: return "Overige";
  }
  assert(!"Should not get here");
  throw std::logic_error("Unknown ribi::cmap::Competency");
}
