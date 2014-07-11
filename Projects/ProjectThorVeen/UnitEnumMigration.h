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
#ifndef UnitEnumMigrationH
#define UnitEnumMigrationH
//---------------------------------------------------------------------------
#include <iosfwd>
#include <map>
//---------------------------------------------------------------------------
enum EnumMigration
{
  allSurvive
};
//---------------------------------------------------------------------------
//EnumMigrationConverter is a Singleton
class EnumMigrationConverter
{
  public:
    static EnumMigrationConverter * instance();
    EnumMigration toEnum(const std::string&) const;
    std::string toString(const EnumMigration&) const;
    void cout(const EnumMigration&) const;
  protected:
    EnumMigrationConverter();
    ~EnumMigrationConverter(){};

  private:
    static EnumMigrationConverter * mpInstance;
    mutable std::map<EnumMigration,std::string> mMap;
    mutable std::map<EnumMigration,std::string>::const_iterator mIter;

};
//---------------------------------------------------------------------------


#endif
