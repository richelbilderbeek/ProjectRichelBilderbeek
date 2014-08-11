//---------------------------------------------------------------------------
/*
Project Richel Bilderbeek, Richel Bilderbeek's work
Copyright (C) 2010-2014 Richel Bilderbeek

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
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "richelbilderbeekmenudialog.h"

#include "aafmenudialog.h"
#include "about.h"
#include "alphabetafilter.h"
#include "alphabetagammafilter.h"
#include "alphafilter.h"
#include "approximator.h"
#include "asciiartermenudialog.h"
#include "athleticlandmenudialog.h"
#include "beerwantermenudialog.h"
#include "binarynewickvector.h"
#include "boenkenmenudialog.h"
#include "caesarciphermenudialog.h"
#include "canvas.h"
#ifdef INCLUDE_CHESS_20140617
#include "chessbitboard.h"
#include "chessboard.h"
#include "chessboardwidget.h"
#include "chessgame.h"
#include "chesswidget.h"
#endif // INCLUDE_CHESS_20140617
#include "codebreakermenudialog.h"
#include "codetohtmlmenudialog.h"
#ifdef INCLUDE_CONCEPTMAP_20140811
#include "conceptmap.h"
#include "conceptmapwidget.h"
#endif // INCLUDE_CONCEPTMAP_20140811
#include "connectthree.h"
#include "connectthreemenudialog.h"
#include "connectthreewidget.h"
#include "container.h"
#include "copy_if.h"
#include "counter.h"
#include "createglossarymenudialog.h"
#include "createqtprojectzipfilemenudialog.h"
#include "daswahreschlagerfestmenudialog.h"
#include "dial.h"
#include "dialwidget.h"
#include "dotmatrixchar.h"
#include "dotmatrixmenudialog.h"
#include "dotmatrixstring.h"
#include "dotmatrixtext.h"
#include "drawcanvas.h"
#include "encranger.h"
#include "encrangermenudialog.h"
#include "exercise.h"
#include "fileio.h"
#include "filteroperationermenudialog.h"
#include "fixedlagsmootherkalmanfilter.h"
#include "functionplottermenudialog.h"
#include "fuzzy_equal_to.h"
#include "gaborfilter.h"
#include "gaborfiltermenudialog.h"
#include "gaborfilterwidget.h"
#include "geometry.h"
#include "graycodermenudialog.h"
#include "histogramequalizationermenudialog.h"
#include "hometrainermenudialog.h"
#include "htmlpage.h"
#include "imagecanvas.h"
#include "imagerotatermenudialog.h"
#include "ipaddress.h"
#include "k3opeenrijmenudialog.h"
#include "kalmanfilter.h"
#include "kalmanfilterermenudialog.h"
#include "knokfightermenudialog.h"
#include "laggedwhitenoisesystem.h"
#include "lazy_init.h"
#include "led.h"
#include "ledwidget.h"
#include "loopreader.h"
#include "manydigitnewick.h"
#include "matrix.h"
#include "mazecreatormenudialog.h"
#include "maziakmenudialog.h"
#include "metzndrieenmenudialog.h"
#include "multialphafilter.h"
#include "multiapproximator.h"
#include "multiencrangermenudialog.h"
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
#include "openfoammesh.h"
#include "openquestion.h"
#include "openquestiondialog.h"
#include "paperrockscissorsmenudialog.h"
#include "perfectelasticcollisionmenudialog.h"
#include "pictocodemenudialog.h"
#include "pixelatormenudialog.h"
#include "pixelatormenudialog.h"
#include "plane.h"
//#include "pokevolleymenudialog.h"
#include "polyfile.h"
#include "polyfilefrompolygons.h"
#include "pongmenudialog.h"
#include "predickadvocatormenudialog.h"
#include "primeexpertmenudialog.h"
#ifdef INCLUDE_BRAINWEAVER_20140617
#include "pvdbmenudialog.h"
#endif // INCLUDE_BRAINWEAVER_20140617
#include "pylosmenudialog.h"
#include "qmakewatchermenudialog.h"
#include "qmakewatchermenudialog.h"
#include "qrcfile.h"
#include "qtcreatorprofile.h"
#include "qtstdvectorfunctionmodel.h"
#include "qtstdvectorstringmodel.h"
#include "qtublasmatrixdoublemodel.h"
#include "qtublasvectordoublemodel.h"
#include "qtublasvectorintmodel.h"
#include "quadraticsolvermenudialog.h"
#include "question.h"
#include "questiondialog.h"
#include "rainbow.h"
#include "randomcode.h"
#include "randomcodemenudialog.h"
#include "regextestermenudialog.h"
#include "reversiboard.h"
#include "reversimenudialog.h"
#include "reversiwidget.h"
#include "richelbilderbeekgallerymenudialog.h"
#include "richelbilderbeekplaceholdermenudialog.h"
#include "richelbilderbeekprogram.h"
#include "richelbilderbeekprogramstatus.h"
#include "richelbilderbeekprogramtypes.h"
#include "rubiksclock.h"
#include "rubiksclockdial.h"
#include "rubiksclockdialwidget.h"
#include "rubiksclockmenudialog.h"
#include "rubiksclockwidget.h"
#ifdef INCLUDE_SADD_20140617
#include "searchanddestroychessmenudialog.h"
#endif // INCLUDE_SADD_20140617
#include "secretmessagemenudialog.h"
#include "shape.h"
#include "shapewidget.h"
#include "shinybutton.h"
#include "shinybuttonwidget.h"
#include "simmysterymachinemenudialog.h"
#include "simplelinearregression.h"
#include "simplifynewickmenudialog.h"
#include "simpredatormenudialog.h"
#include "sitemapgeneratormenudialog.h"
#include "sitemapgeneratormenudialog.h"
#include "sortedbinarynewickvector.h"
#include "spaceharrymenudialog.h"
#include "staircasecardcreatormenudialog.h"
#include "stateobservermenudialog.h"
#include "steadystatekalmanfilter.h"
#include "steadystatekalmanfilterparameters.h"
#include "stopwatch.h"
#include "stylesheetsettermenudialog.h"
#include "surfaceplottermenudialog.h"
#ifdef INCLUDE_TANKBATTALION_20140617
#include "tankbattalionmenudialog.h"
#endif // INCLUDE_TANKBATTALION_20140617
#include "testaboutmenudialog.h"
#include "testapproximatormenudialog.h"
#include "testapproximatormenudialog.h"
#include "testtimer.h"
#include "testbinarynewickvectormenudialog.h"
#ifdef INCLUDE_TESTCHESS_20140617
#include "testchessmenudialog.h"
#endif // INCLUDE_TESTCHESS_20140617
#ifdef INCLUDE_CONCEPTMAP_20140811
#include "testconceptmapmenudialog.h"
#endif // INCLUDE_CONCEPTMAP_20140811
#include "testdialmenudialog.h"
#include "testdrawcanvasmenudialog.h"
#include "testentrancemenudialog.h"
#include "testexercisemenudialog.h"
#include "testfunctionparsermenudialog.h"
#include "testgroupwidgetmenudialog.h"
#include "testimagecanvasmenudialog.h"
#include "testledmenudialog.h"
#include "testmultiapproximatormenudialog.h"
#include "testmulticanvasmenudialog.h"
//#include "testmultiplechoicequestionmenudialog.h"
#include "testnewickvectordialog.h"
#include "testopenquestionmenudialog.h"
#include "testplanemenudialog.h"
#include "testpolyfilefrompolygonsmenudialog.h"
#include "testpolyfilemenudialog.h"
#include "testpylosmenudialog.h"
#include "testqrcfilemenudialog.h"
#include "testqtarrowitemsmenudialog.h"
#include "testqtcreatorprofilemenudialog.h"
#include "testqtkeyboardfriendlygraphicsviewmenudialog.h"
#include "testqtmodelsmenudialog.h"
#include "testqtroundededitrectitemmenudialog.h"
#include "testqtroundedrectitemmenudialog.h"
//#include "testqtroundedtextrectitemmenudialog.h" //OBSOLETE
//#include "testquestionmenudialog.h"
#include "testshapemenudialog.h"
#include "testshinybuttonmenudialog.h"
#include "testsimplelinearregressionmenudialog.h"
#include "testtextcanvasmenudialog.h"
//#include "testtictactoemenudialog.h"
#include "testtogglebuttonmenudialog.h"
#include "testtogglebuttonmenudialog.h"
#include "testtrianglemenudialog.h"
#include "testtwodigitnewickmenudialog.h"
#include "textcanvas.h"
#include "thresholdfilterermenudialog.h"
#include "tictactoeboard.h"
#include "tictactoemenudialog.h"
#include "togglebutton.h"
#include "togglebuttonwidget.h"
#include "trace.h"
#include "trianglefile.h"
#include "trianglemeshcreatormenudialog.h"
#include "tronmenudialog.h"
#include "twodigitnewick.h"
#include "valentinecarddecryptermenudialog.h"
#include "vigenereciphermenudialog.h"
#include "visualabcmenudialog.h"
#include "wkttosvgmenudialog.h"
#include "xenonzeromenudialog.h"
#include "xml.h"

#pragma GCC diagnostic pop

ribi::ProjectRichelBilderbeekMenuDialog::ProjectRichelBilderbeekMenuDialog()
  : m_menus(CreateMenus())
{
  #ifndef NDEBUG
  Test();
  for (const auto& p: CreateMenus())
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
  if (s == "--status" || s == "-s")
  {
    ShowStatus();
    return 0;
  }
  if (s == "--program" || s == "-p")
  {
    for (const auto& m: CreateMenus())
    {
      assert(m);
      std::cout << m->GetProgram()->GetName() << '\n';
    }
    return 0;
  }
  //Find menu dialog and execute it with one argument less
  for (const auto& m: CreateMenus())
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

ribi::About ribi::ProjectRichelBilderbeekMenuDialog::GetAboutStatic() noexcept
{
  About a(
    "Richel Bilderbeek",
    "Project Richel Bilderbeek",
    "Richel Bilderbeek's work",
    "the 8th of August 2014",
    "2010-2014",
    "http://www.richelbilderbeek.nl/ProjectRichelBilderbeek.htm",
    GetVersionStatic(),
    GetVersionHistoryStatic());
  //a.AddLibrary("TestTwoDigitNewick version: " + WtTestTwoDigitNewickDialog::GetVersion());
  a.AddLibrary("AlphaBetaFilter version: " + AlphaBetaFilter::GetVersion());
  a.AddLibrary("AlphaBetaGammaFilter version: " + AlphaBetaGammaFilter::GetVersion());
  a.AddLibrary("AlphaFilter version: " + AlphaFilter::GetVersion());
  a.AddLibrary("AminoAcidFighter version: " + aaf::MenuDialog().GetVersion());
  a.AddLibrary("Approximator version: " + Approximator<double,double>::GetVersion());
  a.AddLibrary("AsciiArter version: " + AsciiArterMenuDialog().GetVersion());
  a.AddLibrary("AthleticLand version: " + AthleticLandMenuDialog().GetVersion());
  a.AddLibrary("BeerWanter version: " + BeerWanterMenuDialog().GetVersion());
  a.AddLibrary("Big Integer Library (by Matt McCutchen) version: 2010.04.30");
  a.AddLibrary("BinaryNewickVector version: " + BinaryNewickVector::GetVersion());
  a.AddLibrary("Boenken version: " + Boenken::MenuDialog().GetVersion());

#ifdef INCLUDE_BRAINWEAVER_20140617
  a.AddLibrary("Brainweaver version: " + pvdb::MenuDialog().GetVersion());
#endif // INCLUDE_BRAINWEAVER_20140617

  a.AddLibrary("Canvas version: " + Canvas::GetVersion());
#ifdef INCLUDE_CHESS_20140617
  a.AddLibrary("Chess::BitBoard version: " + Chess::BitBoard::GetVersion());
  a.AddLibrary("Chess::Board version: " + Chess::Board::GetVersion());
  a.AddLibrary("Chess::BoardWidget version: " + Chess::BoardWidget::GetVersion());
  a.AddLibrary("Chess::Game version: " + Chess::Game::GetVersion());
  a.AddLibrary("Chess::Widget version: " + Chess::ChessWidget::GetVersion());
#endif
#ifdef INCLUDE_CONCEPTMAP_20140811
  a.AddLibrary("cmap::ConceptMap version: " + cmap::ConceptMap::GetVersion());
  a.AddLibrary("cmap::ConceptMapWidget version: " + cmap::Widget::GetVersion());
#endif // INCLUDE_CONCEPTMAP_20140811
  a.AddLibrary("CodeToHtml version: " + c2h::CodeToHtmlMenuDialog().GetVersion());
  a.AddLibrary("ConnectThree version: " + con3::ConnectThree::GetVersion());
  a.AddLibrary("ConnectThreeWidget version: " + con3::ConnectThreeWidget::GetVersion());
  a.AddLibrary("Container version: " + Container().GetVersion());
  a.AddLibrary("Copy_if version: " + Copy_if_version::GetVersion());
  a.AddLibrary("Counter version: " + Counter::GetVersion());
  a.AddLibrary("CreateQtProjectZipFile version: " + CreateQtProjectZipFile::MenuDialog().GetVersion());
  a.AddLibrary("DasWahreSchlagerfest version: " + DasWahreSchlagerfestMenuDialog().GetVersion());
  a.AddLibrary("Dial version: " + Dial::GetVersion());
  a.AddLibrary("DialWidget version: " + DialWidget::GetVersion());
  a.AddLibrary("DotMatrixChar version: " + DotMatrixChar::GetVersion());
  a.AddLibrary("DotMatrixString version: " + DotMatrixString::GetVersion());
  a.AddLibrary("DotMatrixText version: " + DotMatrixText::GetVersion());
  a.AddLibrary("DrawCanvas version: " + DrawCanvas::GetVersion());
  a.AddLibrary("Encranger (class) version: " + Encranger::GetVersion());
  a.AddLibrary("Encranger (tool) version: " + ToolEncrangerMenuDialog().GetVersion());
  a.AddLibrary("Exercise version: " + Exercise::GetVersion());
  a.AddLibrary("FileIo version: " + fileio::FileIo().GetVersion());
  a.AddLibrary("foam::Mesh version: " + ribi::foam::Mesh::GetVersion());
  a.AddLibrary("Fuzzy_equal_to version: " + fuzzy_equal_to::GetVersion());
  a.AddLibrary("GaborFilter version: " + GaborFilter::GetVersion());
  a.AddLibrary("GaborFilterWidget version: " + GaborFilterWidget::GetVersion());
  a.AddLibrary("Geometry version: " + Geometry().GetVersion());
  a.AddLibrary("Help version: " + Help::GetVersion());
  //a.AddLibrary("Hometrainer version: " + HometrainerMenuDialog().GetVersion());
  a.AddLibrary("HtmlPage version: " + HtmlPage::GetVersion());
  a.AddLibrary("ImageCanvas version: " + ImageCanvas::GetVersion());
  a.AddLibrary("IpAddress version: " + IpAddress::GetVersion());
  a.AddLibrary("K3OpEenRij version: " + K3OpEenRijMenuDialog().GetVersion());
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
  a.AddLibrary("Knokfighter version: " + KnokfighterMenuDialog().GetVersion());
  a.AddLibrary("Lazy_init version: " + Lazy_initVersion::GetVersion());
  a.AddLibrary("Led version: " + Led::GetVersion());
  a.AddLibrary("LedWidget version: " + LedWidget::GetVersion());
  a.AddLibrary("LoopReader version: " + LoopReader<int>::GetVersion());
  a.AddLibrary("ManyDigitNewick version: " + ManyDigitNewick::GetVersion());
  a.AddLibrary("Matrix version: " + Matrix::GetVersion());
  a.AddLibrary("Maziak version: " + maziak::MenuDialog().GetVersion());
  //a.AddLibrary("MetZnDrieenMenu version: " + MetZnDrieenMenuDialog().GetVersion());
  a.AddLibrary("MultiAlphaFilter version: " + MultiAlphaFilter::GetVersion());
  a.AddLibrary("MultiApproximator version: " + MultiApproximator<double,double>::GetVersion());
  a.AddLibrary("MultipleChoiceQuestion version: " + MultipleChoiceQuestion::GetVersion());
  a.AddLibrary("MultipleChoiceQuestionDialog version: " + MultipleChoiceQuestionDialog::GetVersion());
  a.AddLibrary("MultiVector version: " + MultiVector<int>::GetVersion());
  a.AddLibrary("Music::Chord version: " + Music::Chord::GetVersion());
  a.AddLibrary("Music::Note version: " + Music::Note::GetVersion());
  a.AddLibrary("Music::Scale version: " + Music::Scale::GetVersion());
  a.AddLibrary("MysteryMachine version: " + MysteryMachine::GetVersion());
  a.AddLibrary("MysteryMachineWidget version: " + MysteryMachineWidget::GetVersion());
  a.AddLibrary("Newick version: " + Newick::GetVersion());
  a.AddLibrary("NewickVector version: " + NewickVector::GetVersion());
  a.AddLibrary("OpenQuestion version: " + OpenQuestion::GetVersion());
  a.AddLibrary("OpenQuestionDialog version: " + OpenQuestionDialog::GetVersion());
  a.AddLibrary("PaperRockScissors version: " + PaperRockScissorsMenuDialog().GetVersion());
  const std::unique_ptr<Plane> plane(
    new Plane(
      Plane::Coordinat3D(0.0,0.0,0.0),
      Plane::Coordinat3D(1.0,0.0,0.0),
      Plane::Coordinat3D(0.0,1.0,0.0)
    )
  );
  assert(plane);
  a.AddLibrary("Plane version: " + plane->GetVersion());
  //a.AddLibrary("PokeVolley version: " + PokeVolleyMenuDialog().GetVersion());
  a.AddLibrary("PolyFile version: " + PolyFile::GetVersion());
  a.AddLibrary("PolyFileFromPolygons version: " + PolyFileFromPolygons::GetVersion());
  a.AddLibrary("Pong version: " + PongMenuDialog().GetVersion());
  a.AddLibrary("Pylos version: " + pylos::MenuDialog().GetVersion());
  a.AddLibrary("QmakeWatcher version: " + QmakeWatcherMenuDialog().GetVersion());
  a.AddLibrary("QrcFile version: " + QrcFile::GetVersion());
  a.AddLibrary("QtCreatorProFile version: " + QtCreatorProFile::GetVersion());
  a.AddLibrary("QtStdVectorFunctionModel version: " + QtStdVectorFunctionModel::GetVersion());
  a.AddLibrary("QtStdVectorStringModel version: " + QtStdVectorStringModel::GetVersion());
  a.AddLibrary("QtUblasMatrixDoubleModel version: " + QtUblasMatrixDoubleModel::GetVersion());
  a.AddLibrary("QtUblasVectorDoubleModel version: " + QtUblasVectorDoubleModel::GetVersion());
  a.AddLibrary("QtUblasVectorIntModel version: " + QtUblasVectorIntModel::GetVersion());
  a.AddLibrary("Question version: " + Question::GetVersion());
  a.AddLibrary("QuestionDialog version: " + QuestionDialog::GetVersion());
  a.AddLibrary("Rainbow version: " + Rainbow::GetVersion());
  a.AddLibrary("RandomCode version: " + RandomCode::GetVersion());
  a.AddLibrary("RegexTester version: " + RegexTesterMenuDialog().GetVersion());
  a.AddLibrary("Reversi (game) version: " + reversi::MenuDialog().GetVersion());
  a.AddLibrary("reversi::Board version: " + reversi::Board::GetVersion());
  a.AddLibrary("reversi::Widget version: " + reversi::Widget::GetVersion());
  a.AddLibrary("RichelBilderbeekProgram version: " + Program::GetVersion());
  a.AddLibrary("RubiksClock (class) version: " + ruco::Clock::GetVersion());
  a.AddLibrary("RubiksClock (game) version: " + ruco::MenuDialog().GetVersion());
  a.AddLibrary("RubiksClockDialversion: " + ruco::ClockDial::GetVersion());
  a.AddLibrary("RubiksClockDialWidget version: " + ruco::ClockDialWidget::GetVersion());
  a.AddLibrary("RubiksClockWidget version: " + ruco::ClockWidget::GetVersion());

#ifdef INCLUDE_SADD_20140617
  a.AddLibrary("SearchAndDestroyChess version: " + sadc::MenuDialog().GetVersion());
#endif // INCLUDE_SADD_20140617

  a.AddLibrary("Shape version: " + Shape::GetVersion());
  a.AddLibrary("ShapeWidget version: " + ShapeWidget::GetVersion());
  //a.AddLibrary("SimPredator version: " + SimPredatorMenuDialog().GetVersion());
  a.AddLibrary("ShinyButton version: " + ShinyButton::GetVersion());
  a.AddLibrary("ShinyButtonWidget version: " + ShinyButtonWidget::GetVersion());
  a.AddLibrary("SimMysteryMachine version: " + SimMysteryMachineMenuDialog().GetVersion());
  a.AddLibrary("SimpleLinearRegression version: " + SimpleLinearRegression::GetVersion());
  a.AddLibrary("SortedBinaryNewickVector version: " + SortedBinaryNewickVector::GetVersion());
  //a.AddLibrary("SpaceHarry version: " + SpaceHarryMenuDialog().GetVersion());
  a.AddLibrary("StaircaseCardCreator version: " + scc::MenuDialog().GetVersion());
  a.AddLibrary("StateObserver version: " + StateObserverMenuDialog().GetVersion());
  a.AddLibrary("Stopwatch version: " + Stopwatch::GetVersion());
  a.AddLibrary("SuperNsanaBros version: " + NsanaBrosMenuDialog().GetVersion());

#ifdef INCLUDE_TANKBATTALION_20140617
  a.AddLibrary("TankBattalion version: " + taba::MenuDialog().GetVersion());
#endif // INCLUDE_TANKBATTALION_20140617
  a.AddLibrary("TestApproximator version: " + ToolTestApproximatorMenuDialog().GetVersion());
  a.AddLibrary("TestDial version: " + TestDialMenuDialog().GetVersion());
  a.AddLibrary("TestExercise version: " + TestExerciseMenuDialog().GetVersion());
  a.AddLibrary("TestFunctionParser version: " + TestFunctionParserMenuDialog().GetVersion());
  a.AddLibrary("TestLed version: " + TestLedMenuDialog().GetVersion());
  a.AddLibrary("TestMultiApproximator version: " + ToolTestMultiApproximatorMenuDialog().GetVersion());
  a.AddLibrary("TestNewickVector version: " + TestNewickVectorDialog::GetVersion());
  a.AddLibrary("TestPolyFile version: " + TestPolyFileMenuDialog().GetVersion());
  a.AddLibrary("TestPolyFileFromPolygons version: " + TestPolyFileFromPolygonsMenuDialog().GetVersion());
  a.AddLibrary("TestProFile version: " + TestQtCreatorProFileMenuDialog().GetVersion());
  a.AddLibrary("TestQrcFile version: " + TestQrcFileMenuDialog().GetVersion());
  //a.AddLibrary("TestQuestion version: " + TestQuestionMenuDialog().GetVersion());
  a.AddLibrary("TestShape version: " + TestShapeMenuDialog().GetVersion());
  a.AddLibrary("TestShinyButton version: " + TestShinyButtonMenuDialog().GetVersion());
  a.AddLibrary("TestSimpleLinearRegression version: " + ToolTestSimpleLinearRegressionMenuDialog().GetVersion());
  a.AddLibrary("TestToggleButton version: " + TestToggleButtonMenuDialog().GetVersion());
  a.AddLibrary("Triangle version 1.6, by Jonathan Richard Shewchuk (http://www.cs.cmu.edu/~quake/triangle.html)");
  a.AddLibrary("TriangleFile version: " + TriangleFile::GetVersion());
  a.AddLibrary("TriangleMeshCreator version: " + TriangleMeshCreatorMenuDialog().GetVersion());
  a.AddLibrary("TextCanvas version: " + TextCanvas::GetVersion());
  a.AddLibrary("TicTacToe (game) version: " + tictactoe::TicTacToeMenuDialog().GetVersion());
  a.AddLibrary("TicTacToe version: " + tictactoe::Board::GetVersion());
  a.AddLibrary("ToggleButton version: " + ToggleButton::GetVersion());
  a.AddLibrary("ToggleButtonWidget version: " + ToggleButtonWidget::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  a.AddLibrary("Tron version: " + TronMenuDialog().GetVersion());
  a.AddLibrary("TwoDigitNewick version: " + TwoDigitNewick::GetVersion());
  a.AddLibrary("Warp's FunctionParser version: 4.4.3");
  a.AddLibrary("Widget version: " + Widget::GetVersion());
  a.AddLibrary("WktToSvg version: " + WktToSvgMenuDialog().GetVersion());
  a.AddLibrary("XeNonZero version: " + XeNonZeroMenuDialog().GetVersion());
  a.AddLibrary("XML version: " + ribi::xml::GetVersion());
  return a;
}

std::vector<boost::shared_ptr<ribi::MenuDialog>> ribi::ProjectRichelBilderbeekMenuDialog::CreateMenus() noexcept
{
  std::vector<boost::shared_ptr<ribi::MenuDialog>> v;
  for (const ProgramType t: ProgramTypes::GetAll())
  {
    boost::shared_ptr<ribi::MenuDialog> p;
    switch (t)
    {
      case ProgramType::aminoAcidFighter: p.reset(new aaf::MenuDialog); assert(p); break;
      case ProgramType::asciiArter: p.reset(new AsciiArterMenuDialog); break;
      case ProgramType::asciiArterVcl:
      {
        const std::string version = "3.0";
        const std::vector<std::string> version_history {
          "2006-12-13: Version 1.0: initial C++ Builder version, called 'AsciiArter'",
          "2006-12-16: Version 2.0: renamed 'AsciiArter' to 'TestAsciiArter', minor improvements",
          "2008-06-21: Version 3.0: minor improvements"
        };
        const About about(
          About::GetDefaultAuthor(),
          "AsciiArter (VCL)",
          "tool to create ASCII art",
          "the 21st of June 2008",
          "2006-2014",
          "http://www.richelbilderbeek.nl/ToolAsciiArterVcl.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramAsciiArterVcl),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::athleticLand: p.reset(new AthleticLandMenuDialog); break;
      case ProgramType::athleticLandVcl:
      {
        const std::string version = "3.0";
        const std::vector<std::string> version_history {
          "201x-xx-xx: Version 0.0: initial C++ Builder version"
        };
        const About about(
          About::GetDefaultAuthor(),
          "AthleticLand (VCL)",
          "MSX game clone",
          "today",
          "201x-2014",
          "http://www.richelbilderbeek.nl/GameAthleticLandVcl.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramAthleticLandVcl),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::barbaImage:
      {
        const std::string version = "1.0";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: Version 1.0: initial C++ Builder version"
        };
        const About about(
          About::GetDefaultAuthor(),
          "BarbaImage (VCL)",
          "image manipulation toolkit",
          "someday",
          "20xx-201x",
          "http://www.richelbilderbeek.nl/ToolBarbaImageVcl.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramBarbaImage),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::beerWanter: p.reset(new BeerWanterMenuDialog); break;
      case ProgramType::beerWanterVcl:
      {
        const std::string version = "3.0";
        const std::vector<std::string> version_history {
          "2005-11-16: version 1.0: (at that time called) 'Beerwanter 1' was programmed in C++ using the C++ Builder IDE during a 'Spass programmieren' session, which made BeerWanter a game for Windows users only",
          "2005-11-18: version 2.0: (at that time called) 'Beerwanter 2' was programmed after the success of BeerWanter 1.0. The game was made tougher",
          "2005-11-22: version 3.0: (at that time called) 'Beerwanter 3' was programmed after the success of BeerWanter 2.0. The game was made even tougher",
        };
        const About about(
          About::GetDefaultAuthor(),
          "BeerWanter (VCL)",
          "a simple game",
          "the 22nd of November 2005",
          "2005-2014",
          "http://www.richelbilderbeek.nl/GameBeerWanterVcl.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramBeerWanterVcl),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::bochum:
      {
        const std::string version = "1.0";
        const std::vector<std::string> version_history {
          "200x-xx-xx: version 1.0: ",
        };
        const About about(
          About::GetDefaultAuthor(),
          "Bochum",
          "Project about navigation by Kalman filtering and neural nets",
          "someday",
          "200x-200x",
          "http://www.richelbilderbeek.nl/ProjectBochum.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramBochum),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::boenken: p.reset(new Boenken::MenuDialog); break;
      case ProgramType::boenkenVcl:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "Boenken (VCL)",
          "game that is a mix between soccer and billiards",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/GameBoenkenVcl.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramBoenkenVcl),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::brainweaver:
#ifdef INCLUDE_BRAINWEAVER_20140617
        p.reset(new ribi::pvdb::MenuDialog);
#else
     {
        const std::string version = "x.x"; const std::vector<std::string> version_history { "20xx-xx-xx: version x.x: something" };
        const About about(About::GetDefaultAuthor(),"somename","description","someday","20xx-20xx","http://www.richelbilderbeek.nl/Somewhere.htm",version,version_history);
        p.reset(new PlaceholderMenuDialog(about,
            boost::shared_ptr<Program>(new ProgramBrainweaver),
            version,version_history
          )
        );
      }
#endif // INCLUDE_BRAINWEAVER_20140617
        break;
      case ProgramType::bristol:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "Bristol",
          "Project about dynamic plasticity",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ProjectBristol.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramBristol),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::caesarCipher: p.reset(new CaesarCipherMenuDialog); break;
      case ProgramType::chrisWiley:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "The Chris Wiley Project",
          "Project about extra-pair mating",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ProjectChrisWiley.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramChrisWiley),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::codeBreaker: p.reset(new CodeBreakerMenuDialog); break;
      case ProgramType::codeToHtml: p.reset(new c2h::CodeToHtmlMenuDialog); break;
      case ProgramType::connectThree: p.reset(new con3::ConnectThreeMenuDialog); break;
      case ProgramType::corridor:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          "?",
          "Corridor",
          "port of Corridor to Qt Creator",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/GameCorridor.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramCorridor),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::createGlossary: p.reset(new CreateGlossaryMenuDialog); break;
      case ProgramType::createQtProjectZipFile: p.reset(new CreateQtProjectZipFile::MenuDialog); break;
      case ProgramType::crossPoll:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "CrossPoll",
          "project about GMO cross-breeding",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ProjectCrossPoll.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramCrossPoll),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::dasWahreSchlagerfest: p.reset(new DasWahreSchlagerfestMenuDialog); break;
      case ProgramType::dasWahreSchlagerfestVcl:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "Das Wahre Schlagerfest (VCL)",
          "a truely fun game",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/GameDasWahreSchlagerfestVcl.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramDasWahreSchlagerfestVcl),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::dotMatrix: p.reset(new DotMatrixMenuDialog); break;
      case ProgramType::dotMatrixVcl:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "DotMatrix (VCL)",
          "tool to work with a dot-matrix font",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolDotMatrix.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramDotMatrixVcl),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::encranger: p.reset(new ToolEncrangerMenuDialog); break;
      case ProgramType::everythingToPiecesShooter:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          "Joost van den Bogaart",
          "EverythingToPiecesShooter",
          "space shooting game",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/GameEverythingToPiecesShooter.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramEverythingToPiecesShooter),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::fakeEvy:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "FakeEvy",
          "Running trainer generator",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolFakeEvy.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramFakeEvy),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::filterOperationer: p.reset(new FilterOperationerMenuDialog); break;
      case ProgramType::filterOperationerVcl:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "FilterOperationer (VCL)",
          "tool to perform filter operations",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolFilterOperationer.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramFilterOperationerVcl),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::fryskLeareLieder:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "FryskLeareLieder",
          "tool to learn the Frysian language",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolFryskLeareLieder.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramFryskLeareLieder),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::functionPlotter: p.reset(new FunctionPlotterMenuDialog); break;
      case ProgramType::functionPlotterVcl:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "FunctionPlotter (VCL)",
          "tool to plot a function",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolFunctionPlotterVcl.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramFunctionPlotterVcl),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::gaborFilter: p.reset(new ToolGaborFilterMenuDialog); break;
      case ProgramType::gaborFilterVcl:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "GaborFilter (VCL)",
          "tool to perform a Gabor filter operation",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolGaborFilterVcl.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramGaborFilterVcl),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::grayCoder: p.reset(new GrayCoderMenuDialog); break;
      case ProgramType::grayCoderVcl:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "GrayCoder (VCL)",
          "tool to experiment with Gray codes",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolGrayCoderVcl.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramGrayCoderVcl),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::gtst:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "GTST",
          "tool to do social experiments",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ProjectGtst.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramGtst),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::histogramEqualizationer: p.reset(new HistogramEqualizationerMenuDialog); break;
      case ProgramType::histogramEqualizationerVcl:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "HistogramEqualizationer (VCL)",
          "tool to perform a histogram equalization",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/toolHistogramEqualizationerVcl.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramHistogramEqualizationerVcl),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::hometrainer:
        p.reset(new HometrainerMenuDialog);
      break;
      case ProgramType::hometrainerVcl:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "Hometrainer (VCL)",
          "tool to create and practice drills",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolHometrainerVcl.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramHometrainerVcl),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::imageRotater: p.reset(new ImageRotaterMenuDialog); break;
      case ProgramType::imageRotaterClx:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "ImageRotater (CLX)",
          "tool to rotate images",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolImageRotaterClx.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramImageRotaterClx),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::imageRotaterVcl:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "ImageRotater (VCL)",
          "tool to rotate images",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolImageRotaterVcl.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramImageRotaterVcl),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::k3OpEenRij: p.reset(new K3OpEenRijMenuDialog); break;
      case ProgramType::k3OpEenRijVcl:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "K3OpEenRij (VCL)",
          "K3 styled connect-three game",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/GameK3OpEenRijVcl.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramK3OpEenRijVcl),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::kalmanFilterer: p.reset(new kalman::KalmanFiltererMenuDialog); break;
      case ProgramType::keySender:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "KeySender",
          "tool to emulate keystrokes",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolKeySender.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramKeySender),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::knokfighter: p.reset(new KnokfighterMenuDialog); break;
      case ProgramType::knokfighterVcl:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          "Joost van den Bogaart & Richel Bilderbeek",
          "Knokfighter (VCL)",
          "a Double Dragon clone",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/GameKnokfighterVcl.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramKnokfighterVcl),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::kTouchLectureCreator:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "KTouchLectureCreator",
          "creates exercises for KTouch",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolKtouchLectureCreator.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramKTouchLectureCreator),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::lambdaBot:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "LambdaBot",
          "an IRC bot",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolLambdaBot.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramLambdaBot),
            version,
            version_history
          )
        );
      }
      break; //
      case ProgramType::learyCircumplex:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "LearyCircumplex",
          "tool to draw a Leary circumplex",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolLearyCircumplex.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramLearyCircumplex),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::logisticGrowthSimulator:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "LogisticGrowthSimulator",
          "simulation of the logistic growth equation",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolLogisticGrowthSimulator.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramLogisticGrowthSimulator),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::loose:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "Loose",
          "email address assigner",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolLoose.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramLoose),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::martianCafeTuinemaTycoon:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          "Joost van den Bogaart",
          "Martian Cafe Tuinema Tycoon",
          "pub simulation game",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/GameMartianCafeTuinemaTycoon.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramMartianCafeTuinemaTycoon),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::mazeCreator: p.reset(new MazeCreatorMenuDialog); break;
      case ProgramType::mazeCreatorVcl:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "MazeCreator (VCL)",
          "tool to demonstrate maze creation",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolMazeCreatorVcl.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramMazeCreatorVcl),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::maziak: p.reset(new maziak::MenuDialog); break;
      case ProgramType::maziakVcl:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "Maziak (VCL)",
          "simple maze game",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/GameMaziak.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramMaziakVcl),
            version,
            version_history
          )
        );
      }
      break;
      //case ProgramType::metZnDrieen: p.reset(new MetZnDrieenMenuDialog); break;
      case ProgramType::metZnDrieenVcl:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "MetZnDrieen (VCL)",
          "Billy themed connect-three game",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/GameMetZnDrieenVcl.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramMetZnDrieenVcl),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::midiLessonCreator :
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "MidiLessonCreator",
          "tool to create MIDI lessons",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolMidiLessonCreator.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramMidiLessonCreator),
            version,
            version_history
          )
        );
      }
      break; //
      case ProgramType::morpher :
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "Morpher",
          "tool to generate morphed images",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolMorpher.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramMorpher),
            version,
            version_history
          )
        );
      }
      break; //
      case ProgramType::multiEncranger: p.reset(new MultiEncrangerMenuDialog); break;
      case ProgramType::multiEncrangerVcl:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "MultiEncranger (VCL)",
          "multi-line Encranger",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolMultiEncrangerVcl.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramMultiEncrangerVcl),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::muscaDomestica:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "MuscaDomestica",
          "Musca Domestica simulation",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ProjectMuscaDomestica.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramMuscaDomestica),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::musicTheory: p.reset(new MusicTheoryMenuDialog); break;
      case ProgramType::ndsmake:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "ndsmake",
          "make tool to compile to NDS",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolNdsmake.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramNdsmake),
            version,
            version_history
          )
        );
      }
      break; //
      case ProgramType::ndsPaint:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "NDS paint",
          "drawing program for NDS",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolNdsPaint.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramNdsPaint),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::paperRockScissors: p.reset(new PaperRockScissorsMenuDialog); break;
      case ProgramType::paperRockScissorsVcl:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "PaperRockScissors (VCL)",
          "Paper-Rock-Scissors simulation",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolPaperRockScissorsVcl.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramPaperRockScissorsVcl),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::pause:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "Pause",
          "tool that does nothing",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolPause.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramPause),
            version,
            version_history
          )
        );
      }
      break; //
      case ProgramType::perfectElasticCollision: p.reset(new PerfectElasticCollisionMenuDialog); break;
      case ProgramType::picToCode: p.reset(new PicToCodeMenuDialog); break;
      case ProgramType::pixelator: p.reset(new PixelatorMenuDialog); break;
      case ProgramType::pixelatorVcl:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "Pixelator (VCL)",
          "pixelates images",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolPixelatorVcl.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramPixelatorVcl),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::pokeVolleyVcl:
      //p.reset(new PokeVolleyMenuDialog); break;
      {
        const std::string version = "1.0";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version 1.0: initial version"
        };
        const About about(
          "Richel Bilderbeek",
          "PokeVolley",
          "Pokemon-themed Volley game",
          "today",
          "200x-2014",
          "http://www.richelbilderbeek.nl/GamePokeVolley.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramPokeVolleyVcl),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::pong: p.reset(new PongMenuDialog); break;
      case ProgramType::preDickAdvocaTor: p.reset(new PreDickAdvocaTorMenuDialog); break;
      case ProgramType::primeExpert: p.reset(new PrimeExpertMenuDialog); break;
      case ProgramType::projectRichelBilderbeek:
        //Don't do this: this will result in an infinite recursion
        //p.reset(new ProjectRichelBilderbeekMenuDialog);
      {
        p.reset(
          new PlaceholderMenuDialog(
            GetAboutStatic(),
            boost::shared_ptr<Program>(new ProgramProjectRichelBilderbeek),
            GetVersionStatic(),
            GetVersionHistoryStatic()
          )
        );
      }
      break;
      case ProgramType::pylos: p.reset(new pylos::MenuDialog); break;
      case ProgramType::qmakeWatcher: p.reset(new QmakeWatcherMenuDialog); break;
      case ProgramType::quadraticSolver: p.reset(new QuadraticSolverMenuDialog); break;
      case ProgramType::rampalEtienne:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "RampalEtienne",
          "project to determine the probability of finding a phylogenetic tree",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ProjectRampalEtienne.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramRampalEtienne),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::randomCode: p.reset(new RandomCodeMenuDialog); break;
      case ProgramType::randomCodeVcl:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "RandomCode (VLC)",
          "tool to generate random C++ code",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolRandomCodeVcl.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramRandomCodeVcl),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::rasper: /* p.reset(new RasperMenuDialog); */
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "Rasper",
          "Raspberry Pi web interface tool",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolRasper.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramRasper),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::refrigeratorPuzzleSolver:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "RefrigeratorPuzzleSolver",
          "tool to solve a monkey puzzle",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolRefrigeratorPuzzleSolver.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramRefrigeratorPuzzleSolver),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::regexTester: p.reset(new RegexTesterMenuDialog); break;
      case ProgramType::reversi: p.reset(new reversi::MenuDialog); break;
      case ProgramType::reversiVcl:
      {
        const std::string version = "1.0";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: Version 1.0: initial C++ Builder version"
        };
        const About about(
          About::GetDefaultAuthor(),
          "Reversi (VCL)",
          "reversi game",
          "the 24th of September 2007",
          "2007-2014",
          "http://www.richelbilderbeek.nl/GameReversiVcl.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramReversiVcl),
            version,
            version_history
          )
        );
      }
      break;

      case ProgramType::richelBilderbeekGallery: p.reset(new GalleryMenuDialog); break;
      case ProgramType::richelbilderbeekNlSitemapGenerator: p.reset(new SitemapGeneratorMenuDialog); break;
      case ProgramType::rubiksClock: p.reset(new ruco::MenuDialog); break;
      case ProgramType::rubiksClockVcl:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "RubiksClock (VCL)",
          "RubiksClock simulation",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/GameRubiksClockVcl.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramRubiksClockVcl),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::searchAndDestroyChess:
