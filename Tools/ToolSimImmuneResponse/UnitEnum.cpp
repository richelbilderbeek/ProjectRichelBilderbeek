//---------------------------------------------------------------------------
/*
  SimImmuneResponse. Active simulation about the human immune response
  Copyright (C) 2008  Richèl Bilderbeek

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#include <stdexcept>
#include <cassert>
#include <boost/lexical_cast.hpp>

#pragma hdrstop
#include "UnitEnum.h"
//---------------------------------------------------------------------------
const std::string CellTypeToString(const EnumCellType c)
{
  switch(c)
  {
    case activatedBcell: return "activated B cell";
    case activatedCytotoxicTcell: return "activated cyctotoxic T cell";
    case activatedThelperCell: return "activated T helper cell";
    case antibody: return "antibody";
    case bCell: return "B cell";
    case cellHealthy: return "healthy cell";
    case cellInfected: return "infected cell";
    case cytokine: return "cytokine";
    case cytotoxicTcell: return "cyctotoxic T cell";
    case macrophageWithVirusParticles: return "macrophage with virus particles";
    case macrophageWithoutVirusParticles: return "macrophage without virus particles";
    case tHelperCell: return "t helper cell";
    case virus: return "virus";
  }

  assert(!"Should not get here");
  throw std::domain_error("Unknown cell type of integer value "
    + boost::lexical_cast<std::string>(static_cast<int>(c) ) );
}
//---------------------------------------------------------------------------

#pragma package(smart_init)
