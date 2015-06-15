//---------------------------------------------------------------------------
/*
Project Richel Bilderbeek, Richel Bilderbeek's work
Copyright (C) 2010-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ProjectRichelBilderbeek.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <Wt/WApplication>
#include <Wt/WEnvironment>

#include "fileio.h"
#include "ipaddress.h"
#include "trace.h"
#include "wtautoconfig.h"
#include "wtentrance.h"
#include "wtselectfiledialog.h"
#include "wtrichelbilderbeekmenudialog.h"
#pragma GCC diagnostic pop

///TODO
///List sorted on my priority
/// - Add an IP-address/'personal' page
/// - Add SearchAndDestroyChess
/// - Add TestCss to change IP-address/'personal' CSS
/// - Let all WtRichelBilderbeek classes be documented using Doxygen
/// - Test Wt real-time gaming possibilities

struct WtApplication : public Wt::WApplication
{
  WtApplication(const Wt::WEnvironment& env)
  : Wt::WApplication(env)
  {
    this->setTitle("Project Richel Bilderbeek");
    this->useStyleSheet("wt.css");
    this->enableUpdates(true);
    boost::shared_ptr<const ribi::IpAddress> ip_address(new ribi::IpAddress(env.clientAddress()));
    ribi::WtEntrance::Get()->Visit(ip_address.get());
    root()->addWidget(new ribi::RichelBilderbeek::WtMenuDialog(ip_address->Get()));
  }
};

Wt::WApplication *createApplication(
  const Wt::WEnvironment& env)
{
  return new WtApplication(env);
}

int main(int argc, char **argv)
{
  START_TRACE();

  ribi::WtSelectFileDialog::SetPath(ribi::fileio::FileIo().GetPath(argv[0]));
  ribi::WtAutoConfig::SaveDefaultStylesheet();
  ribi::WtAutoConfig a(argc,argv,createApplication);
  return a.Run();
}

/*



INCLUDEPATH += \
    ../../Classes/CppWtAboutDialog \
    ../../Classes/CppWtAutoConfig \
    ../../Classes/CppWtConnectThreeWidget \
    ../../Classes/CppWtDialWidget \
    ../../Classes/CppWtEntrance \
    ../../Classes/CppWtExercise \
    ../../Classes/CppWtGroupWidget \
    ../../Classes/CppWtLedWidget \
    ../../Classes/CppWtMultipleChoiceQuestionDialog \
    ../../Classes/CppWtMysteryMachineWidget \
    ../../Classes/CppWtOpenQuestionDialog \
    ../../Classes/CppWtQuestionDialog \
    ../../Classes/CppWtRichelBilderbeekGalleryDialog \
    ../../Classes/CppWtRubiksClockWidget \
    ../../Classes/CppWtSelectFileDialog \
    ../../Classes/CppWtServerPusher \
    ../../Classes/CppWtShapeGroupWidget \
    ../../Classes/CppWtShapeWidget \
    ../../Classes/CppWtShinyButtonWidget \
    ../../Classes/CppWtTicTacToeWidget \
    ../../Classes/CppWtTimedServerPusher \
    ../../Classes/CppWtToggleButtonWidget \
    ../../Games/GameConnectThree \
    ../../Games/GamePylos \
    ../../Games/GameRubiksClock \
    ../../Games/GameTicTacToe \
    ../../Projects/ProjectGtst \
    ../../Projects/RichelbilderbeekNl \
    ../../Tools/ToolAsciiArter \
    ../../Tools/ToolCodeToHtml \
    ../../Tools/ToolCreateQtProjectZipFile \
    ../../Tools/ToolEncranger \
    ../../Tools/ToolHometrainer \
    ../../Tools/ToolKalmanFilterer \
    ../../Tools/ToolRandomCode \
    ../../Tools/ToolRegexTester \
    ../../Tools/ToolSimMysteryMachine \
    ../../Tools/ToolStateObserver \
    ../../Tools/ToolTestDial \
    ../../Tools/ToolTestEntrance \
    ../../Tools/ToolTestExercise \
    ../../Tools/ToolTestFunctionParser \
    ../../Tools/ToolTestGroupWidget \
    ../../Tools/ToolTestLed \
    ../../Tools/ToolTestNewickVector \
    ../../Tools/ToolTestQrcFile \
    ../../Tools/ToolTestQtArrowItems \
    ../../Tools/ToolTestQtCreatorProFile \
    ../../Tools/ToolTestQuestion \
    ../../Tools/ToolTestSelectFileDialog \
    ../../Tools/ToolTestServerPusher \
    ../../Tools/ToolTestShape \
    ../../Tools/ToolTestShinyButton \
    ../../Tools/ToolTestTimedServerPusher \
    ../../Tools/ToolTestToggleButton \
    ../../Tools/ToolTestTwoDigitNewick \
    ../../Tools/ToolTimePoll

SOURCES += \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp \
    ../../Classes/CppWtConnectThreeWidget/wtconnectthreewidget.cpp \
    ../../Classes/CppWtDialWidget/wtdialwidget.cpp \
    ../../Classes/CppWtEntrance/wtentrance.cpp \
    ../../Classes/CppWtExercise/wtexercise.cpp \
    ../../Classes/CppWtGroupWidget/wtgroupwidget.cpp \
    ../../Classes/CppWtLedWidget/wtledwidget.cpp \
    ../../Classes/CppWtMultipleChoiceQuestionDialog/wtmultiplechoicequestiondialog.cpp \
    ../../Classes/CppWtMysteryMachineWidget/wtmysterymachinewidget.cpp \
    ../../Classes/CppWtOpenQuestionDialog/wtopenquestiondialog.cpp \
    ../../Classes/CppWtQuestionDialog/wtquestiondialog.cpp \
    ../../Classes/CppWtRichelBilderbeekGalleryDialog/wtrichelbilderbeekgallerydialog.cpp \
    ../../Classes/CppWtRubiksClockWidget/wtrubiksclockwidget.cpp \
    ../../Classes/CppWtSelectFileDialog/wtselectfiledialog.cpp \
    ../../Classes/CppWtServerPusher/wtserverpusher.cpp \
    ../../Classes/CppWtServerPusher/wtserverpusherclient.cpp \
    ../../Classes/CppWtShapeGroupWidget/wtshapegroupwidget.cpp \
    ../../Classes/CppWtShapeWidget/wtshapewidget.cpp \
    ../../Classes/CppWtShinyButtonWidget/wtshinybuttonwidget.cpp \
    ../../Classes/CppWtTicTacToeWidget/wttictactoewidget.cpp \
    ../../Classes/CppWtTimedServerPusher/wttimedserverpusher.cpp \
    ../../Classes/CppWtTimedServerPusher/wttimedserverpusherclient.cpp \
    ../../Classes/CppWtToggleButtonWidget/wttogglebuttonwidget.cpp \
    ../../Games/GameConnectThree/qtconnectthreeresources.cpp \
    ../../Games/GameConnectThree/wtconnectthreegamedialog.cpp \
    ../../Games/GameConnectThree/wtconnectthreemenudialog.cpp \
    ../../Games/GameConnectThree/wtconnectthreeresources.cpp \
    ../../Games/GameConnectThree/wtselectplayerwidget.cpp \
    ../../Games/GameRubiksClock/wtrubiksclockmaindialog.cpp \
    ../../Games/GameRubiksClock/wtrubiksclockmenudialog.cpp \
    ../../Games/GameTicTacToe/wttictactoegamedialog.cpp \
    ../../Games/GameTicTacToe/wttictactoemenudialog.cpp \
    ../../Projects/ProjectGtst/administrator.cpp \
    ../../Projects/ProjectGtst/administratordialog.cpp \
    ../../Projects/ProjectGtst/administratordialogstate.cpp \
    ../../Projects/ProjectGtst/administratordialogstateloggedin.cpp \
    ../../Projects/ProjectGtst/administratordialogstatenotloggedin.cpp \
    ../../Projects/ProjectGtst/administrators.cpp \
    ../../Projects/ProjectGtst/chatmessage.cpp \
    ../../Projects/ProjectGtst/chatshapefactory.cpp \
    ../../Projects/ProjectGtst/chooseactionoption.cpp \
    ../../Projects/ProjectGtst/debugdialog.cpp \
    ../../Projects/ProjectGtst/group.cpp \
    ../../Projects/ProjectGtst/groupassigner.cpp \
    ../../Projects/ProjectGtst/groupfinished.cpp \
    ../../Projects/ProjectGtst/grouploggedin.cpp \
    ../../Projects/ProjectGtst/groupnotloggedin.cpp \
    ../../Projects/ProjectGtst/groupparticipating.cpp \
    ../../Projects/ProjectGtst/groups.cpp \
    ../../Projects/ProjectGtst/logfile.cpp \
    ../../Projects/ProjectGtst/parameters.cpp \
    ../../Projects/ProjectGtst/parametersassignpayoff.cpp \
    ../../Projects/ProjectGtst/parameterschat.cpp \
    ../../Projects/ProjectGtst/parameterschooseaction.cpp \
    ../../Projects/ProjectGtst/parametersfinished.cpp \
    ../../Projects/ProjectGtst/parametersgroupassign.cpp \
    ../../Projects/ProjectGtst/parametersgroupreassign.cpp \
    ../../Projects/ProjectGtst/parametersquiz.cpp \
    ../../Projects/ProjectGtst/parametersviewresultsgroup.cpp \
    ../../Projects/ProjectGtst/parametersviewresultsvoting.cpp \
    ../../Projects/ProjectGtst/parametersvoting.cpp \
    ../../Projects/ProjectGtst/participant.cpp \
    ../../Projects/ProjectGtst/participantdialog.cpp \
    ../../Projects/ProjectGtst/participantdialogstate.cpp \
    ../../Projects/ProjectGtst/participantdialogstateassignpayoff.cpp \
    ../../Projects/ProjectGtst/participantdialogstatechat.cpp \
    ../../Projects/ProjectGtst/participantdialogstatechooseaction.cpp \
    ../../Projects/ProjectGtst/participantdialogstatefinished.cpp \
    ../../Projects/ProjectGtst/participantdialogstategroupassign.cpp \
    ../../Projects/ProjectGtst/participantdialogstategroupreassign.cpp \
    ../../Projects/ProjectGtst/participantdialogstateloggedin.cpp \
    ../../Projects/ProjectGtst/participantdialogstatenotloggedin.cpp \
    ../../Projects/ProjectGtst/participantdialogstatequiz.cpp \
    ../../Projects/ProjectGtst/participantdialogstates.cpp \
    ../../Projects/ProjectGtst/participantdialogstateviewresultsgroup.cpp \
    ../../Projects/ProjectGtst/participantdialogstateviewresultsvoting.cpp \
    ../../Projects/ProjectGtst/participantdialogstatevoting.cpp \
    ../../Projects/ProjectGtst/participantstate.cpp \
    ../../Projects/ProjectGtst/participantstateassignpayoff.cpp \
    ../../Projects/ProjectGtst/participantstatechat.cpp \
    ../../Projects/ProjectGtst/participantstatechooseaction.cpp \
    ../../Projects/ProjectGtst/participantstatefinished.cpp \
    ../../Projects/ProjectGtst/participantstategroupassign.cpp \
    ../../Projects/ProjectGtst/participantstategroupreassign.cpp \
    ../../Projects/ProjectGtst/participantstateloggedin.cpp \
    ../../Projects/ProjectGtst/participantstatenotloggedin.cpp \
    ../../Projects/ProjectGtst/participantstatequiz.cpp \
    ../../Projects/ProjectGtst/participantstateviewresultsgroup.cpp \
    ../../Projects/ProjectGtst/participantstateviewresultsvoting.cpp \
    ../../Projects/ProjectGtst/participantstatevoting.cpp \
    ../../Projects/ProjectGtst/payoff.cpp \
    ../../Projects/ProjectGtst/payoffs.cpp \
    ../../Projects/ProjectGtst/projectgtstmenudialog.cpp \
    ../../Projects/ProjectGtst/repeatassigner.cpp \
    ../../Projects/ProjectGtst/repeatassignerfixed.cpp \
    ../../Projects/ProjectGtst/repeatassignerrandomgeometric.cpp \
    ../../Projects/ProjectGtst/repeatassignerrandomuniform.cpp \
    ../../Projects/ProjectGtst/resources.cpp \
    ../../Projects/ProjectGtst/server.cpp \
    ../../Projects/ProjectGtst/serverstate.cpp \
    ../../Projects/ProjectGtst/serverstateassignpayoff.cpp \
    ../../Projects/ProjectGtst/serverstatechat.cpp \
    ../../Projects/ProjectGtst/serverstatechooseaction.cpp \
    ../../Projects/ProjectGtst/serverstatefinished.cpp \
    ../../Projects/ProjectGtst/serverstategroupassign.cpp \
    ../../Projects/ProjectGtst/serverstategroupreassign.cpp \
    ../../Projects/ProjectGtst/serverstatequiz.cpp \
    ../../Projects/ProjectGtst/serverstates.cpp \
    ../../Projects/ProjectGtst/serverstateviewresultsgroup.cpp \
    ../../Projects/ProjectGtst/serverstateviewresultsvoting.cpp \
    ../../Projects/ProjectGtst/serverstatevoting.cpp \
    ../../Projects/ProjectGtst/serverstatewaiting.cpp \
    ../../Projects/ProjectGtst/state.cpp \
    ../../Projects/ProjectGtst/test.cpp \
    ../../Projects/ProjectGtst/testparameterparsing.cpp \
    ../../Projects/ProjectGtst/testparameters.cpp \
    ../../Projects/ProjectGtst/testparticipant.cpp \
    ../../Projects/ProjectGtst/teststate.cpp \
    ../../Projects/ProjectGtst/vote.cpp \
    ../../Projects/ProjectGtst/votingoption.cpp \
    ../../Projects/RichelbilderbeekNl/qtrichelbilderbeekgalleryresources.cpp \
    ../../Tools/ToolAsciiArter/wtasciiartermaindialog.cpp \
    ../../Tools/ToolCodeToHtml/wtcodetohtmldialog.cpp \
    ../../Tools/ToolCodeToHtml/wtcodetohtmlmenudialog.cpp \
    ../../Tools/ToolHometrainer/wthometrainerloadexercisedialog.cpp \
    ../../Tools/ToolHometrainer/wthometrainermenudialog.cpp \
    ../../Tools/ToolHometrainer/wthometrainerstartexercisedialog.cpp \
    ../../Tools/ToolHometrainer/wtselecthometrainerfiledialog.cpp \
    ../../Tools/ToolRandomCode/wtrandomcodegeneratedialog.cpp \
    ../../Tools/ToolRandomCode/wtrandomcodemenudialog.cpp \
    ../../Tools/ToolSimMysteryMachine/wtsimmysterymachinemaindialog.cpp \
    ../../Tools/ToolSimMysteryMachine/wtsimmysterymachinemenudialog.cpp \
    ../../Tools/ToolTestDial/wttestdialmaindialog.cpp \
    ../../Tools/ToolTestDial/wttestdialmenudialog.cpp \
    ../../Tools/ToolEncranger/wttoolencrangermaindialog.cpp \
    ../../Tools/ToolEncranger/wttoolencrangermenudialog.cpp \
    ../../Tools/ToolTestEntrance/wttestentrancemaindialog.cpp \
    ../../Tools/ToolTestEntrance/wttestentrancemenudialog.cpp \
    ../../Tools/ToolTestExercise/wttestexercisemaindialog.cpp \
    ../../Tools/ToolTestExercise/wttestexercisemenudialog.cpp \
    ../../Tools/ToolTestFunctionParser/wttestfunctionparsermaindialog.cpp \
    ../../Tools/ToolTestFunctionParser/wttestfunctionparsermenudialog.cpp \
    ../../Tools/ToolTestGroupWidget/wttestgroupwidgetmaindialog.cpp \
    ../../Tools/ToolTestGroupWidget/wttestgroupwidgetmenudialog.cpp \
    ../../Tools/ToolTestLed/wttestledmaindialog.cpp \
    ../../Tools/ToolTestLed/wttestledmenudialog.cpp \
    ../../Tools/ToolTestNewickVector/wttestnewickvectordialog.cpp \
    ../../Tools/ToolTestQuestion/wttestquestionmaindialog.cpp \
    ../../Tools/ToolTestQuestion/wttestquestionmenudialog.cpp \
    ../../Tools/ToolTestSelectFileDialog/wttestselectfiledialogmaindialog.cpp \
    ../../Tools/ToolTestSelectFileDialog/wttestselectfiledialogmenudialog.cpp \
    ../../Tools/ToolTestServerPusher/testserverpusherdata.cpp \
    ../../Tools/ToolTestServerPusher/testserverpushermenudialog.cpp \
    ../../Tools/ToolTestServerPusher/testserverpusherwtmaindialog.cpp \
    ../../Tools/ToolTestServerPusher/testserverpusherwtmenudialog.cpp \
    ../../Tools/ToolTestShape/wttestshapemaindialog.cpp \
    ../../Tools/ToolTestShape/wttestshapemenudialog.cpp \
    ../../Tools/ToolTestShinyButton/wttestshinybuttonmaindialog.cpp \
    ../../Tools/ToolTestShinyButton/wttestshinybuttonmenudialog.cpp \
    ../../Tools/ToolTestTimedServerPusher/testtimedserverpusherdata.cpp \
    ../../Tools/ToolTestTimedServerPusher/testtimedserverpushermenudialog.cpp \
    ../../Tools/ToolTestTimedServerPusher/testtimedserverpusherwtmaindialog.cpp \
    ../../Tools/ToolTestTimedServerPusher/testtimedserverpusherwtmenudialog.cpp \
    ../../Tools/ToolTestToggleButton/wttesttogglebuttonmaindialog.cpp \
    ../../Tools/ToolTestToggleButton/wttesttogglebuttonmenudialog.cpp \
    ../../Tools/ToolTestTwoDigitNewick/wttesttwodigitnewickdialog.cpp \
    ../../Tools/ToolTimePoll/timepolldata.cpp \
    ../../Tools/ToolTimePoll/timepollmenudialog.cpp \
    ../../Tools/ToolTimePoll/timepollwtmaindialog.cpp \
    ../../Tools/ToolTimePoll/timepollwtmenudialog.cpp \
    wtmain.cpp \
    wtrichelbilderbeekadmindialog.cpp \
    wtrichelbilderbeekmenudialog.cpp \
    wtrichelbilderbeekmenuitem.cpp

HEADERS += \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h \
    ../../Classes/CppWtConnectThreeWidget/wtconnectthreewidget.h \
    ../../Classes/CppWtDialWidget/wtdialwidget.h \
    ../../Classes/CppWtEntrance/wtentrance.h \
    ../../Classes/CppWtExercise/wtexercise.h \
    ../../Classes/CppWtGroupWidget/wtgroupwidget.h \
    ../../Classes/CppWtLedWidget/wtledwidget.h \
    ../../Classes/CppWtMultipleChoiceQuestionDialog/wtmultiplechoicequestiondialog.h \
    ../../Classes/CppWtMysteryMachineWidget/wtmysterymachinewidget.h \
    ../../Classes/CppWtOpenQuestionDialog/wtopenquestiondialog.h \
    ../../Classes/CppWtQuestionDialog/wtquestiondialog.h \
    ../../Classes/CppWtRichelBilderbeekGalleryDialog/wtrichelbilderbeekgallerydialog.h \
    ../../Classes/CppWtRubiksClockWidget/wtrubiksclockwidget.h \
    ../../Classes/CppWtSelectFileDialog/wtselectfiledialog.h \
    ../../Classes/CppWtServerPusher/wtserverpusher.h \
    ../../Classes/CppWtServerPusher/wtserverpusherclient.h \
    ../../Classes/CppWtShapeGroupWidget/wtshapegroupwidget.h \
    ../../Classes/CppWtShapeWidget/wtshapewidget.h \
    ../../Classes/CppWtShinyButtonWidget/wtshinybuttonwidget.h \
    ../../Classes/CppWtTicTacToeWidget/wttictactoewidget.h \
    ../../Classes/CppWtTimedServerPusher/wttimedserverpusher.h \
    ../../Classes/CppWtTimedServerPusher/wttimedserverpusherclient.h \
    ../../Classes/CppWtToggleButtonWidget/wttogglebuttonwidget.h \
    ../../Games/GameConnectThree/qtconnectthreeresources.h \
    ../../Games/GameConnectThree/wtconnectthreegamedialog.h \
    ../../Games/GameConnectThree/wtconnectthreemenudialog.h \
    ../../Games/GameConnectThree/wtconnectthreeresources.h \
    ../../Games/GameConnectThree/wtselectplayerwidget.h \
    ../../Games/GameRubiksClock/wtrubiksclockmaindialog.h \
    ../../Games/GameRubiksClock/wtrubiksclockmenudialog.h \
    ../../Games/GameTicTacToe/wttictactoegamedialog.h \
    ../../Games/GameTicTacToe/wttictactoemenudialog.h \
    ../../Projects/ProjectGtst/administrator.h \
    ../../Projects/ProjectGtst/administratordialog.h \
    ../../Projects/ProjectGtst/administratordialogstate.h \
    ../../Projects/ProjectGtst/administratordialogstateloggedin.h \
    ../../Projects/ProjectGtst/administratordialogstatenotloggedin.h \
    ../../Projects/ProjectGtst/administrators.h \
    ../../Projects/ProjectGtst/all_groups.h \
    ../../Projects/ProjectGtst/all_parameters.h \
    ../../Projects/ProjectGtst/all_participantdialogstates.h \
    ../../Projects/ProjectGtst/all_participantstates.h \
    ../../Projects/ProjectGtst/all_serverstates.h \
    ../../Projects/ProjectGtst/chatmessage.h \
    ../../Projects/ProjectGtst/chatshapefactory.h \
    ../../Projects/ProjectGtst/chooseactionoption.h \
    ../../Projects/ProjectGtst/debugdialog.h \
    ../../Projects/ProjectGtst/forward_declarations.h \
    ../../Projects/ProjectGtst/group.h \
    ../../Projects/ProjectGtst/groupassigner.h \
    ../../Projects/ProjectGtst/groupfinished.h \
    ../../Projects/ProjectGtst/grouploggedin.h \
    ../../Projects/ProjectGtst/groupnotloggedin.h \
    ../../Projects/ProjectGtst/groupparticipating.h \
    ../../Projects/ProjectGtst/groups.h \
    ../../Projects/ProjectGtst/logfile.h \
    ../../Projects/ProjectGtst/parameters.h \
    ../../Projects/ProjectGtst/parametersassignpayoff.h \
    ../../Projects/ProjectGtst/parameterschat.h \
    ../../Projects/ProjectGtst/parameterschooseaction.h \
    ../../Projects/ProjectGtst/parametersfinished.h \
    ../../Projects/ProjectGtst/parametersgroupassign.h \
    ../../Projects/ProjectGtst/parametersgroupreassign.h \
    ../../Projects/ProjectGtst/parametersquiz.h \
    ../../Projects/ProjectGtst/parametersviewresultsall.h \
    ../../Projects/ProjectGtst/parametersviewresultsgroup.h \
    ../../Projects/ProjectGtst/parametersviewresultsvoting.h \
    ../../Projects/ProjectGtst/parametersvoting.h \
    ../../Projects/ProjectGtst/participant.h \
    ../../Projects/ProjectGtst/participantdialog.h \
    ../../Projects/ProjectGtst/participantdialogstate.h \
    ../../Projects/ProjectGtst/participantdialogstateassignpayoff.h \
    ../../Projects/ProjectGtst/participantdialogstatechat.h \
    ../../Projects/ProjectGtst/participantdialogstatechooseaction.h \
    ../../Projects/ProjectGtst/participantdialogstatefinished.h \
    ../../Projects/ProjectGtst/participantdialogstategroupassign.h \
    ../../Projects/ProjectGtst/participantdialogstategroupreassign.h \
    ../../Projects/ProjectGtst/participantdialogstateloggedin.h \
    ../../Projects/ProjectGtst/participantdialogstatenotloggedin.h \
    ../../Projects/ProjectGtst/participantdialogstatequiz.h \
    ../../Projects/ProjectGtst/participantdialogstates.h \
    ../../Projects/ProjectGtst/participantdialogstateviewresultsgroup.h \
    ../../Projects/ProjectGtst/participantdialogstateviewresultsvoting.h \
    ../../Projects/ProjectGtst/participantdialogstatevoting.h \
    ../../Projects/ProjectGtst/participantstate.h \
    ../../Projects/ProjectGtst/participantstateassignpayoff.h \
    ../../Projects/ProjectGtst/participantstatechat.h \
    ../../Projects/ProjectGtst/participantstatechooseaction.h \
    ../../Projects/ProjectGtst/participantstatefinished.h \
    ../../Projects/ProjectGtst/participantstategroupassign.h \
    ../../Projects/ProjectGtst/participantstategroupreassign.h \
    ../../Projects/ProjectGtst/participantstateloggedin.h \
    ../../Projects/ProjectGtst/participantstatenotloggedin.h \
    ../../Projects/ProjectGtst/participantstatequiz.h \
    ../../Projects/ProjectGtst/participantstateviewresultsgroup.h \
    ../../Projects/ProjectGtst/participantstateviewresultsvoting.h \
    ../../Projects/ProjectGtst/participantstatevoting.h \
    ../../Projects/ProjectGtst/payoff.h \
    ../../Projects/ProjectGtst/payoffs.h \
    ../../Projects/ProjectGtst/projectgtstmenudialog.h \
    ../../Projects/ProjectGtst/repeatassigner.h \
    ../../Projects/ProjectGtst/repeatassignerfixed.h \
    ../../Projects/ProjectGtst/repeatassignerrandomgeometric.h \
    ../../Projects/ProjectGtst/repeatassignerrandomuniform.h \
    ../../Projects/ProjectGtst/resources.h \
    ../../Projects/ProjectGtst/server.h \
    ../../Projects/ProjectGtst/serverstate.h \
    ../../Projects/ProjectGtst/serverstateassignpayoff.h \
    ../../Projects/ProjectGtst/serverstatechat.h \
    ../../Projects/ProjectGtst/serverstatechooseaction.h \
    ../../Projects/ProjectGtst/serverstatefinished.h \
    ../../Projects/ProjectGtst/serverstategroupassign.h \
    ../../Projects/ProjectGtst/serverstategroupreassign.h \
    ../../Projects/ProjectGtst/serverstatequiz.h \
    ../../Projects/ProjectGtst/serverstates.h \
    ../../Projects/ProjectGtst/serverstateviewresultsgroup.h \
    ../../Projects/ProjectGtst/serverstateviewresultsvoting.h \
    ../../Projects/ProjectGtst/serverstatevoting.h \
    ../../Projects/ProjectGtst/serverstatewaiting.h \
    ../../Projects/ProjectGtst/state.h \
    ../../Projects/ProjectGtst/test.h \
    ../../Projects/ProjectGtst/vote.h \
    ../../Projects/ProjectGtst/votingoption.h \
    ../../Tools/ToolAsciiArter/wtasciiartermaindialog.h \
    ../../Tools/ToolCodeToHtml/wtcodetohtmldialog.h \
    ../../Tools/ToolCodeToHtml/wtcodetohtmlmenudialog.h \
    ../../Tools/ToolHometrainer/wthometrainerloadexercisedialog.h \
    ../../Tools/ToolHometrainer/wthometrainermenudialog.h \
    ../../Tools/ToolHometrainer/wthometrainerstartexercisedialog.h \
    ../../Tools/ToolHometrainer/wtselecthometrainerfiledialog.h \
    ../../Tools/ToolRandomCode/wtrandomcodegeneratedialog.h \
    ../../Tools/ToolRandomCode/wtrandomcodemenudialog.h \
    ../../Tools/ToolSimMysteryMachine/wtsimmysterymachinemaindialog.h \
    ../../Tools/ToolSimMysteryMachine/wtsimmysterymachinemenudialog.h \
    ../../Tools/ToolTestDial/wttestdialmaindialog.h \
    ../../Tools/ToolTestDial/wttestdialmenudialog.h \
    ../../Tools/ToolEncranger/wttoolencrangermaindialog.h \
    ../../Tools/ToolEncranger/wttoolencrangermenudialog.h \
    ../../Tools/ToolTestEntrance/wttestentrancemaindialog.h \
    ../../Tools/ToolTestEntrance/wttestentrancemenudialog.h \
    ../../Tools/ToolTestExercise/wttestexercisemaindialog.h \
    ../../Tools/ToolTestExercise/wttestexercisemenudialog.h \
    ../../Tools/ToolTestFunctionParser/wttestfunctionparsermaindialog.h \
    ../../Tools/ToolTestFunctionParser/wttestfunctionparsermenudialog.h \
    ../../Tools/ToolTestGroupWidget/wttestgroupwidgetmaindialog.h \
    ../../Tools/ToolTestGroupWidget/wttestgroupwidgetmenudialog.h \
    ../../Tools/ToolTestLed/wttestledmaindialog.h \
    ../../Tools/ToolTestLed/wttestledmenudialog.h \
    ../../Tools/ToolTestNewickVector/wttestnewickvectordialog.h \
    ../../Tools/ToolTestQuestion/wttestquestionmaindialog.h \
    ../../Tools/ToolTestQuestion/wttestquestionmenudialog.h \
    ../../Tools/ToolTestSelectFileDialog/wttestselectfiledialogmaindialog.h \
    ../../Tools/ToolTestSelectFileDialog/wttestselectfiledialogmenudialog.h \
    ../../Tools/ToolTestServerPusher/testserverpusherdata.h \
    ../../Tools/ToolTestServerPusher/testserverpushermenudialog.h \
    ../../Tools/ToolTestServerPusher/testserverpusherwtmaindialog.h \
    ../../Tools/ToolTestServerPusher/testserverpusherwtmenudialog.h \
    ../../Tools/ToolTestShape/wttestshapemaindialog.h \
    ../../Tools/ToolTestShape/wttestshapemenudialog.h \
    ../../Tools/ToolTestShinyButton/wttestshinybuttonmaindialog.h \
    ../../Tools/ToolTestShinyButton/wttestshinybuttonmenudialog.h \
    ../../Tools/ToolTestTimedServerPusher/testtimedserverpusherdata.h \
    ../../Tools/ToolTestTimedServerPusher/testtimedserverpushermenudialog.h \
    ../../Tools/ToolTestTimedServerPusher/testtimedserverpusherwtmaindialog.h \
    ../../Tools/ToolTestTimedServerPusher/testtimedserverpusherwtmenudialog.h \
    ../../Tools/ToolTestToggleButton/wttesttogglebuttonmaindialog.h \
    ../../Tools/ToolTestToggleButton/wttesttogglebuttonmenudialog.h \
    ../../Tools/ToolTestTwoDigitNewick/wttesttwodigitnewickdialog.h \
    ../../Tools/ToolTimePoll/timepolldata.h \
    ../../Tools/ToolTimePoll/timepollmenudialog.h \
    ../../Tools/ToolTimePoll/timepollwtmaindialog.h \
    ../../Tools/ToolTimePoll/timepollwtmenudialog.h \
    wtrichelbilderbeekadmindialog.h \
    wtrichelbilderbeekmenudialog.h \
    wtrichelbilderbeekmenuitem.h

RESOURCES += \
    ../../Games/GameConnectThree/GameConnectThree.qrc \
    ../../Games/GamePylos/GamePylos.qrc \
    ../../Games/GameRubiksClock/GameRubiksClock.qrc \
    ../../Projects/ProjectGtst/ProjectGtst.qrc \
    ../../Projects/RichelbilderbeekNl/qtrichelbilderbeekgalleryresources.qrc \
    ../../Tools/ToolAsciiArter/ToolAsciiArter.qrc \
    ../../Tools/ToolCodeToHtml/ToolCodeToHtml.qrc \
    ../../Tools/ToolHometrainer/ToolHometrainer.qrc \
    ../../Tools/ToolRandomCode/ToolRandomCode.qrc \
    ../../Tools/ToolSimMysteryMachine/ToolSimMysteryMachine.qrc \
    ../../Tools/ToolStateObserver/ToolStateObserver.qrc \
    ../../Tools/ToolTestDial/ToolTestDial.qrc \
    ../../Tools/ToolEncranger/ToolEncranger.qrc \
    ../../Tools/ToolTestEntrance/ToolTestEntrance.qrc \
    ../../Tools/ToolTestExercise/ToolTestExercise.qrc \
    ../../Tools/ToolTestFunctionParser/ToolTestFunctionParser.qrc \
    ../../Tools/ToolTestGroupWidget/ToolTestGroupWidget.qrc \
    ../../Tools/ToolTestLed/ToolTestLed.qrc \
    ../../Tools/ToolTestQuestion/ToolTestQuestion.qrc \
    ../../Tools/ToolTestSelectFileDialog/ToolTestSelectFileDialog.qrc \
    ../../Tools/ToolTestShape/ToolTestShape.qrc \
    ../../Tools/ToolTestShinyButton/ToolTestShinyButton.qrc \
    ../../Tools/ToolTestToggleButton/ToolTestToggleButton.qrc \
    ProjectRichelBilderbeek.qrc

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppAsciiArter/Licence.txt \
    ../../Classes/CppBinaryNewickVector/Licence.txt \
    ../../Classes/CppCodeToHtml/Licence.txt \
    ../../Classes/CppConnectThree/Licence.txt \
    ../../Classes/CppConnectThreeWidget/Licence.txt \
    ../../Classes/CppCounter/Licence.txt \
    ../../Classes/CppDial/Licence.txt \
    ../../Classes/CppDialWidget/Licence.txt \
    ../../Classes/CppEncranger/Licence.txt \
    ../../Classes/CppExercise/Licence.txt \
    ../../Classes/CppGaborFilter/Licence.txt \
    ../../Classes/CppGaborFilterWidget/Licence.txt \
    ../../Classes/CppHtmlPage/Licence.txt \
    ../../Classes/CppIpAddress/Licence.txt \
    ../../Classes/CppKalmanFilter/Licence.txt \
    ../../Classes/CppLazy_init/Licence.txt \
    ../../Classes/CppLed/Licence.txt \
    ../../Classes/CppLedWidget/Licence.txt \
    ../../Classes/CppManyDigitNewick/Licence.txt \
    ../../Classes/CppMatrix/Licence.txt \
    ../../Classes/CppMultipleChoiceQuestion/Licence.txt \
    ../../Classes/CppMultipleChoiceQuestionDialog/Licence.txt \
    ../../Classes/CppMusic/Licence.txt \
    ../../Classes/CppMysteryMachine/Licence.txt \
    ../../Classes/CppMysteryMachineWidget/Licence.txt \
    ../../Classes/CppNewick/Licence.txt \
    ../../Classes/CppPylos/Licence.txt \
    ../../Classes/CppQrcFile/Licence.txt \
    ../../Classes/CppQtModel/Licence.txt \
    ../../Classes/CppStateObserver/Licence.txt \
    ../../Games/GamePylos/Licence.txt \
    ../../Games/GamePylos/PylosGoal1.png \
    ../../Games/GamePylos/PylosGoal2.png \
    ../../Games/GamePylos/PylosLine.png \
    ../../Games/GamePylos/PylosMove.png \
    ../../Games/GamePylos/PylosPlace.png \
    ../../Games/GamePylos/PylosRemove1.png \
    ../../Games/GamePylos/PylosRemove2.png \
    ../../Games/GamePylos/PylosSquare.png \
    ../../Games/GamePylos/R.png \
    ../../Games/GamePylos/sprite_hole.png \
    ../../Games/GamePylos/sprite_player1.png \
    ../../Games/GamePylos/sprite_player1_remove.png \
    ../../Games/GamePylos/sprite_player1_select.png \
    ../../Games/GamePylos/sprite_player2.png \
    ../../Games/GamePylos/sprite_player2_remove.png \
    ../../Games/GamePylos/sprite_player2_select.png \
    ../../Games/GamePylos/zip.sh \
    ../../Games/GameRubiksClock/GameRubiksClock.png \
    ../../Games/GameRubiksClock/GameRubiksClockWelcome_2_1.png \
    ../../Games/GameRubiksClock/GameRubiksClockWelcomeNoLegend.png \
    ../../Games/GameRubiksClock/Licence.txt \
    ../../Projects/ProjectGtst/Cycle_100.png \
    ../../Projects/ProjectGtst/drd.sh \
    ../../Projects/ProjectGtst/Experiment_100.png \
    ../../Projects/ProjectGtst/ExperimentFlow.png \
    ../../Projects/ProjectGtst/GroupDynamics_100.png \
    ../../Projects/ProjectGtst/Groups.png \
    ../../Projects/ProjectGtst/gtst_start_and_auto_update.sh \
    ../../Projects/ProjectGtst/helgrind.sh \
    ../../Projects/ProjectGtst/helgrind_test_concurrency.sh \
    ../../Projects/ProjectGtst/IPGG.png \
    ../../Projects/ProjectGtst/Licence.txt \
    ../../Projects/ProjectGtst/Period_100_58.png \
    ../../Projects/ProjectGtst/ProjectGtst.odp \
    ../../Projects/ProjectGtst/ProjectGtstArchitectureMenuDialog.dia \
    ../../Projects/ProjectGtst/ProjectGtstArchitectureMenuDialog.png \
    ../../Projects/ProjectGtst/ProjectGtstArchitectureServer.dia \
    ../../Projects/ProjectGtst/ProjectGtstArchitectureServer.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogAssignPayoff.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogAssignPayoffParameters.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogChat.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogChatParameters.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogChooseAction.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogChooseAction2.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogChooseActionParameters.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogFinished.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogFinishedParameters.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogGroupAssign.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogGroupAssign2.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogGroupAssign2Parameters.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogGroupAssignParameters.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogGroupReAssign.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogGroupReAssignParameters.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogLoggedIn.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogLoggedInParameters.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogNotLoggedIn.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogNotLoggedInParameters.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogViewResultsGroup.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogViewResultsGroupParameters.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogViewResultsVoting.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogViewResultsVotingParameters.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogVoting.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogVoting2.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogVotingParameters.png \
    ../../Projects/ProjectGtst/R.png \
    ../../Projects/ProjectGtst/RichelbilderbeekNlBackground.png \
    ../../Projects/ProjectGtst/TotalExperimentFlow.png \
    ../../Tools/ToolAsciiArter/AsciiArter.png \
    ../../Tools/ToolAsciiArter/Licence.txt \
    ../../Tools/ToolAsciiArter/R.png \
    ../../Tools/ToolAsciiArter/RichelbilderbeekNlBackground.png \
    ../../Tools/ToolRegexTester/Licence.txt \
    ../../Tools/ToolStateObserver/Licence.txt \
    ../../Tools/ToolStateObserver/ToolStateObserverWelcome.png \
    ../../Tools/ToolStateObserver/zip.sh

#
#
# Boost
#
#

unix {
  LIBS += \
  -lboost_date_time \
  -lboost_filesystem \
  -lboost_program_options \
  -lboost_regex \
  -lboost_signals \
  -lboost_system
}

#
#
# Wt
#
#
unix {
  LIBS += \
  -lwt \
  -lwthttp
}

win32 {
  INCLUDEPATH += ../../Libraries/wt/src
}

*/
