//---------------------------------------------------------------------------
/*
Project Richel Bilderbeek, Richel Bilderbeek's work
Copyright (C) 2010-2013 Richel Bilderbeek

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
#include "qtrichelbilderbeekprogram.h"

#include <cassert>
#include <fstream>
#include <stdexcept>

#include <QLabel>
#include <QVBoxLayout>

#include "qtasciiartermenudialog.h"
#include "qtbeerwantermenudialog.h"
#include "qtboenkenmenudialog.h"
#include "qtcodetohtmlmenudialog.h"
#include "qtconnectthreemenudialog.h"
#include "qtcreateglossarymenudialog.h"
#include "qtcreateqtprojectzipfilemenudialog.h"
#include "qtdaswahreschlagerfestmenudialog.h"
#include "qtk3opeenrijmenudialog.h"
#include "qtk3opeenrijresources.h"
#include "qtkalmanfilterermenudialog.h"
#include "qtmazecreatormenudialog.h"
#include "qtmaziakmenudialog.h"
#include "qtmusictheorymenudialog.h"
#include "qtperfectelasticcollisionmenudialog.h"
#include "qtpictocodemenudialog.h"
#include "qtpylosmenudialog.h"
#include "qtqmakewatchermenudialog.h"
#include "qtquadraticsolvermenudialog.h"
#include "qtrandomcodemenudialog.h"
#include "qtregextestermenudialog.h"
#include "qtrichelbilderbeekgallerymenudialog.h"
#include "qtrubiksclockmenudialog.h"
#include "qtsimmysterymachinemenudialog.h"
#include "qtsitemapgeneratormenudialog.h"
#include "qtsitemapgeneratormenudialog.h"
#include "qtstateobservermenudialog.h"
#include "qttestdialmenudialog.h"
#include "qttestfunctionparsermenudialog.h"
#include "qttestleddialog.h"
#include "qttestmultiplechoicequestionmenudialog.h"
#include "qttestopenquestionmenudialog.h"
#include "qttestpylosmenudialog.h"
#include "qttestqrcfilemenudialog.h"
#include "qttestqtarrowitemsmenudialog.h"
#include "qttestqtcreatorprofilemenudialog.h"
#include "qttestqtcreatorprofilemenudialog.h"
#include "qttestqtkeyboardfriendlygraphicsviewmenudialog.h"
#include "qttestqtroundededitrectitemmenudialog.h"
#include "qttestqtroundedrectitemmenudialog.h"
#include "qttestqtroundedtextrectitemmenudialog.h"
#include "qttestquestionmenudialog.h"
#include "qttestshapemenudialog.h"
#include "qttestshinybuttonmenudialog.h"
#include "qttesttogglebuttonmaindialog.h"
#include "qttesttogglebuttonmenudialog.h"
#include "qttictactoemenudialog.h"
#include "qttooldotmatrixmenudialog.h"
#include "qttoolencrangermaindialog.h"
#include "qttoolencrangermenudialog.h"
#include "qttoolgaborfiltermenudialog.h"
#include "qttoolgraycodermenudialog.h"
#include "qttoolmultiencrangermaindialog.h"
#include "qttoolmultiencrangermenudialog.h"
#include "qttoolprimeexpertmenudialog.h"
#include "qttoolsimplifynewickmenudialog.h"
#include "qttooltestapproximatormenudialog.h"
#include "qttooltestcanvasmenudialog.h"
#include "qttooltestmultiapproximatormenudialog.h"
#include "qttooltestqtmodelsmenudialog.h"
#include "qttooltestsimplelinearregressionmenudialog.h"
#include "richelbilderbeekprogram.h"

#pragma GCC diagnostic pop

ribi::QtHideAndShowDialog * ribi::QtRichelBilderbeekProgram::CreateQtMenuDialog(const RichelBilderbeek::ProgramType type)
{
  using namespace RichelBilderbeek;
  QtHideAndShowDialog *  p = nullptr;
  switch (type)
  {
    case ProgramType::aminoAcidFighter: break;
    case ProgramType::asciiArter: p = new QtAsciiArterMenuDialog; break;
    case ProgramType::barbaImage: break;
    case ProgramType::beerWanter: p = new QtBeerWanterMenuDialog; break;
    case ProgramType::billysGarden: break;
    case ProgramType::bochum: break;
    case ProgramType::boenken: p = new QtBoenkenMenuDialog; break;
    case ProgramType::brainweaver: break;
    case ProgramType::bristol: break;
    case ProgramType::chrisWiley: break;
    case ProgramType::codeToHtml: p = new QtCodeToHtmlMenuDialog; break;
    case ProgramType::connectThree: p = new QtConnectThreeMenuDialog; break;
    case ProgramType::corridor: break;
    case ProgramType::createGlossary: p = new QtCreateGlossaryMenuDialog; break;
    case ProgramType::createQtProjectZipFile: p = new QtCreateQtProjectZipFileMenuDialog; break;
    case ProgramType::crossPoll: break;
    case ProgramType::dasWahreSchlagerfest: p = new QtDasWahreSchlagerfestMenuDialog; break;
    case ProgramType::dotMatrix: p = new QtDotMatrixMenuDialog;  break;
    case ProgramType::encranger: p = new QtToolEncrangerMenuDialog; break;
    case ProgramType::everythingToPiecesShooter: break;
    case ProgramType::fakeEvy: break;
    case ProgramType::filterOperationer: break;
    case ProgramType::fryskLeareLieder: break;
    case ProgramType::functionPlotter: break;
    case ProgramType::gaborFilter: p = new QtToolGaborFilterMenuDialog; break;
    case ProgramType::grayCoder: p = new QtGrayCoderMenuDialog; break;
    case ProgramType::gtst: break;
    case ProgramType::histogramEqualizationer: break;
    case ProgramType::hometrainer: break;
    case ProgramType::imageRotaterClx: break;
    case ProgramType::imageRotaterVcl: break;
    case ProgramType::k3OpEenRij:
    {
      const boost::shared_ptr<const ribi::QtK3OpEenRijResources> resources(new ribi::QtK3OpEenRijResources);
      p = new QtK3OpEenRijMenuDialog(resources);
    }
    break;
    case ProgramType::kalmanFilterer: p = new kalman::QtKalmanFiltererMenuDialog; break;
    case ProgramType::keySender: break;
    case ProgramType::knokfighter: break;
    case ProgramType::kTouchLectureCreator: break;
    case ProgramType::lambdaBot: break;
    case ProgramType::learyCircumplex: break;
    case ProgramType::logisticGrowthSimulator: break;
    case ProgramType::loose: break;
    case ProgramType::martianCafeTuinemaTycoon: break;
    case ProgramType::mazeCreator: p = new QtMazeCreatorMenuDialog; break;
    case ProgramType::maziak: p = new QtMaziakMenuDialog; break;
    case ProgramType::metZnDrieen: break;
    case ProgramType::midiLessonCreator: break;
    case ProgramType::morpher: break;
    case ProgramType::multiEncranger: p = new QtToolMultiEncrangerMenuDialog; break;
    case ProgramType::muscaDomestica: break;
    case ProgramType::musicTheory: p = new QtMusicTheoryMenuDialog; break;
    case ProgramType::ndsmake: break;
    case ProgramType::ndsPaint: break;
    case ProgramType::paperRockScissors: break;
    case ProgramType::pause: break;
    case ProgramType::perfectElasticCollision: p = new QtPerfectElasticCollisionMenuDialog; break;
    case ProgramType::picToCode: p = new QtPicToCodeMenuDialog; break;
    case ProgramType::pixelator: break;
    case ProgramType::pokeVolley: break;
    case ProgramType::pong: break;
    case ProgramType::primeExpert: p = new QtToolPrimeExpertMenuDialog;  break;
    case ProgramType::pylos: p = new QtPylosMenuDialog; break;
    case ProgramType::qmakeWatcher: new QtQmakeWatcherMenuDialog; break;
    case ProgramType::quadraticSolver: new QtQuadraticSolverMenuDialog; break;
    case ProgramType::rampal: break;
    case ProgramType::rasper: break;
    case ProgramType::randomCode: p = new QtRandomCodeMenuDialog; break;
    case ProgramType::refrigeratorPuzzleSolver: break;
    case ProgramType::regexTester: p = new QtRegexTesterMenuDialog; break;
    case ProgramType::reversi: break;
    case ProgramType::richelBilderbeekGallery: p = new QtRichelBilderbeekGalleryMenuDialog; break;
    case ProgramType::richelbilderbeekNlSitemapGenerator: p = new QtSitemapGeneratorMenuDialog; break;
    case ProgramType::rubiksClock: p = new QtRubiksClockMenuDialog; break;
    case ProgramType::searchAndDestroyChess: break;
    case ProgramType::secretMessage: break;
    case ProgramType::simBrainiac: break;
    case ProgramType::simImmuneResponse: break;
    case ProgramType::simMysteryMachine: p = new QtSimMysteryMachineMenuDialog; break;
    case ProgramType::simplifyNewick: p = new QtToolSimplifyNewickMenuDialog; break;
    case ProgramType::simPredator: break;
    case ProgramType::simStagecraft: break;
    case ProgramType::soaSim: break;
    case ProgramType::solvePuzzleX: break;
    case ProgramType::spaceHarry: break;
    case ProgramType::staircaseCardCreator: break;
    case ProgramType::stateObserver: p = new QtStateObserverMenuDialog; break;
    case ProgramType::styleSheetSetter: break;
    case ProgramType::superNsanaBros: break;
    case ProgramType::surfacePlotter: break;
    case ProgramType::tankBattalion: break;
    case ProgramType::testAbout: break;
    case ProgramType::testApproximator: p = new QtToolTestApproximatorMenuDialog; break;
    case ProgramType::testBouncingBallsWidget: break;
    case ProgramType::testBouncingRectsWidget: break;
    case ProgramType::testBroadcastServer: break;
    case ProgramType::testBinaryNewickVector: /* p = new QtTestBinaryNewickVectorMenuDialog; */break;
    case ProgramType::testCanvas: p = new QtToolTestCanvasMenuDialog; break;
    case ProgramType::testChess: break;
    case ProgramType::testDial: p = new QtTestDialMenuDialog; break;
    case ProgramType::testEntrance: break;
    case ProgramType::testExercise: break;
    case ProgramType::testFunctionParser: p = new QtTestFunctionParserMenuDialog; break;
    case ProgramType::testGnuplotInterface: break;
    case ProgramType::testGraphicsProxyWidget: break;
    case ProgramType::testGravityWidget: break;
    case ProgramType::testGroupWidget: break;
    case ProgramType::testHugeVector: break;
    case ProgramType::testLazy_init: break;
    case ProgramType::testLed: p = new QtTestLedDialog; break;
    case ProgramType::testManyDigitNewick: break;
    case ProgramType::testMultiApproximator: p = new QtToolTestMultiApproximatorMenuDialog; break;
    case ProgramType::testMultipleChoiceQuestion: p = new QtTestMultipleChoiceQuestionMenuDialog; break;
    case ProgramType::testMultiVector: break;
    case ProgramType::testNdsmake: break;
    case ProgramType::testNeuralNet: /* p = new QtTestNeuralNetMenuDialog; */ break;
    case ProgramType::testNewick: break;
    case ProgramType::testNewickVector: break;
    case ProgramType::testOpenQuestion: p = new QtTestOpenQuestionMenuDialog;  break;
    case ProgramType::testPylos: p = new QtTestPylosMenuDialog; break;
    case ProgramType::testQrcFile: p = new QtTestQrcFileMenuDialog; break;
    case ProgramType::testQtCreatorProFile: p = new QtTestQtCreatorProFileMenuDialog; break;
    case ProgramType::testQtHideAndShowDialog: break;
    case ProgramType::testQtOcrWidget: break;
    case ProgramType::testQtRoundedEditRectItem: p = new QtTestQtRoundedEditRectItemMenuDialog; break;
    case ProgramType::testQtRoundedRectItem: p = new QtTestQtRoundedRectItemMenuDialog; break;
    case ProgramType::testQtRoundedTextRectItem: p = new QtTestQtRoundedTextRectItemMenuDialog; break;
    case ProgramType::testQuestion: p = new QtTestQuestionMenuDialog; break;
    case ProgramType::testReversi: break;
    case ProgramType::testSelectFileDialog: break;
    case ProgramType::testServerPusher: break;
    case ProgramType::testShape: p = new QtTestShapeMenuDialog; break;
    case ProgramType::testShinyButton: p = new QtTestShinyButtonMenuDialog; break;
    case ProgramType::testSimpleLinearRegression:  p = new QtToolTestSimpleLinearRegressionMenuDialog; break;
    case ProgramType::testStopwatch: break;
    case ProgramType::testQtArrowItems: p = new QtTestQtArrowItemsMenuDialog; break;
    case ProgramType::testQtKeyboardFriendlyGraphicsView: p = new QtTestKeyboardFriendlyGraphicsViewMenuDialog; break;
    case ProgramType::testQtModels: p = new QtToolTestQtModelsMenuDialog; break;
    case ProgramType::testTextPositionWidget: break;
    case ProgramType::testTicTacToe: break;
    case ProgramType::testTimedServerPusher: break;
    case ProgramType::testToggleButton: p = new QtTestToggleButtonMenuDialog; break;
    case ProgramType::testTwoDigitNewick: /* p = new QtTestTwoDigitNewickMenuDialog; */ break;
    case ProgramType::thorVeen: break;
    case ProgramType::thresholdFilterer: break;
    case ProgramType::ticTacToe: p = new QtTicTacToeMenuDialog; break;
    case ProgramType::ticTacToeLearner: break;
    case ProgramType::ticTacToeValuer: break;
    case ProgramType::timePoll: break;
    case ProgramType::tronCollection: break;
    case ProgramType::ubuntuOneWatcher: break;
    case ProgramType::vanDenBogaart: break;
    case ProgramType::virtualBastard: break;
    case ProgramType::visualAbc: break;
    case ProgramType::xeNonZero: break;
    case ProgramType::zork: break;
    case ProgramType::n_types:
      assert(!"Unimplemented RichelBilderbeek::ProgramType");
      throw std::logic_error("Unimplemented RichelBilderbeek::ProgramType");
  }
  //p might be nullptr
  return p;
}


