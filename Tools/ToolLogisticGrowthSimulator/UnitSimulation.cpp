//---------------------------------------------------------------------------
/*
  Logistic Growth Simulator, logistic growth simulation
  Copyright (C) 2009  Richel Bilderbeek

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
#pragma hdrstop

#include "UnitSimulation.h"

//---------------------------------------------------------------------------
Simulation::Simulation(
  const double& initPopSize,
  const Parameters& params)
  : mParams(params)
{
  mPopSizes.push_back(initPopSize);
}
//---------------------------------------------------------------------------
void Simulation::Run(const int& nGenerations)
{
  while (static_cast<int>(mPopSizes.size()) < nGenerations) NextGeneration();
}
//---------------------------------------------------------------------------
void Simulation::NextGeneration()
{
  const double popNow = mPopSizes.back();
  const double popNext = mParams.mR * popNow * (mParams.mK - popNow);
  mPopSizes.push_back(popNext);
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
