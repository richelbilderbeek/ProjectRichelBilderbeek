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
#ifndef UnitFemaleChoiceH
#define UnitFemaleChoiceH
//---------------------------------------------------------------------------
#include <memory>
#include <boost/noncopyable.hpp>
//---------------------------------------------------------------------------
#include <memory>
#include "UnitEnumMatingSystem.h"
class SingleFemalePool;
class SingleMalePool;
class CouplePool;
class DeadPool;
class MatingSystemBase;
//---------------------------------------------------------------------------
class FemaleChoiceBase : public boost::noncopyable
{
  public:
  FemaleChoiceBase() {}
  virtual ~FemaleChoiceBase() {}
  void setMatingSystem(const EnumMatingSystem& matingSystem);
  virtual void choose(
    std::auto_ptr<SingleFemalePool>& singleFemalePool,
    std::auto_ptr<SingleMalePool>& singleMalePool,
    std::auto_ptr<CouplePool>& couplePool,
    std::auto_ptr<DeadPool>& deadPool) const = 0;
  protected:
    std::auto_ptr<MatingSystemBase> mMatingSystem;

};
//---------------------------------------------------------------------------
class FemaleChoiceWinnerFight2males : public FemaleChoiceBase
{
  public:
  FemaleChoiceWinnerFight2males(const EnumMatingSystem& matingSystem);
  ~FemaleChoiceWinnerFight2males() {}
  void choose(
    std::auto_ptr<SingleFemalePool>& singleFemalePool,
    std::auto_ptr<SingleMalePool>& singleMalePool,
    std::auto_ptr<CouplePool>& couplePool,
    std::auto_ptr<DeadPool>& deadPool) const;
};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#endif
