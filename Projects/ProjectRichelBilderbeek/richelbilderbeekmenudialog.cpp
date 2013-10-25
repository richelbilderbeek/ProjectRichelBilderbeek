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
#include "richelbilderbeekmenudialog.h"

#include "approximator.h"
#include "alphabetafilter.h"
#include "alphabetagammafilter.h"
#include "alphafilter.h"
#include "asciiartermenudialog.h"
#include "beerwantermenudialog.h"
#include "binarynewickvector.h"
#include "codetohtmlmenudialog.h"
#include "connectthree.h"
#include "connectthreewidget.h"
#include "copy_if.h"
#include "counter.h"
#include "createqtprojectzipfilemenudialog.h"
#include "dial.h"
#include "dialwidget.h"
#include "encranger.h"
#include "exercise.h"
#include "fixedlagsmootherkalmanfilter.h"
#include "fuzzy_equal_to.h"
#include "fuzzy_equal_to.h"
#include "gaborfilter.h"
#include "gaborfilterwidget.h"
#include "hometrainermenudialog.h"
#include "htmlpage.h"
#include "ipaddress.h"
#include "kalmanfilter.h"
#include "laggedwhitenoisesystem.h"
#include "lazy_init.h"
#include "led.h"
#include "ledwidget.h"
#include "loopreader.h"
#include "manydigitnewick.h"
#include "matrix.h"
#include "multialphafilter.h"
#include "multiplechoicequestion.h"
#include "multiplechoicequestiondialog.h"
#include "multivector.h"
#include "musicchord.h"
#include "musicnote.h"
#include "tooltestapproximatormenudialog.h"
#include "tooltestmultiapproximatormenudialog.h"
#include "musicscale.h"
#include "multiapproximator.h"
#include "mysterymachine.h"
#include "mysterymachinewidget.h"
#include "newick.h"
#include "newickvector.h"
#include "openquestion.h"
#include "openquestiondialog.h"
#include "pylosmenudialog.h"
#include "qrcfile.h"
#include "qtcreatorprofile.h"
#include "question.h"
#include "questiondialog.h"
#include "rainbow.h"
#include "randomcode.h"
#include "regextestermenudialog.h"
#include "richelbilderbeekprogram.h"
#include "richelbilderbeekprogramstatus.h"
#include "rubiksclock.h"
#include "rubiksclockdial.h"
#include "rubiksclockdialwidget.h"
#include "rubiksclockmenudialog.h"
#include "rubiksclockwidget.h"
#include "shape.h"
#include "shapewidget.h"
#include "shinybutton.h"
#include "shinybuttonwidget.h"
#include "simmysterymachinemenudialog.h"
#include "sortedbinarynewickvector.h"
#include "stateobservermenudialog.h"
#include "steadystatekalmanfilter.h"
#include "steadystatekalmanfilterparameters.h"
#include "stopwatch.h"
#include "testdialmenudialog.h"
#include "toolencrangermenudialog.h"
#include "hometrainermenudialog.h"
#include "testexercisemenudialog.h"
#include "testfunctionparsermenudialog.h"
#include "tooltestledmenudialog.h"
#include "tooltestsimplelinearregressionmenudialog.h"
#include "testnewickvectordialog.h"
#include "testqrcfilemenudialog.h"
#include "testqtarrowitemsmenudialog.h"
#include "testqtcreatorprofilemenudialog.h"
#include "testquestionmenudialog.h"
#include "testshapemenudialog.h"
#include "testshinybuttonmenudialog.h"
#include "testtogglebuttonmenudialog.h"
#include "tictactoe.h"
#include "qmakewatchermenudialog.h"
#include "tictactoemenudialog.h"
#include "togglebutton.h"
#include "togglebuttonwidget.h"
#include "trace.h"
#include "twodigitnewick.h"

#pragma GCC diagnostic pop

ribi::RichelBilderbeek::ProjectRichelBilderbeekMenuDialog::ProjectRichelBilderbeekMenuDialog()
  : m_programs(ribi::RichelBilderbeek::Program::GetAllPrograms())
{
  #ifndef NDEBUG
  std::for_each(m_programs.begin(), m_programs.end(),
    [](const boost::shared_ptr<Program>& p)
    {
      assert(p);
    }
  );
  #endif
}