#ifdef INCLUDE_SADD_20140617
        p.reset(new sadc::MenuDialog);
#else
     {
        const std::string version = "x.x"; const std::vector<std::string> version_history { "20xx-xx-xx: version x.x: something" };
        const About about(About::GetDefaultAuthor(),"somename","description","someday","20xx-20xx","http://www.richelbilderbeek.nl/Somewhere.htm",version,version_history);
        p.reset(new PlaceholderMenuDialog(about,
            boost::shared_ptr<Program>(new ProgramSearchAndDestroyChess),
            version,version_history
          )
        );
      }

#endif
      break;
      case ProgramType::searchAndDestroyChessVcl:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "SearchAndDestroyChess (VCL)",
          "Kriegspiel game",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/GameSearchAndDestroyChessVcl.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramSearchAndDestroyChessVcl),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::secretMessage: p.reset(new ribi::sema::MenuDialog); break;
      case ProgramType::secretMessageVcl:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "SecretMessage (VCL)",
          "put/extract secret messages in/from images",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolSecretMessageVcl.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramSecretMessageVcl),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::simBrainiac:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "SimBrainiac",
          "simulation of the teaching form Brainiac",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolSimBrainiac.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramSimBrainiac),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::simImmuneResponse:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "SimImmuneResponse",
          "humane immune response simulation",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolSimImmuneResponse.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramSimImmuneResponse),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::simMysteryMachine: p.reset(new SimMysteryMachineMenuDialog); break;
      case ProgramType::simplifyNewick: p.reset(new ToolSimplifyNewickMenuDialog); break;
      case ProgramType::simPredatorVcl:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "SimPredator",
          "natural selection simulation",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolSimPredator.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramSimStagecraft),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::simStagecraft:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "SimStagecraft",
          "stagecraft simulation",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolSimStagecraft.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramSimStagecraft),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::soaSim:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "SoaSim",
          "STD simulation",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolSoaSim.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramSoaSim),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::solvePuzzleX:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "SolvePuzzleX",
          "solve the puzzle given by X",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolSolvePuzzleX.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramSolvePuzzleX),
            version,
            version_history
          )
        );
      }
      break;
      //case ProgramType::spaceHarry: p.reset(new SpaceHarryMenuDialog); break;
      case ProgramType::spaceHarryVcl:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "SpaceHarry (VCL)",
          "simple Space Harrier clone",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/GameSpaceHarryVcl.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramSpaceHarryVcl),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::staircaseCardCreator:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "StaircaseCardCreator",
          "tool to create staircase cards",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/ToolStaircaseCardCreator.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramStaircaseCardCreator),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::stateObserver: p.reset(new StateObserverMenuDialog); break;
      case ProgramType::styleSheetSetter: p.reset(new StyleSheetSetterMenuDialog); break;
      case ProgramType::superNsanaBros: p.reset(new NsanaBrosMenuDialog); break;
      case ProgramType::surfacePlotter: p.reset(new SurfacePlotterMenuDialog); break;
      case ProgramType::surfacePlotterVcl:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramSurfacePlotterVcl),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::tankBattalion:
