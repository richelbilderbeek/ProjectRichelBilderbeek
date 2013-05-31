//---------------------------------------------------------------------------
/*
  The Chris Wiley Project, simulation on mixed-pair mating
  Copyright (C) 2009  Richl Bilderbeek

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
#include <cstdlib>
//---------------------------------------------------------------------------
#include "parameters.h"
//---------------------------------------------------------------------------
void Parameters::reset()
{
   nFemales = 0;
   nMales = 0;
   fractionMaleA = 0.0;
   fractionFemaleA = 0.0;
   bestOfHowMuch = 0;
   assessingErrorA = 0.0;
   assessingErrorB = 0.0;
   meanTraitA = 0.0;
   meanTraitB = 0.0;
   meanPreferenceA = 0.0;
   meanPreferenceB = 0.0;
   stdDevTraitA = 0.0;
   stdDevTraitB = 0.0;
   stdDevPreferenceA = 0.0;
   stdDevPreferenceB = 0.0;
   sigmaSquared = 0.0;
   nSimulations = 0;
   //simIndex = 0;
   costTrait = 0.0;
   costPreference = 0.0;
   mutationRate = 0.0;
   matingSystem = monogamy;
   femaleSampling = bestOfNconspicific;
   densityDependentSelection = afterMating;
}
//---------------------------------------------------------------------------
unsigned int Parameters::getNmalesAwanted() const
{
  //return static_cast<double>(nMales) * fractionMaleA;
  //return nMales * fractionMaleA;
  const unsigned int result = nMales * fractionMaleA;
  const unsigned int nMalesBwanted = getNmalesBwanted();
  if (result+nMalesBwanted==nMales) return result;
  else if (result+nMalesBwanted==nMales-1) return result+1;
  else assert(!"Should not get here"); std::exit(1); return 0;
}
//---------------------------------------------------------------------------
unsigned int Parameters::getNmalesBwanted() const
{
  return nMales * (1.0-fractionMaleA);
}
//---------------------------------------------------------------------------
unsigned int Parameters::getNfemalesAwanted() const
{
  //return static_cast<double>(nFemales) * fractionFemaleA;
  //return nFemales * fractionFemaleA;
  const unsigned int result = nFemales * fractionFemaleA;
  const unsigned int nFemalesBwanted = getNfemalesBwanted();
  if (result+nFemalesBwanted==nFemales) return result;
  else if (result+nFemalesBwanted==nFemales-1) return result+1;
  else assert(!"Should not get here"); std::exit(1); return 0;
}
//---------------------------------------------------------------------------
unsigned int Parameters::getNfemalesBwanted() const
{
  //return static_cast<double>(nFemales) * (1.0-fractionFemaleA);
  return nFemales * (1.0-fractionFemaleA);
}
//---------------------------------------------------------------------------
void Parameters::readFromFile(const std::string& fileName)
{
  assert(fileExists(fileName)==true);
  std::ifstream in (fileName.c_str());
  std::string myString;
  int tempInt;
  for (int i=0; !in.eof(); ++i)
  {
    in >> myString;
    if (myString=="nGenerations")      { in >> nGenerations; continue; }
    if (myString=="nFemales")          { in >> nFemales; continue; }
    if (myString=="nMales")            { in >> nMales; continue; }
    if (myString=="fractionMaleA")     { in >> fractionMaleA; continue; }
    if (myString=="fractionFemaleA")   { in >> fractionFemaleA; continue; }
    if (myString=="bestOfHowMuch")     { in >> bestOfHowMuch; continue; }
    if (myString=="assessingErrorA")   { in >> assessingErrorA; continue; }
    if (myString=="assessingErrorB")   { in >> assessingErrorB; continue; }
    if (myString=="meanTraitA")        { in >> meanTraitA; continue; }
    if (myString=="meanTraitB")        { in >> meanTraitB; continue; }
    if (myString=="meanPreferenceA")   { in >> meanPreferenceA; continue; }
    if (myString=="meanPreferenceB")   { in >> meanPreferenceB; continue; }
    if (myString=="stdDevTraitA")      { in >> stdDevTraitA; continue; }
    if (myString=="stdDevTraitB")      { in >> stdDevTraitB; continue; }
    if (myString=="stdDevPreferenceA") { in >> stdDevPreferenceA; continue; }
    if (myString=="stdDevPreferenceB") { in >> stdDevPreferenceB; continue; }
    if (myString=="sigmaSquared")      { in >> sigmaSquared; continue; }
    if (myString=="nSimulations")      { in >> nSimulations; continue; }
    if (myString=="nOffspring")        { in >> nOffspring; continue; }
    if (myString=="surviveSpeciesAlpha") { in >> surviveSpeciesAlpha; continue; }
    if (myString=="surviveSpeciesBeta")  { in >> surviveSpeciesBeta; continue; }
    if (myString=="costTrait")  { in >> costTrait; continue; }
    if (myString=="costPreference")  { in >> costPreference; continue; }
    if (myString=="mutationRate")  { in >> mutationRate; continue; }
    if (myString=="matingSystem")  { in >> tempInt; matingSystem = static_cast<enumMatingSystem>(tempInt); continue; }
    if (myString=="femaleSampling")  { in >> tempInt; femaleSampling = static_cast<enumFemaleSampling>(tempInt); continue; }
    if (myString=="densityDependentSelection")  { in >> tempInt; densityDependentSelection = static_cast<enumDensityDependentSelection>(tempInt); continue; }
    assert(!"Unknown file parameter"); std::exit(1);
  }
  in.close();
}
//---------------------------------------------------------------------------
void Parameters::writeToFile(const std::string& fileName)
{
  std::ofstream out (fileName.c_str());
  out << "nGenerations" << '\t'       << nGenerations << '\n';
  out << "nFemales" << '\t'           << nFemales << '\n';
  out << "nMales" << '\t'             << nMales << '\n';
  out << "fractionMaleA" << '\t'      << fractionMaleA << '\n';
  out << "fractionFemaleA" << '\t'    << fractionFemaleA << '\n';
  out << "bestOfHowMuch" << '\t'      << bestOfHowMuch << '\n';
  out << "assessingErrorA" << '\t'    << assessingErrorA << '\n';
  out << "assessingErrorB" << '\t'    << assessingErrorB << '\n';
  out << "meanTraitA" << '\t'         << meanTraitA << '\n';
  out << "meanTraitB" << '\t'         << meanTraitB << '\n';
  out << "meanPreferenceA" << '\t'    << meanPreferenceA << '\n';
  out << "meanPreferenceB" << '\t'    << meanPreferenceB << '\n';
  out << "stdDevTraitA" << '\t'       << stdDevTraitA << '\n';
  out << "stdDevTraitB" << '\t'       << stdDevTraitB << '\n';
  out << "stdDevPreferenceA" << '\t'  << stdDevPreferenceA << '\n';
  out << "stdDevPreferenceB" << '\t'  << stdDevPreferenceB << '\n';
  out << "sigmaSquared" << '\t'       << sigmaSquared << '\n';
  out << "nSimulations" << '\t'       << nSimulations << '\n';
  out << "nOffspring" << '\t'         << nOffspring << '\n';
  out << "surviveSpeciesAlpha" << '\t'  << surviveSpeciesAlpha << '\n';
  out << "surviveSpeciesBeta" << '\t'   << surviveSpeciesBeta << '\n';
  out << "costTrait" << '\t'   << costTrait << '\n';
  out << "costPreference" << '\t'   << costPreference << '\n';
  out << "mutationRate" << '\t'   << mutationRate << '\n';
  out << "matingSystem" << '\t'   << static_cast<int>(matingSystem) << '\n';
  out << "femaleSampling" << '\t'   << static_cast<int>(femaleSampling) << '\n';
  out << "densityDependentSelection" << '\t'   << static_cast<int>(densityDependentSelection) << '\n';
  out.close();
}
//---------------------------------------------------------------------------
