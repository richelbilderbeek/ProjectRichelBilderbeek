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
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "richelbilderbeekmenudialog.h"

#include "about.h"
#include "alphabetafilter.h"
#include "alphabetagammafilter.h"
#include "alphafilter.h"
#include "aminoacidfightermenudialog.h"
#include "approximator.h"
#include "asciiartermenudialog.h"
#include "athleticlandmenudialog.h"
#include "beerwantermenudialog.h"
#include "binarynewickvector.h"
#include "functionplottermenudialog.h"
#include "boenkenmenudialog.h"
#include "codetohtmlmenudialog.h"
#include "connectthree.h"
#include "connectthreemenudialog.h"
#include "connectthreewidget.h"
#include "copy_if.h"
#include "counter.h"
#include "createglossarymenudialog.h"
#include "createqtprojectzipfilemenudialog.h"
#include "daswahreschlagerfestmenudialog.h"
#include "richelbilderbeekprogramtypes.h"
#include "dial.h"
#include "secretmessagemenudialog.h"
#include "pixelatormenudialog.h"
#include "stylesheetsettermenudialog.h"
#include "toolsurfaceplottermenudialog.h"
#include "imagerotatermenudialog.h"
#include "dialwidget.h"
#include "encranger.h"
#include "exercise.h"
#include "fixedlagsmootherkalmanfilter.h"
#include "fuzzy_equal_to.h"
#include "gaborfilter.h"
#include "gaborfilterwidget.h"
#include "hometrainermenudialog.h"
#include "htmlpage.h"
#include "ipaddress.h"
#include "k3opeenrijmenudialog.h"
#include "filteroperationermenudialog.h"
#include "kalmanfilter.h"
#include "kalmanfilterermenudialog.h"
#include "histogramequalizationermenudialog.h"
#include "knokfightermenudialog.h"
#include "laggedwhitenoisesystem.h"
#include "testconceptmapmenudialog.h"
#include "thresholdfilterermenudialog.h"
#include "tooltestapproximatormenudialog.h"
#include "lazy_init.h"
#include "led.h"
#include "ledwidget.h"
#include "predickadvocatormenudialog.h"
#include "pixelatormenudialog.h"
#include "loopreader.h"
#include "manydigitnewick.h"
#include "matrix.h"
#include "xenonzeromenudialog.h"
#include "mazecreatormenudialog.h"
#include "maziakmenudialog.h"
#include "metzndrieenmenudialog.h"
#include "multialphafilter.h"
#include "multiapproximator.h"
#include "multiplechoicequestion.h"
#include "multiplechoicequestiondialog.h"
#include "multivector.h"
#include "musicchord.h"
#include "musicnote.h"
#include "musicscale.h"
#include "musictheorymenudialog.h"
#include "mysterymachine.h"
#include "mysterymachinewidget.h"
#include "newick.h"
#include "newickvector.h"
#include "nsanabrosmenudialog.h"
#include "openquestion.h"
#include "openquestiondialog.h"
#include "paperrockscissorsmenudialog.h"
#include "perfectelasticcollisionmenudialog.h"
#include "pictocodemenudialog.h"
#include "pokevolleymenudialog.h"
#include "pongmenudialog.h"
#include "pylosmenudialog.h"
#include "qmakewatchermenudialog.h"
#include "qrcfile.h"
#include "qtcreatorprofile.h"
#include "quadraticsolvermenudialog.h"
#include "question.h"
#include "questiondialog.h"
#include "rainbow.h"
#include "randomcode.h"
#include "randomcodemenudialog.h"
#include "regextestermenudialog.h"
#include "reversimenudialog.h"
#include "richelbilderbeekprogram.h"
#include "richelbilderbeekprogramstatus.h"
#include "rubiksclock.h"
#include "rubiksclockdial.h"
#include "rubiksclockdialwidget.h"
#include "rubiksclockmenudialog.h"
#include "rubiksclockwidget.h"
#include "searchanddestroychessmenudialog.h"
#include "shape.h"
#include "shapewidget.h"
#include "shinybutton.h"
#include "shinybuttonwidget.h"
#include "simmysterymachinemenudialog.h"
#include "simpredatormenudialog.h"
#include "sitemapgeneratormenudialog.h"
#include "sortedbinarynewickvector.h"
#include "spaceharrymenudialog.h"
#include "stateobservermenudialog.h"
#include "steadystatekalmanfilter.h"
#include "pvdbmenudialog.h"
#include "steadystatekalmanfilterparameters.h"
#include "stopwatch.h"
#include "tankbattalionmenudialog.h"
#include "testdialmenudialog.h"
#include "testdialmenudialog.h"
#include "testexercisemenudialog.h"
#include "testfunctionparsermenudialog.h"
#include "testgroupwidgetmenudialog.h"
#include "testmultiplechoicequestionmenudialog.h"
#include "testnewickvectordialog.h"
#include "testopenquestionmenudialog.h"
#include "testpylosmenudialog.h"
#include "testqrcfilemenudialog.h"
#include "testqtarrowitemsmenudialog.h"
#include "testqtcreatorprofilemenudialog.h"
#include "testqtkeyboardfriendlygraphicsviewmenudialog.h"
#include "testqtroundededitrectitemmenudialog.h"
#include "testqtroundedrectitemmenudialog.h"
#include "testqtroundedtextrectitemmenudialog.h"
#include "testquestionmenudialog.h"
#include "testshapemenudialog.h"
#include "testshinybuttonmenudialog.h"
#include "testtogglebuttonmenudialog.h"
#include "tictactoe.h"
#include "tictactoemenudialog.h"
#include "togglebutton.h"
#include "togglebuttonwidget.h"

