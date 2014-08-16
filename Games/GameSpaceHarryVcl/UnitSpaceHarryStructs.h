//---------------------------------------------------------------------------
/*
  Space Harry, a simple 'Space Harrier' clone
<<<<<<< HEAD
  Copyright (C) 2007  Richèl Bilderbeek
=======
  Copyright (C) 2007  Richel Bilderbeek
>>>>>>> develop

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
#ifndef UnitSpaceHarryStructsH
#define UnitSpaceHarryStructsH
//---------------------------------------------------------------------------
namespace Extctrls { class TImage; };

struct Bullet
{
  Bullet(
    const double anyX = 0.0,
    const double anyY = 0.0,
    const double anyZ = 0.0,
    const double anyDx = 0.0,
    const double anyDy = 0.0,
    const double anyDz = 0.0,
    const Extctrls::TImage * anyImage = 0)
  : x(anyX), y(anyY), z(anyZ), dX(anyDx), dY(anyDy), dZ(anyDz), image(anyImage) {}
  double x,y,z,dX,dY,dZ;
  const Extctrls::TImage * image;
};

bool operator<(const Bullet& b1, const Bullet& b2) { return b1.z < b2.z; }
//---------------------------------------------------------------------------
struct Enemy
{
  Enemy(
    const double anyX = 0.0,
    const double anyY = 0.0,
    const double anyZ = 0.0,
    const int anyNhitpoints = 1,
    const Extctrls::TImage * anyImage = 0)
  : x(anyX), y(anyY), z(anyZ),
    nHitpoints(anyNhitpoints),
    image(anyImage) {}
  double x,y,z;
  int nHitpoints;
  const Extctrls::TImage * image;
};
//---------------------------------------------------------------------------
struct Collision
{
  Collision(
    const double anyX = 0.0,
    const double anyY = 0.0,
    const double anyZ = 0.0,
    const int anyTimeLength = 0.0,
    const Extctrls::TImage * anyImage = 0)
  : x(anyX), y(anyY), z(anyZ),
    image(anyImage), timeLength(anyTimeLength), nTicks(0) {}
  double x,y,z;
  int timeLength; //Time steps to self destruct
  int nTicks; //Ticks
  const Extctrls::TImage * image;
};
//---------------------------------------------------------------------------
struct Sprite
{
  Sprite(
    const double anyX = 0.0,
    const double anyY = 0.0,
    const double anyZ = 0.0,
    const Extctrls::TImage * anyImage = 0)
  : x(anyX), y(anyY), z(anyZ), image(anyImage) {}
  double x,y,z;
  const Extctrls::TImage * image;
};

bool operator<(const Sprite& b1, const Sprite& b2) { return b1.z > b2.z; }
//---------------------------------------------------------------------------

#endif