const std::vector<boost::shared_ptr<ribi::MenuDialog> > ribi::RichelBilderbeek::ProjectRichelBilderbeekMenuDialog::CreateMenus() const
{
  typedef boost::shared_ptr<ribi::MenuDialog> MenuPtr;
  std::vector<MenuPtr> v;
  { const MenuPtr p { new AsciiArterMenuDialog  }; v.push_back(p); }
  { const MenuPtr p { new CodeToHtmlMenuDialog  }; v.push_back(p); }
  { const MenuPtr p { new HometrainerMenuDialog }; v.push_back(p); }
  return v;
}

const std::vector<std::string> ribi::RichelBilderbeek::ProjectRichelBilderbeekMenuDialog::GetHelp() const noexcept
{
  return {
    "ProjectRichelBilderbeekConsole help menu",
    "",
    "ProjectRichelBilderbeekConsole is a console front-end for multiple",
    "console applications. ",
    "",
    "Uses: ",
    "  ProjectRichelBilderbeekConsole [option]",
    "  ProjectRichelBilderbeekConsole [program] [option]",
    "",
    "Allowed options for ProjectRichelBilderbeekConsole:",
    "-a, --about               display about message",
    "-h, --help                produce this help message",
    "-i, --history             display version history",
    "-l, --licence             display licence",
    "-p, --program             list all possible programs",
    "-s, --status              display class statuses",
    "-v, --version             display class versions",
    "",
    "Example uses:",
    "  ProjectRichelBilderbeekConsole --help",
    "  ProjectRichelBilderbeekConsole Hometrainer --help"
    };
}
int ribi::RichelBilderbeek::ProjectRichelBilderbeekMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());

  if (argc == 1)
  {
    const std::vector<std::string> v { GetHelp() };
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(std::cout,"\n"));
    return 1;
  }
  const std::string s { argv[1] };
  if (s == std::string("--status") || s == std::string("-s"))
  {
    const std::vector<boost::shared_ptr<ribi::RichelBilderbeek::Program> > v = GetPrograms();
    std::for_each(
      v.begin(),v.end(),
      [](const boost::shared_ptr<ribi::RichelBilderbeek::Program>& p)
      {
        std::cout << p.get() << '\n';
      }
    );
    return 0;
  }

  //Find menu dialog and execute it with one argument less
  assert(!"TODO");
  return 1;
}