#include "tooldotmatrixmenudialog.h"
#include "toolencrangermenudialog.h"
#include "toolgaborfiltermenudialog.h"
#include "toolgraycodermenudialog.h"
#include "toolmultiencrangermenudialog.h"
#include "toolprimeexpertmenudialog.h"
#include "toolsimplifynewickmenudialog.h"
#include "tooltestapproximatormenudialog.h"
#include "tooltestcanvasmenudialog.h"
#include "tooltestledmenudialog.h"
#include "tooltestmultiapproximatormenudialog.h"
#include "tooltestqtmodelsmenudialog.h"
#include "tooltestsimplelinearregressionmenudialog.h"
#include "trace.h"
#include "tronmenudialog.h"
#include "twodigitnewick.h"
#pragma GCC diagnostic pop

ribi::ProjectRichelBilderbeekMenuDialog::ProjectRichelBilderbeekMenuDialog()
  : m_menus(CreateMenus())
{
  #ifndef NDEBUG
  Test();
  for (auto p: CreateMenus())
  {
    assert(p);
  }
  #endif
}

int ribi::ProjectRichelBilderbeekMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());

  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  const std::string s { argv[1] };
  if (s == std::string("--status") || s == std::string("-s"))
  {
    ShowStatus();
    return 0;
  }
  if (s == std::string("--program") || s == std::string("-p"))
  {
    for (const auto m: CreateMenus())
    {
      assert(m);
      std::cout << m->GetProgram()->GetName() << '\n';
    }
    return 0;
  }
  //Find menu dialog and execute it with one argument less
  for (const auto m: CreateMenus())
  {
    assert(m);
    if (s == m->GetProgram()->GetName() || s == m->GetAbout().GetFileTitle())
    {
      std::vector<std::string> sub_argv;
      std::copy(argv.begin() + 1,argv.end(),std::back_inserter(sub_argv));
      return m->Execute(sub_argv);
    }
  }
  std::cout << GetHelp() << '\n';
  return 1;
}

