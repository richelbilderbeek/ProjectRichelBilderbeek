/*
  SimBrainiac, a simulation of Brainiacs interacting
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

#pragma hdrstop

#include "UnitSimBrainiac.h"

//---------------------------------------------------------------------------
std::vector<Brainiac> GetBrainiacs(
  const int nBrainiacs,
  const int nCorrectAnswerLevels,
  const int nHasQuestionLevels)
{
  assert(nBrainiacs > 0);
  assert(nCorrectAnswerLevels > 0);
  assert(nHasQuestionLevels > 0);

  std::vector<Brainiac> brainiacs;
  brainiacs.reserve(nBrainiacs);

  const double dCorrectAnswer = 1.0 / static_cast<double>(nCorrectAnswerLevels + 1);
  const double dHasQuestion   = 1.0 / static_cast<double>(nHasQuestionLevels   + 1);

  for (int i=0; i!=nBrainiacs; ++i)
  {
    const int correctAnswerLevel = std::rand() % nCorrectAnswerLevels;
    const int hasQuestionLevel   = std::rand() % nHasQuestionLevels;
    const double pCorrectAnswer =
      dCorrectAnswer
      + (static_cast<double>(correctAnswerLevel) * dCorrectAnswer);
    const double pHasQuestion =
      dHasQuestion
      + (static_cast<double>(hasQuestionLevel) * dHasQuestion);
    assert(pCorrectAnswer >= 0.0);
    assert(pCorrectAnswer < 1.0);
    assert(pHasQuestion >= 0.0);
    assert(pHasQuestion < 1.0);
    brainiacs.push_back(Brainiac(pCorrectAnswer,pHasQuestion) );
  }
  assert(nBrainiacs == static_cast<int>(brainiacs.size()));
  std::random_shuffle(brainiacs.begin(), brainiacs.end() );
  return brainiacs;
}
//---------------------------------------------------------------------------
SimBrainiac::SimBrainiac(const std::vector<Brainiac>& brainiacs)
  : mBrainiacs(brainiacs)
{

}
//---------------------------------------------------------------------------
const std::vector<Brainiac>& SimBrainiac::GetBrainiacs() const
{
  return mBrainiacs;
}
//---------------------------------------------------------------------------
//Go to next time step
void SimBrainiac::Tick()
{
  //Lowest index  = loser
  //Highest index = brainiac
  //Every tick it is possible for the loser to become the brainiac
  const int size = mBrainiacs.size();

  for (int i=0; i!=size-1; ++i)
  {
    //i has question?
    if (GetRandomUniform() > mBrainiacs[i].pHasQuestion) continue;
    //i has a question...
    //Will i's opponent know the answer
    if (GetRandomUniform() < mBrainiacs[i + 1].pCorrectAnswer) continue;
    //Nope, swap i and its opponent
    std::swap(mBrainiacs[i], mBrainiacs[i+1]);
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
