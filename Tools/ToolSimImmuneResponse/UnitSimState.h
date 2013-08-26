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
#ifndef UnitSimStateH
#define UnitSimStateH
//---------------------------------------------------------------------------
#include <string>
#include <set>
#include "UnitEnum.h"

struct SimState
{
  const std::string GetFeedback() const;


  const bool IsPresent(const EnumLocation location, const EnumCellType cellType) const;
  const bool IsPresent(const EnumCellType cellType) const;

  std::set<EnumCellType>& GetLocation(const EnumLocation location);
  const std::set<EnumCellType>& GetLocation(const EnumLocation location) const;

  //Celltypes that are present at a specific location
  std::set<EnumCellType> mInBloodStream;
  std::set<EnumCellType> mInBoneMarrow;
  std::set<EnumCellType> mInCellTissue;
  std::set<EnumCellType> mInLymphNode;

};
#endif