const ribi::About ribi::ProjectRichelBilderbeekMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "Project Richel Bilderbeek",
    "Richel Bilderbeek's work",
    "the 15th of November 2013",
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
  a.AddLibrary("BeerWanter version: " + BeerWanterMenuDialog().GetVersion());
  a.AddLibrary("Big Integer Library (by Matt McCutchen) version: 2010.04.30");
  a.AddLibrary("BinaryNewickVector version: " + BinaryNewickVector::GetVersion());
  a.AddLibrary("Brainweaver version: " + pvdb::MenuDialog().GetVersion());
  a.AddLibrary("CodeToHtml version: " + c2h::CodeToHtmlMenuDialog().GetVersion());
  a.AddLibrary("ConnectThree version: " + ConnectThree::GetVersion());
  a.AddLibrary("ConnectThreeWidget version: " + ConnectThreeWidget::GetVersion());
  a.AddLibrary("Copy_if version: " + Copy_if_version::GetVersion());
  a.AddLibrary("Counter version: " + Counter::GetVersion());
  a.AddLibrary("CreateQtProjectZipFile version: " + CreateQtProjectZipFile::MenuDialog().GetVersion());
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
  a.AddLibrary("Pylos version: " + PylosMenuDialog().GetVersion());
  a.AddLibrary("QmakeWatcher version: " + QmakeWatcherMenuDialog().GetVersion());
  a.AddLibrary("QrcFile version: " + QrcFile::GetVersion());
  a.AddLibrary("QtCreatorProFile version: " + QtCreatorProFile::GetVersion());
  a.AddLibrary("Question version: " + Question::GetVersion());
  a.AddLibrary("QuestionDialog version: " + QuestionDialog::GetVersion());
  a.AddLibrary("Rainbow version: " + Rainbow::GetVersion());
  a.AddLibrary("RandomCode version: " + RandomCode::GetVersion());
  a.AddLibrary("Rectangle version: " + Rect::GetVersion());
  a.AddLibrary("RegexTester version: " + RegexTesterMenuDialog().GetVersion());
  a.AddLibrary("RichelBilderbeekProgram version: " + Program::GetVersion());
  a.AddLibrary("RubiksClock (class) version: " + RubiksClock::GetVersion());
  a.AddLibrary("RubiksClock (game) version: " + RubiksClockMenuDialog().GetVersion());
  a.AddLibrary("RubiksClockDialversion: " + RubiksClockDial::GetVersion());
  a.AddLibrary("RubiksClockDialWidget version: " + RubiksClockDialWidget::GetVersion());
  a.AddLibrary("RubiksClockWidget version: " + RubiksClockWidget::GetVersion());
  a.AddLibrary("Shape version: " + Shape::GetVersion());
  a.AddLibrary("ShapeWidget version: " + ShapeWidget::GetVersion());
  a.AddLibrary("ShinyButton version: " + ShinyButton::GetVersion());
  a.AddLibrary("ShinyButtonWidget version: " + ShinyButtonWidget::GetVersion());
  a.AddLibrary("SimMysteryMachine version: " + SimMysteryMachineMenuDialog().GetVersion());
  a.AddLibrary("SortedBinaryNewickVector version: " + SortedBinaryNewickVector::GetVersion());
  a.AddLibrary("StateObserver version: " + StateObserverMenuDialog().GetVersion());
  a.AddLibrary("Stopwatch version: " + Stopwatch::GetVersion());
  a.AddLibrary("TestApproximator version: " + ToolTestApproximatorMenuDialog().GetVersion());
  a.AddLibrary("TestDial version: " + TestDialMenuDialog().GetVersion());
  a.AddLibrary("Encranger version: " + ToolEncrangerMenuDialog().GetVersion());
  a.AddLibrary("TestExercise version: " + TestExerciseMenuDialog().GetVersion());
  a.AddLibrary("TestFunctionParser version: " + TestFunctionParserMenuDialog().GetVersion());
  a.AddLibrary("TestLed version: " + TestLedMenuDialog().GetVersion());
  a.AddLibrary("TestNewickVector version: " + TestNewickVectorDialog::GetVersion());
  a.AddLibrary("TestProFile version: " + TestQtCreatorProFileMenuDialog().GetVersion());
  a.AddLibrary("TestQrcFile version: " + TestQrcFileMenuDialog().GetVersion());
  a.AddLibrary("TestQuestion version: " + TestQuestionMenuDialog().GetVersion());
  a.AddLibrary("TestMultiApproximator version: " + ToolTestMultiApproximatorMenuDialog().GetVersion());
  a.AddLibrary("TestShape version: " + TestShapeMenuDialog().GetVersion());
  a.AddLibrary("TestShinyButton version: " + TestShinyButtonMenuDialog().GetVersion());
  a.AddLibrary("TestSimpleLinearRegression version: " + ToolTestSimpleLinearRegressionMenuDialog().GetVersion());
  a.AddLibrary("TestToggleButton version: " + TestToggleButtonMenuDialog().GetVersion());
  a.AddLibrary("TicTacToe (game) version: " + TicTacToeMenuDialog().GetVersion());
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

