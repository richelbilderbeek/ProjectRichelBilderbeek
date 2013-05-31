#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtrichelbilderbeekprogram.h"

#include <cassert>
#include <stdexcept>

#include <boost/filesystem.hpp>

#include <QLabel>
#include <QVBoxLayout>

#include "richelbilderbeekprogram.h"

#include "qtasciiartermenudialog.h"
#include "qtbeerwantermenudialog.h"
#include "qtkalmanfilterermenudialog.h"
#include "qtboenkenmenudialog.h"
#include "qtcodetohtmlmenudialog.h"
#include "qtconnectthreemenudialog.h"
#include "qtcreateglossarymenudialog.h"
#include "qtcreateqtprojectzipfilemenudialog.h"
#include "qtdaswahreschlagerfestmenudialog.h"
#include "qtmazecreatormenudialog.h"
#include "qtmaziakmenudialog.h"
#include "qtmusictheorymenudialog.h"
#include "qtperfectelasticcollisionmenudialog.h"
#include "qtpylosmenudialog.h"
#include "qtpictocodemenudialog.h"
#include "qtrandomcodemenudialog.h"
#include "qtregextestermenudialog.h"
#include "qtrichelbilderbeekgallerymenudialog.h"
#include "qtrubiksclockmenudialog.h"
#include "qtsimmysterymachinemenudialog.h"
#include "qtsitemapgeneratormenudialog.h"
#include "qtsitemapgeneratormenudialog.h"
#include "qtstateobservermenudialog.h"
#include "qttestdialmenudialog.h"
#include "qttestencrangerdialog.h"
#include "qttestfunctionparsermenudialog.h"
#include "qttestleddialog.h"
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
#include "qttoolgaborfiltermenudialog.h"
#include "qttooltestqtmodelsmenudialog.h"

QDialog * QtRichelBilderbeekProgram::CreateQtMenuDialog(const RichelBilderbeek::ProgramType type)
{
  using namespace RichelBilderbeek;
  QDialog *  p = nullptr;
  switch (type)
  {
    case ProgramType::asciiArter: p = new QtAsciiArterMenuDialog; break;
    case ProgramType::barbaImage: break;
    case ProgramType::beerWanter: p = new QtBeerWanterMenuDialog; break;
    case ProgramType::bochum: break;
    case ProgramType::boenken: p = new QtBoenkenMenuDialog; break;
    case ProgramType::chrisWiley: break;
    case ProgramType::codeToHtml: p = new QtCodeToHtmlMenuDialog; break;
    case ProgramType::connectThree: p = new QtConnectThreeMenuDialog; break;
    case ProgramType::createGlossary: p = new QtCreateGlossaryMenuDialog; break;
    case ProgramType::createQtProjectZipFile: p = new QtCreateQtProjectZipFileMenuDialog; break;
    case ProgramType::createSitemap: p = new QtSitemapGeneratorMenuDialog; break;
    case ProgramType::crossPoll: break;
    case ProgramType::dasWahreSchlagerfest: p = new QtDasWahreSchlagerfestMenuDialog; break;
    case ProgramType::dotMatrix: break;
    case ProgramType::encranger: break;
    case ProgramType::filterOperationer: break;
    case ProgramType::fryskLeareLieder: break;
    case ProgramType::functionPlotter: break;
    case ProgramType::gaborFilter: p = new QtToolGaborFilterMenuDialog; break;
    case ProgramType::gnuplotInterface: break;
    case ProgramType::grayCoder: break;
    case ProgramType::gtst: break;
    case ProgramType::histogramEqualizationer: break;
    case ProgramType::hometrainer: break;
    case ProgramType::imageRotater: break;
    case ProgramType::k3OpEenRij: break;
    case ProgramType::kalmanFilterer: p = new QtKalmanFiltererMenuDialog; break;
    case ProgramType::keySender: break;
    case ProgramType::knokfighter: break;
    case ProgramType::kTouchLectureCreator: break;
    case ProgramType::learyCircumplex: break;
    case ProgramType::logisticGrowthSimulator: break;
    case ProgramType::loose: break;
    case ProgramType::mazeCreator: p = new QtMazeCreatorMenuDialog; break;
    case ProgramType::maziak: p = new QtMaziakMenuDialog; break;
    case ProgramType::morpher: break;
    case ProgramType::multiEncranger: break;
    case ProgramType::muscaDomestica: break;
    case ProgramType::musicTheory: p = new QtMusicTheoryMenuDialog; break;
    case ProgramType::ndsMake: break;
    case ProgramType::newickVector: break;
    case ProgramType::paperRockScissors: break;
    case ProgramType::pause: break;
    case ProgramType::perfectElasticCollision: p = new QtPerfectElasticCollisionMenuDialog; break;
    case ProgramType::picToCode: p = new QtPicToCodeMenuDialog; break;
    case ProgramType::pixelator: break;
    case ProgramType::pokeVolley: break;
    case ProgramType::pylos: p = new QtPylosMenuDialog; break;
    case ProgramType::qmakeWatcher: break;
    case ProgramType::quadraticSolver: break;
    case ProgramType::rasper: break;
    case ProgramType::randomCode: p = new QtRandomCodeMenuDialog; break;
    case ProgramType::refrigeratorPuzzleSolver: break;
    case ProgramType::regexTester: p = new QtRegexTesterMenuDialog; break;
    case ProgramType::reversi: break;
    case ProgramType::richelBilderbeekGallery: p = new QtRichelBilderbeekGalleryMenuDialog; break;
    case ProgramType::richelBilderbeekNlSitemapGenerator: p = new QtSitemapGeneratorMenuDialog; break;
    case ProgramType::rubiksClock: p = new QtRubiksClockMenuDialog; break;
    case ProgramType::searchAndDestroyChess: break;
    case ProgramType::secretMessage: break;
    case ProgramType::simBrainiac: break;
    case ProgramType::simImmuneResponse: break;
    case ProgramType::simplifyNewick: /* p = new QtSimplifyNewickMenuDialog; */ break;
    case ProgramType::simMysteryMachine: p = new QtSimMysteryMachineMenuDialog; break;
    case ProgramType::simStagecraft: break;
    case ProgramType::soaSim: break;
    case ProgramType::solvePuzzleX: break;
    case ProgramType::spaceHarry: break;
    case ProgramType::stateObserver: p = new QtStateObserverMenuDialog; break;
    case ProgramType::styleSheetSetter: break;
    case ProgramType::surfacePlotter: break;
    case ProgramType::testAbout: break;
    case ProgramType::testBroadcastServer: break;
    case ProgramType::testBinaryNewickVector: /* p = new QtTestBinaryNewickVectorMenuDialog; */break;
    case ProgramType::testChess: break;
    case ProgramType::testDial: p = new QtTestDialMenuDialog; break;
    case ProgramType::testEncranger: p = new QtTestEncrangerDialog; break;
    case ProgramType::testEntrance: break;
    case ProgramType::testExercise: break;
    case ProgramType::testFunctionParser: p = new QtTestFunctionParserMenuDialog; break;
    case ProgramType::testGroupWidget: break;
    case ProgramType::testLed: p = new QtTestLedDialog; break;
    case ProgramType::testMultiVector: break;
    case ProgramType::testNdsMake: break;
    case ProgramType::testNeuralNet: /* p = new QtTestNeuralNetMenuDialog; */ break;
    case ProgramType::testPrimeExpert: /* p = new QtTestPrimeExpertMenuDialog; */ break;
    case ProgramType::testPylos: p = new QtTestPylosMenuDialog; break;
    case ProgramType::testQrcFile: p = new QtTestQrcFileMenuDialog; break;
    case ProgramType::testQtCreatorProFile: p = new QtTestQtCreatorProFileMenuDialog; break;
    case ProgramType::testQtRoundedEditRectItem: p = new QtTestQtRoundedEditRectItemMenuDialog; break;
    case ProgramType::testQtRoundedRectItem: p = new QtTestQtRoundedRectItemMenuDialog; break;
    case ProgramType::testQtRoundedTextRectItem: p = new QtTestQtRoundedTextRectItemMenuDialog; break;
    case ProgramType::testQuestion: p = new QtTestQuestionMenuDialog; break;
    case ProgramType::testSelectFile: break;
    case ProgramType::testServerPusher: break;
    case ProgramType::testShape: p = new QtTestShapeMenuDialog; break;
    case ProgramType::testShinyButton: p = new QtTestShinyButtonMenuDialog; break;
    case ProgramType::testStopwatch: break;
    case ProgramType::testQtArrowItems: p = new QtTestQtArrowItemsMenuDialog; break;
    case ProgramType::testQtKeyboardFriendlyGraphicsView: p = new QtTestKeyboardFriendlyGraphicsViewMenuDialog; break;
    case ProgramType::testQtModels: p = new QtToolTestQtModelsMenuDialog; break;
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
    case ProgramType::twoDigitNewick: break;
    case ProgramType::ubuntuOneWatcher: break;
    case ProgramType::visualAbc: break;
    case ProgramType::n_types:
      assert(!"Unimplemented RichelBilderbeek::ProgramType");
      throw std::logic_error("Unimplemented RichelBilderbeek::ProgramType");
  }
  //p might be nullptr
  return p;
}


