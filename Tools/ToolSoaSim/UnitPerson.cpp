//---------------------------------------------------------------------------
/*
  SoaSim, a simulator of sexually transmitted diseases
  Copyright (C) 2007  Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#pragma hdrstop

#include "UnitPerson.h"

#include <cmath>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
Person::Person(
  const double anyX,
  const double anyY,
  const double anyPproposeSafe,
  const double anyPagreeSafe,
  const double anyPagreeUnsafe,
  Extctrls::TImage * const anyImage
  )
  : x(anyX), y(anyY),
    pProposeSafe(anyPproposeSafe),
    pAgreeSafe(anyPagreeSafe),
    pAgreeUnsafe(anyPagreeUnsafe),
    image(anyImage),
    isInfected(false),
    direction( M_PI * 2.0 * GetRandomUniform() )
{

}
//---------------------------------------------------------------------------
bool Person::ProposeSafe() const
{
  if (GetRandomUniform() < pProposeSafe) return true;
  return false;
}
//---------------------------------------------------------------------------
bool Person::AgreeSafe() const
{
  if (GetRandomUniform() < pAgreeSafe) return true;
  return false;
}
//---------------------------------------------------------------------------
bool Person::AgreeUnsafe() const
{
  if (GetRandomUniform() < pAgreeUnsafe) return true;
  return false;
}
//---------------------------------------------------------------------------
//From htpp://www.richelbilderbeek.nl/CppGetRandomUniform.htm
const double GetRandomUniform()
{
  return static_cast<double>(std::rand())/static_cast<double>(RAND_MAX);
}
//---------------------------------------------------------------------------

#pragma package(smart_init)


