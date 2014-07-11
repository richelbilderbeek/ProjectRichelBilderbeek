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
#ifndef UnitBirdWatcherH
#define UnitBirdWatcherH
//---------------------------------------------------------------------------
#include <memory>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include "UnitEnumPedigreeCharter.h"
//---------------------------------------------------------------------------
class Weather;
class BirdBase;
class BirdHawkDove;
class PedigreeCharterBase;
//---------------------------------------------------------------------------
//class BirdWatcher is a Singleton
//Its function is to assure that every bird is created only once
//and deleted exactly once.
//Also it measures stats of the birds
class BirdWatcher
{
  public:
  static BirdWatcher* instance();
  void reportNewBird(BirdBase* bird);    //DEBUGGING
  void reportNewBird(const boost::shared_ptr<BirdBase>& bird);
  void reportDeadBird(const int& index); //DEBUGGING
  void reset();
  void setPedigreeCharter(const EnumPedigreeCharter& pedigreeCharter);

  std::vector<std::string> getPedigree() const;

  std::vector<double> getMeansConditionHeritable() const;
  std::vector<double> getMeansConditionEnvironmental() const;
  std::vector<double> getMeansConditionParental() const;

  std::vector<double> getMeansPlayHawkAlpha() const;
  std::vector<double> getMeansPlayHawkBeta() const;

  protected:
  BirdWatcher();
  ~BirdWatcher();
  private:
  //std::vector<std::vector<int> > mIndices;
  #ifndef NDEBUG
  std::vector<int> mIndices;
  #endif
  std::vector<std::vector<boost::shared_ptr<const BirdBase> > > mBirds;
  //std::vector<std::vector<double> > mPlayHawkAlpha;
  //std::vector<std::vector<double> >mPlayHawkBeta;
  std::auto_ptr<PedigreeCharterBase> mPedigreeCharter;
  static boost::scoped_ptr<BirdWatcher> mpInstance;
  Weather * mWeather;

  #ifndef NDEBUG
    static int mConstructorCalled;
  #endif

  //Deletion friends
  //friend std::auto_ptr<BirdWatcher>;
  friend boost::checked_delete<BirdWatcher>(BirdWatcher*);

};
//---------------------------------------------------------------------------

#endif
