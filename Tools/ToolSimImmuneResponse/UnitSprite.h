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
#ifndef UnitSpriteH
#define UnitSpriteH
//---------------------------------------------------------------------------
#include "UnitEnum.h"
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
namespace Extctrls{ struct TImage; };
//---------------------------------------------------------------------------
struct Sprite : public boost::noncopyable
{
  Sprite(const double x, const double y) : mX(x), mY(y) { }

  virtual const EnumCellType GetCellType() const = 0;
  virtual const Extctrls::TImage * const GetImage() const = 0;
  virtual const bool CanGrab(const int x, const int y) const;

  virtual void Move();
  void Move(const double dx, const double dy);

  virtual const std::auto_ptr<EnumLocation> WantsToMigrateTo() const;
  virtual const std::auto_ptr<EnumCellType> WantsToChangeTo() const;

  const int GetWidth() const;
  const int GetHeight() const;
  const double GetX() const { return mX; }
  const double GetY() const { return mY; }
  void SetX(const double x) { mX = x; }
  void SetY(const double y) { mY = y; }

  static double maxx;
  static double maxy;
  static double speed;

  private:

  double mX;
  double mY;
};
//---------------------------------------------------------------------------
struct SpriteActiveCell : public Sprite
{
  SpriteActiveCell(const double x, const double y);
  void Move();
  bool mGoLeft;
};
//---------------------------------------------------------------------------
struct SpriteActivatedBcell : public SpriteActiveCell
{
  SpriteActivatedBcell(const double x, const double y) : SpriteActiveCell(x,y) {}

  const EnumCellType GetCellType() const { return activatedBcell; }
  const Extctrls::TImage * const GetImage() const { return mImage; }

  static void SetImage(Extctrls::TImage * image) { mImage = image; }

  private:
  static Extctrls::TImage * mImage;
};
//---------------------------------------------------------------------------
struct SpriteActivatedCytotoxicTcell : public SpriteActiveCell
{
  SpriteActivatedCytotoxicTcell(const double x, const double y) : SpriteActiveCell(x,y) {}
  const EnumCellType GetCellType() const { return activatedCytotoxicTcell; }
  const Extctrls::TImage * const GetImage() const { return mImage; }

  static void SetImage(Extctrls::TImage * image) { mImage = image; }

  private:
  static Extctrls::TImage * mImage;
};
//---------------------------------------------------------------------------
struct SpriteActivatedThelperCell : public SpriteActiveCell
{
  SpriteActivatedThelperCell(const double x, const double y) : SpriteActiveCell(x,y) {}
  const EnumCellType GetCellType() const { return activatedThelperCell; }
  const Extctrls::TImage * const GetImage() const { return mImage; }

  static void SetImage(Extctrls::TImage * image) { mImage = image; }

  private:
  static Extctrls::TImage * mImage;
};
//---------------------------------------------------------------------------
struct SpriteAntibody : public Sprite
{
  SpriteAntibody(const double x, const double y) : Sprite(x,y) {}
  const EnumCellType GetCellType() const { return antibody; }
  const Extctrls::TImage * const GetImage() const { return mImage; }
  const bool CanGrab(const int x, const int y) const { return false; }

  const std::auto_ptr<EnumLocation> WantsToMigrateTo() const;

  static void SetImage(Extctrls::TImage * image) { mImage = image; }

  private:
  static Extctrls::TImage * mImage;
};
//---------------------------------------------------------------------------
struct SpriteBcell : public Sprite
{
  SpriteBcell(const double x, const double y) : Sprite(x,y) {}
  const EnumCellType GetCellType() const { return bCell; }
  const Extctrls::TImage * const GetImage() const { return mImage; }

  static void SetImage(Extctrls::TImage * image) { mImage = image; }

  private:
  static Extctrls::TImage * mImage;
};
//---------------------------------------------------------------------------
struct SpriteCellInfected : public Sprite
{
  SpriteCellInfected(const double x, const double y) : Sprite(x,y) {}
  const EnumCellType GetCellType() const { return cellInfected; }
  const Extctrls::TImage * const GetImage() const { return mImage; }
  const bool CanGrab(const int x, const int y) const { return false; }
  void Move();

