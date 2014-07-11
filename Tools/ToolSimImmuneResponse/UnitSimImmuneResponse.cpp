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
#include <cassert>
#include <algorithm>
#include <stdexception>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include "UnitSprite.h"
#pragma hdrstop

#include "UnitSimImmuneResponse.h"
#include "UnitFormSimImmuneResponseMain.h"
//---------------------------------------------------------------------------
SimImmuneResponse::SimImmuneResponse()
  : mBloodStream(new BloodStream),
    mBoneMarrow(new BoneMarrow),
    mCellTissue(new CellTissue),
    mLymphNode(new LymphNode)
{


}
//---------------------------------------------------------------------------
const boost::shared_ptr<Location>& SimImmuneResponse::GetLocation(const EnumLocation location) const
{
  switch (location)
  {
    case bloodStream: return mBloodStream;
    case boneMarrow: return mBoneMarrow;
    case cellTissue: return mCellTissue;
    case lymphNode: return mLymphNode;
  }
  assert(!"Should not get here");
  throw std::domain_error("Unknown location with integer value of "
    + boost::lexical_cast<std::string>(static_cast<int>(location) ) );
}
//---------------------------------------------------------------------------
boost::shared_ptr<Location>& SimImmuneResponse::GetLocation(const EnumLocation location)
{
  switch (location)
  {
    case bloodStream: return mBloodStream;
    case boneMarrow: return mBoneMarrow;
    case cellTissue: return mCellTissue;
    case lymphNode: return mLymphNode;
  }
 assert(!"Should not get here");
  throw std::domain_error("Unknown location with integer value of "
    + boost::lexical_cast<std::string>(static_cast<int>(location) ) );
}
//---------------------------------------------------------------------------
const bool SimImmuneResponse::CanGrabSprite(
  const EnumLocation location,
  const int x,
  const int y) const
{
  return GetLocation(location)->CanGrabSprite(x,y);
}
//---------------------------------------------------------------------------
const boost::shared_ptr<Sprite> SimImmuneResponse::GrabSprite(
  const EnumLocation location,
  const int x,
  const int y)
{
  return GetLocation(location)->GrabSprite(x,y);
}
//---------------------------------------------------------------------------
void SimImmuneResponse::AddSprite(const EnumCellType cellType, const EnumLocation location)
{
  const double x = Sprite::maxx * 0.5;
  const double y = 0.0;
  this->AddSprite(GetSprite(cellType,x,y), location);
}
//---------------------------------------------------------------------------
void SimImmuneResponse::AddSprite(const boost::shared_ptr<Sprite>& s, const EnumLocation location)
{
  GetLocation(location)->AddSprite(s);
}
//---------------------------------------------------------------------------
const std::list<boost::shared_ptr<Sprite> >& SimImmuneResponse::GetSprites(const EnumLocation& location) const
{
  return GetLocation(location)->GetSprites();
}
//---------------------------------------------------------------------------
void SimImmuneResponse::Tick()
{
  //Clean mSimState
  mSimState = SimState();
  //Collect all migrants
  std::list<std::pair<EnumLocation, boost::shared_ptr<Sprite> > > migrants;
  mBloodStream->RemoveEmigrants(migrants);
  mBoneMarrow->RemoveEmigrants(migrants);
  mCellTissue->RemoveEmigrants(migrants);
  mLymphNode->RemoveEmigrants(migrants);
  mBloodStream->AddMigrants(migrants);
  mBoneMarrow->AddMigrants(migrants);
  mCellTissue->AddMigrants(migrants);
  mLymphNode->AddMigrants(migrants);
  //Re-update it
  mBloodStream->UpdateSimState(mSimState);
  mBoneMarrow->UpdateSimState(mSimState);
  mCellTissue->UpdateSimState(mSimState);
  mLymphNode->UpdateSimState(mSimState);
  //Respond to it
  mBloodStream->RespondToSimState();
  mBoneMarrow->RespondToSimState();
  mCellTissue->RespondToSimState();
  mLymphNode->RespondToSimState();
  //Move all sprites
  mBloodStream->MoveAllSprites();
  mBoneMarrow->MoveAllSprites();
  mCellTissue->MoveAllSprites();
  mLymphNode->MoveAllSprites();
}
//---------------------------------------------------------------------------
const std::string SimImmuneResponse::GetFeedback() const
{
  return mSimState.GetFeedback();
}
//---------------------------------------------------------------------------



#pragma package(smart_init)
