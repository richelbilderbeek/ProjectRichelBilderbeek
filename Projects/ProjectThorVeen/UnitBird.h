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
#ifndef UnitBirdH
#define UnitBirdH
//---------------------------------------------------------------------------
#include <iosfwd>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include "UnitEnumBirdType.h"
//---------------------------------------------------------------------------
class BirdFactoryBase;
class BirdGeneralParameters;
class BirdHawkDoveParameters;
class BirdWatcher;
//---------------------------------------------------------------------------
//Every bird has a condition
class BirdBase : public boost::noncopyable
{
  public:
  BirdBase();
  virtual ~BirdBase();
  BirdBase(const BirdFactoryBase * birdFactory);
  BirdBase(const boost::shared_ptr<BirdBase>& mother, const boost::shared_ptr<BirdBase>& father);
  void initBase(const boost::shared_ptr<BirdGeneralParameters>& params);
  virtual bool willFight(const boost::shared_ptr<BirdBase>& male) = 0;
  virtual bool willDieLoserFight() const = 0;
  virtual std::string getClassName() const;
  virtual EnumBirdType getClassType() const = 0;

  static void setMutationConditionHeritable(
    const BirdFactoryBase * birdFactory,
    const double& mutationConstitution);

  //Getters
  int getIndexMother() const;
  int getIndexFather() const;
  int getBirdIndex() const;
  double getCondition() const;

  double getConditionHeritable() const;
  double getConditionEnvironment() const;
  double getConditionParental() const;

  static void InitBirdWatcher();

  protected:
  //Bird physical parameters
  double mConditionHeritable;
  double mConditionEnvironment;
  double mConditionParental;
  static double mMutationConditionHeritable;
  //Measuring
  static BirdWatcher * mBirdWatcher;
  static int mBirdIndexCounter;
  int mBirdIndex;
  int mIndexMother;
  int mIndexFather;

};
//---------------------------------------------------------------------------
class BirdHawkDove : public BirdBase
{
  public:
  BirdHawkDove(
    const BirdFactoryBase * birdFactory,
    const boost::shared_ptr<BirdGeneralParameters>& birdGeneralParams,
    const boost::shared_ptr<BirdHawkDoveParameters>& hawkDoveParams);
  BirdHawkDove(const boost::shared_ptr<BirdBase>& mother, const boost::shared_ptr<BirdBase>& father);
  ~BirdHawkDove() {}
  bool willFight(const boost::shared_ptr<BirdBase>& male);
  bool willDieLoserFight() const;

  static void setMutationPlayHawkAlpha(const BirdFactoryBase * birdFactory, const double& mutationPlayHawkAlpha);
  static void setMutationPlayHawkBeta(const BirdFactoryBase * birdFactory,  const double& mutationPlayHawkBeta);
  static void setPdieHawkHawkLoser(const BirdFactoryBase * birdFactory,  const double& pDieHawkHawkLoser);

  std::string getClassName() const;
  EnumBirdType getClassType() const;
  double getPlayHawkAlpha() const;
  double getPlayHawkBeta() const;
  private:
  //BirdHawkDove(BirdFactoryBase*);
  static double mMutationPlayHawkAlpha;
  static double mMutationPlayHawkBeta;
  static double mPdieHawkHawkLoser;
  double mPlayHawkAlpha;
  double mPlayHawkBeta;
};
//---------------------------------------------------------------------------
//typedef BirdBase BirdBaseMale;
//typedef BirdBase BirdBaseFemale;
//---------------------------------------------------------------------------

#endif
