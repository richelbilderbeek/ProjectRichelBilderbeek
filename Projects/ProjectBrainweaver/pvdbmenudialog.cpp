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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "pvdbmenudialog.h"

#include <cassert>
#include <iostream>

#include <boost/make_shared.hpp>

#include "container.h"
#include "conceptmap.h"
#include "fileio.h"
#include "fuzzy_equal_to.h"
#include "geometry.h"
#include "plane.h"
#include "ribi_regex.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"
#include "xml.h"
#pragma GCC diagnostic pop

int ribi::pvdb::MenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  assert(!"TODO");
  return 1;
}

ribi::About ribi::pvdb::MenuDialog::GetAbout() const noexcept
{
  About a(
    "The Brainweaver Team",
    "Brainweaver",
    "tool to create and assess concept maps",
    "the 18th of May 2014",
    "2012-2015",
    "http://www.richelbilderbeek.nl/ProjectBrainweaver.htm",
    GetVersion(),
    GetVersionHistory());

  a.AddLibrary("apfloat version: 2.4.1");
  a.AddLibrary("ConceptMap version: " + ribi::cmap::ConceptMap::GetVersion());
  a.AddLibrary("Container version: " + ribi::Container().GetVersion());
  a.AddLibrary("FileIo version: " + ribi::fileio::FileIo().GetVersion());
  a.AddLibrary("fuzzy_equal_to version: " + fuzzy_equal_to::GetVersion());
  a.AddLibrary("Geometry version: " + Geometry().GetVersion());
  a.AddLibrary("Plane version: " + Plane::GetVersion());
  a.AddLibrary("ribi::Regex version: " + ribi::Regex::GetVersion());

  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::pvdb::MenuDialog::GetHelp() const noexcept
{
  return Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {

    },
    {

    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::pvdb::MenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramBrainweaver
  };
  assert(p);
  return p;
}

std::string ribi::pvdb::MenuDialog::GetVersion() const noexcept
{
  return "0.50";
}

std::vector<std::string> ribi::pvdb::MenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2012-06-17: Version 0.01: concept version of ProjectVanDenBogaart, using 'IronHide' style",
    "2012-10-18: Version 0.02: able to crosscompile to windows, few dialogs present",
    "2012-10-19: Version 0.03: added use of QtHideAndShowDialog, most dialogs present",
    "2012-10-24: Version 0.04: added QtPvdbClusterWidget",
    "2012-10-28: Version 0.05: added Cluster and ConceptMap, added AutoSave, ClusterWidget and Cluster work okay, file I/O working okay",
    "2012-11-10: Version 0.06: added first working QtConceptMap",
    "2012-11-13: Version 0.07: added edges and helpers to QtConceptMap",
    "2012-11-15: Version 0.08: concepts on edges in QtConceptMap are editable, QtConceptMap always looks pretty",
    "2012-11-18: Version 0.09: added edges with arrowheads, deletion of nodes and edges possible, put help items in status bar",
    "2012-11-22: Version 0.10: editing of concepts and their examples, tools icon (doing nothing yet)",
    "2012-11-24: Version 0.11: allow adding new relations",
    "2012-11-25: Version 0.12: allow connecting to center node",
    "2012-11-27: Version 0.13: added program flow tests",
    "2012-11-28: Version 0.14: fixed many program flow and widget and dialog bugs",
    "2012-12-02: Version 0.15: also relations can move",
    "2012-12-08: Version 0.16: use quadratic Bezier curve for relations, locations of moved relations are saved",
    "2012-12-13: Version 0.17: improved keyboard friendliness",
    "2012-12-25: Version 0.18: major architectural changes, using 'Brainbow' style",
    "2012-12-26: Version 0.19: program overview works again, concept map widgets for editing, rating and displaying work fine",
    "2012-12-28: Version 0.20: got Wine execution working again, rating works partially",
    "2012-12-31: Version 0.21: fixed bugs in cluster dialog, added test concept dialog, temporarily removed concept maps",
    "2013-01-01: Version 0.22: added test node and edge dialogs, removed crosscompiler errors by replacing std::all_of by count_if",
    "2013-01-08: Version 0.23: got editing and rating of concepts working",
    "2013-01-10: Version 0.24: backward-compatibility with previous .cmp files",
    "2013-01-13: Version 0.25: initial (incorrect) rating values calculation",
    "2013-01-18: Version 0.26: calculate rating values correctly",
    "2013-01-20: Version 0.27: added graphics to menu's, using 'Dolphin' style",
    "2013-01-23: Version 0.28: allow ConceptMapEdit arrows having solitary focus, progress on printing",
    "2013-02-12: Version 0.29: changed name to Brainweaver, progress on printing",
    "2013-04-21: Version 0.30: shows sub-concepts maps in rating well, allows saving without going back to the main menu",
    "2013-05-04: Version 0.31: improved printing for student and assessor, first steps in implementing undo functionality",
    "2013-07-27: Version 0.32: first step in semi-automated rating mechanism",
    "2013-08-06: Version 0.33: added icons and artwork",
    "2013-08-18: Version 0.34: fixed file dialog",
    "2013-08-30: Version 0.35: fixed segmentation faults, replaced print dialogs by save file dialogs",
    "2013-09-07: Version 0.36: placed all classes in namespace ribi::pvdb, minor changes",
    "2013-09-15: Version 0.37: minor changes, added wordwrap in concept names",
    "2013-09-21: Version 0.38: minor changes, added wordwrap in examples in concept map widgets",
    "2013-09-29: Version 0.39: minor changes, added wordwrap in examples in rate examples dialog",
    "2013-10-03: Version 0.40: minor changes, added wordwrap in some more player",
    "2013-12-29: Version 0.43: bugfixes, renaming, refactoring, preparing for undo functionality",
    "2013-12-31: Version 0.44: when tallying the relevancies of a concept its connected examples, the node names connected to the edges are displayed",
    "2013-12-31: Version 0.45: sub concept map creation bug fixes",
    "2013-xx-xx: Version 0.46: edges connected to center node have no label",
    "2014-04-19: Version 0.47: hotfix",
    "2014-05-04: Version 0.48: edges connected to center node have center node again",
    "2014-05-11: Version 0.49: wordwrap in tally relevancies dialog",
    "2014-05-18: Version 0.50: edges connected to center node have no label, that cannot be edited"
  };
}
