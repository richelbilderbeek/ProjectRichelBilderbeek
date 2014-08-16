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
#ifndef UnitResultsH
#define UnitResultsH
//---------------------------------------------------------------------------
#include <iosfwd>
#include <memory>
#include <vector>
#include <boost/noncopyable.hpp>
//---------------------------------------------------------------------------
//class Results is a Singleton
class Results : public boost::noncopyable
{
  public:
  static Results* instance();

  /*void tallySingleFemales(const int& nSingleFemales);
  void tallySingleMales(const int& nSingleMales);
  void tallyCouples(const int& nCouples);
  void tallyMigrants(const int& nMigrants);
  void tallyDeath(const int& nDeath);*/

  std::vector<int> mNsingleFemales;
  std::vector<int> mNsingleMales;
  std::vector<int> mNcouples;
  std::vector<int> mNmigrants;
  std::vector<int> mNdead;
  std::vector<std::string> mLog;

  void log(const std::string& s);
  void log(const char* s); //For non-string compilation
  void reset();

  private:


  friend class std::auto_ptr<Results>;
  Results();
  ~Results();
  static const std::auto_ptr<Results> mpInstance;
};
//---------------------------------------------------------------------------

#endif