const std::vector<boost::shared_ptr<ribi::MenuDialog>> ribi::ProjectRichelBilderbeekMenuDialog::CreateMenus() noexcept
{
  std::vector<boost::shared_ptr<ribi::MenuDialog>> v;
  for (const ProgramType t: ProgramTypes::GetAll())
  {
    boost::shared_ptr<ribi::MenuDialog> p;
    switch (t)
    {
      case ProgramType::aminoAcidFighter: p.reset(new AminoAcidFighterMenuDialog); break;
      case ProgramType::asciiArter: p.reset(new AsciiArterMenuDialog); break;
      case ProgramType::asciiArterVcl: break;
      case ProgramType::athleticLand: p.reset(new AthleticLandMenuDialog); break;
      case ProgramType::athleticLandVcl: break;
      case ProgramType::barbaImage: break;
      case ProgramType::beerWanter: p.reset(new BeerWanterMenuDialog); break;
      case ProgramType::beerWanterVcl: break;
      case ProgramType::bochum: break;
      case ProgramType::boenken: p.reset(new Boenken::MenuDialog); break;
      case ProgramType::boenkenVcl: break;
      case ProgramType::brainweaver: p.reset(new ribi::pvdb::MenuDialog); break;
      case ProgramType::bristol: break;
      case ProgramType::chrisWiley: break;
      case ProgramType::codeToHtml: p.reset(new c2h::CodeToHtmlMenuDialog); break;
      case ProgramType::connectThree: p.reset(new ConnectThreeMenuDialog); break;
      case ProgramType::corridor: break;
      case ProgramType::createGlossary: p.reset(new CreateGlossaryMenuDialog); break;
      case ProgramType::createQtProjectZipFile: p.reset(new CreateQtProjectZipFile::MenuDialog); break;
      case ProgramType::crossPoll: break;
      case ProgramType::dasWahreSchlagerfest: p.reset(new DasWahreSchlagerfestMenuDialog); break;
      case ProgramType::dasWahreSchlagerfestVcl: break;
      case ProgramType::dotMatrix: p.reset(new ToolDotMatrixMenuDialog); break;
      case ProgramType::dotMatrixVcl: break;
      case ProgramType::encranger: p.reset(new ToolEncrangerMenuDialog); break;
      case ProgramType::everythingToPiecesShooter: break;
      case ProgramType::fakeEvy: break;
      case ProgramType::filterOperationer: p.reset(new FilterOperationerMenuDialog); break;
      case ProgramType::filterOperationerVcl: break;
      case ProgramType::fryskLeareLieder: break;
      case ProgramType::functionPlotter: p.reset(new FunctionPlotterMenuDialog); break;
      case ProgramType::functionPlotterVcl: break;
      case ProgramType::gaborFilter: p.reset(new ToolGaborFilterMenuDialog); break;
      case ProgramType::gaborFilterVcl: break;
      case ProgramType::grayCoder: p.reset(new GrayCoderMenuDialog); break;
      case ProgramType::grayCoderVcl: break;
      case ProgramType::gtst: break;
      case ProgramType::histogramEqualizationer: p.reset(new HistogramEqualizationerMenuDialog); break;
      case ProgramType::histogramEqualizationerVcl: break;
      case ProgramType::hometrainer: p.reset(new HometrainerMenuDialog); break;
      case ProgramType::hometrainerVcl: break;
      case ProgramType::imageRotater: p.reset(new ImageRotaterMenuDialog); break;
      case ProgramType::imageRotaterClx: break;
      case ProgramType::imageRotaterVcl: break;
      case ProgramType::k3OpEenRij: p.reset(new K3OpEenRijMenuDialog); break;
      case ProgramType::k3OpEenRijVcl: break;
      case ProgramType::kalmanFilterer: p.reset(new kalman::KalmanFiltererMenuDialog); break;
      case ProgramType::keySender: break;
      case ProgramType::knokfighter: p.reset(new KnokfighterMenuDialog); break;
      case ProgramType::knokfighterVcl: break;
      case ProgramType::kTouchLectureCreator: break;
      case ProgramType::lambdaBot: break;
      case ProgramType::learyCircumplex: break;
      case ProgramType::logisticGrowthSimulator : break;
      case ProgramType::loose: break;
      case ProgramType::martianCafeTuinemaTycoon: break;
      case ProgramType::mazeCreator: p.reset(new MazeCreatorMenuDialog); break;
      case ProgramType::mazeCreatorVcl: break;
      case ProgramType::maziak: p.reset(new MaziakMenuDialog); break;
      case ProgramType::maziakVcl: break;
      case ProgramType::metZnDrieen: p.reset(new MetZnDrieenMenuDialog); break;
      case ProgramType::metZnDrieenVcl: break;
      case ProgramType::midiLessonCreator : break;
      case ProgramType::morpher : break;
      case ProgramType::multiEncranger: p.reset(new ToolMultiEncrangerMenuDialog); break;
      case ProgramType::multiEncrangerVcl: break;
      case ProgramType::muscaDomestica: break;
      case ProgramType::musicTheory: p.reset(new MusicTheoryMenuDialog); break;
      case ProgramType::ndsmake: break;
      case ProgramType::ndsPaint: break;
      case ProgramType::paperRockScissors: p.reset(new PaperRockScissorsMenuDialog); break;
      case ProgramType::pause: break;
      case ProgramType::perfectElasticCollision: p.reset(new PerfectElasticCollisionMenuDialog); break;
      case ProgramType::picToCode: p.reset(new PicToCodeMenuDialog); break;
      case ProgramType::pixelator: p.reset(new PixelatorMenuDialog); break;
      case ProgramType::pixelatorVcl: break;
      case ProgramType::pokeVolley: p.reset(new PokeVolleyMenuDialog); break;
      case ProgramType::pong: p.reset(new PongMenuDialog); break;
      case ProgramType::preDickAdvocaTor: p.reset(new PreDickAdvocaTorMenuDialog); break;
      case ProgramType::primeExpert: p.reset(new PrimeExpertMenuDialog); break;
      case ProgramType::projectRichelBilderbeek: p.reset(new ProjectRichelBilderbeekMenuDialog); break;
      case ProgramType::pylos: p.reset(new PylosMenuDialog); break;
      case ProgramType::qmakeWatcher: break;
      case ProgramType::quadraticSolver: p.reset(new QuadraticSolverMenuDialog); break;
      case ProgramType::rampal: break;
      case ProgramType::randomCode: p.reset(new RandomCodeMenuDialog); break;
      case ProgramType::randomCodeVcl: break;
      case ProgramType::rasper: break;
      case ProgramType::refrigeratorPuzzleSolver: break;
      case ProgramType::regexTester: p.reset(new RegexTesterMenuDialog); break;
      case ProgramType::reversi: p.reset(new ReversiMenuDialog); break;
      case ProgramType::richelBilderbeekGallery: break;
      case ProgramType::richelbilderbeekNlSitemapGenerator: break;
      case ProgramType::rubiksClock: p.reset(new RubiksClockMenuDialog); break;
      case ProgramType::rubiksClockVcl: break;
      case ProgramType::searchAndDestroyChess: p.reset(new sadc::MenuDialog); break;
      case ProgramType::searchAndDestroyChessVcl: break;
      case ProgramType::secretMessage: p.reset(new ribi::SecretMessage::MenuDialog); break;
      case ProgramType::secretMessageVcl: break;
      case ProgramType::simBrainiac: break;
      case ProgramType::simImmuneResponse: break;
      case ProgramType::simMysteryMachine: p.reset(new SimMysteryMachineMenuDialog); break;
      case ProgramType::simplifyNewick: p.reset(new ToolSimplifyNewickMenuDialog); break;
      case ProgramType::simPredator: p.reset(new SimPredatorMenuDialog); break;
      case ProgramType::simStagecraft: break;
      case ProgramType::soaSim: break;
      case ProgramType::solvePuzzleX: break;
      case ProgramType::spaceHarry: p.reset(new SpaceHarryMenuDialog); break;
      case ProgramType::spaceHarryVcl: break;
      case ProgramType::staircaseCardCreator: break;
      case ProgramType::stateObserver: p.reset(new StateObserverMenuDialog); break;
      case ProgramType::styleSheetSetter: p.reset(new StyleSheetSetterMenuDialog); break;
      case ProgramType::superNsanaBros: p.reset(new NsanaBrosMenuDialog); break;
      case ProgramType::surfacePlotter: p.reset(new ToolSurfacePlotterMenuDialog); break;
      case ProgramType::surfacePlotterVcl: break;
      case ProgramType::tankBattalion: p.reset(new TankBattalionMenuDialog); break;
      case ProgramType::testAbout: break;
      case ProgramType::testApproximator: p.reset(new ToolTestApproximatorMenuDialog); break;
      case ProgramType::testBinaryNewickVector: break;
      case ProgramType::testBouncingBallsWidget: break;
      case ProgramType::testBouncingRectsWidget: break;
      case ProgramType::testBroadcastServer: break;
      case ProgramType::testCanvas: p.reset(new ToolTestCanvasMenuDialog); break;
      case ProgramType::testChess: break;
      case ProgramType::testConceptMap: p.reset(new TestConceptMapMenuDialog); break;
      case ProgramType::testDial: p.reset(new TestDialMenuDialog); break;
      case ProgramType::testEntrance: break;
      case ProgramType::testExercise: p.reset(new TestExerciseMenuDialog); break;
      case ProgramType::testFunctionParser: p.reset(new TestFunctionParserMenuDialog); break;
      case ProgramType::testGnuplotInterface: break;
      case ProgramType::testGraphicsProxyWidget: break;
      case ProgramType::testGravityWidget: break;
      case ProgramType::testGroupWidget: p.reset(new TestGroupWidgetMenuDialog); break;
      case ProgramType::testHugeVector: break;
      case ProgramType::testLazy_init: break;
      case ProgramType::testLed: p.reset(new TestLedMenuDialog); break;
      case ProgramType::testManyDigitNewick: break;
      case ProgramType::testMultiApproximator: p.reset(new ToolTestMultiApproximatorMenuDialog); break;
      case ProgramType::testMultipleChoiceQuestion: p.reset(new TestMultipleChoiceQuestionMenuDialog); break;
      case ProgramType::testMultiVector: break;
      case ProgramType::testNdsmake: break;
      case ProgramType::testNeuralNet: break;
      case ProgramType::testNewick: break;
      case ProgramType::testNewickVector: break;
      case ProgramType::testOpenQuestion: p.reset(new TestOpenQuestionMenuDialog); break;
      case ProgramType::testPylos: p.reset(new TestPylosMenuDialog); break;
      case ProgramType::testQrcFile: p.reset(new TestQrcFileMenuDialog); break;
      case ProgramType::testQtArrowItems : p.reset(new TestQtArrowItemsMenuDialog); break;
      case ProgramType::testQtCreatorProFile: p.reset(new TestQtCreatorProFileMenuDialog); break;
      case ProgramType::testQtHideAndShowDialog: break;
      case ProgramType::testQtKeyboardFriendlyGraphicsView: p.reset(new TestKeyboardFriendlyGraphicsViewMenuDialog); break;
      case ProgramType::testQtModels: p.reset(new ToolTestQtModelsMenuDialog); break;
      case ProgramType::testQtOcrWidget: break;
      case ProgramType::testQtRoundedEditRectItem: p.reset(new TestQtRoundedEditRectItemMenuDialog); break;
      case ProgramType::testQtRoundedRectItem: p.reset(new TestQtRoundedRectItemMenuDialog); break;
      case ProgramType::testQtRoundedTextRectItem: p.reset(new TestQtRoundedTextRectItemMenuDialog); break;
      case ProgramType::testQuestion: p.reset(new TestQuestionMenuDialog); break;
      case ProgramType::testReversi: break;
      case ProgramType::testSelectFileDialog: break;
      case ProgramType::testServerPusher: break;
      case ProgramType::testShape: p.reset(new TestShapeMenuDialog); break;
      case ProgramType::testShinyButton: p.reset(new TestShinyButtonMenuDialog); break;
      case ProgramType::testSimpleLinearRegression: p.reset(new ToolTestSimpleLinearRegressionMenuDialog); break;
      case ProgramType::testStopwatch: break;
      case ProgramType::testTextPositionWidget: break;
      case ProgramType::testTicTacToe: break;
      case ProgramType::testTimedServerPusher: break;
      case ProgramType::testToggleButton: break;
      case ProgramType::testTwoDigitNewick: break;
      case ProgramType::thorVeen: break;
      case ProgramType::thresholdFilterer: p.reset(new ThresholdFiltererMenuDialog); break;
      case ProgramType::thresholdFiltererVcl: break;
      case ProgramType::ticTacToe: p.reset(new TicTacToeMenuDialog); break;
      case ProgramType::ticTacToeLearner: break;
      case ProgramType::ticTacToeValuer: break;
      case ProgramType::timePoll: break;
      case ProgramType::tronCollection: p.reset(new TronMenuDialog); break;
      case ProgramType::tronCollectionVcl: break;
      case ProgramType::ubuntuOneWatcher: break;
      case ProgramType::vanDenBogaart: break;
      case ProgramType::virtualBastard: break;
      case ProgramType::visualAbc: break;
      case ProgramType::xeNonZero: p.reset(new XeNonZeroMenuDialog); break;
      case ProgramType::zork: break;
      case ProgramType::n_types:
        assert(!"Must not use n_types");
        throw std::logic_error("ribi::ProjectRichelBilderbeekMenuDialog::CreateMenus");
    }
    assert(p);
    v.push_back(p);
  }
  assert(!v.empty());
  assert(static_cast<int>(v.size()) == static_cast<int>(ProgramType::n_types)
    && "All types must be present");
  return v;
}


