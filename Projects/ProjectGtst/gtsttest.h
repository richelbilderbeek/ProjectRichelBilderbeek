
/*
GTST, Game Theory Server
Copyright (C) 2011-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

//From http://www.richelbilderbeek.nl/ProjectGtst.htm

#ifndef PROJECTGTSTTEST_H
#define PROJECTGTSTTEST_H

#include "gtstforward_declarations.h"
#include <boost/checked_delete.hpp>



namespace ribi {
namespace gtst {

///\brief
///Class to test the non-Wt classes
struct Test
{
  ///\brief ServerTest contructor performs all tests
  ///
  ///This contructor is only called once
  Test(Server * const server);
  Test(const Test&) = delete;
  Test& operator=(const Test&) = delete;

  private:
  ~Test() {}
  friend void boost::checked_delete<>(Test*);

  private:
  ///Tests the parsing of the parameter files
  void TestParameterParsing();
  void TestParameters();
  void TestParticipant();

  ///TestStates test State
  void TestState();

  ///Create parameter file 1
  void CreateParameterFile1();

  ///Create parameter file for TestServer1_2
  void CreateParameterFileForTestServer1_2();

  ///Create parameter file 2
  void CreateParameterFile2();

  ///Create parameter file 3
  void CreateParameterFile3();

  ///Create parameter file 4
  void CreateParameterFile4();

  ///Create parameter file 5
  void CreateParameterFile5();

  ///Create parameter file 6
  void CreateParameterFile6();

  ///Create parameter file 7
  void CreateParameterFile7();

  Server * const m_server;
};

} //~namespace gtst
} //~namespace ribi

#endif // TEST_H
