//---------------------------------------------------------------------------
/*
Brainweaver, tool to create and assess concept maps
Copyright (C) 2012-2015 The Brainweaver Team

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ProjectBrainweaver.htm
//---------------------------------------------------------------------------
#ifndef PVDBFILEFACTORY_H
#define PVDBFILEFACTORY_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

namespace ribi {

namespace pvdb {

struct File;

///Factory of pvdb::File
struct FileFactory
{
  FileFactory();

  boost::shared_ptr<pvdb::File> Create() const noexcept;

  #ifndef NDEBUG
  ///DeepCopy is only used for debugging
  boost::shared_ptr<pvdb::File> DeepCopy(const boost::shared_ptr<const pvdb::File>& file) const noexcept;
  #endif

  std::vector<boost::shared_ptr<pvdb::File>> GetTests() const noexcept;

  int GetNumberOfTests() const noexcept { return 6; }

  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace pvdb

} //~namespace ribi

#endif // PVDBFILEFACTORY_H
