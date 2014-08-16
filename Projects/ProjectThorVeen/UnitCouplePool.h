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
#ifndef UnitCouplePoolH
#define UnitCouplePoolH
//---------------------------------------------------------------------------
#include <vector>
#include <memory>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
//---------------------------------------------------------------------------
class BirdBase;
class Couple;
class DeadPool;
//---------------------------------------------------------------------------
class CouplePool : public boost::noncopyable
{
  public:
  CouplePool() {}
  void addCouple(
    boost::shared_ptr<BirdBase>& female,
    boost::shared_ptr<BirdBase>& male);

  boost::shared_ptr<Couple> getRandomCouple() const;

  void doEmpty(std::auto_ptr<DeadPool>& deadPool);
  bool isEmpty() const;
  int getSize() const;
  private:

  std::vector< boost::shared_ptr<Couple> > mCouples;

};


#endif
