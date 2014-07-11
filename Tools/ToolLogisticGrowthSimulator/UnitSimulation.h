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
#ifndef UnitSimulationH
#define UnitSimulationH
//---------------------------------------------------------------------------
#include <vector>
//---------------------------------------------------------------------------
struct Parameters
{
  double mR; //Intrinsic growth rate
  double mK; //Carrying capacity
};
//---------------------------------------------------------------------------
struct Simulation
{
  Simulation(
    const double& initPopSize,
    const Parameters& params);

  const Parameters mParams;

  void Run(const int& nGenerations);

  const std::vector<double>& GetPopSizes() const { return mPopSizes; }

  private:
  std::vector<double> mPopSizes;

  void NextGeneration();
};

#endif
