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
#include <string>
//---------------------------------------------------------------------------
#include "UnitPedigreeCharter.h"
//---------------------------------------------------------------------------
#include "UnitBird.h"
#include "UnitHelperFunctions.h"
//---------------------------------------------------------------------------
PedigreeCharterBase::PedigreeCharterBase()
{
  mPedigree.resize(0);
}
//---------------------------------------------------------------------------
PedigreeCharterBase::~PedigreeCharterBase()
{

}
//---------------------------------------------------------------------------
std::vector<std::string> PedigreeCharterBase::getPedigree() const
{
  return mPedigree;
}
//---------------------------------------------------------------------------
PedigreeCharterNone::PedigreeCharterNone()
  : mDefaultText("PedigreeCharterNone does NOTHING")
{

}
//---------------------------------------------------------------------------
PedigreeCharterNone::~PedigreeCharterNone()
{

}
//---------------------------------------------------------------------------
std::string PedigreeCharterNone::getClassName() const
{
  return "PedigreeCharterNone";
}
//---------------------------------------------------------------------------
PedigreeCharterAll::PedigreeCharterAll()
{

}
//---------------------------------------------------------------------------
PedigreeCharterAll::~PedigreeCharterAll()
{

}
//---------------------------------------------------------------------------
std::string PedigreeCharterAll::getClassName() const
{
  return "PedigreeCharterAll";
}
//---------------------------------------------------------------------------
void PedigreeCharterNone::doChartLegend(const BirdHawkDove* bird)
{
  mPedigree.resize(0);
  mPedigree.push_back(mDefaultText);
}
//---------------------------------------------------------------------------
void PedigreeCharterNone::doChart(const BirdHawkDove* bird)
{
  //PedigreeCharterNone does NOTHING!
}
//---------------------------------------------------------------------------
void PedigreeCharterAll::doChartLegend(const BirdHawkDove* bird)
{
  const std::string pedigreeLegend = "ID\tFather\tMother\tPlayHawkAlpha\tPlayHawkBeta";
  mPedigree.push_back(pedigreeLegend);  
}
//---------------------------------------------------------------------------
void PedigreeCharterAll::doChart(const BirdHawkDove* bird)
{
  const std::string pedigree = helper::itoa(bird->getBirdIndex())
    + '\t' + helper::itoa(bird->getIndexFather())
    + '\t' + helper::itoa(bird->getIndexMother())
    + '\t' + helper::ftoa(bird->getPlayHawkAlpha())
    + '\t' + helper::ftoa(bird->getPlayHawkBeta());
  mPedigree.push_back(pedigree);
}
//---------------------------------------------------------------------------

#pragma package(smart_init)
