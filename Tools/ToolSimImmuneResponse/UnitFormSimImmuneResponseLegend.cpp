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
#include <cassert>   //For assert
#include <cmath>     //For std::sqrt
#include <algorithm> //For std::min
#include <boost/lexical_cast.hpp>
#include <stdexcept>
#include <vcl.h>
#include "UnitSprite.h"
#pragma hdrstop

#include "UnitFormSimImmuneResponseLegend.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSimImmuneResponseLegend *FormSimImmuneResponseLegend;
//---------------------------------------------------------------------------
__fastcall TFormSimImmuneResponseLegend::TFormSimImmuneResponseLegend(TComponent* Owner)
  : TForm(Owner)
{
  SpriteActivatedBcell::SetImage(ImageActivatedBcell);
  SpriteActivatedCytotoxicTcell::SetImage(ImageActivatedCytotoxicTcell);
  SpriteActivatedThelperCell::SetImage(ImageActivatedThelperCell);
  SpriteAntibody::SetImage(ImageAntibody);
  SpriteBcell::SetImage(ImageBcell);
  SpriteCellInfected::SetImage(ImageCellInfected);
  SpriteCellHealthy::SetImage(ImageCellHealthy);
  SpriteCytokine::SetImage(ImageCytokine);
  SpriteCytotoxicTcell::SetImage(ImageCytotoxicTcell);
  SpriteMacrophageWithoutVirusParticles::SetImage(ImageMacrophageWithoutVirusParticles);
  SpriteMacrophageWithVirusParticles::SetImage(ImageMacrophageWithVirusParticles);
  SpriteThelperCell::SetImage(ImageThelperCell);
  SpriteVirus::SetImage(ImageVirus);
}
//---------------------------------------------------------------------------
const TImage * const TFormSimImmuneResponseLegend::ToImage(
  const EnumCellType t) const
{
  switch(t)
  {
    case activatedBcell:                  return ImageActivatedBcell;
    case activatedCytotoxicTcell:         return ImageActivatedCytotoxicTcell;
    case activatedThelperCell:            return ImageActivatedThelperCell;
    case antibody:                        return ImageAntibody;
    case bCell:                           return ImageBcell;
    case cellInfected:                    return ImageCellInfected;
    case cellHealthy:                     return ImageCellHealthy;
    case cytokine:                        return ImageCytokine;
    case cytotoxicTcell:                  return ImageCytotoxicTcell;
    case tHelperCell:                     return ImageThelperCell;
    case macrophageWithVirusParticles:    return ImageMacrophageWithVirusParticles;
    case macrophageWithoutVirusParticles: return ImageMacrophageWithoutVirusParticles;
    case virus:                           return ImageVirus;
  }
  assert(!"Should not get here");
  throw std::domain_error("Unknown cell type " + CellTypeToString(t));
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppDrawLymphocyte.htm
void DrawLymphocyte(
  TImage * const image,
  const unsigned char rMax,
  const unsigned char gMax,
  const unsigned char bMax)
{
  assert(image!=0);
  const int width  = image->Picture->Bitmap->Width;
  const int height = image->Picture->Bitmap->Height;
  const double midX = static_cast<double>(width ) / 2.0;
  const double midY = static_cast<double>(height) / 2.0;
  const double maxDist = std::min(midX,midY); //Distance to end
  const double edgeDist = maxDist * 0.7; //Distance to edge

  for (int y=0; y!=height; ++y)
  {
    unsigned char * const line
      = static_cast<unsigned char *>(image->Picture->Bitmap->ScanLine[y]);
    const double yD = static_cast<double>(y);
    for (int x=0; x!=width; ++x)
    {
      const double xD = static_cast<double>(x);
      const double dist = std::sqrt( ((xD - midX) * (xD - midX)) + ((yD - midY) * (yD - midY)) );
      if (dist <= edgeDist)
      {
        const double relDist = dist / edgeDist;
        const int r = (0.5 + (0.5 * relDist)) * static_cast<double>(rMax);
        const int g = (0.5 + (0.5 * relDist)) * static_cast<double>(gMax);
        const int b = (0.5 + (0.5 * relDist)) * static_cast<double>(bMax);
        assert( r >= 0);
        assert( r < 256);
        assert( g >= 0);
        assert( g < 256);
        assert( b >= 0);
        assert( b < 256);
        line[x*3+2] = (r == 0 ? 1 : r); //Never use a zero for red
        line[x*3+1] = (g == 0 ? 1 : g); //Never use a zero for green
        line[x*3+0] = (b == 0 ? 1 : b); //Never use a zero for blue
      }
      else if (dist <= maxDist)
      {
        const double relDist = (dist - edgeDist) / (maxDist - edgeDist);
        const int r = (0.5 + (0.5 * (1.0 - relDist))) * static_cast<double>(rMax);
        const int g = (0.5 + (0.5 * (1.0 - relDist))) * static_cast<double>(gMax);
        const int b = (0.5 + (0.5 * (1.0 - relDist))) * static_cast<double>(bMax);
        assert( r >= 0);
        assert( r < 256);
        assert( g >= 0);
        assert( g < 256);
        assert( b >= 0);
        assert( b < 256);
        line[x*3+2] = (r == 0 ? 1 : r); //Never use a zero for red
        line[x*3+1] = (g == 0 ? 1 : g); //Never use a zero for green
        line[x*3+0] = (b == 0 ? 1 : b); //Never use a zero for blue
      }
      else
      {
        line[x*3+2] = 0;
        line[x*3+1] = 0;
        line[x*3+0] = 0;
      }
    }
  }
}
//---------------------------------------------------------------------------