#ifdef INCLUDE_TANKBATTALION_20140617
        p.reset(new taba::MenuDialog);
#else
      {
        const std::string version = "x.x"; const std::vector<std::string> version_history { "20xx-xx-xx: version x.x: something" };
        const About about(About::GetDefaultAuthor(),"somename","description","someday","20xx-20xx","http://www.richelbilderbeek.nl/Somewhere.htm",version,version_history);
        p.reset(new PlaceholderMenuDialog(about,
            boost::shared_ptr<Program>(new ProgramTankBattalion),
            version,version_history
          )
        );
      }
#endif
      break;
      case ProgramType::testAbout: p.reset(new TestAboutMenuDialog); break;
      case ProgramType::testApproximator: p.reset(new ToolTestApproximatorMenuDialog); break;
      case ProgramType::testBinaryNewickVector: p.reset(new TestBinaryNewickVectorMenuDialog); break;
      case ProgramType::testBouncingBallsWidget:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramTestBouncingBallsWidget),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::testBouncingRectsWidget:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramTestBouncingRectsWidget),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::testBroadcastServer:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramTestBroadcastServer),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::testChess:
#ifdef INCLUDE_CHESS_20140617
      p.reset(new TestChessMenuDialog);
#else
      {
        const std::string version = "x.x"; const std::vector<std::string> version_history { "20xx-xx-xx: version x.x: something" };
        const About about(About::GetDefaultAuthor(),"somename","description","someday","20xx-20xx","http://www.richelbilderbeek.nl/Somewhere.htm",version,version_history);
        p.reset(new PlaceholderMenuDialog(about,
            boost::shared_ptr<Program>(new ProgramTestChess),
            version,version_history
          )
        );
      }