ribi::QtHideAndShowDialog * ribi::QtRichelBilderbeekProgram::CreateQtPlaceholderDialog(const RichelBilderbeek::ProgramType type)
{
  QtHideAndShowDialog * const d = new QtHideAndShowDialog;
  assert(!d->layout());
  QVBoxLayout * const layout = new QVBoxLayout;
  d->setLayout(layout);
  assert(d->layout());
  const boost::shared_ptr<RichelBilderbeek::Program> p = RichelBilderbeek::Program::CreateProgram(type);
  assert(p);
  {
    const std::string title = p->GetScreenName() + "(placeholder)";
    d->setWindowTitle(title.c_str());
  }
  {
    QLabel * const label = new QLabel((p->GetScreenName() + "(placeholder)").c_str());
    label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    layout->addWidget(label);
  }
  if (IsRegularFile(p->GetFilenameConsole()))
  {
    const QPixmap pixmap(p->GetFilenameConsole().c_str());
    QLabel * const label = new QLabel;
    label->setPixmap(pixmap);
    layout->addWidget(label);
  }
  if (IsRegularFile(p->GetFilenameDesktop()))
  {
    const QPixmap pixmap(p->GetFilenameDesktop().c_str());
    QLabel * const label = new QLabel;
    label->setPixmap(pixmap);
    layout->addWidget(label);
  }
  if (IsRegularFile(p->GetFilenameDesktopWindowsOnly()))
  {
    const QPixmap pixmap(p->GetFilenameDesktopWindowsOnly().c_str());
    QLabel * const label = new QLabel;
    label->setPixmap(pixmap);
    layout->addWidget(label);
  }
  if (IsRegularFile(p->GetFilenameWeb()))
  {
    const QPixmap pixmap(p->GetFilenameWeb().c_str());
    QLabel * const label = new QLabel;
    label->setPixmap(pixmap);
    layout->addWidget(label);
  }
  assert(d);
  return d;
}


bool ribi::QtRichelBilderbeekProgram::IsRegularFile(const std::string& filename)
{
  std::fstream f;
  f.open(filename.c_str(),std::ios::in);
  return f.is_open();
}
