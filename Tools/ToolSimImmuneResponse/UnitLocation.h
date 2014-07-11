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
#ifndef UnitLocationH
#define UnitLocationH
//---------------------------------------------------------------------------
#include <list>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include "UnitSprite.h"
#include "UnitEnum.h"
#include "UnitSimState.h"
//---------------------------------------------------------------------------
struct Location : public boost::noncopyable
{
  typedef std::list<boost::shared_ptr<Sprite> >::iterator Iterator;
  typedef std::list<boost::shared_ptr<Sprite> >::const_iterator ConstIterator;
  typedef std::list<std::pair<EnumLocation, boost::shared_ptr<Sprite> > >::iterator PairIterator;
  typedef std::list<std::pair<EnumLocation, boost::shared_ptr<Sprite> > >::const_iterator ConstPairIterator;


  virtual void RespondToSimState() = 0;
  virtual const EnumLocation GetLocation() const = 0;
  virtual void ChangeAllSprites();

  void MoveAllSprites();

  const std::list<boost::shared_ptr<Sprite> >& GetSprites() const { return mSprites; }
  boost::shared_ptr<Sprite>& GetSprite(const std::size_t i);
  const boost::shared_ptr<Sprite>& GetSprite(const std::size_t i) const;
  const std::list<boost::shared_ptr<Sprite> > GetSpritesNear(
    boost::shared_ptr<Sprite>& sprite) const;

  void AddSprite(const boost::shared_ptr<Sprite>& s);
  const bool CanGrabSprite(const int x, const int y) const;
  const boost::shared_ptr<Sprite> GrabSprite(const int x, const int y);
  const bool IsPresent(const EnumCellType cellType) const;

  void RemoveEmigrants(
    std::list<std::pair<EnumLocation, boost::shared_ptr<Sprite> > >& emigrants);
  void AddMigrants(
    const std::list<std::pair<EnumLocation, boost::shared_ptr<Sprite> > >& immigrants);

  const int Count(const EnumCellType cellType) const;

  void ReplaceAll(
    const EnumCellType replaceWhat,
    const EnumCellType replaceWith);
  void ReplaceOne(
    const EnumCellType replaceWhat,
    const EnumCellType replaceWith
    );
  void RemoveOne(const EnumCellType cellType);

  void UpdateSimState(SimState& state) const;

  private:
  std::list<boost::shared_ptr<Sprite> > mSprites;

  struct SpriteMover : public std::unary_function<Sprite,void>
  {
    void operator() (boost::shared_ptr<Sprite>& s) const;
  };

  struct SpriteChanger : public std::unary_function<Sprite,void>
  {
    void operator() (boost::shared_ptr<Sprite>& s) const;
  };

  struct SpriteNear : public std::unary_function<Sprite,void>
  {
    SpriteNear(const boost::shared_ptr<Sprite>& sprite);
    const bool operator() (const boost::shared_ptr<Sprite>& sprite) const;
    const boost::shared_ptr<Sprite>& mSprite;
  };

  struct CellTypeFinder : public std::unary_function<Sprite,bool>
  {
    CellTypeFinder(const EnumCellType cellType);
    const bool operator() (const boost::shared_ptr<Sprite>& s) const;
    const EnumCellType mCellType;
  };

  //Emigrate = to move away (independent of location)
  struct SpriteWantsToEmigrate : public std::unary_function<Sprite,void>
  {
    SpriteWantsToEmigrate(const bool yesNo) : mYesNo(yesNo) {}
    const bool operator() (const boost::shared_ptr<Sprite>& sprite) const;
    const bool mYesNo;
  };

  //Immigrate = to move into (dependent of location)
  struct SpriteWantsToImmigrate : public std::unary_function<Sprite,void>
  {
    SpriteWantsToImmigrate(const EnumLocation location) : mLocation(location) {}
    const bool operator() (const std::pair<EnumLocation, boost::shared_ptr<Sprite> >& p) const;
    const EnumLocation mLocation;
  };

};
//---------------------------------------------------------------------------
struct BloodStream : public Location
{
  BloodStream();
  const EnumLocation GetLocation() const { return bloodStream; }
  void RespondToSimState();
};
//---------------------------------------------------------------------------
struct BoneMarrow : public Location
{
  const EnumLocation GetLocation() const { return boneMarrow; }
  void RespondToSimState();
};
//---------------------------------------------------------------------------
struct CellTissue : public Location
{
  CellTissue();
  const EnumLocation GetLocation() const { return cellTissue; }
  void RespondToSimState();
};
//---------------------------------------------------------------------------
struct LymphNode : public Location
{
  const EnumLocation GetLocation() const { return lymphNode; }
  void RespondToSimState();
};
//---------------------------------------------------------------------------




#endif