#endif // INCLUDE_CHESS_20140617
      break;
      case ProgramType::testConceptMap:
      {
        #ifdef INCLUDE_CONCEPTMAP_20140811
        p.reset(new TestConceptMapMenuDialog);
        #else
        const std::string version = "x.x"; const std::vector<std::string> version_history { "20xx-xx-xx: version x.x: something" };
        const About about(About::GetDefaultAuthor(),"somename","description","someday","20xx-20xx","http://www.richelbilderbeek.nl/Somewhere.htm",version,version_history);
        p.reset(new PlaceholderMenuDialog(about,
            boost::shared_ptr<Program>(new ProgramTestChess),
            version,version_history
          )
        );
        #endif // INCLUDE_CONCEPTMAP_20140811
      }
      break;
      case ProgramType::testDial: p.reset(new TestDialMenuDialog); break;
      case ProgramType::testDrawCanvas: p.reset(new TestDrawCanvasMenuDialog); break;
      case ProgramType::testEntrance: p.reset(new ToolTestEntrance::MenuDialog); break;
      case ProgramType::testExercise: p.reset(new TestExerciseMenuDialog); break;
      case ProgramType::testFunctionParser: p.reset(new TestFunctionParserMenuDialog); break;
      case ProgramType::testGnuplotInterface:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramTestGnuplotInterface),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::testGraphicsProxyWidget:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramTestGraphicsProxyWidget),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::testGravityWidget:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramTestGravityWidget),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::testGroupWidget: p.reset(new TestGroupWidgetMenuDialog); break;
      case ProgramType::testHugeVector:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramTestHugeVector),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::testImageCanvas: p.reset(new TestImageCanvasMenuDialog); break;
      case ProgramType::testLazy_init:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramTestLazy_init),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::testLed: p.reset(new TestLedMenuDialog); break;
      case ProgramType::testManyDigitNewick:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramTestManyDigitNewick),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::testMultiApproximator: p.reset(new ToolTestMultiApproximatorMenuDialog); break;
      case ProgramType::testMultiCanvas: p.reset(new TestMultiCanvasMenuDialog); break;
      case ProgramType::testMultipleChoiceQuestion:
      {
        #ifdef ADD_TESTMULTIPLECHOOCEQUESTIONDIALOG
        p.reset(new TestMultipleChoiceQuestionMenuDialog);
        #else
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramTestTimedServerPusher),
            version,
            version_history
          )
        );
        #endif
      }
      break;
      case ProgramType::testMultiVector:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramTestMultiVector),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::testNdsmake:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramTestNdsmake),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::testNeuralNet:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramTestNeuralNet),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::testNewick:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramTestNewick),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::testNewickVector:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramTestNewickVector),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::testOpenQuestion: p.reset(new TestOpenQuestionMenuDialog); break;
      case ProgramType::testPlane: p.reset(new TestPlaneMenuDialog); break;
      case ProgramType::testPolyFile: p.reset(new TestPolyFileMenuDialog); break;
      case ProgramType::testPolyFileFromPolygons: p.reset(new TestPolyFileFromPolygonsMenuDialog); break;
      case ProgramType::testPylos: p.reset(new TestPylosMenuDialog); break;
      case ProgramType::testQrcFile: p.reset(new TestQrcFileMenuDialog); break;
      case ProgramType::testQtArrowItems : p.reset(new TestQtArrowItemsMenuDialog); break;
      case ProgramType::testQtCreatorProFile: p.reset(new TestQtCreatorProFileMenuDialog); break;
      case ProgramType::testQtHideAndShowDialog:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramTestQtHideAndShowDialog),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::testQtKeyboardFriendlyGraphicsView: p.reset(new TestKeyboardFriendlyGraphicsViewMenuDialog); break;
      case ProgramType::testQtModels: p.reset(new ToolTestQtModelsMenuDialog); break;
      case ProgramType::testQtOcrWidget:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramTestQtOcrWidget),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::testQtRoundedEditRectItem: p.reset(new TestQtRoundedEditRectItemMenuDialog); break;
      case ProgramType::testQtRoundedRectItem: p.reset(new TestQtRoundedRectItemMenuDialog); break;
      //case ProgramType::testQtRoundedTextRectItem: p.reset(new TestQtRoundedTextRectItemMenuDialog); break; //OBSOLETE
      case ProgramType::testQuestion:
      {
        #ifdef ADD_TESTQUESTIONDIALOG
        p.reset(new TestQuestionMenuDialog);
        #else
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramTestTimedServerPusher),
            version,
            version_history
          )
        );
        #endif
      }
      break;
      case ProgramType::testReversi:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramTestReversi),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::testSelectFileDialog:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramTestSelectFileDialog),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::testServerPusher:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramTestServerPusher),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::testShape: p.reset(new TestShapeMenuDialog);
      break;
      case ProgramType::testShinyButton: p.reset(new TestShinyButtonMenuDialog); break;
      case ProgramType::testSimpleLinearRegression: p.reset(new ToolTestSimpleLinearRegressionMenuDialog); break;
      case ProgramType::testStopwatch:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramTestStopwatch),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::testTextCanvas: p.reset(new TestTextCanvasMenuDialog); break;
      case ProgramType::testTextPositionWidget:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramTestTextPositionWidget),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::testTicTacToe:
      {
        #ifdef ADD_TESTTICTACTOE
        p.reset(new TestTicTacToeMenuDialog);
        #else
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramTestTimedServerPusher),
            version,
            version_history
          )
        );
        #endif
      }
      break;
      case ProgramType::testTimedServerPusher:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "TestTimedServerPusher",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramTestTimedServerPusher),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::testToggleButton: p.reset(new TestToggleButtonMenuDialog); break;
      case ProgramType::testTriangle: p.reset(new TestTriangleMenuDialog); break;
      case ProgramType::testTwoDigitNewick: p.reset(new TestTwoDigitNewickMenuDialog); break;
      case ProgramType::thorVeen:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramThorVeen),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::thresholdFilterer: p.reset(new ThresholdFiltererMenuDialog); break;
      case ProgramType::thresholdFiltererVcl:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramThresholdFiltererVcl),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::ticTacToe: p.reset(new tictactoe::TicTacToeMenuDialog); break;
      case ProgramType::ticTacToeLearner:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramTicTacToeLearner),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::ticTacToeValuer:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramTicTacToeValuer),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::timePoll:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramTimePoll),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::triangleMeshCreator: p.reset(new TriangleMeshCreatorMenuDialog); break;
      case ProgramType::tronCollection: p.reset(new TronMenuDialog); break;
      case ProgramType::tronCollectionVcl:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramTronCollectionVcl),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::ubuntuOneWatcher:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramUbuntuOneWatcher),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::valentineCardDecrypter : p.reset(new ValentineCardDecrypterMenuDialog); break;
      case ProgramType::vanDenBogaart:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramVanDenBogaart),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::vigenereCipher: p.reset(new VigenereCipherMenuDialog); break;
      case ProgramType::virtualBastard:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          About::GetDefaultAuthor(),
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramVirtualBastard),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::visualAbc: p.reset(new VisualAbcMenuDialog); break;
      case ProgramType::wktToSvg: p.reset(new WktToSvgMenuDialog); break;
      case ProgramType::xeNonZero: p.reset(new XeNonZeroMenuDialog); break;
      case ProgramType::zork:
      {
        const std::string version = "x.x";
        const std::vector<std::string> version_history {
          "20xx-xx-xx: version x.x: something",
        };
        const About about(
          "Not me",
          "somename",
          "description",
          "someday",
          "20xx-20xx",
          "http://www.richelbilderbeek.nl/Somewhere.htm",
          version,
          version_history
        );
        p.reset(
          new PlaceholderMenuDialog(
            about,
            boost::shared_ptr<Program>(new ProgramZork),
            version,
            version_history
          )
        );
      }
      break;
      case ProgramType::n_types:
        assert(!"Must not use n_types");
        throw std::logic_error("ribi::ProjectRichelBilderbeekMenuDialog::CreateMenus");
    }
    v.push_back(p);
  }
  assert(static_cast<int>(v.size()) == static_cast<int>(ProgramType::n_types)
    && "All types must be present");
  return v;
}


