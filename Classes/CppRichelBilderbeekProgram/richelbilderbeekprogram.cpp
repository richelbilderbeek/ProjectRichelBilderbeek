//---------------------------------------------------------------------------
/*
RichelBilderbeek::Program, class for a program by Richel Bilderbeek
Copyright (C) 2012-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppProjectRichelBilderbeekProgram.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "richelbilderbeekprogram.h"

#include <iostream>
#include <stdexcept>

#include "richelbilderbeekprogramtypes.h"
#include "richelbilderbeekprogramstatus.h"
#include "trace.h"
#pragma GCC diagnostic pop

boost::shared_ptr<ribi::Program> ribi::Program::CreateProgram(const ProgramType type) noexcept
{
  boost::shared_ptr<Program> p;
  switch (type)
  {
    case ProgramType::aminoAcidFighter: p.reset(new ProgramAminoAcidFighter); break;
    case ProgramType::asciiArter: p.reset(new ProgramAsciiArter); break;
    case ProgramType::asciiArterVcl: p.reset(new ProgramAsciiArterVcl); break;
    case ProgramType::barbaImage: p.reset(new ProgramBarbaImage); break;
    case ProgramType::beerWanter: p.reset(new ProgramBeerWanter); break;
    case ProgramType::beerWanterVcl: p.reset(new ProgramBeerWanterVcl); break;
    case ProgramType::athleticLand: p.reset(new ProgramAthleticLand); break;
    case ProgramType::athleticLandVcl: p.reset(new ProgramAthleticLandVcl); break;
    case ProgramType::bochum: p.reset(new ProgramBochum); break;
    case ProgramType::boenken: p.reset(new ProgramBoenken); break;
    case ProgramType::boenkenVcl: p.reset(new ProgramBoenkenVcl); break;
    case ProgramType::brainweaver: p.reset(new ProgramBrainweaver); break;
    case ProgramType::bristol: p.reset(new ProgramBristol); break;
    case ProgramType::caesarCipher: p.reset(new ProgramCaesarCipher); break;
    case ProgramType::chrisWiley: p.reset(new ProgramChrisWiley); break;
    case ProgramType::codeBreaker: p.reset(new ProgramCodeBreaker); break;
    case ProgramType::codeToHtml: p.reset(new ProgramCodeToHtml); break;
    case ProgramType::connectThree: p.reset(new ProgramConnectThree); break;
    case ProgramType::corridor: p.reset(new ProgramCorridor); break;
    case ProgramType::createGlossary: p.reset(new ProgramCreateGlossary); break;
    case ProgramType::createQtProjectZipFile: p.reset(new ProgramCreateQtProjectZipFile); break;
    case ProgramType::crossPoll: p.reset(new ProgramCrossPoll); break;
    case ProgramType::dasWahreSchlagerfest: p.reset(new ProgramDasWahreSchlagerfest); break;
    case ProgramType::dasWahreSchlagerfestVcl: p.reset(new ProgramDasWahreSchlagerfestVcl); break;
    case ProgramType::dotMatrix: p.reset(new ProgramDotMatrix); break;
    case ProgramType::dotMatrixVcl: p.reset(new ProgramDotMatrixVcl); break;
    case ProgramType::encranger: p.reset(new ProgramEncranger); break;
    case ProgramType::everythingToPiecesShooter: p.reset(new ProgramEverythingToPiecesShooter); break;
    case ProgramType::fakeEvy: p.reset(new ProgramFakeEvy); break;
    case ProgramType::filterOperationer: p.reset(new ProgramFilterOperationer); break;
    case ProgramType::filterOperationerVcl: p.reset(new ProgramFilterOperationerVcl); break;
    case ProgramType::fryskLeareLieder: p.reset(new ProgramFryskLeareLieder); break;
    case ProgramType::functionPlotter: p.reset(new ProgramFunctionPlotter); break;
    case ProgramType::functionPlotterVcl: p.reset(new ProgramFunctionPlotterVcl); break;
    case ProgramType::gaborFilter: p.reset(new ProgramGaborFilter); break;
    case ProgramType::gaborFilterVcl: p.reset(new ProgramGaborFilterVcl); break;
    case ProgramType::grayCoder: p.reset(new ProgramGrayCoder); break;
    case ProgramType::grayCoderVcl: p.reset(new ProgramGrayCoderVcl); break;
    case ProgramType::gtst: p.reset(new ProgramGtst); break;
    case ProgramType::histogramEqualizationer: p.reset(new ProgramHistogramEqualizationer); break;
    case ProgramType::histogramEqualizationerVcl: p.reset(new ProgramHistogramEqualizationerVcl); break;
    case ProgramType::hometrainer: p.reset(new ProgramHometrainer); break;
    case ProgramType::hometrainerVcl: p.reset(new ProgramHometrainerVcl); break;
    case ProgramType::imageRotater: p.reset(new ProgramImageRotater); break;
    case ProgramType::imageRotaterClx: p.reset(new ProgramImageRotaterClx); break;
    case ProgramType::imageRotaterVcl: p.reset(new ProgramImageRotaterVcl); break;
    case ProgramType::k3OpEenRij: p.reset(new ProgramK3OpEenRij); break;
    case ProgramType::k3OpEenRijVcl: p.reset(new ProgramK3OpEenRijVcl); break;
    case ProgramType::kalmanFilterer: p.reset(new ProgramKalmanFilterer); break;
    case ProgramType::keySender: p.reset(new ProgramKeySender); break;
    case ProgramType::knokfighter: p.reset(new ProgramKnokfighter); break;
    case ProgramType::knokfighterVcl: p.reset(new ProgramKnokfighterVcl); break;
    case ProgramType::kTouchLectureCreator: p.reset(new ProgramKTouchLectureCreator); break;
    case ProgramType::lambdaBot: p.reset(new ProgramLambdaBot); break;
    case ProgramType::learyCircumplex: p.reset(new ProgramLearyCircumplex); break;
    case ProgramType::logisticGrowthSimulator: p.reset(new ProgramLogisticGrowthSimulator); break;
    case ProgramType::loose: p.reset(new ProgramLoose); break;
    case ProgramType::martianCafeTuinemaTycoon: p.reset(new ProgramMartianCafeTuinemaTycoon); break;
    case ProgramType::mazeCreator: p.reset(new ProgramMazeCreator); break;
    case ProgramType::mazeCreatorVcl: p.reset(new ProgramMazeCreatorVcl); break;
    case ProgramType::maziak: p.reset(new ProgramMaziak); break;
    case ProgramType::maziakVcl: p.reset(new ProgramMaziakVcl); break;
    //case ProgramType::metZnDrieen: p.reset(new ProgramMetZnDrieen); break;
    case ProgramType::metZnDrieenVcl: p.reset(new ProgramMetZnDrieenVcl); break;
    case ProgramType::midiLessonCreator: p.reset(new ProgramMidiLessonCreator); break;
    case ProgramType::morpher: p.reset(new ProgramMorpher); break;
    case ProgramType::multiEncranger: p.reset(new ProgramMultiEncranger); break;
    case ProgramType::multiEncrangerVcl: p.reset(new ProgramMultiEncrangerVcl); break;
    case ProgramType::muscaDomestica: p.reset(new ProgramMuscaDomestica); break;
    case ProgramType::musicTheory: p.reset(new ProgramMusicTheory); break;
    case ProgramType::ndsmake: p.reset(new ProgramNdsmake); break;
    case ProgramType::ndsPaint: p.reset(new ProgramNdsPaint); break;
    case ProgramType::paperRockScissors: p.reset(new ProgramPaperRockScissors); break;
    case ProgramType::paperRockScissorsVcl: p.reset(new ProgramPaperRockScissorsVcl); break;
    case ProgramType::pause: p.reset(new ProgramPause); break;
    case ProgramType::perfectElasticCollision: p.reset(new ProgramPerfectElasticCollision); break;
    case ProgramType::picToCode: p.reset(new ProgramPicToCode); break;
    case ProgramType::pixelator: p.reset(new ProgramPixelator); break;
    case ProgramType::pixelatorVcl: p.reset(new ProgramPixelatorVcl); break;
    case ProgramType::pokeVolleyVcl: p.reset(new ProgramPokeVolleyVcl); break;
    case ProgramType::pong: p.reset(new ProgramPong); break;
    case ProgramType::preDickAdvocaTor: p.reset(new ProgramPreDickAdvocaTor); break;
    case ProgramType::primeExpert: p.reset(new ProgramPrimeExpert); break;
    case ProgramType::projectRichelBilderbeek: p.reset(new ProgramProjectRichelBilderbeek); break;
    case ProgramType::pylos: p.reset(new ProgramPylos); break;
    case ProgramType::qmakeWatcher: p.reset(new ProgramQmakeWatcher); break;
    case ProgramType::quadraticSolver: p.reset(new ProgramQuadraticSolver); break;
    case ProgramType::rampalEtienne: p.reset(new ProgramRampalEtienne); break;
    case ProgramType::randomCode: p.reset(new ProgramRandomCode); break;
    case ProgramType::randomCodeVcl: p.reset(new ProgramRandomCodeVcl); break;
    case ProgramType::rasper: p.reset(new ProgramRasper); break;
    case ProgramType::refrigeratorPuzzleSolver: p.reset(new ProgramRefrigeratorPuzzleSolver); break;
    case ProgramType::regexTester: p.reset(new ProgramRegexTester); break;
    case ProgramType::reversi: p.reset(new ProgramReversi); break;
    case ProgramType::reversiVcl: p.reset(new ProgramReversiVcl); break;
    case ProgramType::richelBilderbeekGallery: p.reset(new ProgramRichelBilderbeekGallery); break;
    case ProgramType::richelbilderbeekNlSitemapGenerator: p.reset(new ProgramRichelBilderbeekNlSitemapGenerator); break;
    case ProgramType::rubiksClock: p.reset(new ProgramRubiksClock); break;
    case ProgramType::rubiksClockVcl: p.reset(new ProgramRubiksClockVcl); break;
    case ProgramType::searchAndDestroyChess: p.reset(new ProgramSearchAndDestroyChess); break;
    case ProgramType::searchAndDestroyChessVcl: p.reset(new ProgramSearchAndDestroyChessVcl); break;
    case ProgramType::secretMessage: p.reset(new ProgramSecretMessage); break;
    case ProgramType::secretMessageVcl: p.reset(new ProgramSecretMessageVcl); break;
    case ProgramType::simBrainiac: p.reset(new ProgramSimBrainiac); break;
    case ProgramType::simImmuneResponse: p.reset(new ProgramSimImmuneResponse); break;
    case ProgramType::simMysteryMachine: p.reset(new ProgramSimMysteryMachine); break;
    case ProgramType::simplifyNewick: p.reset(new ProgramSimplifyNewick); break;
    case ProgramType::simPredatorVcl: p.reset(new ProgramSimPredatorVcl); break;
    case ProgramType::simStagecraft: p.reset(new ProgramSimStagecraft); break;
    case ProgramType::soaSim: p.reset(new ProgramSoaSim); break;
    case ProgramType::solvePuzzleX: p.reset(new ProgramSolvePuzzleX); break;
    //case ProgramType::spaceHarry: p.reset(new ProgramSpaceHarry); break;
    case ProgramType::spaceHarryVcl: p.reset(new ProgramSpaceHarryVcl); break;
    case ProgramType::staircaseCardCreator: p.reset(new ProgramStaircaseCardCreator); break;
    case ProgramType::stateObserver: p.reset(new ProgramStateObserver); break;
    case ProgramType::styleSheetSetter: p.reset(new ProgramStyleSheetSetter); break;
    case ProgramType::superNsanaBros: p.reset(new ProgramSuperNsanaBros); break;
    case ProgramType::surfacePlotter: p.reset(new ProgramSurfacePlotter); break;
    case ProgramType::surfacePlotterVcl: p.reset(new ProgramSurfacePlotterVcl); break;
    case ProgramType::tankBattalion: p.reset(new ProgramTankBattalion); break;
    case ProgramType::testAbout: p.reset(new ProgramTestAbout); break;
    case ProgramType::testApproximator: p.reset(new ProgramTestApproximator); break;
    case ProgramType::testBinaryNewickVector: p.reset(new ProgramTestBinaryNewickVector); break;
    case ProgramType::testBouncingBallsWidget: p.reset(new ProgramTestBouncingBallsWidget); break;
    case ProgramType::testBouncingRectsWidget: p.reset(new ProgramTestBouncingRectsWidget); break;
    case ProgramType::testBroadcastServer: p.reset(new ProgramTestBroadcastServer); break;
    case ProgramType::testChess: p.reset(new ProgramTestChess); break;
    case ProgramType::testConceptMap: p.reset(new ProgramTestConceptMap); break;
    case ProgramType::testDial: p.reset(new ProgramTestDial); break;
    case ProgramType::testDrawCanvas: p.reset(new ProgramTestDrawCanvas); break;
    case ProgramType::testEntrance: p.reset(new ProgramTestEntrance); break;
    case ProgramType::testExercise: p.reset(new ProgramTestExercise); break;
    case ProgramType::testFunctionParser: p.reset(new ProgramTestFunctionParser); break;
    case ProgramType::testGnuplotInterface: p.reset(new ProgramTestGnuplotInterface); break;
    case ProgramType::testGraphicsProxyWidget: p.reset(new ProgramTestGraphicsProxyWidget); break;
    case ProgramType::testGravityWidget: p.reset(new ProgramTestGravityWidget); break;
    case ProgramType::testGroupWidget: p.reset(new ProgramTestGroupWidget); break;
    case ProgramType::testHugeVector: p.reset(new ProgramTestHugeVector); break;
    case ProgramType::testImageCanvas: p.reset(new ProgramTestImageCanvas); break;
    case ProgramType::testLazy_init: p.reset(new ProgramTestLazy_init); break;
    case ProgramType::testLed: p.reset(new ProgramTestLed); break;
    case ProgramType::testManyDigitNewick: p.reset(new ProgramTestManyDigitNewick); break;
    case ProgramType::testMultiApproximator: p.reset(new ProgramTestMultiApproximator); break;
    case ProgramType::testMultiCanvas: p.reset(new ProgramTestMultiCanvas); break;
    case ProgramType::testMultipleChoiceQuestion: p.reset(new ProgramTestMultipleChoiceQuestion); break;
    case ProgramType::testMultiVector: p.reset(new ProgramTestMultiVector); break;
    case ProgramType::testNdsmake: p.reset(new ProgramTestNdsmake); break;
    case ProgramType::testNeuralNet: p.reset(new ProgramTestNeuralNet); break;
    case ProgramType::testNewick: p.reset(new ProgramTestNewick); break;
    case ProgramType::testNewickVector: p.reset(new ProgramTestNewickVector); break;
    case ProgramType::testOpenQuestion: p.reset(new ProgramTestOpenQuestion); break;
    case ProgramType::testPlane: p.reset(new ProgramTestPlane); break;
    case ProgramType::testPolyFile: p.reset(new ProgramTestPolyFile); break;
    case ProgramType::testPolyFileFromPolygons: p.reset(new ProgramTestPolyFileFromPolygons); break;
    case ProgramType::testPylos: p.reset(new ProgramTestPylos); break;
    case ProgramType::testQrcFile: p.reset(new ProgramTestQrcFile); break;
    case ProgramType::testQtArrowItems: p.reset(new ProgramTestQtArrowItems); break;
    case ProgramType::testQtCreatorProFile: p.reset(new ProgramTestQtCreatorProFile); break;
    case ProgramType::testQtHideAndShowDialog: p.reset(new ProgramTestQtHideAndShowDialog); break;
    case ProgramType::testQtKeyboardFriendlyGraphicsView: p.reset(new ProgramTestQtKeyboardFriendlyGraphicsView); break;
    case ProgramType::testQtOcrWidget: p.reset(new ProgramTestQtOcrWidget); break;
    case ProgramType::testQtModels: p.reset(new ProgramTestQtModels); break;
    case ProgramType::testQtRoundedEditRectItem: p.reset(new ProgramTestQtRoundedEditRectItem); break;
    case ProgramType::testQtRoundedRectItem: p.reset(new ProgramTestQtRoundedRectItem); break;
    //case ProgramType::testQtRoundedTextRectItem: p.reset(new ProgramTestQtRoundedTextRectItem); break;
    case ProgramType::testQuestion: p.reset(new ProgramTestQuestion); break;
    case ProgramType::testReversi: p.reset(new ProgramTestReversi); break;
    case ProgramType::testSelectFileDialog: p.reset(new ProgramTestSelectFileDialog); break;
    case ProgramType::testServerPusher: p.reset(new ProgramTestServerPusher); break;
    case ProgramType::testShape: p.reset(new ProgramTestShape); break;
    case ProgramType::testShinyButton: p.reset(new ProgramTestShinyButton); break;
    case ProgramType::testSimpleLinearRegression: p.reset(new ProgramTestSimpleLinearRegression); break;
    case ProgramType::testStopwatch: p.reset(new ProgramTestStopwatch); break;
    case ProgramType::testTextCanvas: p.reset(new ProgramTestTextCanvas); break;
    case ProgramType::testTextPositionWidget: p.reset(new ProgramTestTextPositionWidget); break;
    case ProgramType::testTicTacToe: p.reset(new ProgramTestTicTacToe); break;
    case ProgramType::testTimedServerPusher: p.reset(new ProgramTestTimedServerPusher); break;
    case ProgramType::testToggleButton: p.reset(new ProgramTestToggleButton); break;
    case ProgramType::testTriangle: p.reset(new ProgramTestTriangle); break;
    case ProgramType::triangleMeshCreator: p.reset(new ProgramTriangleMeshCreator); break;
    case ProgramType::testTwoDigitNewick: p.reset(new ProgramTestTwoDigitNewick); break;
    case ProgramType::thorVeen: p.reset(new ProgramThorVeen); break;
    case ProgramType::thresholdFilterer: p.reset(new ProgramThresholdFilterer); break;
    case ProgramType::thresholdFiltererVcl: p.reset(new ProgramThresholdFiltererVcl); break;
    case ProgramType::ticTacToe: p.reset(new ProgramTicTacToe); break;
    case ProgramType::ticTacToeLearner: p.reset(new ProgramTicTacToeLearner); break;
    case ProgramType::ticTacToeValuer: p.reset(new ProgramTicTacToeValuer); break;
    case ProgramType::timePoll: p.reset(new ProgramTimePoll); break;
    case ProgramType::tronCollection: p.reset(new ProgramTronCollection); break;
    case ProgramType::tronCollectionVcl: p.reset(new ProgramTronCollectionVcl); break;
    case ProgramType::ubuntuOneWatcher: p.reset(new ProgramUbuntuOneWatcher); break;
    case ProgramType::valentineCardDecrypter: p.reset(new ProgramValentineCardDecrypter); break;
    case ProgramType::vanDenBogaart: p.reset(new ProgramVanDenBogaart); break;
    case ProgramType::vigenereCipher: p.reset(new ProgramVigenereCipher); break;
    case ProgramType::virtualBastard: p.reset(new ProgramVirtualBastard); break;
    case ProgramType::visualAbc: p.reset(new ProgramVisualAbc); break;
    case ProgramType::wktToSvg: p.reset(new ProgramWktToSvg); break;
    case ProgramType::xeNonZero: p.reset(new ProgramXeNonZero); break;
    case ProgramType::zork: p.reset(new ProgramZork); break;
    case ProgramType::n_types:
      assert(!"Unimplemented RichelBilderbeek::ProgramType");
      throw std::logic_error("Unimplemented RichelBilderbeek::ProgramType");
  }
  #ifndef NDEBUG
  if (!p)
  {
    TRACE(ProgramTypes::ProgramTypeToEnumName(type));
  }
  assert(p);
  if (p->GetType() != type)
  {
    TRACE("ERROR");
    TRACE(p->GetName());
    TRACE(ProgramTypes::ProgramTypeToEnumName(type));
    TRACE(ProgramTypes::ProgramTypeToEnumName(p->GetType()));
  }
  #endif
  assert(p->GetType() == type
    && "type and Program::GetType must match");

  return p;
}

std::string ribi::Program::GetName() const noexcept
{
  return ribi::ProgramTypes::ProgramTypeToEnumName(this->GetType());
}

std::string ribi::Program::GetScreenName() const noexcept
{
  return ribi::ProgramTypes::ProgramTypeToScreenName(this->GetType());
}

std::vector<boost::shared_ptr<ribi::Program>> ribi::Program::GetAllPrograms() noexcept
{
  const std::vector<ProgramType> types = ProgramTypes::GetAll();
  std::vector<boost::shared_ptr<Program>> v;

  for (const ProgramType type: types)
  {
    const boost::shared_ptr<Program> p = CreateProgram(type);
    assert(p);
    v.push_back(p);
  }
  assert(v.size() == types.size());
  std::sort(v.begin(),v.end(),
    [](const boost::shared_ptr<Program>& lhs, const boost::shared_ptr<Program>& rhs) { return lhs->GetName() < rhs->GetName(); }
    );
  return v;
}

std::string ribi::Program::GetFilenameBase() const noexcept
{
  std::string s = this->GetTypeName();
  s[0] = std::toupper(s[0]);
  return s + GetScreenName();
}

std::string ribi::Program::GetTypeName() const noexcept
{
  return ProgramTypes::ProgramTypeToEnumName(this->GetType());
}

std::string ribi::Program::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::Program::GetVersionHistory() noexcept
{
  return {
    "2012-02-19: Version 1.0: initial version"
  };
}

std::ostream& ribi::operator<<(std::ostream& os, const Program& p) noexcept
{
  const std::string name = p.GetName();

  os << name;

  if (name.size() < 10) { os << '\t'; }

  os
     << '\t' << p.GetTypeName()
     << '\t' << ProgramStatusToStr(p.GetStatusConsole())
     << '\t' << ProgramStatusToStr(p.GetStatusDesktopWindowsOnly())
     << '\t' << ProgramStatusToStr(p.GetStatusDesktop())
     << '\t' << ProgramStatusToStr(p.GetStatusWebApplication());
   return os;
}

bool ribi::operator<(const Program& lhs, const Program& rhs) noexcept
{
  if (lhs.GetTypeName() < rhs.GetTypeName()) return true;
  if (lhs.GetTypeName() > rhs.GetTypeName()) return false;
  return lhs.GetName() < rhs.GetName();
}
