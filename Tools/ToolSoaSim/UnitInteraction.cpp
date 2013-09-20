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
#include "UnitPerson.h"

#pragma hdrstop

#include "UnitInteraction.h"

//---------------------------------------------------------------------------
Interaction::Interaction(boost::shared_ptr<Person> a, boost::shared_ptr<Person> b)
  : mA(a), mB(b), mInteraction(aTalksBlistens)
{

}
//---------------------------------------------------------------------------
void Interaction::DoInteraction()
{
  switch(mInteraction)
  {
    case aTalksBlistens:
      //Conversation
      if (std::rand() % 2 == 0)
      { mInteraction = bTalksAlistens; return; }
      //Propose sex
      if (std::rand() % 2 == 0)
      {
        if (mA->ProposeSafe() == true)
        { mInteraction = aProposeSafe; return; }
        else
        { mInteraction = aProposeUnsafe; return; }
      }
      break;
    case bTalksAlistens:
      //Conversation
      if (std::rand() % 2 == 0)
      { mInteraction = aTalksBlistens; return; }
      break;
    case aProposeSafe:
      if (mB->AgreeSafe() == true)
      { mInteraction = bAgreesSafe; return; }
      else
      { mInteraction = bDisagreesSafe; return; }
    case bAgreesSafe:
      mInteraction = aAndBhaveSafeSex;
      break;
    case aAndBhaveSafeSex:
      mInteraction = aAndBleave;
      break;
    case bDisagreesSafe:
      mInteraction = aAndBleave;
      break;
    case aProposeUnsafe:
      if (mB->AgreeUnsafe() == true)
      { mInteraction = bAgreesUnsafe; return; }
      else
      { mInteraction = bDisagreesUnsafe; return; }
    case bAgreesUnsafe:
      mInteraction = aAndBhaveUnsafeSex;
      break;
    case aAndBhaveUnsafeSex:
      mInteraction = aAndBleave;
      //If one is infected, make them both infected
      if (mA->isInfected == true || mB->isInfected == true)
      {
        mA->isInfected = true;
        mB->isInfected = true;
      }
      break;
    case bDisagreesUnsafe:
      mInteraction = aAndBleave;
      break;
    case aAndBleave:
      assert(!"Should not get here."
        && !"This couple should have been taken out of the interaction vector");
      break;
  }
}
//---------------------------------------------------------------------------
//From htpp://www.richelbilderbeek.nl/CppGetRandomUniform.htm
const double GetRandomUniform()
{
  return static_cast<double>(std::rand())/static_cast<double>(RAND_MAX);
}
//---------------------------------------------------------------------------

#pragma package(smart_init)