ribi::Help ribi::ProjectRichelBilderbeekMenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    GetAbout().GetFileTitle() + "Console",
    GetAbout().GetFileDescription(),
    {
      Help::Option('p',"program","lists all possible programs"),
      Help::Option('s',"status", "lists all programs' statuses")
    },
    {
      "ProjectRichelBilderbeekConsole --help",
      "ProjectRichelBilderbeekConsole Hometrainer --help"
    }
  );
}




boost::shared_ptr<const ribi::Program> ribi::ProjectRichelBilderbeekMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p(new ProgramProjectRichelBilderbeek);
  assert(p);
  return p;
}

std::string ribi::ProjectRichelBilderbeekMenuDialog::GetVersionStatic() noexcept
{
  return "1.16";
}

std::vector<std::string> ribi::ProjectRichelBilderbeekMenuDialog::GetVersionHistoryStatic() noexcept
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
    "2013-11-29: Version 1.13: added HistogramEqualizationer, ImageOperationer, ImageRotater, StyleSheetSetter, ThresholdFilterer",
    "2014-02-27: Version 1.14: added PreDickAdvocaTor and ValentineCardDecrypter, added retro versions to some games",
    "2014-04-22: Version 1.15: added CaesarCipher, CodeBreaker and VigenereCipher",
    "2014-08-08: Version 1.16: increased use of TDD in console version"
  };
}

void ribi::ProjectRichelBilderbeekMenuDialog::ShowStatus() const noexcept
{
  typedef boost::shared_ptr<const ribi::Program> ProgramType;

  std::vector<ProgramType> v;
  for (const auto& p: CreateMenus())
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
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  ProjectRichelBilderbeekMenuDialog d;
  //Create all menus
  for (const auto& m: CreateMenus())
  {

    assert(!m->GetVersion().empty());
    assert(!m->GetVersionHistory().empty());
    assert(m->GetProgram());
  }
  //Test all menus
  {
    for (const auto& p: d.CreateMenus())
    {
      assert(p);
      assert(p->GetProgram());
    }
  }
}
#endif
