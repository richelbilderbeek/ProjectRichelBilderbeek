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
#ifndef UnitBreedingH
#define UnitBreedingH
//---------------------------------------------------------------------------
#include<memory>
#include <boost/noncopyable.hpp>
//---------------------------------------------------------------------------
class CouplePool;
class MigrationPool;
class DeadPool;
//---------------------------------------------------------------------------
class BreedingBase : public boost::noncopyable
{
  public:
  BreedingBase() {}
  virtual ~BreedingBase() {}
  virtual void breed(
    std::auto_ptr<CouplePool>& couplePool,
    std::auto_ptr<MigrationPool>& migrationPool,
    std::auto_ptr<DeadPool>& deadPool,
    const int& nFemalesWanted,
    const int& nMalesWanted
    ) const = 0;
};
//---------------------------------------------------------------------------
class BreedingSingleGeneration : public BreedingBase
{
  public:
  BreedingSingleGeneration() {}
  ~BreedingSingleGeneration() {}
  void breed(
    std::auto_ptr<CouplePool>& couplePool,
    std::auto_ptr<MigrationPool>& migrationPool,
    std::auto_ptr<DeadPool>& deadPool,
    const int& nFemalesWanted,
    const int& nMalesWanted) const;
};
//---------------------------------------------------------------------------

#endif