const ribi::About ribi::RichelBilderbeek::ProjectRichelBilderbeekMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "Project Richel Bilderbeek",
    "Richel Bilderbeek's work",
    "the 12th of October 2013",
    "2010-2013",
    "http://www.richelbilderbeek.nl/ProjectRichelBilderbeek.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("TestTwoDigitNewick version: " + WtTestTwoDigitNewickDialog::GetVersion());
  a.AddLibrary("AlphaBetaFilter version: " + AlphaBetaFilter::GetVersion());
  a.AddLibrary("AlphaBetaGammaFilter version: " + AlphaBetaGammaFilter::GetVersion());
  a.AddLibrary("AlphaFilter version: " + AlphaFilter::GetVersion());
  a.AddLibrary("Approximator version: " + Approximator<double,double>::GetVersion());
  a.AddLibrary("AsciiArter version: " + AsciiArterMenuDialog().GetVersion());
  a.AddLibrary("BeerWanter version: " + BeerWanterMenuDialog::GetVersion());
  a.AddLibrary("Big Integer Library (by Matt McCutchen) version: 2010.04.30");
  a.AddLibrary("BinaryNewickVector version: " + BinaryNewickVector::GetVersion());
  a.AddLibrary("CodeToHtml version: " + CodeToHtmlMenuDialog().GetVersion());
  a.AddLibrary("ConnectThree version: " + ConnectThree::GetVersion());
  a.AddLibrary("ConnectThreeWidget version: " + ConnectThreeWidget::GetVersion());
  a.AddLibrary("Copy_if version: " + Copy_if_version::GetVersion());
  a.AddLibrary("Counter version: " + Counter::GetVersion());
  a.AddLibrary("CreateQtProjectZipFile version: " + CreateQtProjectZipFile::MenuDialog::GetVersion());
  a.AddLibrary("Dial version: " + Dial::GetVersion());
  a.AddLibrary("DialWidget version: " + DialWidget::GetVersion());
  a.AddLibrary("Encranger version: " + Encranger::GetVersion());
  a.AddLibrary("Exercise version: " + Exercise::GetVersion());
  a.AddLibrary("Fuzzy_equal_to version: " + fuzzy_equal_to::GetVersion());
  a.AddLibrary("GaborFilter version: " + GaborFilter::GetVersion());
  a.AddLibrary("GaborFilterWidget version: " + GaborFilterWidget::GetVersion());
  a.AddLibrary("Hometrainer version: " + HometrainerMenuDialog().GetVersion());
  a.AddLibrary("HtmlPage version: " + HtmlPage::GetVersion());
  a.AddLibrary("IpAddress version: " + IpAddress::GetVersion());
  a.AddLibrary("kalman::FixedLagSmootherKalmanFilter version: " + kalman::FixedLagSmootherKalmanFilter::GetVersion());
  a.AddLibrary("kalman::KalmanFilter version: " + kalman::KalmanFilter::GetVersion());
  a.AddLibrary("kalman::LaggedWhiteNoiseSystem version: " + kalman::LaggedWhiteNoiseSystem::GetVersion());
  a.AddLibrary("kalman::StandardKalmanFilter version: " + kalman::StandardKalmanFilter::GetVersion());
  a.AddLibrary("kalman::StandardKalmanFilterParameters version: " + kalman::StandardKalmanFilterParameters::GetVersion());
  a.AddLibrary("kalman::StandardWhiteNoiseSystem version: " + kalman::StandardWhiteNoiseSystem::GetVersion());
  a.AddLibrary("kalman::StandardWhiteNoiseSystemParameters version: " + kalman::StandardWhiteNoiseSystemParameters::GetVersion());
  a.AddLibrary("kalman::SteadyStateKalmanFilter version: " + kalman::SteadyStateKalmanFilter::GetVersion());
  a.AddLibrary("kalman::SteadyStateKalmanFilterParameters version: " + kalman::SteadyStateKalmanFilterParameters::GetVersion());
  a.AddLibrary("kalman::WhiteNoiseSystem version: " + kalman::WhiteNoiseSystem::GetVersion());
  a.AddLibrary("Lazy_init version: " + Lazy_initVersion::GetVersion());
  a.AddLibrary("Led version: " + Led::GetVersion());
  a.AddLibrary("LedWidget version: " + LedWidget::GetVersion());
  a.AddLibrary("LoopReader version: " + LoopReader<int>::GetVersion());
  a.AddLibrary("ManyDigitNewick version: " + ManyDigitNewick::GetVersion());
  a.AddLibrary("Matrix version: " + Matrix::GetVersion());
  a.AddLibrary("Matrix version: " + Matrix::GetVersion());
  a.AddLibrary("MultiAlphaFilter version: " + MultiAlphaFilter::GetVersion());
  a.AddLibrary("MultiApproximator version: " + MultiApproximator<double,double>::GetVersion());
  a.AddLibrary("MultipleChoiceQuestion version: " + MultipleChoiceQuestion::GetVersion());
  a.AddLibrary("MultipleChoiceQuestionDialog version: " + MultipleChoiceQuestionDialog::GetVersion());
  a.AddLibrary("MultipleVector version: " + MultiVector<int>::GetVersion());
  a.AddLibrary("Music::Chord version: " + Music::Chord::GetVersion());
  a.AddLibrary("Music::Note version: " + Music::Note::GetVersion());
  a.AddLibrary("Music::Scale version: " + Music::Scale::GetVersion());
  a.AddLibrary("MysteryMachine version: " + MysteryMachine::GetVersion());
  a.AddLibrary("MysteryMachineWidget version: " + MysteryMachineWidget::GetVersion());
  a.AddLibrary("Newick version: " + Newick::GetVersion());
  a.AddLibrary("NewickVector version: " + NewickVector::GetVersion());
  a.AddLibrary("OpenQuestion version: " + OpenQuestion::GetVersion());
  a.AddLibrary("OpenQuestionDialog version: " + OpenQuestionDialog::GetVersion());
  a.AddLibrary("Pylos version: " + PylosMenuDialog::GetVersion());
  a.AddLibrary("QmakeWatcher version: " + QmakeWatcherMenuDialog::GetVersion());
  a.AddLibrary("QrcFile version: " + QrcFile::GetVersion());
  a.AddLibrary("QtCreatorProFile version: " + QtCreatorProFile::GetVersion());
  a.AddLibrary("Question version: " + Question::GetVersion());
  a.AddLibrary("QuestionDialog version: " + QuestionDialog::GetVersion());
  a.AddLibrary("Rainbow version: " + Rainbow::GetVersion());
  a.AddLibrary("RandomCode version: " + RandomCode::GetVersion());
  a.AddLibrary("Rectangle version: " + Rect::GetVersion());
  a.AddLibrary("RegexTester version: " + RegexTesterMenuDialog::GetVersion());
  a.AddLibrary("RichelBilderbeekProgram version: " + RichelBilderbeek::Program::GetVersion());
  a.AddLibrary("RubiksClock (class) version: " + RubiksClock::GetVersion());
  a.AddLibrary("RubiksClock (game) version: " + RubiksClockMenuDialog::GetVersion());
  a.AddLibrary("RubiksClockDialversion: " + RubiksClockDial::GetVersion());
  a.AddLibrary("RubiksClockDialWidget version: " + RubiksClockDialWidget::GetVersion());
  a.AddLibrary("RubiksClockWidget version: " + RubiksClockWidget::GetVersion());
  a.AddLibrary("Shape version: " + Shape::GetVersion());
  a.AddLibrary("ShapeWidget version: " + ShapeWidget::GetVersion());
  a.AddLibrary("ShinyButton version: " + ShinyButton::GetVersion());
  a.AddLibrary("ShinyButtonWidget version: " + ShinyButtonWidget::GetVersion());
  a.AddLibrary("SimMysteryMachine version: " + SimMysteryMachineMenuDialog::GetVersion());
  a.AddLibrary("SortedBinaryNewickVector version: " + SortedBinaryNewickVector::GetVersion());
  a.AddLibrary("StateObserver version: " + StateObserverMenuDialog::GetVersion());
  a.AddLibrary("Stopwatch version: " + Stopwatch::GetVersion());
  a.AddLibrary("TestApproximator version: " + ToolTestApproximatorMenuDialog::GetVersion());
  a.AddLibrary("TestDial version: " + TestDialMenuDialog::GetVersion());
  a.AddLibrary("Encranger version: " + ToolEncrangerMenuDialog::GetVersion());
  a.AddLibrary("TestExercise version: " + TestExerciseMenuDialog::GetVersion());
  a.AddLibrary("TestFunctionParser version: " + TestFunctionParserMenuDialog::GetVersion());
  a.AddLibrary("TestLed version: " + TestLedMenuDialog::GetVersion());
  a.AddLibrary("TestNewickVector version: " + TestNewickVectorDialog::GetVersion());
  a.AddLibrary("TestProFile version: " + TestQtCreatorProFileMenuDialog::GetVersion());
  a.AddLibrary("TestQrcFile version: " + TestQrcFileMenuDialog::GetVersion());
  a.AddLibrary("TestQuestion version: " + TestQuestionMenuDialog::GetVersion());
  a.AddLibrary("TestMultiApproximator version: " + ToolTestMultiApproximatorMenuDialog::GetVersion());
  a.AddLibrary("TestShape version: " + TestShapeMenuDialog::GetVersion());
  a.AddLibrary("TestShinyButton version: " + TestShinyButtonMenuDialog::GetVersion());
  a.AddLibrary("TestSimpleLinearRegression version: " + ToolTestSimpleLinearRegressionMenuDialog::GetVersion());
  a.AddLibrary("TestToggleButton version: " + TestToggleButtonMenuDialog::GetVersion());
  a.AddLibrary("TicTacToe (game) version: " + TicTacToeMenuDialog::GetVersion());
  a.AddLibrary("TicTacToe version: " + TicTacToe::GetVersion());
  a.AddLibrary("ToggleButton version: " + ToggleButton::GetVersion());
  a.AddLibrary("ToggleButtonWidget version: " + ToggleButtonWidget::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  a.AddLibrary("TwoDigitNewick version: " + TwoDigitNewick::GetVersion());
  a.AddLibrary("Warp's FunctionParser version: 4.4.3");
  a.AddLibrary("Widget version: " + Widget::GetVersion());
  return a;
}

