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
#include "qtrichelbilderbeekprogram.h"

#include <cassert>
#include <fstream>
#include <stdexcept>

#include <QLabel>
#include <QVBoxLayout>

#include "fileio.h"
#include "qtasciiartermenudialog.h"
#include "qtbeerwantermenudialog.h"
#include "qtboenkenmenudialog.h"
#include "qtcaesarciphermenudialog.h"
#include "qtcodetohtmlmenudialog.h"
#include "qtconnectthreemenudialog.h"
#include "qtcreateglossarymenudialog.h"
#include "qtcreateqtprojectzipfilemenudialog.h"
#include "qtmutualismbreakdownermenudialog.h"
#include "qtdaswahreschlagerfestmenudialog.h"
#include "qtdotmatrixmenudialog.h"
#include "qtencrangermaindialog.h"
#include "qtencrangermenudialog.h"
#include "qtfilteroperationermenudialog.h"
#include "qtfunctionplottermenudialog.h"
#include "qtgaborfiltermenudialog.h"
#include "qtgraycodermenudialog.h"
#include "qthistogramequalizationermenudialog.h"
#include "qtfisherwrightermaindialog.h"
#include "qthometrainermenudialog.h"
#include "qttestpolyfilemenudialog.h"
#include "qttestpolyfilefrompolygonsmenudialog.h"
#include "qtwkttosvgmenudialog.h"
#include "qtimagerotatermenudialog.h"
#include "qtk3opeenrijmenudialog.h"
#include "qtk3opeenrijresources.h"
#include "qtkalmanfilterermenudialog.h"
#include "qtmazecreatormenudialog.h"
#include "qtmaziakmenudialog2.h"
#include "qtmultiencrangermaindialog.h"
#include "qtmultiencrangermenudialog.h"
#include "qtmusictheorymenudialog.h"
#include "qtperfectelasticcollisionmenudialog.h"
#include "qtlizardpaperrockscissorsspockmenudialog.h"
#include "qttooltestbouncingrectswidgetmaindialog.h"
#include "qttooltestbouncingballswidgetmaindialog.h"
#include "qtsearchanddestroychessmenudialog.h"
#include "qttesttrianglemenudialog.h"
#include "qtpictocodemenudialog.h"
#include "qtpixelatormenudialog.h"
#include "qtpredickadvocatormenudialog.h"
#include "qtprimeexpertmenudialog.h"
#include "qtpvdbmenudialog.h"
#include "qtrichelbilderbeekgalleryresources.h"
#include "qtpylosmenudialog.h"
#include "qtqmakewatchermenudialog.h"
#include "qtquadraticsolvermenudialog.h"
#include "qtrandomcodemenudialog.h"
#include "qtregextestermenudialog.h"
#include "qtreversimaindialog.h"
#include "qtreversimenudialog.h"
#include "qtrichelbilderbeekgallerymenudialog.h"
#include "qtrichelbilderbeekmenudialog.h"
#include "qtrubiksclockmenudialog.h"
#include "qtsecretmessagemenudialog.h"
#include "qtsimmysterymachinemenudialog.h"
#include "qtsimplifynewickmenudialog.h"
#include "qtsitemapgeneratormenudialog.h"
#include "qtsitemapgeneratormenudialog.h"
#include "qtpaperrockscissorswithtraitmenudialog.h"
#include "qtpaperrockscissorsmenudialog.h"
#include "qtsimtoppredatorpreymenudialog.h"
#include "qtstateobservermenudialog.h"
#include "qtstylesheetsettermenudialog.h"
#include "qtfisherwrightermaindialog.h"
#include "qtsurfaceplottermenudialog.h"
#include "qttestaboutmenudialog.h"
#include "qttestapproximatormenudialog.h"
#include "qttestbinarynewickvectormenudialog.h"
#include "qttestchessmenudialog.h"
#include "qttestconceptmapmenudialog.h"
#include "qttestdialmenudialog.h"
#include "qttestdrawcanvasmenudialog.h"
#include "qttestfunctionparsermenudialog.h"
#include "qttestimagecanvasmenudialog.h"
#include "qttestledmenudialog.h"
#include "qttestmanydigitnewickmaindialog.h"
#include "qttestmanydigitnewickmenudialog.h"
#include "qttestmultiapproximatormenudialog.h"
#include "qttestmulticanvasmenudialog.h"
#include "qttestmultiplechoicequestionmenudialog.h"
#include "qttestnewickvectordialog.h"
#include "qttestopenquestionmenudialog.h"
#include "qttestplanemenudialog.h"
#include "qttestpylosmenudialog.h"
#include "qttestpolyfilefrompolygonsmenudialog.h"
#include "qttestqrcfilemenudialog.h"
#include "qttestqtarrowitemsmenudialog.h"
#include "qttestqtcreatorprofilemenudialog.h"
#include "qttestqtcreatorprofilemenudialog.h"
#include "qttestqtkeyboardfriendlygraphicsviewmenudialog.h"
#include "qttestqtmodelsmenudialog.h"
#include "qttestqtroundededitrectitemmenudialog.h"
#include "qttestqtroundedrectitemmenudialog.h"
#include "qttestquestionmenudialog.h"
#include "qttestreversimaindialog.h"
#include "qttestshapemenudialog.h"
#include "qttestshinybuttonmenudialog.h"
#include "qtstochasticityinspectormenudialog.h"
#include "qttestsimplelinearregressionmenudialog.h"
#include "qttesttextcanvasmenudialog.h"
#include "qttesttictactoemenudialog.h"
#include "qttesttogglebuttonmaindialog.h"
#include "qttesttogglebuttonmenudialog.h"
#include "qttesttwodigitnewickmenudialog.h"
#include "qtthresholdfilterermenudialog.h"
#include "qttictactoemenudialog.h"
#include "qttrianglemeshcreatormenudialog.h"
#include "qttronmenudialog.h"
#include "qtvalentinecarddecryptermenudialog.h"
#include "qtvigenereciphermenudialog.h"
#include "qtvisualabcmenudialog.h"
#include "richelbilderbeekprogram.h"

