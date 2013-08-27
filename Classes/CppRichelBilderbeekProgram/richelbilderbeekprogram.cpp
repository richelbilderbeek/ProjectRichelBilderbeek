//---------------------------------------------------------------------------
/*
RichelBilderbeek::Program, class for a program by Richel Bilderbeek
Copyright (C) 2012 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ProjectRichelBilderbeekProgram.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "richelbilderbeekprogram.h"

#include <iostream>
#include <stdexcept>

#include "richelbilderbeekprogramstatus.h"

namespace RichelBilderbeek {

const boost::shared_ptr<Program> Program::CreateProgram(const ProgramType type)
{
  boost::shared_ptr<Program> p;
  switch (type)
  {
    case ProgramType::asciiArter: p.reset(new ProgramAsciiArter); break;
    case ProgramType::barbaImage: p.reset(new ProgramBarbaImage); break;
    case ProgramType::beerWanter: p.reset(new ProgramBeerWanter); break;
    case ProgramType::bochum: p.reset(new ProgramBochum); break;
    case ProgramType::boenken: p.reset(new ProgramBoenken); break;
    case ProgramType::chrisWiley: p.reset(new ProgramChrisWiley); break;
    case ProgramType::codeToHtml: p.reset(new ProgramCodeToHtml); break;
    case ProgramType::connectThree: p.reset(new ProgramCodeToHtml); break;
    case ProgramType::createGlossary: p.reset(new ProgramCreateGlossary); break;
    case ProgramType::createQtProjectZipFile: p.reset(new ProgramCreateQtProjectZipFile); break;
    case ProgramType::createSitemap: p.reset(new ProgramCreateSitemap); break;
    case ProgramType::crossPoll: p.reset(new ProgramCrossPoll); break;
    case ProgramType::dasWahreSchlagerfest: p.reset(new ProgramDasWahreSchlagerfest); break;
    case ProgramType::dotMatrix: p.reset(new ProgramDotMatrix); break;
    case ProgramType::encranger: p.reset(new ProgramEncranger); break;
    case ProgramType::filterOperationer: p.reset(new ProgramFilterOperationer); break;
    case ProgramType::fryskLeareLieder: p.reset(new ProgramFryskLeareLieder); break;
    case ProgramType::functionPlotter: p.reset(new ProgramFunctionPlotter); break;
    case ProgramType::gaborFilter: p.reset(new ProgramGaborFilter); break;
    case ProgramType::gnuplotInterface: p.reset(new ProgramGnuplotInterface); break;
    case ProgramType::grayCoder: p.reset(new ProgramGrayCoder); break;
    case ProgramType::gtst: p.reset(new ProgramGtst); break;
    case ProgramType::histogramEqualizationer: p.reset(new ProgramHistogramEqualizationer); break;
    case ProgramType::hometrainer: p.reset(new ProgramHometrainer); break;
    case ProgramType::imageRotater: p.reset(new ProgramImageRotater); break;
    case ProgramType::k3OpEenRij: p.reset(new ProgramK3OpEenRij); break;
    case ProgramType::kalmanFilterer: p.reset(new ProgramKalmanFilterer); break;
    case ProgramType::keySender: p.reset(new ProgramKeySender); break;
    case ProgramType::knokfighter: p.reset(new ProgramKnokfighter); break;
    case ProgramType::kTouchLectureCreator: p.reset(new ProgramKTouchLectureCreator); break;
    case ProgramType::learyCircumplex: p.reset(new ProgramLearyCircumplex); break;
    case ProgramType::logisticGrowthSimulator: p.reset(new ProgramLogisticGrowthSimulator); break;
    case ProgramType::loose: p.reset(new ProgramLoose); break;
    case ProgramType::mazeCreator: p.reset(new ProgramMazeCreator); break;
    case ProgramType::maziak: p.reset(new ProgramMaziak); break;
    case ProgramType::morpher: p.reset(new ProgramMorpher); break;
    case ProgramType::multiEncranger: p.reset(new ProgramMultiEncranger); break;
    case ProgramType::muscaDomestica: p.reset(new ProgramMuscaDomestica); break;
    case ProgramType::musicTheory: p.reset(new ProgramMusicTheory); break;
    case ProgramType::ndsMake: p.reset(new ProgramNdsmake); break;
    case ProgramType::newickVector: p.reset(new ProgramNewickVector); break;
    case ProgramType::paperRockScissors: p.reset(new ProgramPaperRockScissors); break;
    case ProgramType::pause: p.reset(new ProgramPause); break;
    case ProgramType::perfectElasticCollision: p.reset(new ProgramPerfectElasticCollision); break;
    case ProgramType::picToCode: p.reset(new ProgramPicToCode); break;
    case ProgramType::pixelator: p.reset(new ProgramPixelator); break;
    case ProgramType::pokeVolley: p.reset(new ProgramPokeVolley); break;
    case ProgramType::pylos: p.reset(new ProgramPylos); break;
    case ProgramType::qmakeWatcher: p.reset(new ProgramQmakeWatcher); break;
    case ProgramType::quadraticSolver: p.reset(new ProgramQuadraticSolver); break;
    case ProgramType::randomCode: p.reset(new ProgramRandomCode); break;
    case ProgramType::rasper: p.reset(new ProgramRasper); break;
    case ProgramType::refrigeratorPuzzleSolver: p.reset(new ProgramRefrigeratorPuzzleSolver); break;
    case ProgramType::regexTester: p.reset(new ProgramRegexTester); break;
    case ProgramType::reversi: p.reset(new ProgramReversi); break;
    case ProgramType::richelBilderbeekGallery: p.reset(new ProgramRichelBilderbeekGallery); break;
    case ProgramType::richelBilderbeekNlSitemapGenerator: p.reset(new ProgramRichelBilderbeekNlSitemapGenerator); break;
    case ProgramType::rubiksClock: p.reset(new ProgramRubiksClock); break;
    case ProgramType::searchAndDestroyChess: p.reset(new ProgramSearchAndDestroyChess); break;
    case ProgramType::secretMessage: p.reset(new ProgramSecretMessage); break;
    case ProgramType::simBrainiac: p.reset(new ProgramSimBrainiac); break;
    case ProgramType::simImmuneResponse: p.reset(new ProgramSimImmuneResponse); break;
    case ProgramType::simMysteryMachine: p.reset(new ProgramSimMysteryMachine); break;
    case ProgramType::simplifyNewick: p.reset(new ProgramSimplifyNewick); break;
    case ProgramType::simStagecraft: p.reset(new ProgramSimStagecraft); break;
    case ProgramType::soaSim: p.reset(new ProgramSoaSim); break;
    case ProgramType::solvePuzzleX: p.reset(new ProgramSolvePuzzleX); break;
    case ProgramType::spaceHarry: p.reset(new ProgramSpaceHarry); break;
    case ProgramType::stateObserver: p.reset(new ProgramStateObserver); break;
    case ProgramType::styleSheetSetter: p.reset(new ProgramStyleSheetSetter); break;
    case ProgramType::surfacePlotter: p.reset(new ProgramSurfacePlotter); break;
    case ProgramType::testAbout: p.reset(new ProgramTestAbout); break;
    case ProgramType::testBinaryNewickVector: p.reset(new ProgramTestBinaryNewickVector); break;
    case ProgramType::testBroadcastServer: p.reset(new ProgramTestBroadcastServer); break;
    case ProgramType::testChess: p.reset(new ProgramTestChess); break;
    case ProgramType::testDial: p.reset(new ProgramTestDial); break;
    case ProgramType::testEncranger: p.reset(new ProgramTestEncranger); break;
    case ProgramType::testEntrance: p.reset(new ProgramTestEntrance); break;
    case ProgramType::testExercise: p.reset(new ProgramTestExercise); break;
    case ProgramType::testFunctionParser: p.reset(new ProgramTestFunctionParser); break;
    case ProgramType::testGroupWidget: p.reset(new ProgramTestGroupWidget); break;
    case ProgramType::testLed: p.reset(new ProgramTestLed); break;
    case ProgramType::testMultiVector: p.reset(new ProgramTestMultiVector); break;
    case ProgramType::testNdsMake: p.reset(new ProgramTestNdsMake); break;
    case ProgramType::testNeuralNet: p.reset(new ProgramTestNeuralNet); break;
    case ProgramType::testPrimeExpert: p.reset(new ProgramTestPrimeExpert); break;
    case ProgramType::testPylos: p.reset(new ProgramTestPylos); break;
    case ProgramType::testQrcFile: p.reset(new ProgramTestQrcFile); break;
    case ProgramType::testQtArrowItems: p.reset(new ProgramTestQtArrowItems); break;
    case ProgramType::testQtCreatorProFile: p.reset(new ProgramTestQtCreatorProFile); break;
    case ProgramType::testQtKeyboardFriendlyGraphicsView: p.reset(new ProgramTestQtKeyboardFriendlyGraphicsView); break;
    case ProgramType::testQtModels: p.reset(new ProgramTestQtModels); break;
    case ProgramType::testQtRoundedEditRectItem: p.reset(new ProgramTestQtRoundedEditRectItem); break;
    case ProgramType::testQtRoundedRectItem: p.reset(new ProgramTestQtRoundedRectItem); break;
    case ProgramType::testQtRoundedTextRectItem: p.reset(new ProgramTestQtRoundedTextRectItem); break;
    case ProgramType::testQuestion: p.reset(new ProgramTestQuestion); break;
    case ProgramType::testSelectFile: p.reset(new ProgramTestSelectFile); break;
    case ProgramType::testServerPusher: p.reset(new ProgramTestServerPusher); break;
    case ProgramType::testShape: p.reset(new ProgramTestShape); break;
    case ProgramType::testShinyButton: p.reset(new ProgramTestShinyButton); break;
    case ProgramType::testStopwatch: p.reset(new ProgramTestStopwatch); break;
    case ProgramType::testTicTacToe: p.reset(new ProgramTestTicTacToe); break;
    case ProgramType::testTimedServerPusher: p.reset(new ProgramTestTimedServerPusher); break;
    case ProgramType::testToggleButton: p.reset(new ProgramTestToggleButton); break;
    case ProgramType::testTwoDigitNewick: p.reset(new ProgramTestTwoDigitNewick); break;
    case ProgramType::thorVeen: p.reset(new ProgramThorVeen); break;
    case ProgramType::thresholdFilterer: p.reset(new ProgramThresholdFilterer); break;
    case ProgramType::ticTacToe: p.reset(new ProgramTicTacToe); break;
    case ProgramType::ticTacToeLearner: p.reset(new ProgramTicTacToeLearner); break;
    case ProgramType::ticTacToeValuer: p.reset(new ProgramTicTacToeValuer); break;
    case ProgramType::timePoll: p.reset(new ProgramTimePoll); break;
    case ProgramType::twoDigitNewick: p.reset(new ProgramTwoDigitNewick); break;
    case ProgramType::ubuntuOneWatcher: p.reset(new ProgramUbuntuOneWatcher); break;
    case ProgramType::visualAbc: p.reset(new ProgramVisualAbc); break;
    case ProgramType::n_types:
      assert(!"Unimplemented RichelBilderbeek::ProgramType");
      throw std::logic_error("Unimplemented RichelBilderbeek::ProgramType");
  }
  assert(p);
  return p;
}

const std::vector<boost::shared_ptr<Program> > Program::GetAllPrograms()
{
  const std::vector<ProgramType> types = GetAllProgramTypes();
  std::vector<boost::shared_ptr<Program> > v;

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

const std::string Program::GetFilenameBase() const
{
  std::string s = this->GetTypeName();
  s[0] = std::toupper(s[0]);
  return s + GetName();
}

const std::string Program::GetFilenameConsole() const
{
  return GetFilenameBase() + "Console.png";
}

const std::string Program::GetFilenameDesktop() const
{
  return GetFilenameBase() + "Desktop.png";
}

const std::string Program::GetFilenameDesktopWindowsOnly() const
{
  return GetFilenameBase() + "DesktopWindowsOnly.png";
}

const std::string Program::GetFilenameWeb() const
{
  return GetFilenameBase() + "Web.png";
}

const std::string Program::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> Program::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2012-02-19: Version 1.0: initial version");
  return v;
}

std::ostream& operator<<(std::ostream& os, const Program * const p)
{
  const std::string name = p->GetName();

  os << name;

  if (name.size() < 10) os << '\t';

  os
     << '\t' << p->GetTypeName()
     << '\t' << ProgramStatusToStr(p->GetStatusConsole())
     << '\t' << ProgramStatusToStr(p->GetStatusDesktopWindowsOnly())
     << '\t' << ProgramStatusToStr(p->GetStatusDesktop())
     << '\t' << ProgramStatusToStr(p->GetStatusWebApplication());
   return os;
}

bool operator<(const Program& lhs, const Program& rhs)
{
  if (lhs.GetTypeName() < rhs.GetTypeName()) return true;
  if (lhs.GetTypeName() > rhs.GetTypeName()) return false;
  return lhs.GetName() < rhs.GetName();
}

} //namespace RichelBilderbeek

