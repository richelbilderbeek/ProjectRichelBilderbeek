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
#ifndef UnitSimulationTypeH
#define UnitSimulationTypeH
//---------------------------------------------------------------------------
class SimulationParameters;
class SingleMalePool;
class SingleFemalePool;
class CouplePool;
class MigrationPool;
class DeadPool;
class MaleCompetitionBase;
class FemaleChoiceBase;
class BreedingBase;
class MigrationBase;
class BirdFactoryBase;

//---------------------------------------------------------------------------
#include <memory>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include "UnitEnumFemaleChoice.h"
#include "UnitEnumMigration.h"
#include "UnitEnumBirdType.h"
#include "UnitEnumMatingSystem.h"
//---------------------------------------------------------------------------
class SimulationTypeBase : public boost::noncopyable
{
  public:
  SimulationTypeBase();
  virtual ~SimulationTypeBase() {}
  virtual void execute() = 0;
  void initializePools();

  protected:
  std::auto_ptr<SingleMalePool  > mSingleMalePool;
  std::auto_ptr<SingleFemalePool> mSingleFemalePool;
  std::auto_ptr<CouplePool      > mCouplePool;
  std::auto_ptr<MigrationPool   > mMigrationPool;
  std::auto_ptr<DeadPool   > mDeadPool;

  boost::shared_ptr<SimulationParameters> mSimulationParameters;

  std::auto_ptr<FemaleChoiceBase> mFemaleChoice;
  std::auto_ptr<BreedingBase> mBreeding;
  std::auto_ptr<MigrationBase> mMigration;
  std::auto_ptr<BirdFactoryBase> mBirdFactory;

  void setFemaleChoice(
    const EnumFemaleChoice& femaleChoice,
    const EnumMatingSystem& matingSystem);

  void setBreeding();
  void setMigration(const EnumMigration& migration);
  void setBirdType(const EnumBirdType& birdType);
  //void setMaleCompetition(
};
//---------------------------------------------------------------------------
class SimulationTypeCartoonModel : public SimulationTypeBase
{
  public:
  SimulationTypeCartoonModel(const boost::shared_ptr<SimulationParameters>& simulationParameters);
  ~SimulationTypeCartoonModel() {}
  void execute();
};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#endif