const ribi::Help ribi::ProjectRichelBilderbeekMenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    GetAbout().GetFileTitle() + std::string("Console"),
    GetAbout().GetFileDescription(),
    {
      Help::Option('p',"program","lists all possible programs"),
      Help::Option('s',"status", "lists all programs' statuses")
    },
    {
      std::string("ProjectRichelBilderbeekConsole --help"),
      std::string("ProjectRichelBilderbeekConsole Hometrainer --help")
    }
  );
}




const boost::shared_ptr<const ribi::Program> ribi::ProjectRichelBilderbeekMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p(new ProgramProjectRichelBilderbeek);
  assert(p);
  return p;
}

const std::string ribi::ProjectRichelBilderbeekMenuDialog::GetVersion() const noexcept
{
  return "1.13";
}

const std::vector<std::string> ribi::ProjectRichelBilderbeekMenuDialog::GetVersionHistory() const noexcept
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
    "2013-10-12: Version 1.11: added DotMatrix, Encranger, GrayCoder, MultiEncranger, PrimeExpert, QuadraticSolver, TestCanvas, TestMultipleChoiceQuestion, TestOpenQuestion",
    "2013-11-15: Version 1.12: improved console application interface, use of .pri files, added Brainweaver",
    "2013-11-29: Version 1.13: added HistogramEqualizationer, ImageOperationer, ImageRotater, StyleSheetSetter, ThresholdFilterer"
  };
}

