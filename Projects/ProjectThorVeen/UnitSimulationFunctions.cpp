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
#pragma hdrstop
//---------------------------------------------------------------------------
#include "UnitSimulationFunctions.h"
//---------------------------------------------------------------------------
#include <math>
#include "Assert.h"
//#include <exception>
#include <stdexcept>

#ifndef NDEBUG
#include <vcl>
#endif
//---------------------------------------------------------------------------
namespace simFunc
{
  double logisticEquation(const double& x, const double& alpha, const double& beta)
  {
    Assert(alpha > -1000.0 && alpha < 1000.0);
    Assert(beta  > -1000.0 && beta  < 1000.0);
    Assert(x     > -1000.0 && x     < 1000.0);
    const double numerator = std::exp( (alpha*x)+beta );
    const double denominator = 1.0 + std::exp( (alpha*x) + beta );
    Assert(denominator!=0.0);
    return (numerator/denominator);
    //  if (((alpha*x) + beta ) < 1000.000) return 0.0; //You approch 0.0/(1.0+0.0)
    //  if (((alpha*x) + beta ) < 0.001) return 0.5; //You approach 1.0/(1.0+1.0)
    //You approach INF/(1.0+INF)
    //  return 1.0;
  }

};

#pragma package(smart_init)
