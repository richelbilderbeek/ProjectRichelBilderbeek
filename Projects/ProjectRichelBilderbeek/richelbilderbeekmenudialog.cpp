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
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "richelbilderbeekmenudialog.h"

#include "about.h"
#include "alphabetafilter.h"
#include "alphabetagammafilter.h"
#include "alphafilter.h"
#include "approximator.h"
#include "asciiartermenudialog.h"
#include "beerwantermenudialog.h"
#include "binarynewickvector.h"
#include "testnewickvectormenudialog.h"
#include "beast.h"
#include "fisherwrightermenudialog.h"
#include "boenkenmenudialog.h"
#include "caesarciphermenudialog.h"
#include "canvas.h"
#include "chessbitboard.h"
#include "chessboard.h"
#include "chessboardwidget.h"
#include "chessgame.h"
#include "chesswidget.h"
#include "codetohtmlmenudialog.h"
#include "conceptmap.h"
//#include "conceptmapwidget.h"
#include "connectthree.h"
#include "connectthreemenudialog.h"
#include "testmultivectormenudialog.h"
#include "connectthreewidget.h"
#include "container.h"
#include "copy_if.h"
#include "counter.h"
#include "createqtprojectzipfilemenudialog.h"
#include "createglossarymenudialog.h"
#include "daswahreschlagerfestmenudialog.h"
#include "dial.h"
#include "testquestionmenudialog.h"
#include "testtictactoemenudialog.h"
#include "dialwidget.h"
#include "dotmatrixchar.h"
#include "dna_r.h"
#include "newickutils.h"
#include "ribi_rinside.h"
#include "phylogeny_r.h"
#include "dotmatrixmenudialog.h"
#include "dotmatrixstring.h"
#include "testmanydigitnewickmenudialog.h"
#include "testmultivectormenudialog.h"
#include "testnewickmenudialog.h"
#include "testmultivectormenudialog.h"
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
#include "laggedwhitenoisesystem.h"
#include "lazy_init.h"
#include "led.h"
#include "ledwidget.h"
#include "lizardpaperrockscissorsspockmenudialog.h"
#include "loopreader.h"
#include "manydigitnewick.h"
#include "matrix.h"
#include "mazecreatormenudialog.h"
#include "maziakmenudialog.h"
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
#include "mutualismbreakdownermenudialog.h"
#include "mysterymachine.h"
#include "mysterymachinewidget.h"
#include "newick.h"
#include "newickvector.h"
#include "testmultiplechoicequestionmenudialog.h"
#include "openfoammesh.h"
#include "openquestion.h"
#include "openquestiondialog.h"
#include "paperrockscissorsmenudialog.h"
#include "paperrockscissorswithtraitmenudialog.h"
#include "perfectelasticcollisionmenudialog.h"
#include "pictocodemenudialog.h"
#include "pixelatormenudialog.h"
#include "pixelatormenudialog.h"
#include "plane.h"
#include "simtoppredatorpreymenudialog.h"
#include "polyfile.h"
#include "polyfilefrompolygons.h"
#include "predickadvocatormenudialog.h"
#include "primeexpertmenudialog.h"
#include "pvdbmenudialog.h"
#include "pylosmenudialog.h"
#include "qmakewatchermenudialog.h"
#include "qmakewatchermenudialog.h"
#include "qrcfile.h"
#include "qtcreatorprofilezipscript.h"
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
#include "searchanddestroychessmenudialog.h"
#include "secretmessagemenudialog.h"
#include "shape.h"
#include "stochasticityinspectormenudialog.h"
#include "shapewidget.h"
#include "shinybutton.h"
#include "shinybuttonwidget.h"
#include "simmysterymachinemenudialog.h"
#include "simplelinearregression.h"
#include "simplifynewickmenudialog.h"
#include "sitemapgeneratormenudialog.h"
#include "sitemapgeneratormenudialog.h"
#include "sortedbinarynewickvector.h"
#include "staircasecardcreatormenudialog.h"
#include "stateobservermenudialog.h"
#include "steadystatekalmanfilter.h"
#include "steadystatekalmanfilterparameters.h"
#include "stopwatch.h"
#include "stylesheetsettermenudialog.h"
#include "surfaceplottermenudialog.h"
#include "tankbattalionmenudialog.h"
#include "testaboutmenudialog.h"
#include "testapproximatormenudialog.h"
#include "testapproximatormenudialog.h"
#include "testtimer.h"
#include "testbinarynewickvectormenudialog.h"
#include "testchessmenudialog.h"
#include "testchessmenudialog.h"
#include "testconceptmapmenudialog.h"
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
    assert(p || !p);
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
    "the 24th of May 2015",
    "2010-2015",
    "http://www.richelbilderbeek.nl/ProjectRichelBilderbeek.htm",
    GetVersionStatic(),
    GetVersionHistoryStatic());
  //a.AddLibrary("TestTwoDigitNewick version: " + WtTestTwoDigitNewickDialog::GetVersion());
  a.AddLibrary("AlphaBetaFilter version: " + AlphaBetaFilter::GetVersion());
  a.AddLibrary("AlphaBetaGammaFilter version: " + AlphaBetaGammaFilter::GetVersion());
  a.AddLibrary("AlphaFilter version: " + AlphaFilter::GetVersion());
  a.AddLibrary("Approximator version: " + Approximator<double,double>::GetVersion());
  a.AddLibrary("apfloat version: 2.4.1");
  a.AddLibrary("AsciiArter version: " + AsciiArterMenuDialog().GetVersion());

  a.AddLibrary("BeastR version: " + ribi::Beast().GetVersion());

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
  a.AddLibrary("DasWahreSchlagerfest version: " + dws::MenuDialog().GetVersion());
  a.AddLibrary("Dial version: " + Dial::GetVersion());
  a.AddLibrary("DialWidget version: " + DialWidget::GetVersion());
  a.AddLibrary("DnaR version: " + ribi::DnaR().GetVersion());
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
  a.AddLibrary("Lazy_init version: " + Lazy_initVersion::GetVersion());
  a.AddLibrary("Led version: " + Led::GetVersion());
  a.AddLibrary("LedWidget version: " + LedWidget::GetVersion());
  a.AddLibrary("LoopReader version: " + LoopReader<int>::GetVersion());
  a.AddLibrary("ManyDigitNewick version: " + ManyDigitNewick::GetVersion());
  a.AddLibrary("Matrix version: " + Matrix::GetVersion());
  a.AddLibrary("Maziak version: " + maziak::MenuDialog().GetVersion());
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
  a.AddLibrary("Newick version: " + Newick().GetVersion());
  a.AddLibrary("NewickUtils version: " + ribi::NewickUtils().GetVersion());
  a.AddLibrary("NewickVector version: " + NewickVector::GetVersion());
  a.AddLibrary("OpenQuestion version: " + OpenQuestion::GetVersion());
  a.AddLibrary("OpenQuestionDialog version: " + OpenQuestionDialog::GetVersion());
  const std::unique_ptr<Plane> plane(
    new Plane(
      Plane::Coordinat3D(0.0,0.0,0.0),
      Plane::Coordinat3D(1.0,0.0,0.0),
      Plane::Coordinat3D(0.0,1.0,0.0)
    )
  );
  assert(plane);
  a.AddLibrary("PhylogenyR version: " + ribi::PhylogenyR().GetVersion());
  a.AddLibrary("Plane version: " + plane->GetVersion());
  a.AddLibrary("PolyFile version: " + PolyFile::GetVersion());
  a.AddLibrary("PolyFileFromPolygons version: " + PolyFileFromPolygons::GetVersion());
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
  a.AddLibrary("Rinside version: " + ribi::Rinside().GetVersion());
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
  a.AddLibrary("TankBattalion version: " + taba::MenuDialog().GetVersion());
  a.AddLibrary("TestApproximator version: " + ToolTestApproximatorMenuDialog().GetVersion());
  a.AddLibrary("TestDial version: " + TestDialMenuDialog().GetVersion());
  a.AddLibrary("TestExercise version: " + TestExerciseMenuDialog().GetVersion());
  a.AddLibrary("TestFunctionParser version: " + TestFunctionParserMenuDialog().GetVersion());
  a.AddLibrary("TestLed version: " + TestLedMenuDialog().GetVersion());
  a.AddLibrary("TestMultiApproximator version: " + ToolTestMultiApproximatorMenuDialog().GetVersion());
  a.AddLibrary("TestNewickVector version: " + TestNewickVectorMenuDialog().GetVersion());
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
      case ProgramType::asciiArter: p.reset(new AsciiArterMenuDialog); break;
      case ProgramType::asciiArterVcl: break;
      case ProgramType::athleticLandVcl: break;
      case ProgramType::barbaImage: break;
      case ProgramType::beerWanter: p.reset(new BeerWanterMenuDialog); break;
      case ProgramType::beerWanterVcl: break;
      case ProgramType::bochum: break;
      case ProgramType::boenken: p.reset(new Boenken::MenuDialog); break;
      case ProgramType::boenkenVcl: break;
      case ProgramType::brainweaver: p.reset(new ribi::pvdb::MenuDialog); break;
      case ProgramType::bristol: break;
      case ProgramType::caesarCipher: p.reset(new CaesarCipherMenuDialog); break;
      case ProgramType::chrisWiley: break;
      //case ProgramType::codeBreaker: p.reset(new CodeBreakerMenuDialog); break;
      case ProgramType::codeToHtml: p.reset(new c2h::CodeToHtmlMenuDialog); break;
      case ProgramType::connectThree: p.reset(new con3::ConnectThreeMenuDialog); break;
      case ProgramType::corridor: break;
      case ProgramType::createGlossary: p.reset(new CreateGlossaryMenuDialog); break;
      case ProgramType::createQtProjectZipFile: p.reset(new CreateQtProjectZipFile::MenuDialog); break;
      case ProgramType::crossPoll: break;
      case ProgramType::dasWahreSchlagerfest: p.reset(new dws::MenuDialog); break;
      case ProgramType::dasWahreSchlagerfestVcl: break;
      case ProgramType::dotMatrix: p.reset(new DotMatrixMenuDialog); break;
      case ProgramType::dotMatrixVcl: break;
      case ProgramType::encranger: p.reset(new ToolEncrangerMenuDialog); break;
      case ProgramType::everythingToPiecesShooter: break;
      case ProgramType::filterOperationer: p.reset(new FilterOperationerMenuDialog); break;
      case ProgramType::filterOperationerVcl: break;
      case ProgramType::fisherWrighter: p.reset(new ribi::fw::MenuDialog); break;
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
      case ProgramType::knokfighterVcl: break;
      case ProgramType::kTouchLectureCreator: break;
      case ProgramType::lambdaBot: break;
      case ProgramType::learyCircumplex: break;
      case ProgramType::lizardPaperRockScissorsSpock: p.reset(new ribi::lprss::MenuDialog); break;
      case ProgramType::logisticGrowthSimulator: break;
      case ProgramType::loose: break;
      case ProgramType::martianCafeTuinemaTycoon: break;
      case ProgramType::mazeCreator: p.reset(new MazeCreatorMenuDialog); break;
      case ProgramType::mazeCreatorVcl: break;
      case ProgramType::maziak: p.reset(new maziak::MenuDialog); break;
      case ProgramType::maziakVcl: break;
      case ProgramType::metZnDrieenVcl: break;
      case ProgramType::midiLessonCreator: break;
      case ProgramType::morpher: break;
      case ProgramType::multiEncranger: p.reset(new MultiEncrangerMenuDialog); break;
      case ProgramType::multiEncrangerVcl: break;
      case ProgramType::muscaDomestica: break;
      case ProgramType::musicTheory: p.reset(new MusicTheoryMenuDialog); break;
      case ProgramType::mutualismBreakdowner: p.reset(new ribi::mb::MenuDialog); break;
      case ProgramType::ndsmake: break;
      case ProgramType::paperRockScissors: p.reset(new ribi::prs::MenuDialog); break;
      case ProgramType::paperRockScissorsVcl: break;
      case ProgramType::paperRockScissorsWithTrait: p.reset(new ribi::prswt::MenuDialog); break;
      case ProgramType::pause: break;
      case ProgramType::perfectElasticCollision: p.reset(new PerfectElasticCollisionMenuDialog); break;
      case ProgramType::picToCode: p.reset(new p2c::MenuDialog); break;
      case ProgramType::pixelator: p.reset(new PixelatorMenuDialog); break;
      case ProgramType::pixelatorVcl: break;
      case ProgramType::pokeVolleyVcl: break;
      case ProgramType::preDickAdvocaTor: p.reset(new PreDickAdvocaTorMenuDialog); break;
      case ProgramType::primeExpert: p.reset(new PrimeExpertMenuDialog); break;
      case ProgramType::projectRichelBilderbeek: break;
      case ProgramType::pylos: p.reset(new pylos::MenuDialog); break;
      case ProgramType::qmakeWatcher: p.reset(new QmakeWatcherMenuDialog); break;
      case ProgramType::quadraticSolver: p.reset(new QuadraticSolverMenuDialog); break;
      case ProgramType::rampalEtienne: break;
      case ProgramType::randomCode: p.reset(new RandomCodeMenuDialog); break;
      case ProgramType::randomCodeVcl: break;
      case ProgramType::rasper: break;
      case ProgramType::refrigeratorPuzzleSolver: break;
      case ProgramType::regexTester: p.reset(new RegexTesterMenuDialog); break;
      case ProgramType::reversi: p.reset(new reversi::MenuDialog); break;
      case ProgramType::reversiVcl: break;
      case ProgramType::richelBilderbeekGallery: p.reset(new GalleryMenuDialog); break;
      case ProgramType::richelbilderbeekNlSitemapGenerator: p.reset(new SitemapGeneratorMenuDialog); break;
      case ProgramType::rubiksClock: p.reset(new ruco::MenuDialog); break;
      case ProgramType::rubiksClockVcl: break;
      case ProgramType::searchAndDestroyChess: p.reset(new sadc::MenuDialog); break;
      case ProgramType::searchAndDestroyChessVcl: break;
      case ProgramType::secretMessage: p.reset(new ribi::sema::MenuDialog); break;
      case ProgramType::secretMessageVcl: break;
      case ProgramType::simBrainiac: break;
      case ProgramType::simImmuneResponse: break;
      case ProgramType::simMysteryMachine: p.reset(new SimMysteryMachineMenuDialog); break;
      case ProgramType::simplifyNewick: p.reset(new ToolSimplifyNewickMenuDialog); break;
      case ProgramType::simPredatorVcl: break;
      case ProgramType::simStagecraft: break;
      case ProgramType::simTopPredatorPrey: p.reset(new ribi::SimTopPredatorPreyMenuDialog); break;
      case ProgramType::soaSim: break;
      case ProgramType::solvePuzzleX: break;
      case ProgramType::spaceHarryVcl: break;
      case ProgramType::staircaseCardCreator: break;
      case ProgramType::stateObserver: p.reset(new StateObserverMenuDialog); break;
      case ProgramType::stochasticityInspector: p.reset(new StochasticityInspectorMenuDialog); break;
      case ProgramType::styleSheetSetter: p.reset(new StyleSheetSetterMenuDialog); break;
      case ProgramType::surfacePlotter: p.reset(new SurfacePlotterMenuDialog); break;
      case ProgramType::surfacePlotterVcl: break;
      case ProgramType::tankBattalion: p.reset(new taba::MenuDialog); break;
      case ProgramType::testAbout: p.reset(new TestAboutMenuDialog); break;
      case ProgramType::testApproximator: p.reset(new ToolTestApproximatorMenuDialog); break;
      case ProgramType::testBinaryNewickVector: p.reset(new TestBinaryNewickVectorMenuDialog); break;
      case ProgramType::testBouncingBallsWidget: break;
      case ProgramType::testBouncingRectsWidget: break;
      case ProgramType::testBroadcastServer: break;
      case ProgramType::testChess: p.reset(new ribi::TestChessMenuDialog); break;
      case ProgramType::testConceptMap: p.reset(new TestConceptMapMenuDialog); break;
      case ProgramType::testDial: p.reset(new TestDialMenuDialog); break;
      case ProgramType::testDrawCanvas: p.reset(new TestDrawCanvasMenuDialog); break;
      case ProgramType::testEntrance: p.reset(new ToolTestEntrance::MenuDialog); break;
      case ProgramType::testExercise: p.reset(new TestExerciseMenuDialog); break;
      case ProgramType::testFunctionParser: p.reset(new TestFunctionParserMenuDialog); break;
      case ProgramType::testGnuplotInterface: break;
      case ProgramType::testGraphicsProxyWidget: break;
      case ProgramType::testGravityWidget: break;
      case ProgramType::testGroupWidget: p.reset(new TestGroupWidgetMenuDialog); break;
      case ProgramType::testHugeVector: break;
      case ProgramType::testImageCanvas: p.reset(new TestImageCanvasMenuDialog); break;
      case ProgramType::testLazy_init: break;
      case ProgramType::testLed: p.reset(new TestLedMenuDialog); break;
      case ProgramType::testManyDigitNewick: p.reset(new TestManyDigitNewickMenuDialog); break;
      case ProgramType::testMultiApproximator: p.reset(new ToolTestMultiApproximatorMenuDialog); break;
      case ProgramType::testMultiCanvas: p.reset(new TestMultiCanvasMenuDialog); break;
      case ProgramType::testMultipleChoiceQuestion: p.reset(new TestMultipleChoiceQuestionMenuDialog); break;
      case ProgramType::testMultiVector: p.reset(new TestMultiVectorMenuDialog); break;
      case ProgramType::testNdsmake: break;
      case ProgramType::testNeuralNet: break;
      case ProgramType::testNewick: p.reset(new TestNewickMenuDialog); break;
      case ProgramType::testNewickVector:
        //p.reset(new TestNewickVectorMenuDialog);
      break;
      case ProgramType::testOpenQuestion: p.reset(new TestOpenQuestionMenuDialog); break;
      case ProgramType::testPlane: p.reset(new TestPlaneMenuDialog); break;
      case ProgramType::testPolyFile: p.reset(new TestPolyFileMenuDialog); break;
      case ProgramType::testPolyFileFromPolygons: p.reset(new TestPolyFileFromPolygonsMenuDialog); break;
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
      case ProgramType::testQuestion: p.reset(new TestQuestionMenuDialog); break;
      case ProgramType::testReversi: break;
      case ProgramType::testSelectFileDialog: break;
      case ProgramType::testServerPusher: break;
      case ProgramType::testShape: p.reset(new TestShapeMenuDialog);break;
      case ProgramType::testShinyButton: p.reset(new TestShinyButtonMenuDialog); break;
      case ProgramType::testSimpleLinearRegression: p.reset(new ToolTestSimpleLinearRegressionMenuDialog); break;
      case ProgramType::testStopwatch: break;
      case ProgramType::testTextCanvas: p.reset(new TestTextCanvasMenuDialog); break;
      case ProgramType::testTextPositionWidget: break;
      case ProgramType::testTicTacToe: p.reset(new TestTicTacToeMenuDialog); break;
      case ProgramType::testTimedServerPusher: break;
      case ProgramType::testToggleButton: p.reset(new TestToggleButtonMenuDialog); break;
      case ProgramType::testTriangle: p.reset(new TestTriangleMenuDialog); break;
      case ProgramType::testTwoDigitNewick: p.reset(new TestTwoDigitNewickMenuDialog); break;
      case ProgramType::thorVeen: break;
      case ProgramType::thresholdFilterer: p.reset(new ThresholdFiltererMenuDialog); break;
      case ProgramType::thresholdFiltererVcl: break;
      case ProgramType::ticTacToe: p.reset(new tictactoe::TicTacToeMenuDialog); break;
      case ProgramType::timePoll: break;
      case ProgramType::triangleMeshCreator: p.reset(new TriangleMeshCreatorMenuDialog); break;
      case ProgramType::tronCollection: p.reset(new TronMenuDialog); break;
      case ProgramType::tronCollectionVcl: break;
      case ProgramType::ubuntuOneWatcher: break;
      case ProgramType::valentineCardDecrypter : p.reset(new ValentineCardDecrypterMenuDialog); break;
      case ProgramType::vigenereCipher: p.reset(new VigenereCipherMenuDialog); break;
      case ProgramType::virtualBastard: break;
      case ProgramType::visualAbc: p.reset(new VisualAbcMenuDialog); break;
      case ProgramType::wktToSvg: p.reset(new WktToSvgMenuDialog); break;
      case ProgramType::xeNonZero: p.reset(new XeNonZeroMenuDialog); break;
      case ProgramType::zork: break;
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
  return "1.20";
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
    "2014-08-14: Version 1.16: increased use of TDD in console version",
    "2014-08-17: Version 1.17: removed code-that-might-once-be-added",
    "2015-01-04: Version 1.18: made placeholder dialogs look nice",
    "2015-02-22: Version 1.19: after splitting codebase up in multiple GitHubs",
    "2015-05-24: Version 1.20: added multiple simulations",
    "2015-06-14: Version 1.21: removed placeholder dialogs, added some older code"
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
    assert(!m || !m->GetVersion().empty());
    assert(!m || !m->GetVersionHistory().empty());
    assert(!m || m->GetProgram());
  }
}
#endif
