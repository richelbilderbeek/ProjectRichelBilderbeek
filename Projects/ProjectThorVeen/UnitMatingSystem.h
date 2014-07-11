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
#ifndef UnitMatingSystemH
#define UnitMatingSystemH
//---------------------------------------------------------------------------
#include <iosfwd>
#include <memory>
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
class BirdBase;
class SingleMalePool;
class CouplePool;
//---------------------------------------------------------------------------
// MatingSystemBase is a Strategy design pattern
// Therefore, MatingSystemBase is an Abstract Base Class
class MatingSystemBase
{
  public:
  MatingSystemBase();
  virtual ~MatingSystemBase();
  virtual std::string getClassName() const = 0;
  virtual void makeCouple(
    boost::shared_ptr<BirdBase>& female,
    boost::shared_ptr<BirdBase>& male,
    std::auto_ptr<SingleMalePool>& singleMalePool,
    std::auto_ptr<CouplePool>& couplePool) const = 0;

};
//---------------------------------------------------------------------------
class MatingSystemMonogamy : public MatingSystemBase
{
  public:
  MatingSystemMonogamy();
  ~MatingSystemMonogamy();
  std::string getClassName() const;
  void makeCouple(
    boost::shared_ptr<BirdBase>& female,
    boost::shared_ptr<BirdBase>& male,
    std::auto_ptr<SingleMalePool>& singleMalePool,
    std::auto_ptr<CouplePool>& couplePool) const;
};
//---------------------------------------------------------------------------
class MatingSystemPolygyny : public MatingSystemBase
{
  public:
  MatingSystemPolygyny();
  ~MatingSystemPolygyny();
  std::string getClassName() const;
  void makeCouple(
    boost::shared_ptr<BirdBase>& female,
    boost::shared_ptr<BirdBase>& male,
    std::auto_ptr<SingleMalePool>& singleMalePool,
    std::auto_ptr<CouplePool>& couplePool) const;
};
//---------------------------------------------------------------------------

#endif
 