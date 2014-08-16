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
#include "UnitBirdHawkDoveParameters.h"
//---------------------------------------------------------------------------
#include <string>
#include "UnitHelperFunctions.h"
//---------------------------------------------------------------------------
std::vector<std::string> BirdHawkDoveParameters::getText() const
{
  std::vector<std::string> text;
  text.push_back("PlayHawkAlphaMean: "     + helper::ftoa(mPlayHawkAlphaMean    ));
  text.push_back("PlayHawkAlphaStdDev: "   + helper::ftoa(mPlayHawkAlphaStdDev  ));
  text.push_back("PlayHawkAlphaMutation: " + helper::ftoa(mPlayHawkAlphaMutation));
  text.push_back("PlayHawkBetaMean: "      + helper::ftoa(mPlayHawkBetaMean     ));
  text.push_back("PlayHawkBetaStdDev: "    + helper::ftoa(mPlayHawkBetaStdDev   ));
  text.push_back("PlayHawkBetaMutation: "  + helper::ftoa(mPlayHawkBetaMutation ));
  text.push_back("PdieHawkHawkLoser: "  + helper::ftoa(mPdieHawkHawkLoser));

  return text;
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
