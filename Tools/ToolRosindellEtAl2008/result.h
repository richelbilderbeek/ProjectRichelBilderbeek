//---------------------------------------------------------------------------
/*
RosindellEtAl2008, refactoring an extension of Rosindel at al., 2008 [1]
Copyright (C) 2015 Richel Bilderbeek
Original version by James Rosindell

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
//From http://www.richelbilderbeek.nl/ToolRosindellEtAl2008.htm
//
//Article with original code:
//
// [1] Rosindell, James, Yan Wong, and Rampal S. Etienne.
//     "A coalescence approach to spatial neutral ecology."
//      Ecological Informatics 3.3 (2008): 259-271.
//---------------------------------------------------------------------------
#ifndef RESULT_H
#define RESULT_H

#include <iosfwd>
#include "dispersalkernel.h"

struct Result
{
  Result(
    const int survey_area_width,
    const int m_survey_area_height,
    const double m_speciation_rate,
    const double m_dispersal_distance,
    const DispersalKernel m_dispersal_kernel_type,
    const double m_species_richness
  );

  double GetSpeciesRichness() const noexcept { return m_species_richness; }

  const int m_survey_area_width;
  const int m_survey_area_height;
  const double m_speciation_rate;
  const double m_dispersal_distance;
  const DispersalKernel m_dispersal_kernel_type;
  const double m_species_richness; //The result
};

std::ostream& operator<<(std::ostream& os,const Result& result);

#endif // RESULT_H
