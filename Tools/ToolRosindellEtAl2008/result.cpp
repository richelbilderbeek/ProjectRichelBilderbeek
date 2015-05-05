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
#include "result.h"
#include <ostream>

Result::Result(
  const int survey_area_width,
  const int survey_area_height,
  const double speciation_rate,
  const double dispersal_distance,
  const DispersalKernel dispersal_kernel_type,
  const double species_richness
) : m_survey_area_width{survey_area_width},
    m_survey_area_height{survey_area_height},
    m_speciation_rate{speciation_rate},
    m_dispersal_distance{dispersal_distance},
    m_dispersal_kernel_type{dispersal_kernel_type},
    m_species_richness{species_richness}

{

}

std::ostream& operator<<(std::ostream& os,const Result& result)
{
  os
    << result.m_survey_area_width << " "
    << result.m_survey_area_height << " "
    << result.m_speciation_rate << " "
    << result.m_dispersal_distance << " "
    << ToStr(result.m_dispersal_kernel_type) << " "
    << result.m_species_richness
  ;
  return os;
}
