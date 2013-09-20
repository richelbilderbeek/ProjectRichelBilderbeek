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
#ifndef UnitPersonH
#define UnitPersonH
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
namespace Extctrls
{
  struct TImage;
};
//---------------------------------------------------------------------------
struct Person
{
  double x;
  double y;
  double direction;
  bool isInfected;
  const double pProposeSafe;
  const double pAgreeSafe;
  const double pAgreeUnsafe;
  Extctrls::TImage * const image;
  Person(
    const double anyX,
    const double anyY,
    const double anyPproposeSafe,
    const double anyPagreeSafe,
    const double anyPagreeUnsafe,
    Extctrls::TImage * const anyImage
  );
  bool ProposeSafe() const;
  bool AgreeSafe() const;
  bool AgreeUnsafe() const;
};
//---------------------------------------------------------------------------
const double GetRandomUniform();
//---------------------------------------------------------------------------


#endif
