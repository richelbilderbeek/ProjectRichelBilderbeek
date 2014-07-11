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
#ifndef UnitMigrationPoolH
#define UnitMigrationPoolH
//---------------------------------------------------------------------------
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
//---------------------------------------------------------------------------
class BirdBase;
//---------------------------------------------------------------------------
class MigrationPool: public boost::noncopyable
{
  public:
  MigrationPool() {}
  void addFemale(boost::shared_ptr<BirdBase>& female);
  void addMale(boost::shared_ptr<BirdBase>& male);

  boost::shared_ptr<BirdBase> getFemale();
  boost::shared_ptr<BirdBase> getMale();

  bool isEmpty() const;
  bool hasFemales() const;
  bool hasMales() const;
  int getNfemales() const;
  int getNmales() const;
  int getSize() const;
  private:
  std::vector<boost::shared_ptr<BirdBase> > mFemales;
  std::vector<boost::shared_ptr<BirdBase> > mMales;

};

#endif
