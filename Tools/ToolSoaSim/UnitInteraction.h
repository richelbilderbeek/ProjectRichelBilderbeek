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
#ifndef UnitInteractionH
#define UnitInteractionH
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
struct Person;
//---------------------------------------------------------------------------
struct Interaction
{
  enum InteractionState
  {
    aTalksBlistens,
    bTalksAlistens,
    aProposeSafe,
    bAgreesSafe,
    aAndBhaveSafeSex,
    bDisagreesSafe,
    aProposeUnsafe,
    bAgreesUnsafe,
    aAndBhaveUnsafeSex,
    bDisagreesUnsafe,
    aAndBleave
  } mInteraction;

  boost::shared_ptr<Person> mA;
  boost::shared_ptr<Person> mB;

  Interaction(boost::shared_ptr<Person> a, boost::shared_ptr<Person> b);
  void DoInteraction();
};
//---------------------------------------------------------------------------
const double GetRandomUniform();
//---------------------------------------------------------------------------

#endif
