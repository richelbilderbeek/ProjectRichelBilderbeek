//---------------------------------------------------------------------------
/*
  SimImmuneResponse. Active simulation about the human immune response
  Copyright (C) 2008  Richel Bilderbeek

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
#ifndef UnitSimImmuneResponseH
#define UnitSimImmuneResponseH
//---------------------------------------------------------------------------
#include <list>
#include <vector>
#include <string>
#include <queue>
#include <boost/shared_ptr.hpp>
#include "UnitEnum.h"
#include "UnitSprite.h"
#include "UnitLocation.h"
#include "UnitSimState.h"

//namespace Extctrls { struct TImage; }
//struct TFormSimImmuneResponseMain;
//---------------------------------------------------------------------------
struct SimImmuneResponse
{
  SimImmuneResponse();

  const bool CanGrabSprite(
    const EnumLocation location,
    const int x,
    const int y) const;
  const boost::shared_ptr<Sprite> GrabSprite(
    const EnumLocation location,
    const int x,
    const int y);
  const std::list<boost::shared_ptr<Sprite> >& GetSprites(const EnumLocation& location) const;

  void AddSprite(const boost::shared_ptr<Sprite>& s, const EnumLocation location);
  void AddSprite(const EnumCellType cellType, const EnumLocation location);
  void Tick();


  const std::string GetFeedback() const;


  boost::shared_ptr<Location>& GetLocation(const EnumLocation location);
  const boost::shared_ptr<Location>& GetLocation(const EnumLocation location) const;

  private:

  boost::shared_ptr<Location> mBloodStream;
  boost::shared_ptr<Location> mBoneMarrow;
  boost::shared_ptr<Location> mCellTissue;
  boost::shared_ptr<Location> mLymphNode;

  SimState mSimState;


};

#endif
