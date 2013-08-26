//---------------------------------------------------------------------------
#include <algorithm>
#include <numeric>
#pragma hdrstop

#include "UnitLocation20080504.h"

//---------------------------------------------------------------------------
const bool Location::CanGrabSprite(
  const int x,
  const int y) const
{
  typedef std::vector<boost::shared_ptr<Sprite> >::const_iterator Iterator;
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
  typedef std::vector<boost::shared_ptr<Sprite> >::reverse_iterator Iterator;
  const Iterator j = mSprites.rend();
  for (Iterator i = mSprites.rbegin(); i!=j; ++i)
  {

    if ((*i)->CanGrab(x,y)==true)
    {
      std::swap( *i, mSprites.back() );
      boost::shared_ptr<Sprite> sprite = mSprites.back();
      mSprites.pop_back();
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
void Location::RemoveEmigrants(
  std::vector<std::pair<EnumLocation, boost::shared_ptr<Sprite> > >& emigrants)
{
  #ifndef NDEBUG
    const std::size_t oldSumSize = emigrants.size() + mSprites.size();
  #endif

  typedef std::vector<boost::shared_ptr<Sprite> >::iterator Iterator;
  for (Iterator i = mSprites.begin(); i!=mSprites.end(); ++i) //mSprites changes size!
  {
    const std::auto_ptr<EnumLocation> location = (*i)->WantsToMigrateTo();
    if (location.get() != 0)
    {
      emigrants.push_back( std::make_pair(*location.get(),*i) );
      //Overwrite the old value, without modifying the sequence of mSprites
      //(could not get the erase-remove idiom working on a single iterator)
      std::copy( i + 1, mSprites.end(), i);
      mSprites.pop_back(); //Remove the last duplicated sprite
      --i;
    }
  }

  #ifndef NDEBUG
    const std::size_t newSumSize = emigrants.size() + mSprites.size();
    assert(oldSumSize==newSumSize);
  #endif
}
//---------------------------------------------------------------------------
void Location::AddMigrants(
  std::vector<std::pair<EnumLocation, boost::shared_ptr<Sprite> > >& immigrants)
{
  #ifndef NDEBUG
    const std::size_t oldSumSize = immigrants.size() + mSprites.size();
  #endif

  typedef std::vector<std::pair<EnumLocation, boost::shared_ptr<Sprite> > >::iterator Iterator;

  for (Iterator i = immigrants.begin(); i!=immigrants.end(); ++i) //immigrants changes size!
  {
    if (i->first == this->GetLocation())
    {
      mSprites.push_back(i->second); //Copy only the immigrants to mSprites
      //Overwrite the old value, changes the sequence of immigrants
      *i = immigrants.back(); //Overwrite old immigrants
      immigrants.pop_back();  //Remove the last duplicated immigrants
      --i;
    }
  }

  #ifndef NDEBUG
    const std::size_t newSumSize = immigrants.size() + mSprites.size();
    assert(oldSumSize==newSumSize);
  #endif

}
//---------------------------------------------------------------------------
void Location::ReplaceOne(
  const EnumCellType replaceWhat,
  const EnumCellType replaceWith)
{
  assert(replaceWhat != replaceWith);

  typedef std::vector<boost::shared_ptr<Sprite> >::iterator Iterator;

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

  typedef std::vector<boost::shared_ptr<Sprite> >::iterator Iterator;
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
  typedef std::vector<boost::shared_ptr<Sprite> >::iterator Iterator;

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
  //(could not get the erase-remove idiom working on a single iterator)
  std::copy( randomIterator + 1, j, randomIterator);
  mSprites.pop_back();

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
const boost::shared_ptr<Sprite>& Location::GetSprite(const std::size_t i) const
{
  return mSprites[i];
}
//---------------------------------------------------------------------------
/*
const std::vector<boost::shared_ptr<Sprite> > Location::GetSpritesNear(
  boost::shared_ptr<Sprite>& sprite) const
{
  std::vector<boost::shared_ptr<Sprite> > v;

  typedef std::vector<boost::shared_ptr<Sprite> >::const_iterator Iterator;
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
    //For every sprite, find all sprites near
    typedef std::vector<boost::shared_ptr<Sprite> >::iterator Iterator;
    for (Iterator i = mSprites.begin(); i!=mSprites.end(); ++i)
    {
      assert(i >= mSprites.begin());
      assert(i < mSprites.end());
      assert( (*i).get() !=0);
      /*
      //Infected cell spawns viruses
      if ( (*i)->GetCellType() == cellInfected
        && (std::rand() >> 4) % 1000 == 0)
      {
        //Add viruses without using a for-loop ;-)
        this->AddSprite( ::GetSprite(virus, (*i)->GetX(), (*i)->GetY() ) );
        this->AddSprite( ::GetSprite(virus, (*i)->GetX(), (*i)->GetY() ) );
        this->AddSprite( ::GetSprite(virus, (*i)->GetX(), (*i)->GetY() ) );
        this->AddSprite( ::GetSprite(virus, (*i)->GetX(), (*i)->GetY() ) );
        this->AddSprite( ::GetSprite(virus, (*i)->GetX(), (*i)->GetY() ) );
        this->AddSprite( ::GetSprite(virus, (*i)->GetX(), (*i)->GetY() ) );
        this->AddSprite( ::GetSprite(virus, (*i)->GetX(), (*i)->GetY() ) );
        this->AddSprite( ::GetSprite(virus, (*i)->GetX(), (*i)->GetY() ) );
        this->AddSprite( ::GetSprite(virus, (*i)->GetX(), (*i)->GetY() ) );
        this->AddSprite( ::GetSprite(virus, (*i)->GetX(), (*i)->GetY() ) );
        //Remove infected cell
        std::copy( i + 1, mSprites.end(), i);
        mSprites.pop_back(); //Remove the last duplicated sprite
        --i;
        continue;
      }
      */
    }
  }

  //For every sprite, find all sprites near
  {
    typedef std::vector<boost::shared_ptr<Sprite> >::iterator Iterator;
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
          && (std::rand() >> 4) % 100 == 0 )
        {
          //Make healthy cell infected
          (*i) = ::GetSprite(cellInfected,(*i)->GetX(), (*i)->GetY() );
          //Remove virus
          std::copy( j + 1, mSprites.end(), j);
          mSprites.pop_back(); //Remove the last duplicated sprite
          --j;
          continue;
        }

        //Let macrophages without virus particles ingest viruses
        if ( (*i)->GetCellType() == macrophageWithoutVirusParticles
          && (*j)->GetCellType() == virus)
        {
          //Make macrophage without virus particles eat virus
          (*i) = ::GetSprite(macrophageWithVirusParticles,(*i)->GetX(), (*i)->GetY() );
          //Remove virus
          std::copy( j + 1, mSprites.end(), j);
          mSprites.pop_back(); //Remove the last duplicated sprite
          --j;
          continue;
        }

        //Let the macrophages and cytokines destroy the viruses
        if ( (*i)->GetCellType() == macrophageWithVirusParticles
          && (*j)->GetCellType() == virus
          && this->IsPresent(antibody) )
        {
          //Remove virus
          std::copy( j + 1, mSprites.end(), j);
          mSprites.pop_back(); //Remove the last duplicated sprite
          --j;
          continue;
        }

        //Activate B cell
        if ( (*i)->GetCellType() == cytokine
          && (*j)->GetCellType() == bCell )
        {
          (*i) = ::GetSprite(activatedBcell,(*i)->GetX(), (*i)->GetY() );
        }

        //Activate cytotoxic T cell
        if ( (*i)->GetCellType() == cytokine
          && (*j)->GetCellType() == cytotoxicTcell )
        {
          (*i) = ::GetSprite(activatedCytotoxicTcell,(*i)->GetX(), (*i)->GetY() );
        }

        if ( (*i)->GetCellType() == activatedCytotoxicTcell
          && (*j)->GetCellType() == cellInfected )
        {
          //Remove infected cell
          std::copy( j + 1, mSprites.end(), j);
          mSprites.pop_back(); //Remove the last duplicated sprite
          --j;
          continue;
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
  typedef std::vector<boost::shared_ptr<Sprite> >::const_iterator Iterator;
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
  //Activate T helper cells
  if ( this->IsPresent(macrophageWithVirusParticles)
    && this->IsPresent(tHelperCell))
  {
    this->ReplaceAll(tHelperCell,activatedThelperCell);
  }

  //Let T helper cells produce cytokines
  if (IsPresent(activatedThelperCell)
    && (std::rand() >> 4) % 100 == 0
    && this->Count(cytokine) < 5)
  {
    this->AddSprite(boost::shared_ptr<Sprite>(new SpriteCytokine(Sprite::maxx * 0.5,-32.0)));
  }

  if ( this->IsPresent(cytokine) )
  {
    //Activate B cells on cytokines
    if (this->IsPresent(bCell))
      this->ReplaceAll(bCell,activatedBcell);
    //Activate CT cells on cytokines
    if (this->IsPresent(cytotoxicTcell))
      this->ReplaceAll(cytotoxicTcell,activatedCytotoxicTcell);
  }

  //Let the B cells produce antibodies
  if (this->IsPresent(activatedBcell)
    && (std::rand() >> 4) % 100 == 0
    && this->Count(antibody) < 5)
  {
    this->AddSprite(boost::shared_ptr<Sprite>(new SpriteAntibody(Sprite::maxx * 0.5,-32.0)));
  }

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



#pragma package(smart_init)
