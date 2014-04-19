//---------------------------------------------------------------------------
/*
ConceptMap, concept map classes
Copyright (C) 2013-2014 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppConceptMap.htm
//---------------------------------------------------------------------------
#include "conceptmapcompetency.h"

#include <cassert>
#include <stdexcept>

std::vector<ribi::cmap::Competency> ribi::cmap::GetAllCompetencies() noexcept
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

std::string ribi::cmap::CompetencyToDutchStr(const ribi::cmap::Competency type) noexcept
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
