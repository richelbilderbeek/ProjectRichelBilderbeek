//---------------------------------------------------------------------------
/*
  The Thor Veen Project, simulation to investigate honest signalling
  Copyright (C) 2006  Richel Bilderbeek

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
//Precompiled headers
#pragma hdrstop
//---------------------------------------------------------------------------
#include "assert.h"
#include "UnitSimulationParameters.h"
#include "UnitSimulationType.h"
#include "UnitExceptions.h"
//---------------------------------------------------------------------------
#include "UnitSimulation.h"
//---------------------------------------------------------------------------
Simulation::Simulation(const boost::shared_ptr<SimulationParameters>& params)
{
  setSimulationType(params);
}
//---------------------------------------------------------------------------
void Simulation::execute()
{
  assert(mSimulationType.get()!=0);
  try
  {
    mSimulationType->execute();
  }
  catch(NoCouplesException& e)
  {
    //No problem
  }
}
//---------------------------------------------------------------------------
void Simulation::setSimulationType(const boost::shared_ptr<SimulationParameters>& params)
{
  assert(params.get()!=0);

  switch(params->mEnumSimulationType)
  {
    case cartoonModel: mSimulationType.reset(new SimulationTypeCartoonModel(params)); break;
    default: assert(!"Should not get here");
  }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#pragma package(smart_init)