#include "trace.h"
#include "richelbilderbeekprogramtypes.h"

#pragma GCC diagnostic pop


std::unique_ptr<ribi::QtHideAndShowDialog> ribi::QtRichelBilderbeekProgram::CreateQtMenuDialog(const ProgramType type) const noexcept
{
  QtHideAndShowDialog *  p = nullptr;
  switch (type)
  {
    case ProgramType::asciiArter: p = new QtAsciiArterMenuDialog; break;
    case ProgramType::asciiArterVcl: break;
    case ProgramType::athleticLandVcl: break;
    case ProgramType::barbaImage: break;
    case ProgramType::beerWanter: p = new QtBeerWanterMenuDialog; break;
    case ProgramType::beerWanterVcl: break;
    case ProgramType::bochum: break;
    case ProgramType::boenken: p = new QtBoenkenMenuDialog; break;
    case ProgramType::boenkenVcl: break;
    case ProgramType::brainweaver: p = new pvdb::QtPvdbMenuDialog; break;
    case ProgramType::bristol: break;
    case ProgramType::caesarCipher: p = new QtCaesarCipherMenuDialog; break;
    case ProgramType::chrisWiley: break;
    case ProgramType::codeToHtml: p = new c2h::QtCodeToHtmlMenuDialog; break;
    case ProgramType::connectThree: p = new con3::QtConnectThreeMenuDialog; break;
    case ProgramType::corridor: break;
    case ProgramType::createGlossary: p = new QtCreateGlossaryMenuDialog; break;
    case ProgramType::createQtProjectZipFile: p = new QtCreateQtProjectZipFileMenuDialog; break;
    case ProgramType::crossPoll: break;
    case ProgramType::dasWahreSchlagerfest: p = new dws::QtMenuDialog; break;
    case ProgramType::dasWahreSchlagerfestVcl: break;
    case ProgramType::dotMatrix: p = new QtDotMatrixMenuDialog; break;
    case ProgramType::dotMatrixVcl: break;
    case ProgramType::encranger: p = new QtToolEncrangerMenuDialog; break;
    case ProgramType::everythingToPiecesShooter: break;
    case ProgramType::filterOperationer: p = new QtFilterOperationerMenuDialog; break;
    case ProgramType::filterOperationerVcl: break;
    case ProgramType::fisherWrighter: break; //p = new ribi::fw::QtFisherWrighterMainDialog; break;
    case ProgramType::fryskLeareLieder: break;
    case ProgramType::functionPlotter: p = new QtFunctionPlotterMenuDialog; break;
    case ProgramType::functionPlotterVcl: break;
    case ProgramType::gaborFilter: p = new QtToolGaborFilterMenuDialog; break;
    case ProgramType::gaborFilterVcl: break;
    case ProgramType::grayCoder: p = new QtGrayCoderMenuDialog; break;
    case ProgramType::grayCoderVcl: break;
    case ProgramType::gtst: break;
    case ProgramType::histogramEqualizationer: p = new QtHistogramEqualizationerMenuDialog; break;
    case ProgramType::histogramEqualizationerVcl: break;
    case ProgramType::hometrainer: p = new QtHometrainerMenuDialog; break;
    case ProgramType::hometrainerVcl: break;
    case ProgramType::imageRotater: p = new QtImageRotaterMenuDialog; break;
    case ProgramType::imageRotaterClx: break;
    case ProgramType::imageRotaterVcl: break;
    case ProgramType::k3OpEenRij:
    {
      const boost::shared_ptr<const ribi::QtK3OpEenRijResources> resources(new ribi::QtK3OpEenRijResources);
      p = new QtK3OpEenRijMenuDialog(resources);
    }
    break;
    case ProgramType::k3OpEenRijVcl: break;
    case ProgramType::kalmanFilterer: p = new kalman::QtKalmanFiltererMenuDialog; break;
    case ProgramType::keySender: break;
    case ProgramType::knokfighterVcl: break;
    case ProgramType::kTouchLectureCreator: break;
    case ProgramType::lambdaBot: break;
    case ProgramType::learyCircumplex: break;
    case ProgramType::lizardPaperRockScissorsSpock: p = new QtLizardPaperRockScissorsSpockMenuDialog; break;
    case ProgramType::logisticGrowthSimulator: break;
    case ProgramType::loose: break;
    case ProgramType::martianCafeTuinemaTycoon: break;
    case ProgramType::mazeCreator: p = new QtMazeCreatorMenuDialog; break;
    case ProgramType::mazeCreatorVcl: break;
    case ProgramType::maziak: p = new maziak::QtMaziakMenuDialog2; break;
    case ProgramType::maziakVcl: break;
    case ProgramType::metZnDrieenVcl: break;
    case ProgramType::midiLessonCreator: break;
    case ProgramType::morpher: break;
    case ProgramType::multiEncranger: p = new QtMultiEncrangerMenuDialog; break;
    case ProgramType::multiEncrangerVcl: break;
    case ProgramType::muscaDomestica: break;
    case ProgramType::musicTheory: p = new QtMusicTheoryMenuDialog; break;
    case ProgramType::mutualismBreakdowner: p = new ribi::mb::QtMutualismBreakdownerMenuDialog; break;
    case ProgramType::ndsmake: break;
    case ProgramType::paperRockScissors: p = new QtPaperRockScissorsMenuDialog; break;
    case ProgramType::paperRockScissorsVcl: break;
    case ProgramType::paperRockScissorsWithTrait: p = new QtPaperRockScissorsWithTraitMenuDialog; break;
    case ProgramType::pause: break;
    case ProgramType::perfectElasticCollision: p = new QtPerfectElasticCollisionMenuDialog; break;
    case ProgramType::preDickAdvocaTor: p = new QtPreDickAdvocaTorMenuDialog; break;
    case ProgramType::picToCode: p = new p2c::QtMenuDialog; break;
    case ProgramType::pixelator: p = new QtPixelatorMenuDialog; break;
    case ProgramType::pixelatorVcl: break;
    case ProgramType::pokeVolleyVcl: break;
    case ProgramType::primeExpert: p = new QtToolPrimeExpertMenuDialog;  break;
    case ProgramType::projectRichelBilderbeek: p = new QtRichelBilderbeekMenuDialog; break;
    case ProgramType::pylos: p = new pylos::QtPylosMenuDialog; break;
    case ProgramType::qmakeWatcher: p = new QtQmakeWatcherMenuDialog; break;
    case ProgramType::quadraticSolver: p = new QtQuadraticSolverMenuDialog; break;
    case ProgramType::rampalEtienne: break;
    case ProgramType::rasper: break;
    case ProgramType::randomCode: p = new QtRandomCodeMenuDialog; break;
    case ProgramType::randomCodeVcl: break;
    case ProgramType::refrigeratorPuzzleSolver: break;
    case ProgramType::regexTester: p = new QtRegexTesterMenuDialog; break;
    case ProgramType::reversi: p = new reversi::QtReversiMenuDialog; break;
    case ProgramType::reversiVcl: break;
    case ProgramType::richelBilderbeekGallery: p = new QtRichelBilderbeekGalleryMenuDialog; break;
    case ProgramType::richelbilderbeekNlSitemapGenerator: p = new QtSitemapGeneratorMenuDialog; break;
    case ProgramType::rubiksClock: p = new ruco::QtRubiksClockMenuDialog; break;
    case ProgramType::rubiksClockVcl: break;
    case ProgramType::searchAndDestroyChess: p = new sadc::QtSearchAndDestroyChessMenuDialog; break;
    case ProgramType::searchAndDestroyChessVcl: break;
    case ProgramType::secretMessage: p = new sema::QtMenuDialog; break;
    case ProgramType::secretMessageVcl: break;
    case ProgramType::simBrainiac: break;
    case ProgramType::simImmuneResponse: break;
    case ProgramType::simMysteryMachine: p = new QtSimMysteryMachineMenuDialog; break;
    case ProgramType::simplifyNewick: p = new QtToolSimplifyNewickMenuDialog; break;
    case ProgramType::simTopPredatorPrey: p = new QtSimTopPredatorPreyMenuDialog; break;
    case ProgramType::simPredatorVcl: break;
    case ProgramType::simStagecraft: break;
    case ProgramType::soaSim: break;
    case ProgramType::solvePuzzleX: break;
    case ProgramType::spaceHarryVcl: break;
    case ProgramType::staircaseCardCreator: break;
    case ProgramType::stateObserver: p = new QtStateObserverMenuDialog; break;
    case ProgramType::stochasticityInspector: p = new QtStochasticityInspectorMenuDialog; break;
    case ProgramType::styleSheetSetter: p = new QtStyleSheetSetterMenuDialog; break;
    case ProgramType::surfacePlotter: p = new QtSurfacePlotterMenuDialog; break;
    case ProgramType::surfacePlotterVcl: break;
    case ProgramType::tankBattalion: break;
    case ProgramType::testAbout: p = new QtTestAboutMenuDialog; break;
    case ProgramType::testApproximator: p = new QtToolTestApproximatorMenuDialog; break;
    case ProgramType::testBouncingBallsWidget: p = new QtToolTestBouncingBallsWidgetMainDialog; break;
    case ProgramType::testBouncingRectsWidget: p = new QtToolTestBouncingRectsWidgetMainDialog; break;
    case ProgramType::testBroadcastServer: break;
    case ProgramType::testBinaryNewickVector: p = new QtTestBinaryNewickVectorMenuDialog; break;
    case ProgramType::testChess: p = new QtTestChessMenuDialog; break;
    case ProgramType::testConceptMap: p = new ribi::cmap::QtTestMenuDialog; break;
    case ProgramType::testDial: p = new QtTestDialMenuDialog; break;
    case ProgramType::testDrawCanvas: p = new QtTestDrawCanvasMenuDialog; break;
    case ProgramType::testEntrance: break;
    case ProgramType::testExercise: break;
    case ProgramType::testFunctionParser: p = new QtTestFunctionParserMenuDialog; break;
    case ProgramType::testGnuplotInterface: break;
    case ProgramType::testGraphicsProxyWidget: break;
    case ProgramType::testGravityWidget: break;
    case ProgramType::testGroupWidget: break;
    case ProgramType::testHugeVector: break;
    case ProgramType::testImageCanvas: p = new QtTestImageCanvasMenuDialog; break;
    case ProgramType::testLazy_init: break;
    case ProgramType::testLed: p = new QtTestLedMenuDialog; break;
    case ProgramType::testManyDigitNewick: p = new QtTestManyDigitNewickMenuDialog; break;
    case ProgramType::testMultiApproximator: p = new QtToolTestMultiApproximatorMenuDialog; break;
    case ProgramType::testMultiCanvas: p = new QtTestMultiCanvasMenuDialog; break;
    case ProgramType::testMultipleChoiceQuestion: p = new QtTestMultipleChoiceQuestionMenuDialog; break;
    case ProgramType::testMultiVector: break;
    case ProgramType::testNdsmake: break;
    case ProgramType::testNeuralNet: /* p = new QtTestNeuralNetMenuDialog; */ break;
    case ProgramType::testNewick: break;
    case ProgramType::testNewickVector: p = new QtTestNewickVectorDialog; break;
    case ProgramType::testOpenQuestion: p = new QtTestOpenQuestionMenuDialog;  break;
    case ProgramType::testPlane: p = new QtTestPlaneMenuDialog; break;
    case ProgramType::testPylos: p = new pylos::QtTestPylosMenuDialog; break;
    case ProgramType::testPolyFile: p = new QtTestPolyFileMenuDialog; break;
    case ProgramType::testPolyFileFromPolygons: p = new QtTestPolyFileFromPolygonsMenuDialog; break;
    case ProgramType::testQrcFile: p = new QtTestQrcFileMenuDialog; break;
    case ProgramType::testQtCreatorProFile: p = new QtTestQtCreatorProFileMenuDialog; break;
    case ProgramType::testQtHideAndShowDialog: break;
    case ProgramType::testQtOcrWidget: break;
    case ProgramType::testQtRoundedEditRectItem: p = new QtTestQtRoundedEditRectItemMenuDialog; break;
    case ProgramType::testQtRoundedRectItem: p = new QtTestQtRoundedRectItemMenuDialog; break;
    case ProgramType::testQuestion: p = new QtTestQuestionMenuDialog; break;
    case ProgramType::testReversi: p = new QtTestReversiMainDialog; break;
    case ProgramType::testSelectFileDialog: break;
    case ProgramType::testServerPusher: break;
    case ProgramType::testShape: p = new QtTestShapeMenuDialog; break;
    case ProgramType::testShinyButton: p = new QtTestShinyButtonMenuDialog; break;
    case ProgramType::testSimpleLinearRegression:  p = new QtToolTestSimpleLinearRegressionMenuDialog; break;
    case ProgramType::testStopwatch: break;
    case ProgramType::testQtArrowItems: p = new QtTestQtArrowItemsMenuDialog; break;
    case ProgramType::testQtKeyboardFriendlyGraphicsView: p = new QtTestKeyboardFriendlyGraphicsViewMenuDialog; break;
    case ProgramType::testQtModels: p = new QtToolTestQtModelsMenuDialog; break;
    case ProgramType::testTextCanvas: p = new QtTestTextCanvasMenuDialog; break;
    case ProgramType::testTextPositionWidget: break;
    case ProgramType::testTicTacToe: p = new tictactoe::QtTestTicTacToeMenuDialog; break;
    case ProgramType::testTimedServerPusher: break;
    case ProgramType::testToggleButton: p = new QtTestToggleButtonMenuDialog; break;
    case ProgramType::testTriangle: p = new QtTestTriangleMenuDialog; break;
    case ProgramType::testTwoDigitNewick: p = new QtTestTwoDigitNewickMenuDialog; break;
    case ProgramType::thorVeen: break;
    case ProgramType::thresholdFilterer: p = new QtThresholdFiltererMenuDialog; break;
    case ProgramType::thresholdFiltererVcl: break;
    case ProgramType::ticTacToe: p = new tictactoe::QtTicTacToeMenuDialog; break;
    case ProgramType::timePoll: break;
    case ProgramType::triangleMeshCreator: break; p = new QtTriangleMeshCreatorMenuDialog; break;
    case ProgramType::tronCollection: new tron::QtTronMenuDialog; break;
    case ProgramType::tronCollectionVcl: break;
    case ProgramType::ubuntuOneWatcher: break;
    case ProgramType::valentineCardDecrypter: p = new QtValentineCardDecrypterMenuDialog; break;
    case ProgramType::vigenereCipher: p = new QtVigenereCipherMenuDialog; break;
    case ProgramType::virtualBastard: break;
    case ProgramType::visualAbc: p = new QtVisualAbcMenuDialog; break;
    case ProgramType::wktToSvg: p = new QtWktToSvgMenuDialog; break;
    case ProgramType::xeNonZero: break;
    case ProgramType::zork: break;
    case ProgramType::n_types:
      assert(!"Unimplemented ProgramType");
      throw std::logic_error("Unimplemented ProgramType");
  }
  std::unique_ptr<QtHideAndShowDialog> q(p);
  assert(p == q.get());
  return q;
}