const std::string ribi::RichelBilderbeek::ProjectRichelBilderbeekMenuDialog::GetVersion() const noexcept
{
  return "1.11";
}

const std::vector<std::string> ribi::RichelBilderbeek::ProjectRichelBilderbeekMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2010-12-20: Version 0.1: web-application-only project called 'ProjectWtWebsite', initial setup with BeerWanter and Loose",
    "2010-12-21: Version 0.2: added System button",
    "2010-12-22: Version 0.3: added About button",
    "2010-12-22: Version 0.4: added What's New button. Got BeerWanter to work minimally",
    "2010-12-24: Version 0.5: added RandomCode",
    "2011-01-07: Version 0.6: major architecture adjustment, added TicTacToe, temporarily removed BeerWanter, Loose and System",
    "2011-01-09: Version 0.7: added title structure, added response of WtRichelBilderbeek's Close button, added ConnectThree beta",
    "2011-01-10: Version 0.8: ConnectThree to alpha",
    "2011-01-11: Version 0.9: ConnectThree to full version",
    "2011-03-06: Version 0.10: added TestTwoDigitNewick",
    "2011-03-09: Version 0.11: replaced TestTwoDigitNewick by TestNewick",
    "2011-03-22: Version 0.12: added Encranger",
    "2011-03-26: Version 0.13: replaced TestNewick by TestNewickVector",
    "2011-03-27: Version 0.14: added TestAsciiArter",
    "2011-04-13: Version 0.15: added TimePoll",
    "2011-04-16: Version 0.16: major architectural change: use of Wt::WMenu and WtAutoConfig",
    "2011-04-23: Version 0.17: new version of ConnectThree, added Bep to welcome page",
    "2011-04-24: Version 0.18: fixed bug in ConnectThree, improved RandomCode",
    "2011-04-25: Version 0.19: fixed bug in ConnectThree (again), removed Close buttons, fixed doublures in About information",
    "2011-05-30: Version 0.20: removed TimePoll, added GTST",
    "2011-06-11: Version 0.21: added TestTwoDigitNewick, TestDial, TestLed and TimePoll",
    "2011-06-22: Version 0.22: added TestGroupWidget",
    "2011-06-24: Version 0.23: added TestFunctionParser",
    "2011-06-26: Version 0.24: use of WtSafeTimer",
    "2011-06-30: Version 0.25: added TestQuestion, removed TimePoll",
    "2011-07-02: Version 0.26: added TestSelectFileDialog",
    "2011-07-16: Version 0.27: removed GTST and TimePoll, added TestShape",
    "2011-07-26: Version 0.28: added TimePoll",
    "2011-08-20: Version 0.29: added TestServerPusher and TestSTimederverPusher",
    "2011-08-31: Version 0.30: improved TestAsciiArter, TestDial, Encranger, TestFunctionParser and RandomCode, added GTST and TestToggleButton",
    "2011-09-08: Version 0.31: improved TestLed, TestGroupWidget, added RubiksClock",
    "2011-09-16: Version 0.32: added CodeToHtml, added SimMysteryMachine, improved TestQuestion",
    "2011-09-19: Version 0.33: added TestEntrance",
    "2011-09-20: Version 0.34: restyled the main menu",
    "2011-09-22: Version 0.35: added TestShinyButton, restyled the main menu",
    "2011-10-02: Version 0.36: added TestExercise, restyled the main menu",
    "2011-10-24: Version 0.37: added Hometrainer",
    "2011-10-30: Version 0.38: conformized to newer GCC's C++0x implementation, improved Hometrainer, improved WtRichelBilderbeek code",
    "2012-02-12: Version 1.00: renamed project to 'Project Richel Bilderbeek', first step to both a desktop and web application of this project",
    "2012-07-29: Version 1.01: added many programs",
    "2012-12-05: Version 1.02: added AsciiArter, CreateGlossary, MusicTheory, added About screen",
    "2012-12-23: Version 1.03: added Rubik's Clock",
    "2013-05-20: Version 1.04: added RegexTester, TestQuestion, TestQtArrowItems, TestQtModels",
    "2013-05-22: Version 1.05: can crosscompile console and desktop version to Windows",
    "2013-05-25: Version 1.06: scalable architecture, added placeholder dialogs in desktop version",
    "2013-05-26: Version 1.07: changed the main menu, added StateObserver",
    "2013-05-29: Version 1.08: added KalmanFilterer, added About button in desktop version",
    "2013-07-11: Version 1.09: transition phase to Qt5, still supports Qt4",
    "2013-09-19: Version 1.10: added K3OpEenRij, SimplifyNewick, TestApproximator, TestMultiApproximator, TestSimpleLinearRegression, compiles with -Weffc++, added noexcept specifications, use of .pri file",
    "2013-10-12: Version 1.11: added DotMatrix, Encranger, GrayCoder, MultiEncranger, PrimeExpert, QuadraticSolver, TestCanvas, TestMultipleChoiceQuestion, TestOpenQuestion"
  };
}
