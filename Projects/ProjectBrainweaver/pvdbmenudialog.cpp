#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "pvdbmenudialog.h"

#include "fuzzy_equal_to.h"
#include "trace.h"

#ifdef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
namespace pvdb {
#endif

pvdb::MenuDialog::MenuDialog()
{

}

const About pvdb::MenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek (programming) and Toine van den Bogaart (research)",
    "Brainweaver",
    "program to create and assess concept maps",
    "the 30th of June 2013",
    "2012-2013",
    "http://www.richelbilderbeek.nl/ProjectBrainweaver.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  a.AddLibrary("fuzzy_equal_to version: " + fuzzy_equal_to::GetVersion());
  return a;
}

const std::string pvdb::MenuDialog::GetVersion()
{
  return "0.32";
}

const std::vector<std::string> pvdb::MenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2012-06-17: Version 0.01: concept version, using 'IronHide' style");
  v.push_back("2012-10-18: Version 0.02: able to crosscompile to windows, few dialogs present");
  v.push_back("2012-10-19: Version 0.03: added use of QtHideAndShowDialog, most dialogs present");
  v.push_back("2012-10-24: Version 0.04: added QtPvdbClusterWidget");
  v.push_back("2012-10-28: Version 0.05: added Cluster and ConceptMap, added AutoSave, ClusterWidget and Cluster work okay, file I/O working okay");
  v.push_back("2012-11-10: Version 0.06: added first working QtConceptMap");
  v.push_back("2012-11-13: Version 0.07: added edges and helpers to QtConceptMap");
  v.push_back("2012-11-15: Version 0.08: concepts on edges in QtConceptMap are editable, QtConceptMap always looks pretty");
  v.push_back("2012-11-18: Version 0.09: added edges with arrowheads, deletion of nodes and edges possible, put help items in status bar");
  v.push_back("2012-11-22: Version 0.10: editing of concepts and their examples, tools icon (doing nothing yet)");
  v.push_back("2012-11-24: Version 0.11: allow adding new relations");
  v.push_back("2012-11-25: Version 0.12: allow connecting to center node");
  v.push_back("2012-11-27: Version 0.13: added program flow tests");
  v.push_back("2012-11-28: Version 0.14: fixed many program flow and widget and dialog bugs");
  v.push_back("2012-12-02: Version 0.15: also relations can move");
  v.push_back("2012-12-08: Version 0.16: use quadratic Bezier curve for relations, locations of moved relations are saved");
  v.push_back("2012-12-13: Version 0.17: improved keyboard friendliness");
  v.push_back("2012-12-25: Version 0.18: major architectural changes, using 'Brainbow' style");
  v.push_back("2012-12-26: Version 0.19: program overview works again, concept map widgets for editing, rating and displaying work fine");
  v.push_back("2012-12-28: Version 0.20: got Wine execution working again, rating works partially");
  v.push_back("2012-12-31: Version 0.21: fixed bugs in cluster dialog, added test concept dialog, temporarily removed concept maps");
  v.push_back("2013-01-01: Version 0.22: added test node and edge dialogs, removed crosscompiler errors by replacing std::all_of by count_if");
  v.push_back("2013-01-08: Version 0.23: got editing and rating of concepts working");
  v.push_back("2013-01-10: Version 0.24: backward-compatibility with previous .cmp files");
  v.push_back("2013-01-13: Version 0.25: initial (incorrect) rating values calculation");
  v.push_back("2013-01-18: Version 0.26: calculate rating values correctly");
  v.push_back("2013-01-20: Version 0.27: added graphics to menu's, using 'Dolphin' style");
  v.push_back("2013-01-23: Version 0.28: allow ConceptMapEdit arrows having solitary focus, progress on printing");
  v.push_back("2013-02-12: Version 0.29: changed name to Brainweaver (formely called ProjectVanDenBogaart), progress on printing");
  v.push_back("2013-04-21: Version 0.30: Shows sub-concepts maps in rating well, allows saving without going back to the main menu");
  v.push_back("2013-05-04: Version 0.31: Improved printing for student and assessor, first steps in implementing undo functionality");
  v.push_back("2013-05-12: Version 0.32: Fist step in semi-automated rating mechanism");
  return v;
}

#ifdef PVDB_KEEP_NAMESPACE_IN_CPP_FILES
} //~namespace pvdb
#endif