  static void SetImage(Extctrls::TImage * image) { mImage = image; }

  const std::auto_ptr<EnumCellType> WantsToChangeTo() const;

  private:
  static Extctrls::TImage * mImage;
};
//---------------------------------------------------------------------------
struct SpriteCellHealthy : public Sprite
{
  SpriteCellHealthy(const double x, const double y) : Sprite(x,y) {}
  const EnumCellType GetCellType() const { return cellHealthy; }
  const Extctrls::TImage * const GetImage() const { return mImage; }
  const bool CanGrab(const int x, const int y) const { return false; }
  void Move();

  static void SetImage(Extctrls::TImage * image) { mImage = image; }

  private:
  static Extctrls::TImage * mImage;
};
//---------------------------------------------------------------------------
struct SpriteCytokine : public Sprite
{
  SpriteCytokine(const double x, const double y) : Sprite(x,y) {}
  const EnumCellType GetCellType() const { return cytokine; }
  const Extctrls::TImage * const GetImage() const { return mImage; }
  const bool CanGrab(const int x, const int y) const { return false; }
  const std::auto_ptr<EnumLocation> WantsToMigrateTo() const;

  static void SetImage(Extctrls::TImage * image) { mImage = image; }

  private:
  static Extctrls::TImage * mImage;
};
//---------------------------------------------------------------------------
struct SpriteCytotoxicTcell : public Sprite
{
  SpriteCytotoxicTcell(const double x, const double y) : Sprite(x,y) {}
  const EnumCellType GetCellType() const { return cytotoxicTcell; }
  const Extctrls::TImage * const GetImage() const { return mImage; }

  static void SetImage(Extctrls::TImage * image) { mImage = image; }

  private:
  static Extctrls::TImage * mImage;
};
//---------------------------------------------------------------------------
struct SpriteMacrophageWithoutVirusParticles : public SpriteActiveCell
{
  SpriteMacrophageWithoutVirusParticles(const double x, const double y) : SpriteActiveCell(x,y) {}
  const EnumCellType GetCellType() const { return macrophageWithoutVirusParticles; }
  const Extctrls::TImage * const GetImage() const { return mImage; }

  static void SetImage(Extctrls::TImage * image) { mImage = image; }

  private:
  static Extctrls::TImage * mImage;
};
//---------------------------------------------------------------------------
struct SpriteMacrophageWithVirusParticles : public SpriteActiveCell
{
  SpriteMacrophageWithVirusParticles(const double x, const double y) : SpriteActiveCell(x,y) {}
  const EnumCellType GetCellType() const { return macrophageWithVirusParticles; }
  const Extctrls::TImage * const GetImage() const { return mImage; }

  static void SetImage(Extctrls::TImage * image) { mImage = image; }

  private:
  static Extctrls::TImage * mImage;

  bool mGoLeft;
};
//---------------------------------------------------------------------------
struct SpriteThelperCell : public Sprite
{
  SpriteThelperCell(const double x, const double y) : Sprite(x,y) {}
  const EnumCellType GetCellType() const { return tHelperCell; }
  const Extctrls::TImage * const GetImage() const { return mImage; }

  static void SetImage(Extctrls::TImage * image) { mImage = image; }

  private:
  static Extctrls::TImage * mImage;
};
//---------------------------------------------------------------------------
struct SpriteVirus : public Sprite
{
  SpriteVirus(const double x, const double y) : Sprite(x,y) {}
  const EnumCellType GetCellType() const { return virus; }
  const Extctrls::TImage * const GetImage() const { return mImage; }
  const bool CanGrab(const int x, const int y) const { return false; }
  const std::auto_ptr<EnumLocation> WantsToMigrateTo() const;

  static void SetImage(Extctrls::TImage * image) { mImage = image; }

  private:
  static Extctrls::TImage * mImage;
};
//---------------------------------------------------------------------------
const boost::shared_ptr<Sprite> GetSprite(
  const EnumCellType& cellType, const double x, const double y);
//---------------------------------------------------------------------------
const double GetRandomUniform();
//---------------------------------------------------------------------------


#endif