void ribi::ProjectRichelBilderbeekMenuDialog::ShowStatus() const noexcept
{
  typedef boost::shared_ptr<const ribi::Program> ProgramType;

  std::vector<ProgramType> v;
  for (auto p: CreateMenus())
  {
    assert(p);
    assert(p->GetProgram());
    v.push_back(p->GetProgram());
  }
  assert(v.size() == CreateMenus().size());

  //Find out the padding
  const int max_length {
    static_cast<int>(
      (*std::max_element(v.begin(),v.end(),
        [](const ProgramType& lhs,const ProgramType& rhs)
        {
          return lhs->GetName().size() < rhs->GetName().size();
        }
      ))->GetName().size()
    )
  };


  for (const ProgramType& p: v)
  {
    const std::string name_no_padding = p->GetName();
    const int cur_length = static_cast<int>(name_no_padding.size());
    const int n_spaces { max_length - cur_length };
    assert(n_spaces >= 0);
    const std::string name {
      cur_length == max_length
      ? name_no_padding
      : name_no_padding + std::string(n_spaces,' ')
    };
    std::cout
       << name
       << '\t' << p->GetTypeName()
       << '\t' << ProgramStatusToStr(p->GetStatusConsole())
       << '\t' << ProgramStatusToStr(p->GetStatusDesktopWindowsOnly())
       << '\t' << ProgramStatusToStr(p->GetStatusDesktop())
       << '\t' << ProgramStatusToStr(p->GetStatusWebApplication())
       << '\n';
  }
}

#ifndef NDEBUG
void ribi::ProjectRichelBilderbeekMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::ProjectRichelBilderbeekMenuDialog::Test()");
  //Create all menus
  for (const auto m: CreateMenus())
  {
    assert(!m->GetVersion().empty());
    assert(!m->GetVersionHistory().empty());
    assert(m->GetProgram());
  }

  TRACE("Finished ribi::ProjectRichelBilderbeekMenuDialog::Test()");
}
#endif
