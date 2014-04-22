//---------------------------------------------------------------------------
/*
GTST, Game Theory Server
Copyright (C) 2011 Richel Bilderbeek

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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "projectgtstmenudialog.h"

#include <boost/filesystem.hpp>

#include <Wt/WBreak>
#include <Wt/WGroupBox>
#include <Wt/WImage>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WText>
#include <Wt/WTextArea>
#include <Wt/WTimer>
#include <Wt/WStackedWidget>
#include <Wt/WMenu>

//QFile must be #included after Wt header files
#include <QFile>

#include "about.h"
#include "administratordialog.h"
#include "all_serverstates.h"
#include "copy_if.h"
#include "counter.h"
#include "debugdialog.h"
#include "fuzzy_equal_to.h"
#include "groupfinished.h"
#include "grouploggedin.h"
#include "groupnotloggedin.h"
#include "groups.h"
#include "ipaddress.h"
#include "led.h"
#include "ledwidget.h"
#include "logfile.h"
#include "multiplechoicequestion.h"
#include "multiplechoicequestiondialog.h"
#include "participant.h"
#include "participantdialog.h"
#include "participantdialogstateassignpayoff.h"
#include "participantdialogstatechat.h"
#include "participantdialogstatechooseaction.h"
#include "participantdialogstatefinished.h"
#include "participantdialogstategroupassign.h"
#include "participantdialogstategroupreassign.h"
#include "participantdialogstatenotloggedin.h"
#include "participantdialogstateviewresultsgroup.h"
#include "participantdialogstateviewresultsvoting.h"
#include "participantdialogstatevoting.h"
#include "rainbow.h"
#include "resources.h"
#include "server.h"
#include "shape.h"
#include "shapewidget.h"
#include "stopwatch.h"
#include "trace.h"
#include "widget.h"
#include "wtaboutdialog.h"
#include "wtautoconfig.h"
#include "wtgroupwidget.h"
#include "wtmultiplechoicequestiondialog.h"
#include "wtserverpusher.h"
#include "wtserverpusherclient.h"
#include "wtselectfiledialog.h"
#include "wtshapewidget.h"
#include "wtshapegroupwidget.h"
#include "wttimedserverpusher.h"
#include "wttimedserverpusherclient.h"


#pragma GCC diagnostic pop

ribi::gtst::MenuDialog::MenuDialog(const SafeIpAddress * const ip_address)
  : m_server(Server::Get())
{
  assert(m_server);
  TRACE_FUNC();
  {
    //MainTimer::Get();
  }
  {
    m_server->TestMe();
  }
  this->setContentAlignment(Wt::AlignCenter);
  {
    Wt::WText * const title = new Wt::WText("GTST");
    title->setStyleClass("title");
    this->addWidget(title);
  }
  //Menu
  {
    Wt::WStackedWidget * const contents = new Wt::WStackedWidget;
    Wt::WMenu * const menu = new Wt::WMenu(contents,Wt::Horizontal);
    //Using CSS styleclass is the best (only?) way to display the menu well
    menu->setStyleClass("menu");
    {
      Wt::WMenuItem * const item = new Wt::WMenuItem(
        "Welcome",
        CreateNewWelcomeDialog((ip_address)));
      menu->addItem(item);
    }
    {
      Wt::WMenuItem * const item = new Wt::WMenuItem(
        "Participant",
        new ParticipantDialog(m_server,ip_address));
      menu->addItem(item);
    }
    {
      Wt::WMenuItem * const item = new Wt::WMenuItem(
        "Administrator",
        new AdministratorDialog(m_server));
      menu->addItem(item);
    }
    {
      Wt::WMenuItem * const item = new Wt::WMenuItem(
        "Debug",
        new DebugDialog(m_server));
      menu->addItem(item);
    }
    {
      Wt::WMenuItem * const item = new Wt::WMenuItem(
        "About the experiment",
        CreateNewAboutTheExperimentDialog());
      menu->addItem(item);
    }
    {
      Wt::WMenuItem * const item = new Wt::WMenuItem(
        "About this program",
        CreateNewAboutDialog());
      menu->addItem(item);
    }

    //Display menu on top
    this->addWidget(menu);
    this->addWidget(new Wt::WBreak);
    //Display contents below menu
    this->addWidget(contents);
  }
}

ribi::WtAboutDialog * ribi::gtst::MenuDialog::CreateNewAboutDialog() const
{
  About a = GetAbout();
  WtAboutDialog * const d = new WtAboutDialog(a,false);
  assert(d);
  return d;
}

Wt::WContainerWidget * ribi::gtst::MenuDialog::CreateNewAboutTheExperimentDialog() const
{
  Wt::WContainerWidget * const dialog = new Wt::WContainerWidget;
  dialog->setContentAlignment(Wt::AlignCenter);
  //Menu
  {
    Wt::WStackedWidget * const contents = new Wt::WStackedWidget;
    Wt::WMenu * const menu = new Wt::WMenu(contents,Wt::Horizontal);
    //Using CSS styleclass is the best (only?) way to display the menu well
    menu->setStyleClass("menu");
    {
      Wt::WMenuItem * const item = new Wt::WMenuItem(
        "General",
        CreateNewAboutTheExperimentGeneralDialog());
      menu->addItem(item);
    }
    {
      Wt::WMenuItem * const item = new Wt::WMenuItem(
        "Experiment flow",
        CreateNewAboutTheExperimentFlowDialog());
      menu->addItem(item);
    }
    {
      Wt::WMenuItem * const item = new Wt::WMenuItem(
        "Parameters",
        CreateNewAboutTheExperimentParametersDialog());
      menu->addItem(item);
    }
    dialog->addWidget(menu);
    dialog->addWidget(new Wt::WBreak);
    //Display contents below menu
    dialog->addWidget(contents);
  }

  return dialog;
}

Wt::WContainerWidget * ribi::gtst::MenuDialog::CreateNewAboutTheExperimentFlowDialog() const
{
  Wt::WContainerWidget * const dialog = new Wt::WContainerWidget;
  dialog->setContentAlignment(Wt::AlignCenter);
  dialog->addWidget(new Wt::WBreak);
  new Wt::WBreak(dialog);
  new Wt::WImage(Resources::GetImageFilenameExperiment(),dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WImage(Resources::GetImageFilenamePeriod(),dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WImage(Resources::GetImageFilenameCycle(),dialog);
  return dialog;
}

Wt::WContainerWidget * ribi::gtst::MenuDialog::CreateNewAboutTheExperimentGeneralDialog() const
{
  Wt::WContainerWidget * const dialog = new Wt::WContainerWidget;
  dialog->setContentAlignment(Wt::AlignCenter);
  dialog->addWidget(new Wt::WBreak);
  new Wt::WBreak(dialog);
  new Wt::WLabel("GTST (\'Game Theory ServerT\') is an open source program",dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("for performing game theory experiments.",dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("When GTST is started on a server, both administrators",dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("and participants can log in and do game theory experiments.",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("GTST has been developed by:",dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("* Lucas Molleman: researcher",dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("* Piet van den Berg: researcher",dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("* Richel Bilderbeek: programming",dialog);
  return dialog;
}

Wt::WContainerWidget * ribi::gtst::MenuDialog::CreateNewAboutTheExperimentParametersDialog() const
{
  Wt::WContainerWidget * const dialog = new Wt::WContainerWidget;
  dialog->setContentAlignment(Wt::AlignCenter);
  dialog->addWidget(new Wt::WBreak);
  new Wt::WBreak(dialog);
  {
    Wt::WGroupBox * const box = new Wt::WGroupBox("Assign payoff",dialog);
    box->addWidget(new Wt::WImage(Resources::GetImageFilenameParticipantDialogAssignPayoff()));
  }
  new Wt::WBreak(dialog);
  {
    Wt::WGroupBox * const box = new Wt::WGroupBox("Chat",dialog);
    box->addWidget(new Wt::WImage(Resources::GetImageFilenameParticipantDialogChat()));
  }
  new Wt::WBreak(dialog);
  {
    Wt::WGroupBox * const box = new Wt::WGroupBox("Choose action",dialog);
    box->addWidget(new Wt::WImage(Resources::GetImageFilenameParticipantDialogChooseAction()));
  }
  new Wt::WBreak(dialog);
  {
    Wt::WGroupBox * const box = new Wt::WGroupBox("Finished",dialog);
    box->addWidget(new Wt::WImage(Resources::GetImageFilenameParticipantDialogFinished()));
  }
  new Wt::WBreak(dialog);
  {
    Wt::WGroupBox * const box = new Wt::WGroupBox("Group assign",dialog);
    box->addWidget(new Wt::WImage(Resources::GetImageFilenameParticipantDialogGroupAssign()));
  }
  new Wt::WBreak(dialog);
  {
    Wt::WGroupBox * const box = new Wt::WGroupBox("Group re-assign",dialog);
    box->addWidget(new Wt::WImage(Resources::GetImageFilenameParticipantDialogGroupReAssign()));
  }
  new Wt::WBreak(dialog);
  {
    Wt::WGroupBox * const box = new Wt::WGroupBox("Logged in",dialog);
    box->addWidget(new Wt::WImage(Resources::GetImageFilenameParticipantDialogLoggedIn()));
  }
  new Wt::WBreak(dialog);
  {
    Wt::WGroupBox * const box = new Wt::WGroupBox("Not logged in",dialog);
    box->addWidget(new Wt::WImage(Resources::GetImageFilenameParticipantDialogNotLoggedIn()));
  }
  new Wt::WBreak(dialog);
  {
    Wt::WGroupBox * const box = new Wt::WGroupBox("View results group",dialog);
    box->addWidget(new Wt::WImage(Resources::GetImageFilenameParticipantDialogViewResultsGroup()));
  }
  new Wt::WBreak(dialog);
  {
    Wt::WGroupBox * const box = new Wt::WGroupBox("View results voting",dialog);
    box->addWidget(new Wt::WImage(Resources::GetImageFilenameParticipantDialogViewResultsVoting()));
  }
  new Wt::WBreak(dialog);
  {
    Wt::WGroupBox * const box = new Wt::WGroupBox("Voting",dialog);
    box->addWidget(new Wt::WImage(Resources::GetImageFilenameParticipantDialogVoting()));
  }
  return dialog;
}

Wt::WContainerWidget * ribi::gtst::MenuDialog::CreateNewWelcomeDialog(
  const SafeIpAddress * const ip_address) const
{
  Wt::WContainerWidget * const dialog = new Wt::WContainerWidget;

  dialog->setContentAlignment(Wt::AlignCenter);
  dialog->addWidget(new Wt::WBreak);
  new Wt::WLabel("Welcome to GTST",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("Choose one of the top items to log in as a participant or administrator",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("Your IP address is ",dialog);
  new Wt::WLabel(ip_address->Get().c_str(),dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  return dialog;
}

const ribi::About ribi::gtst::MenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "GTST",
    "game theory experiment server",
    "the 1st of September 2011",
    "2011",
    "http://www.richelbilderbeek.nl/ProjectGtst.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Copy_if version: " + Copy_if_version::GetVersion());
  a.AddLibrary("FunctionParser (by Warp) version: 4.4.3");
  a.AddLibrary("Fuzzy_equal_to version: " + fuzzy_equal_to::GetVersion());
  a.AddLibrary("IpAddress version: " + IpAddress::GetVersion());
  a.AddLibrary("Led version: " + Led::GetVersion());
  a.AddLibrary("LedWidget version: " + LedWidget::GetVersion());
  a.AddLibrary("MultipleChoiceQuestion version: " + MultipleChoiceQuestion::GetVersion());
  a.AddLibrary("MultipleChoiceQuestionDialog version: " + MultipleChoiceQuestionDialog::GetVersion());
  a.AddLibrary("Question version: " + Question::GetVersion());
  a.AddLibrary("QuestionDialog version: " + QuestionDialog::GetVersion());
  a.AddLibrary("Rainbow version: " + Rainbow::GetVersion());
  a.AddLibrary("Rectangle version: " + Rect::GetVersion());
  a.AddLibrary("Shape version: " + Shape::GetVersion());
  a.AddLibrary("ShapeWidget version: " + ShapeWidget::GetVersion());
  a.AddLibrary("Stopwatch version: " + Stopwatch::GetVersion());
  a.AddLibrary("Trace version: "  + Trace::GetVersion());
  a.AddLibrary("Widget version: "  + Widget::GetVersion());
  a.AddLibrary("WtAutoConfig version: " + WtAutoConfig::GetVersion());
  a.AddLibrary("WtGroupWidget version: " + WtGroupWidget::GetVersion());
  a.AddLibrary("WtMultipleChoiceQuestionDialog version: " + WtMultipleChoiceQuestionDialog::GetVersion());
  a.AddLibrary("WtQuestionDialog version: " + WtQuestionDialog::GetVersion());
  a.AddLibrary("WtServerPusher version: " + WtServerPusher::GetVersion());
  a.AddLibrary("WtServerPusherClient version: " + WtServerPusherClient::GetVersion());
  a.AddLibrary("WtSelectFileDialog version: " + WtSelectFileDialog::GetVersion());
  a.AddLibrary("WtShapeGroupWidget version: " + WtShapeGroupWidget::GetVersion());
  a.AddLibrary("WtShapeWidget version: " + WtShapeWidget::GetVersion());
  a.AddLibrary("WtTimedServerPusher version: " + WtTimedServerPusher::GetVersion());
  a.AddLibrary("WtTimedServerPusherClient version: " + WtTimedServerPusherClient::GetVersion());
  return a;
}

const std::string ribi::gtst::MenuDialog::GetVersion()
{
  return "1.02";
}

const std::vector<std::string> ribi::gtst::MenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-05-09: Version 0.01: initial version, then called ProjectGameTheory");
  v.push_back("2011-05-10: Version 0.02: made bulletproof (at that time)");
  v.push_back("2011-05-11: Version 0.03: added group chat");
  v.push_back("2011-05-11: Version 0.04: added experiment parameter file upload");
  v.push_back("2011-05-11: Version 0.05: added \'I want to participate\' checkbox");
  v.push_back("2011-05-12: Version 0.06: added first step in adding parameter options");
  v.push_back("2011-05-12: Version 0.07: visualizing unassigned participants");
  v.push_back("2011-05-13: Version 0.08: added IP address, added choosing actions by participants");
  v.push_back("2011-05-16: Version 0.09: improved administrator section");
  v.push_back("2011-05-16: Version 0.10: fixed group chat");
  v.push_back("2011-05-16: Version 0.11: added chat tags");
  v.push_back("2011-05-16: Version 0.12: administrator can set experiment phase");
  v.push_back("2011-05-16: Version 0.13: one IP address per participant");
  v.push_back("2011-05-17: Version 0.14: added Chinese sayings, added choose action state");
  v.push_back("2011-05-17: Version 0.15: add timer to chatting, chosing actions and viewing group results");
  v.push_back("2011-05-18: Version 0.16: standarized parameters file, implemented first step of Parameters");
  v.push_back("2011-05-19: Version 0.17: created Parameters structure with default initialization");
  v.push_back("2011-05-19: Version 0.18: created complete backbone of the program");
  v.push_back("2011-05-19: Version 0.19: added waiting for all participants to login");
  v.push_back("2011-05-19: Version 0.20: ID\'s are assigned to participants at login");
  v.push_back("2011-05-23: Version 0.21: implemented voting and choose action step that waits for all before going on");
  v.push_back("2011-05-23: Version 0.22: assign and view payoffs from IPGG");
  v.push_back("2011-05-23: Version 0.23: added experiment flow");
  v.push_back("2011-05-23: Version 0.24: added asynchronous participance");
  v.push_back("2011-05-23: Version 0.25: fixed multiple-vote error, added viewing voting results");
  v.push_back("2011-05-23: Version 0.26: added read-only textarea to stylesheet");
  v.push_back("2011-05-23: Version 0.27: wait for all participants to vote/choose action by default");
  v.push_back("2011-05-23: Version 0.28: repeat the IPGG as often as desired");
  v.push_back("2011-05-24: Version 0.29: improved time display, removed obsolete class, improved documentation");
  v.push_back("2011-05-24: Version 0.30: polished GUI");
  v.push_back("2011-05-24: Version 0.31: fixed important bug in flow, added option to delete patricipants");
  v.push_back("2011-05-24: Version 0.32: implemented ServerTest::TestParticipant");
  v.push_back("2011-05-25: Version 0.33: implemented ServerTest::TestServer1");
  v.push_back("2011-05-25: Version 0.34: implemented ServerTest::TestServer4, updated reading from a parameter file");
  v.push_back("2011-05-26: Version 0.35: added random range in IPGG cycles from parameter file");
  v.push_back("2011-05-26: Version 0.36: added geometric distribution in IPGG cycles from parameter file");
  v.push_back("2011-05-26: Version 0.37: added dynamics group formation, renamed program to GTST");
  v.push_back("2011-05-28: Version 0.38: fixed asynchronous participation");
  v.push_back("2011-05-29: Version 0.39: major refactoring, added ParticipantState to Participant");
  v.push_back("2011-06-01: Version 0.40: major refactoring, put Participants in Groups");
  v.push_back("2011-06-04: Version 0.41: major refactoring, added XML pretty printing of parameter files");
  v.push_back("2011-06-11: Version 0.42: major refactoring, added Debug menu item, successful static group assignment trials");
  v.push_back("2011-06-11: Version 0.43: successful dynamic group assignment trials");
  v.push_back("2011-06-20: Version 0.44: added majority voting and the consensus reached");
  v.push_back("2011-06-21: Version 0.45: respond to the results of the added majority voting");
  v.push_back("2011-06-22: Version 0.46: start using WtSafeTimer");
  v.push_back("2011-06-22: Version 0.47: WtSafeTimer appears to yield a stable heartbeat");
  v.push_back("2011-06-26: Version 0.48: added payoff to earnings parameter option");
  v.push_back("2011-07-03: Version 0.49: Fixed bug, added WtSelectFileDialog");
  v.push_back("2011-07-14: Version 0.50: added first step of quiz state, done some gprof profiling, made some small cosmetic changes");
  v.push_back("2011-07-15: Version 0.51: added download of log files, prevent user uploading parameter file with wrong groups or wrong-sized groups");
  v.push_back("2011-07-19: Version 0.52: changed character chat tags to WtShapeWidgets");
  v.push_back("2011-07-26: Version 0.53: let participant know what happens to him/her each period");
  v.push_back("2011-08-05: Version 0.54: switched to using WtServerPusher and WtTimedServerPusher");
  v.push_back("2011-08-08: Version 0.55: fixed chat tag errors (in WtShapeWidget)");
  v.push_back("2011-08-11: Version 0.56: getting it to work at single-core server");
  v.push_back("2011-08-15: Version 0.57: many small bugfixes, improved XML produced");
  v.push_back("2011-08-15: Version 0.58: policing visible for contestants and logged in XML, show ParticipantDialog and AdministratorDialog being responsive");
  v.push_back("2011-08-19: Version 0.59: fixed bugs in not able to have two experiments after one another, fixed deadlock, show voting result, improved administrator's view of the groups");
  v.push_back("2011-08-29: Version 1.00: initial version");
  v.push_back("2011-09-01: Version 1.01: changed text and GUI, removed status LEDs in debug version");
  v.push_back("2011-09-11: Version 1.02: small bugfix");
  return v;
}

