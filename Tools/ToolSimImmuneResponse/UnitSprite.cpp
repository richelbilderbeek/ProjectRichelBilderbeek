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
#include <algorithm>
#include <cassert>
#include <memory>
#include <stdexcept>
#include <ExtCtrls.hpp>
#pragma hdrstop

#include "UnitSprite.h"

//---------------------------------------------------------------------------
double Sprite::maxx  = 0.0;
double Sprite::maxy  = 0.0;
double Sprite::speed = 1.0;
Extctrls::TImage * SpriteActivatedBcell::mImage = 0;
Extctrls::TImage * SpriteActivatedCytotoxicTcell::mImage = 0;
Extctrls::TImage * SpriteActivatedThelperCell::mImage = 0;
Extctrls::TImage * SpriteAntibody::mImage = 0;
Extctrls::TImage * SpriteBcell::mImage = 0;
Extctrls::TImage * SpriteCellInfected::mImage = 0;
Extctrls::TImage * SpriteCellHealthy::mImage = 0;
Extctrls::TImage * SpriteCytokine::mImage = 0;
Extctrls::TImage * SpriteCytotoxicTcell::mImage = 0;
Extctrls::TImage * SpriteMacrophageWithoutVirusParticles::mImage = 0;
Extctrls::TImage * SpriteMacrophageWithVirusParticles::mImage = 0;
Extctrls::TImage * SpriteThelperCell::mImage = 0;
Extctrls::TImage * SpriteVirus::mImage = 0;
//---------------------------------------------------------------------------
const int Sprite::GetWidth() const
{
  assert(this->GetImage()!=0);
  return this->GetImage()->Picture->Bitmap->Width;
}
//---------------------------------------------------------------------------
const int Sprite::GetHeight() const
{
  assert(this->GetImage()!=0);
  return GetImage()->Picture->Bitmap->Height;
}
//---------------------------------------------------------------------------
const bool Sprite::CanGrab(const int x, const int y) const
{
  if ( x <  mX
    || y <  mY
    || x >= mX + GetWidth()
    || y >= mY + GetHeight()
   )
    return false;
  else
    return true;
}
//---------------------------------------------------------------------------
void Sprite::Move()
{
  Move( (GetRandomUniform() * 2.0 * speed) - speed, (GetRandomUniform() * speed) );
}
//---------------------------------------------------------------------------
void Sprite::Move(const double dx, const double dy)
{
  mX+=dx;
  mY+=dy;
  if (mX + GetWidth() > maxx) mX -= speed;
  else if (mX < 0) mX += speed;
  if (mY > maxy)
  mY = -GetHeight()-2.0; //-2.0 so it can be detected before
                         //actually appearing on screen
}
//---------------------------------------------------------------------------
const std::auto_ptr<EnumLocation> Sprite::WantsToMigrateTo() const
{
  return std::auto_ptr<EnumLocation>();
}
//---------------------------------------------------------------------------
const std::auto_ptr<EnumCellType> Sprite::WantsToChangeTo() const
{
  return std::auto_ptr<EnumCellType>();
}
//---------------------------------------------------------------------------
SpriteActiveCell::SpriteActiveCell(
  const double x, const double y)
  : Sprite(x,y),
  mGoLeft( (std::rand() >> 4 ) % 2 == 0)
{

}
//---------------------------------------------------------------------------
void SpriteActiveCell::Move()
{
  const double dx = GetRandomUniform() * speed * 2.0 * (mGoLeft == true ? 1.0 : -1.0);
  const double dy = GetRandomUniform() * speed * 2.0;

  double x = GetX() + dx;
  double y = GetY() + dy;

  if      (x + GetWidth() > maxx) { x -= speed; mGoLeft = false; }
  else if (x              < 0   ) { x += speed; mGoLeft = true; }
  if (y > maxy)
  y = -GetHeight()-2.0; //-2.0 so it can be detected before
                         //actually appearing on screen
  SetX(x);
  SetY(y);
}
//---------------------------------------------------------------------------
const std::auto_ptr<EnumLocation> SpriteAntibody::WantsToMigrateTo() const
{
  EnumLocation * location = 0;

  if (GetY() < -GetHeight())
  {
    switch( (std::rand() >> 4) % 3)
    {
      case 0: location = new EnumLocation(bloodStream); break;
      //case 1: location = new EnumLocation(boneMarrow ); break;
      case 1: location = new EnumLocation(cellTissue ); break;
      case 2: location = new EnumLocation(lymphNode  ); break;
      default:
        assert(!"Should not get here");
        throw std::logic_error("Unknown location");
    }
  }
  return std::auto_ptr<EnumLocation>(location);
}
//---------------------------------------------------------------------------
void SpriteCellHealthy::Move()
{
  Sprite::Move(0.0,speed/10.0);
}
//---------------------------------------------------------------------------
void SpriteCellInfected::Move()
{
  Sprite::Move(0.0,speed/10.0);
}
//---------------------------------------------------------------------------
const std::auto_ptr<EnumCellType> SpriteCellInfected::WantsToChangeTo() const
{
  EnumCellType * cellType = 0;

  if (GetY() < -GetHeight())
  {
    cellType = new EnumCellType(cellHealthy);
  }

  return std::auto_ptr<EnumCellType>(cellType);
}
//---------------------------------------------------------------------------
const std::auto_ptr<EnumLocation> SpriteCytokine::WantsToMigrateTo() const
{
  EnumLocation * location = 0;

  if (GetY() < -GetHeight())
  {
    switch( (std::rand() >> 4) % 3)
    {
      case 0: location = new EnumLocation(bloodStream); break;
      //case 1: location = new EnumLocation(boneMarrow ); break;
      case 1: location = new EnumLocation(cellTissue ); break;
      case 2: location = new EnumLocation(lymphNode  ); break;
      default:
        assert(!"Should not get here");
        throw std::logic_error("Unknown location");
    }
  }
  return std::auto_ptr<EnumLocation>(location);
}
//---------------------------------------------------------------------------
const std::auto_ptr<EnumLocation> SpriteVirus::WantsToMigrateTo() const
{
  EnumLocation * location = 0;

  if (GetY() < -GetHeight())
  {
    switch( (std::rand() >> 4) % 2)
    {
      case 0: location = new EnumLocation(bloodStream); break;
      case 1: location = new EnumLocation(cellTissue ); break;
      default:
        assert(!"Should not get here");
        throw std::logic_error("Unknown location");
    }
  }
  return std::auto_ptr<EnumLocation>(location);
}
//---------------------------------------------------------------------------
const boost::shared_ptr<Sprite> GetSprite(
  const EnumCellType& cellType, const double x, const double y)
{
  switch (cellType)
  {
    case activatedBcell:
      return boost::shared_ptr<Sprite>(new SpriteActivatedBcell(x,y));
    case activatedCytotoxicTcell:
      return boost::shared_ptr<Sprite>(new SpriteActivatedCytotoxicTcell(x,y));
    case activatedThelperCell:
      return boost::shared_ptr<Sprite>(new SpriteActivatedThelperCell(x,y));
    case antibody:
      return boost::shared_ptr<Sprite>(new SpriteAntibody(x,y));
    case bCell:
      return boost::shared_ptr<Sprite>(new SpriteBcell(x,y));
    case cellHealthy:
      return boost::shared_ptr<Sprite>(new SpriteCellHealthy(x,y));
    case cellInfected:
      return boost::shared_ptr<Sprite>(new SpriteCellInfected(x,y));
    case cytokine:
      return boost::shared_ptr<Sprite>(new SpriteCytokine(x,y));
    case cytotoxicTcell:
      return boost::shared_ptr<Sprite>(new SpriteCytotoxicTcell(x,y));
    case macrophageWithoutVirusParticles:
      return boost::shared_ptr<Sprite>(new SpriteMacrophageWithoutVirusParticles(x,y));
    case macrophageWithVirusParticles:
      return boost::shared_ptr<Sprite>(new SpriteMacrophageWithVirusParticles(x,y));
    case tHelperCell:
      return boost::shared_ptr<Sprite>(new SpriteThelperCell(x,y));
    case virus:
      return boost::shared_ptr<Sprite>(new SpriteVirus(x,y));
  }
  assert(!"Should not get here");
  return boost::shared_ptr<Sprite>();
}
//---------------------------------------------------------------------------
//From htpp://www.richelbilderbeek.nl/CppGetRandomUniform.htm
const double GetRandomUniform()
{
  return static_cast<double>(std::rand())/static_cast<double>(RAND_MAX);
}
//---------------------------------------------------------------------------






#pragma package(smart_init)
