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
#include <fstream>
#include <functional>

 

#include "gtstall_groups.h"
#include "gtstall_parameters.h"
#include "gtstall_serverstates.h"
#include "gtstgroups.h"
#include "gtstgroupassigner.h"
#include "gtstlogfile.h"
#include "gtstparticipant.h"
#include "gtstrepeatassigner.h"
#include "gtststate.h"
#include "stopwatch.h"
#include "gtsttest.h"
#include "gtstserver.h"

void ribi::gtst::Test::TestParameters()
{
  //Check setting parameters
  boost::shared_ptr<Parameters> parameters(new Parameters(m_server));

  assert(parameters->GetParticipants().empty()
    && "Assume default parameters contain no participants");

  //Add one default Participant
  parameters->AddParticipant(parameters->CreateDefaultParticipant());

  assert(parameters->GetParticipants().size() == 1
    && "Assume after >AddParticipant, these is a Participant present");

  //Delete all participants from Parameters
  parameters->DeleteParticipants();

  assert(parameters->GetParticipants().empty()
    && "Assume after DeleteParticipants, these are actually deleted");

  //Again add one default Participant
  parameters->AddParticipant(parameters->CreateDefaultParticipant());

  assert(parameters->GetParticipants().size() == 1
    && "Assume after >AddParticipant, these is a Participant present");

  //Delete all participants from Parameters
  parameters->DeleteParticipants();

  //Delete all participants from Parameters again should work
  parameters->DeleteParticipants();
}


