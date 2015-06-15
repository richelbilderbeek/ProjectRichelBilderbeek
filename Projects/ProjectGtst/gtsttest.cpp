//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ProjectGtst.htm
//---------------------------------------------------------------------------
#include <cassert>
#include "gtsttest.h"

///\brief Test contructor performs all tests
///
///This contructor is only called once
ribi::gtst::Test::Test(Server * const server)
  : m_server(server)
{
  assert(m_server);
  TestState();
  TestParameterParsing();

  TestParticipant();
  TestParameters();


  //Call TestServer1_1 twice, for two different number of periods
  //TestServer1_1(1);
  //TestServer1_1(2);

  //Call TestServer1_2 twice, for two different number of periods
  //TestServer1_2(1);
  //TestServer1_2(2);

  //TestServer4();

  //TestServer9();
}

