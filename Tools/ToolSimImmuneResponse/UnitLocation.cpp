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
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <boost/mpl/copy_if.hpp>
#pragma hdrstop

#include "UnitLocation.h"

//---------------------------------------------------------------------------
//copy_if was dropped from the standard library by accident.
namespace std
{
  template<typename In, typename Out, typename Pred>
  Out copy_if(In first, In last, Out res, Pred Pr)
  {
    while (first != last)
    {
      if (Pr(*first))
        *res++ = *first;
      ++first;
    }
    return res;
  }
}
//---------------------------------------------------------------------------
const bool Location::CanGrabSprite(
  const int x,
  const int y) const
{
  typedef std::list<boost::shared_ptr<Sprite> >::const_iterator Iterator;
  const Iterator j = mSprites.end();
  for (Iterator i = mSprites.begin(); i!=j; ++i)
  {
    if ((*i)->CanGrab(x,y)==true) return true;
  }
  return false;
}
//---------------------------------------------------------------------------
const boost::shared_ptr<Sprite> Location::GrabSprite(
  const int x,
  const int y)
{
  typedef std::list<boost::shared_ptr<Sprite> >::reverse_iterator Iterator;
  const Iterator j = mSprites.rend();
  for (Iterator i = mSprites.rbegin(); i!=j; ++i)
  {

    if ((*i)->CanGrab(x,y)==true)
    {
      boost::shared_ptr<Sprite> sprite(*i);
      mSprites.remove(*i); //Valid *i is not used anymore
      return sprite;
    }
  }
  assert(!"Should not get here");
  return boost::shared_ptr<Sprite>();
}
//---------------------------------------------------------------------------
void Location::AddSprite(const boost::shared_ptr<Sprite>& s)
{
  mSprites.push_back(s);
}
//---------------------------------------------------------------------------
//Those that want to go, must be added to emigrants
void Location::RemoveEmigrants(
  std::list<std::pair<EnumLocation, boost::shared_ptr<Sprite> > >& emigrants)
{

  //Get the leavers, add those to emigrants
  {
    std::list<boost::shared_ptr<Sprite> > leavers;

    //Get the leavers
    std::copy_if(
      mSprites.begin(),
      mSprites.end(),
      std::back_inserter(leavers),
      SpriteWantsToEmigrate(true));

    //Add the leavers to emigrants
    const Iterator j = leavers.end();
    for (Iterator i = leavers.begin(); i!=j; ++i)
    {
      const std::auto_ptr<EnumLocation> locationPtr = (*i)->WantsToMigrateTo();
      assert(locationPtr.get() != 0);
      const EnumLocation location = *(locationPtr).get();
      assert(&location != locationPtr.get()); //Assume copy
      emigrants.push_back( std::make_pair(location,*i) );

      assert(emigrants.back().first == bloodStream
          || emigrants.back().first == boneMarrow
          || emigrants.back().first == cellTissue
          || emigrants.back().first == lymphNode);

    }
  }

  {
    std::list<boost::shared_ptr<Sprite> > stayers;

    std::copy_if(
      mSprites.begin(),
      mSprites.end(),
      std::back_inserter(stayers),
      SpriteWantsToEmigrate(false));

    mSprites.swap(stayers);
  }
}
//---------------------------------------------------------------------------
void Location::AddMigrants(
  const std::list<std::pair<EnumLocation, boost::shared_ptr<Sprite> > >& immigrants)
{

  assert(this->GetLocation() == bloodStream
    || this->GetLocation() == boneMarrow
    || this->GetLocation() == cellTissue
    || this->GetLocation() == lymphNode);


  //Those that want to stay, must be added to mSprites
  const ConstPairIterator j = immigrants.end();
  for (ConstPairIterator i = immigrants.begin(); i!=j; ++i)
  {
    assert((*i).first == bloodStream
        || (*i).first == boneMarrow
        || (*i).first == cellTissue
        || (*i).first == lymphNode);

    if ( (*i).first == this->GetLocation())
      mSprites.push_back( (*i).second );
  }
}
//---------------------------------------------------------------------------
void Location::ReplaceOne(
  const EnumCellType replaceWhat,
  const EnumCellType replaceWith)
{
  assert(replaceWhat != replaceWith);

  typedef std::list<boost::shared_ptr<Sprite> >::iterator Iterator;

  std::vector<Iterator> iterators;

  const Iterator j = mSprites.end();

  Iterator i = std::find_if(mSprites.begin(), j, CellTypeFinder(replaceWhat));
  assert(i!=j && "Nothing to replace once found");

  while (i!=j)
  {
    iterators.push_back(i);
    ++i;
    if (i==j) break;
    i = std::find_if(i, j, CellTypeFinder(replaceWhat));
  }

  const Iterator randomIterator = iterators[ (std::rand() >> 4) % iterators.size() ];
  *randomIterator
    = ::GetSprite(
      replaceWith,
      (*randomIterator)->GetX(),
      (*randomIterator)->GetY() );
}
//---------------------------------------------------------------------------
void Location::ReplaceAll(
  const EnumCellType replaceWhat,
  const EnumCellType replaceWith)
{
  assert(replaceWhat != replaceWith);

  typedef std::list<boost::shared_ptr<Sprite> >::iterator Iterator;
  const Iterator j = mSprites.end();

  Iterator i = std::find_if(mSprites.begin(), j, CellTypeFinder(replaceWhat));
  assert(i!=j && "Nothing to replace found");

  while (i!=j)
  {
    *i = ::GetSprite(replaceWith, (*i)->GetX(), (*i)->GetY() );
    i = std::find_if(mSprites.begin(), mSprites.end(), CellTypeFinder(replaceWhat));
  }
}
//---------------------------------------------------------------------------
const bool Location::IsPresent(const EnumCellType cellType) const
{
  return (
    std::find_if(
      mSprites.begin(), mSprites.end(),
      CellTypeFinder(cellType) )
    != mSprites.end() );
}
//---------------------------------------------------------------------------
void Location::RemoveOne(const EnumCellType cellType)
{
  typedef std::list<boost::shared_ptr<Sprite> >::iterator Iterator;

  std::vector<Iterator> iterators;

  const Iterator j = mSprites.end();

  Iterator i = std::find_if(mSprites.begin(), j, CellTypeFinder(cellType));
  assert(i!=j && "Nothing to remove once found");

  while (i!=j)
  {
    iterators.push_back(i);
    ++i;
    if (i==j) break;
    i = std::find_if(i, j, CellTypeFinder(cellType));
  }

  const Iterator randomIterator = iterators[ (std::rand() >> 4) % iterators.size() ];

  //Overwrite the old value
  mSprites.remove(*randomIterator);

}
//---------------------------------------------------------------------------
const int Location::Count(const EnumCellType cellType) const
{
  return std::count_if(mSprites.begin(), mSprites.end(), CellTypeFinder(cellType));
}
//---------------------------------------------------------------------------
boost::shared_ptr<Sprite>& Location::GetSprite(const std::size_t i)
{
  //Avoid duplication in const and non-const member functions
  //From http://www.richelbilderbeek.nl/CppAvoidDuplicationInConstAndNonConstMemberFunctions.htm
  return const_cast<boost::shared_ptr<Sprite>& >(
    const_cast<const Location&>(*this).GetSprite(i)
  );
}
//---------------------------------------------------------------------------
/*
const boost::shared_ptr<Sprite>& Location::GetSprite(const std::size_t i) const
{
  return mSprites[i];
}
*/
//---------------------------------------------------------------------------
/*
const std::list<boost::shared_ptr<Sprite> > Location::GetSpritesNear(
  boost::shared_ptr<Sprite>& sprite) const
{
  std::list<boost::shared_ptr<Sprite> > v;

  typedef std::list<boost::shared_ptr<Sprite> >::const_iterator Iterator;
  const Iterator j = mSprites.end();

  for (Iterator i = mSprites.begin(); i!=j; ++i)
  {
    if (SpriteNear(*i)(*j)==true) v.push_back(*i);
  }
  return v;
}
*/
//---------------------------------------------------------------------------
void Location::MoveAllSprites()
{
  //Move all sprites
  std::for_each(mSprites.begin(), mSprites.end(), SpriteMover() );

  //Change all sprites
  {
    typedef std::list<boost::shared_ptr<Sprite> >::iterator Iterator;
    for (Iterator i = mSprites.begin(); i!=mSprites.end(); ++i)
    {
      //assert(i >= mSprites.begin());
      //assert(i < mSprites.end());
      assert( (*i).get() !=0);

      //Infected cell spawns viruses
      if ( (*i)->GetCellType() == cellInfected
        && (std::rand() >> 4) % 2000 == 0)
      {
        //Add viruses without using a for-loop ;-)
        this->AddSprite( ::GetSprite(virus, (*i)->GetX(), (*i)->GetY() ) );
        this->AddSprite( ::GetSprite(virus, (*i)->GetX(), (*i)->GetY() ) );
        this->AddSprite( ::GetSprite(virus, (*i)->GetX(), (*i)->GetY() ) );
        //Remove infected cell
        mSprites.remove(*i);
        i = mSprites.begin();
        continue;
      }

      //Let activated T helper cells produce cytokines in lymph node only
      if ((*i)->GetCellType() == activatedThelperCell
        && this->GetLocation() == lymphNode
        && (std::rand() >> 4) % 10 == 0
        && this->Count(cytokine) < 5)
      {
        this->AddSprite(::GetSprite(cytokine, (*i)->GetX(), (*i)->GetY() ) );
      }

      //Let the B cells produce antibodies in lymph node only
      if ((*i)->GetCellType() == activatedBcell
        && this->GetLocation() == lymphNode
        && (std::rand() >> 4) % 100 == 0
        && this->Count(antibody) < 5)
      {
        this->AddSprite(::GetSprite(antibody, (*i)->GetX(), (*i)->GetY() ) );
      }


    }
  }

  //For every sprite, find all sprites near
  {
    typedef std::list<boost::shared_ptr<Sprite> >::iterator Iterator;
    for (Iterator i = mSprites.begin(); i!=mSprites.end(); ++i)
    {
      assert(i!=mSprites.end());

      for (Iterator j = mSprites.begin(); j!=mSprites.end(); ++j)
      {
        if (i==j) continue;
        assert(i!=mSprites.end());
        assert(j!=mSprites.end());
        assert(i!=j);

        //Sprites must be near
        if (SpriteNear(*i)(*j)==false) continue;

        //Healthy cell gets infected by a virus
        if ( (*i)->GetCellType() == cellHealthy
          && (*j)->GetCellType() == virus
          && (std::rand() >> 4) % 500 == 0 )
        {
          //Make healthy cell infected
          (*i) = ::GetSprite(cellInfected,(*i)->GetX(), (*i)->GetY() );
          //Remove virus
          mSprites.remove(*j);
          j = mSprites.begin();
          continue;
        }

        //Let macrophages without virus particles ingest viruses
        if ( (*i)->GetCellType() == macrophageWithoutVirusParticles
          && this->GetLocation() == bloodStream
          && (*j)->GetCellType() == virus)
        {
          //Make macrophage without virus particles eat virus
          (*i) = ::GetSprite(macrophageWithVirusParticles,(*i)->GetX(), (*i)->GetY() );
          //Remove virus
          mSprites.remove(*j);
          j = mSprites.begin();
          continue;
        }

        //Let the macrophages and cytokines destroy the viruses
        if ( (*i)->GetCellType() == macrophageWithVirusParticles
          && (*j)->GetCellType() == virus
          && this->GetLocation() == bloodStream
          && this->IsPresent(antibody) )
        {
          //Remove virus
          mSprites.remove(*j);
          j = mSprites.begin();
          continue;
        }

        //Activate B cell
        if ( (*i)->GetCellType() == bCell
          && (*j)->GetCellType() == cytokine)
        {
          (*i) = ::GetSprite(activatedBcell,(*i)->GetX(), (*i)->GetY() );
        }

        //Activate cytotoxic T cell
        if ( (*i)->GetCellType() == cytotoxicTcell
          && (*j)->GetCellType() == cytokine)
        {
          (*i) = ::GetSprite(activatedCytotoxicTcell,(*i)->GetX(), (*i)->GetY() );
        }

        if ( (*i)->GetCellType() == activatedCytotoxicTcell
          && (*j)->GetCellType() == cellInfected )
        {
          //Remove infected cell
          mSprites.remove(*j);
          j = mSprites.begin();
          continue;
        }

        //Activate T helper cells by macrophages with virus particles
        if ( (*i)->GetCellType() == tHelperCell
          && (*j)->GetCellType() == macrophageWithVirusParticles )
        {
          (*i) = ::GetSprite(activatedThelperCell,(*i)->GetX(), (*i)->GetY() );
        }



      }
    }
  }
}
//---------------------------------------------------------------------------
void Location::ChangeAllSprites()
{
  std::for_each(mSprites.begin(), mSprites.end(), SpriteChanger() );
}
//---------------------------------------------------------------------------
void Location::UpdateSimState(SimState& state) const
{
  typedef std::list<boost::shared_ptr<Sprite> >::const_iterator Iterator;
  const EnumLocation location = this->GetLocation();
  const Iterator j = mSprites.end();
  for (Iterator i = mSprites.begin(); i!=j; ++i)
  {
    state.GetLocation(location).insert((*i)->GetCellType());
  }
}
//---------------------------------------------------------------------------
BloodStream::BloodStream()
{
  const int nViruses = 10;
  for (int i=0; i!=nViruses; ++i)
  {
    this->AddSprite( ::GetSprite(virus,std::rand() % 320, std::rand() % 224) );
  }
}
//---------------------------------------------------------------------------
void BloodStream::RespondToSimState()
{
  //Add viruses, except when there are antibodies and macrophages
  if (Count(virus) < 5
    && (std::rand() >> 4) % 100 == 0
    && this->IsPresent(antibody) == false
    && this->IsPresent(macrophageWithVirusParticles) == false
    && this->IsPresent(macrophageWithoutVirusParticles) == false
    )
  {
    this->AddSprite( ::GetSprite(virus,
      static_cast<double>((std::rand() % static_cast<int>(Sprite::maxx) + 64)) - 32.0, //X coordinat
      -32.0 ));     //Y coordinat
  }

  /*
  //Let macrophages ingest viruses
  if (this->IsPresent(virus)==true
    && this->IsPresent(macrophageWithoutVirusParticles)==true)
  {
    ReplaceAll(macrophageWithoutVirusParticles, macrophageWithVirusParticles);
  }
  */
  /*
  if ( this->IsPresent(cytokine) )
  {
    //Activate B cells on cytokines
    if (this->IsPresent(bCell))
      this->ReplaceAll(bCell,activatedBcell);
    //Activate CT cells on cytokines
    if (this->IsPresent(cytotoxicTcell))
      this->ReplaceAll(cytotoxicTcell,activatedCytotoxicTcell);
  }
  */
  /*
  //Let the macrophages and cytokines destroy the viruses
  if ( this->IsPresent(antibody)
    && this->IsPresent(virus)
    && this->IsPresent(macrophageWithVirusParticles)
    && (std::rand() >> 4) % 10 == 0)
  {
    this->RemoveOne(virus);
  }
  */
}
//---------------------------------------------------------------------------
void BoneMarrow::RespondToSimState()
{
  /*
  if ( this->IsPresent(cytokine) )
  {
    //Activate B cells on cytokines
    if (this->IsPresent(bCell))
      this->ReplaceAll(bCell,activatedBcell);
    //Activate CT cells on cytokines
    if (this->IsPresent(cytotoxicTcell))
      this->ReplaceAll(cytotoxicTcell,activatedCytotoxicTcell);
  }
  */
}
//---------------------------------------------------------------------------
CellTissue::CellTissue()
{
  for (int y=-1; y!=7; ++y) //7 = Number of rows (including -1 for above-screen)
  {
    for (int x=0; x!=10; ++x) //10 = Number of collumns
    {
      boost::shared_ptr<Sprite> sprite(
        new SpriteCellHealthy(
          static_cast<double>(x * 32),   //32 = Sprite width
          static_cast<double>(y * 32))); //32 = Sprite height
      this->AddSprite(sprite);
    }
  }
}
//---------------------------------------------------------------------------
void CellTissue::RespondToSimState()
{
  /*
  //Add viruses
  if (Count(virus) < 1
    && (std::rand() >> 4) % 100 == 0
    && this->IsPresent(activatedCytotoxicTcell) == false)
  {
    this->AddSprite(
      boost::shared_ptr<Sprite>(
        new SpriteVirus( //X coordinat
          static_cast<double>((std::rand() % static_cast<int>(Sprite::maxx) + 64)) - 32.0,
          -32.0 )));     //Y coordinat
  }
  */

  /*
  if ( (std::rand() >> 4) % 100 == 0
    && this->IsPresent(virus)==true
    && this->IsPresent(cellHealthy)==true )
  {
    this->ReplaceOne(cellHealthy,cellInfected);
  }
  */

  /*
  //Infected cell spawns viruses
  if ( (std::rand() >> 4) % 1000 == 0
    && this->IsPresent(cellInfected)==true )
  {
    this->ReplaceOne(cellInfected,virus);
  }
  */

  /*
  if ( this->IsPresent(cytokine) )
  {
    //Activate B cells on cytokines
    if (this->IsPresent(bCell))
      this->ReplaceAll(bCell,activatedBcell);
    //Activate CT cells on cytokines
    if (this->IsPresent(cytotoxicTcell))
      this->ReplaceAll(cytotoxicTcell,activatedCytotoxicTcell);
  }
  */
  /*
  //Let the cytotoxic T lymphocytes destroy the infected cells
  if ( this->IsPresent(cellInfected)
    && this->IsPresent(activatedCytotoxicTcell)
    && (std::rand() >> 4) % 10 == 0 )
  {
    this->RemoveOne(cellInfected);
  }
  */
  //Let the cytotoxic T lymphocytes destroy the viruses
  /*
  if ( this->IsPresent(virus)
    && this->IsPresent(activatedCytotoxicTcell)
    && (std::rand() >> 4) % 10 == 0 )
  {
    this->RemoveOne(virus);
  }
  */
}
//---------------------------------------------------------------------------
void LymphNode::RespondToSimState()
{
  /*
  //Activate T helper cells
  if ( this->IsPresent(macrophageWithVirusParticles)
    && this->IsPresent(tHelperCell))
  {
    this->ReplaceAll(tHelperCell,activatedThelperCell);
  }
  */
  /*
  //Let T helper cells produce cytokines
  if (IsPresent(activatedThelperCell)
    && (std::rand() >> 4) % 100 == 0
    && this->Count(cytokine) < 5)
  {
    this->AddSprite(boost::shared_ptr<Sprite>(new SpriteCytokine(Sprite::maxx * 0.5,-32.0)));
  }
  */

  /*
  if ( this->IsPresent(cytokine) )
  {
    //Activate B cells on cytokines
    if (this->IsPresent(bCell))
      this->ReplaceAll(bCell,activatedBcell);
    //Activate CT cells on cytokines
    if (this->IsPresent(cytotoxicTcell))
      this->ReplaceAll(cytotoxicTcell,activatedCytotoxicTcell);
  }
  */

  /*
  //Let the B cells produce antibodies
  if (this->IsPresent(activatedBcell)
    && (std::rand() >> 4) % 100 == 0
    && this->Count(antibody) < 5)
  {
    this->AddSprite(boost::shared_ptr<Sprite>(new SpriteAntibody(Sprite::maxx * 0.5,-32.0)));
  }
  */

}
//---------------------------------------------------------------------------
void Location::SpriteMover::operator() (boost::shared_ptr<Sprite>& s) const
{
  s->Move();
}
//---------------------------------------------------------------------------
void Location::SpriteChanger::operator() (boost::shared_ptr<Sprite>& s) const
{
  const std::auto_ptr<EnumCellType> cellType = s->WantsToChangeTo();
  if (cellType.get() == 0) return;

  boost::shared_ptr<Sprite> temp = ::GetSprite(*cellType.get(), s->GetX(), s->GetY());
  std::swap(s,temp);
}
//---------------------------------------------------------------------------
Location::CellTypeFinder::CellTypeFinder(const EnumCellType cellType)
  : mCellType(cellType)
{

}
//---------------------------------------------------------------------------
const bool Location::CellTypeFinder::operator() (
  const boost::shared_ptr<Sprite>& s) const
{
  return (s->GetCellType() == mCellType);
}
//---------------------------------------------------------------------------
Location::SpriteNear::SpriteNear(const boost::shared_ptr<Sprite>& sprite)
  : mSprite(sprite)
{
  assert(mSprite.get()!=0);
}
//---------------------------------------------------------------------------
const bool Location::SpriteNear::operator()(const boost::shared_ptr<Sprite>& sprite) const
{
  assert(sprite.get() != 0);
  const int x1 = static_cast<int>(mSprite->GetX());
  const int x2 = static_cast<int>(sprite->GetX());
  const int width1 = mSprite->GetWidth();
  const int width2 = sprite->GetWidth();
  const int y1 = static_cast<int>(mSprite->GetY());
  const int y2 = static_cast<int>(sprite->GetY());
  const int height1 = mSprite->GetHeight();
  const int height2 = sprite->GetHeight();

  return ( std::abs(x1-x2) < std::abs( (width1  + width2 ) / 2 )
        && std::abs(y1-y2) < std::abs( (height1 + height2) / 2 )
    );
}
//---------------------------------------------------------------------------
const bool Location::SpriteWantsToEmigrate::operator() (
  const boost::shared_ptr<Sprite>& sprite) const
{
  const bool wantsTo = sprite->WantsToMigrateTo().get() != 0;
  return (wantsTo == mYesNo);
};
//---------------------------------------------------------------------------
//Immigrate = to move into (dependent of location)
const bool Location::SpriteWantsToImmigrate::operator() (
  const std::pair<EnumLocation, boost::shared_ptr<Sprite> >& p) const
{
  return (p.first == mLocation);
}



#pragma package(smart_init)
