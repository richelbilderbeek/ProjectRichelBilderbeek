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
#ifndef UnitSimBrainiacH
#define UnitSimBrainiacH
//---------------------------------------------------------------------------
#include <vector>
#include "UnitBrainiac.h"

std::vector<Brainiac> GetBrainiacs(
  const int nBrainiacs = 100,
  const int nCorrectAnswerLevels = 10,
  const int nHasQuestionLevels = 10);

struct SimBrainiac
{
  SimBrainiac(const std::vector<Brainiac>& brainiacs = ::GetBrainiacs());
  const std::vector<Brainiac>& GetBrainiacs() const;
  void Tick(); //Go to next time step

  private:
  std::vector<Brainiac> mBrainiacs;

};

//From htpp://www.richelbilderbeek.nl/CppGetRandomUniform.htm
const double GetRandomUniform();


#endif