QtHideAndShowDialog * QtRichelBilderbeekProgram::CreateQtPlaceholderDialog(const RichelBilderbeek::ProgramType type)
{
  QtHideAndShowDialog * const d = new QtHideAndShowDialog;
  assert(!d->layout());
  QVBoxLayout * const layout = new QVBoxLayout;
  d->setLayout(layout);
  assert(d->layout());
  const boost::shared_ptr<RichelBilderbeek::Program> p = RichelBilderbeek::Program::CreateProgram(type);
  assert(p);
  {
    const std::string title = p->GetName() + "(placeholder)";
    d->setWindowTitle(title.c_str());
  }
  {
    QLabel * const label = new QLabel((p->GetName() + "(placeholder)").c_str());
    label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    layout->addWidget(label);
  }
  if (boost::filesystem::is_regular_file(p->GetFilenameConsole()))
  {
    const QPixmap pixmap(p->GetFilenameConsole().c_str());
    QLabel * const label = new QLabel;
    label->setPixmap(pixmap);
    layout->addWidget(label);
  }
  if (boost::filesystem::is_regular_file(p->GetFilenameDesktop()))
  {
    const QPixmap pixmap(p->GetFilenameDesktop().c_str());
    QLabel * const label = new QLabel;
    label->setPixmap(pixmap);
    layout->addWidget(label);
  }
  if (boost::filesystem::is_regular_file(p->GetFilenameDesktopWindowsOnly()))
  {
    const QPixmap pixmap(p->GetFilenameDesktopWindowsOnly().c_str());
    QLabel * const label = new QLabel;
    label->setPixmap(pixmap);
    layout->addWidget(label);
  }
  if (boost::filesystem::is_regular_file(p->GetFilenameWeb()))
  {
    const QPixmap pixmap(p->GetFilenameWeb().c_str());
    QLabel * const label = new QLabel;
    label->setPixmap(pixmap);
    layout->addWidget(label);
  }
  assert(d);
  return d;
}
