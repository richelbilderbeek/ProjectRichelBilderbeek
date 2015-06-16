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
#ifndef QTPVDBDISPLAY_H
#define QTPVDBDISPLAY_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "pvdbfwd.h"
#pragma GCC diagnostic pop

struct QTableWidget;

namespace ribi {

namespace pvdb {

///Functions for printing
struct QtDisplay
{

  static void DisplayRatedConcepts(const boost::shared_ptr<const pvdb::File> file,QTableWidget * const table);
  static void DisplayExamples(const boost::shared_ptr<const pvdb::File> file,QTableWidget * const table);
  static void DisplayValues(const boost::shared_ptr<const pvdb::File> file,QTableWidget * const table);

};

} //~namespace pvdb

} //~namespace ribi

#endif // QTPVDBDISPLAY_H
