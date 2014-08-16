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
#ifndef UnitBirdFactoryH
#define UnitBirdFactoryH
//---------------------------------------------------------------------------
#include <iosfwd>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include "UnitEnumBirdType.h"
//---------------------------------------------------------------------------
class BirdBase;
class BirdGeneralParameters;
class BirdHawkDoveParameters;
class BirdWatcher;
//---------------------------------------------------------------------------
//An Abstract Factory
class BirdFactoryBase : public boost::noncopyable
{
  public:
  BirdFactoryBase() {}
  virtual ~BirdFactoryBase() {}
  void initBase(const boost::shared_ptr<BirdGeneralParameters>& params);
  //createBird should create a new bird of the correct type AND report this to BirdWatcher
  virtual boost::shared_ptr<BirdBase> createBird() const = 0;
  virtual std::string getClassName() const;
  virtual EnumBirdType getClassType() const = 0;

  static void InitBirdWatcher();

  protected:
  boost::shared_ptr<BirdGeneralParameters> mBirdGeneralParams;
  static BirdWatcher * mBirdWatcher;
};
//---------------------------------------------------------------------------
//A Concrete Factory
class BirdFactoryHawkDove : public BirdFactoryBase
{
  public:
  BirdFactoryHawkDove(
    const boost::shared_ptr<BirdGeneralParameters>& birdGeneralParams,
    const boost::shared_ptr<BirdHawkDoveParameters>& birdHawkDoveParams);
  ~BirdFactoryHawkDove() {}
  boost::shared_ptr<BirdBase> createBird() const;
  std::string getClassName() const;
  EnumBirdType getClassType() const;
  private:
  const boost::shared_ptr<BirdHawkDoveParameters> mBirdHawkDoveParams;
};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#endif
