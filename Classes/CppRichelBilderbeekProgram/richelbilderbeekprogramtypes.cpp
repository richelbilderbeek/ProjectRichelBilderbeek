#include "richelbilderbeekprogramtypes.h"

#include "richelbilderbeekprogramtype.h"

#include <cassert>
#include "trace.h"

//Lazy initializion
boost::bimap<ribi::ProgramType,std::string> ribi::ProgramTypes::m_map_to_enumname {};
//Lazy initializion
boost::bimap<ribi::ProgramType,std::string> ribi::ProgramTypes::m_map_to_screenname {};

const boost::bimap<ribi::ProgramType,std::string> ribi::ProgramTypes::CreateEnumNameMap()
{
  #ifndef NDEBUG
  Test();
  #endif

  boost::bimap<ProgramType,std::string> m;
  typedef boost::bimap<ProgramType,std::string>::value_type Pair;
  ///Generated with Gnumeric:
  /// =CONCATENATE("m.insert(Pair(ProgramType::",A1,",std::string(\"",A1,"\")));")
  ///where A1 to Ax contain the programType enum values
  m.insert(Pair(ProgramType::aminoAcidFighter,std::string("aminoAcidFighter")));
  m.insert(Pair(ProgramType::athleticLand,std::string("athleticLand")));
  m.insert(Pair(ProgramType::athleticLandVcl,std::string("athleticLandVcl")));
  m.insert(Pair(ProgramType::asciiArter,std::string("asciiArter")));
  m.insert(Pair(ProgramType::barbaImage,std::string("barbaImage")));
  m.insert(Pair(ProgramType::beerWanter,std::string("beerWanter")));
  m.insert(Pair(ProgramType::bochum,std::string("bochum")));
  m.insert(Pair(ProgramType::boenken,std::string("boenken")));
  m.insert(Pair(ProgramType::brainweaver,std::string("brainweaver")));
  m.insert(Pair(ProgramType::bristol,std::string("bristol")));
  m.insert(Pair(ProgramType::chrisWiley,std::string("chrisWiley")));
  m.insert(Pair(ProgramType::codeToHtml,std::string("codeToHtml")));
  m.insert(Pair(ProgramType::connectThree,std::string("connectThree")));
  m.insert(Pair(ProgramType::corridor,std::string("corridor")));
  m.insert(Pair(ProgramType::createGlossary,std::string("createGlossary")));
  m.insert(Pair(ProgramType::createQtProjectZipFile,std::string("createQtProjectZipFile")));
  m.insert(Pair(ProgramType::crossPoll,std::string("crossPoll")));
  m.insert(Pair(ProgramType::dasWahreSchlagerfest,std::string("dasWahreSchlagerfest")));
  m.insert(Pair(ProgramType::dotMatrix,std::string("dotMatrix")));
  m.insert(Pair(ProgramType::encranger,std::string("encranger")));
  m.insert(Pair(ProgramType::everythingToPiecesShooter,std::string("everythingToPiecesShooter")));
  m.insert(Pair(ProgramType::fakeEvy,std::string("fakeEvy")));
  m.insert(Pair(ProgramType::filterOperationer,std::string("filterOperationer")));
  m.insert(Pair(ProgramType::filterOperationerVcl,std::string("filterOperationerVcl")));
  m.insert(Pair(ProgramType::fryskLeareLieder,std::string("fryskLeareLieder")));
  m.insert(Pair(ProgramType::functionPlotter,std::string("functionPlotter")));
  m.insert(Pair(ProgramType::gaborFilter,std::string("gaborFilter")));
  m.insert(Pair(ProgramType::grayCoder,std::string("grayCoder")));
  m.insert(Pair(ProgramType::gtst,std::string("gtst")));
  m.insert(Pair(ProgramType::histogramEqualizationer,std::string("histogramEqualizationer")));
  m.insert(Pair(ProgramType::histogramEqualizationerVcl,std::string("histogramEqualizationerVcl")));
  m.insert(Pair(ProgramType::hometrainer,std::string("hometrainer")));
  m.insert(Pair(ProgramType::imageRotater,std::string("imageRotater")));
  m.insert(Pair(ProgramType::imageRotaterClx,std::string("imageRotaterClx")));
  m.insert(Pair(ProgramType::imageRotaterVcl,std::string("imageRotaterVcl")));
  m.insert(Pair(ProgramType::k3OpEenRij,std::string("k3OpEenRij")));
  m.insert(Pair(ProgramType::kalmanFilterer,std::string("kalmanFilterer")));
  m.insert(Pair(ProgramType::keySender,std::string("keySender")));
  m.insert(Pair(ProgramType::knokfighter,std::string("knokfighter")));
  m.insert(Pair(ProgramType::kTouchLectureCreator,std::string("kTouchLectureCreator")));
  m.insert(Pair(ProgramType::lambdaBot,std::string("lambdaBot")));
  m.insert(Pair(ProgramType::learyCircumplex,std::string("learyCircumplex")));
  m.insert(Pair(ProgramType::logisticGrowthSimulator,std::string("logisticGrowthSimulator")));
  m.insert(Pair(ProgramType::loose,std::string("loose")));
  m.insert(Pair(ProgramType::martianCafeTuinemaTycoon,std::string("martianCafeTuinemaTycoon")));
  m.insert(Pair(ProgramType::mazeCreator,std::string("mazeCreator")));
  m.insert(Pair(ProgramType::maziak,std::string("maziak")));
  m.insert(Pair(ProgramType::metZnDrieen,std::string("metZnDrieen")));
  m.insert(Pair(ProgramType::midiLessonCreator,std::string("midiLessonCreator")));
  m.insert(Pair(ProgramType::morpher,std::string("morpher")));
  m.insert(Pair(ProgramType::multiEncranger,std::string("multiEncranger")));
  m.insert(Pair(ProgramType::muscaDomestica,std::string("muscaDomestica")));
  m.insert(Pair(ProgramType::musicTheory,std::string("musicTheory")));
  m.insert(Pair(ProgramType::ndsmake,std::string("ndsmake")));
  m.insert(Pair(ProgramType::ndsPaint,std::string("ndsPaint")));
  m.insert(Pair(ProgramType::paperRockScissors,std::string("paperRockScissors")));
  m.insert(Pair(ProgramType::pause,std::string("pause")));
  m.insert(Pair(ProgramType::perfectElasticCollision,std::string("perfectElasticCollision")));
  m.insert(Pair(ProgramType::picToCode,std::string("picToCode")));
  m.insert(Pair(ProgramType::pixelator,std::string("pixelator")));
  m.insert(Pair(ProgramType::pixelatorVcl,std::string("pixelatorVcl")));
  m.insert(Pair(ProgramType::pokeVolley,std::string("pokeVolley")));
  m.insert(Pair(ProgramType::pong,std::string("pong")));
  m.insert(Pair(ProgramType::primeExpert,std::string("primeExpert")));
  m.insert(Pair(ProgramType::projectRichelBilderbeek,std::string("projectRichelBilderbeek")));
  m.insert(Pair(ProgramType::pylos,std::string("pylos")));
  m.insert(Pair(ProgramType::qmakeWatcher,std::string("qmakeWatcher")));
  m.insert(Pair(ProgramType::quadraticSolver,std::string("quadraticSolver")));
  m.insert(Pair(ProgramType::rampal,std::string("rampal")));
  m.insert(Pair(ProgramType::randomCode,std::string("randomCode")));
  m.insert(Pair(ProgramType::rasper,std::string("rasper")));
  m.insert(Pair(ProgramType::refrigeratorPuzzleSolver,std::string("refrigeratorPuzzleSolver")));
  m.insert(Pair(ProgramType::regexTester,std::string("regexTester")));
  m.insert(Pair(ProgramType::reversi,std::string("reversi")));
  m.insert(Pair(ProgramType::richelBilderbeekGallery,std::string("richelBilderbeekGallery")));
  m.insert(Pair(ProgramType::richelbilderbeekNlSitemapGenerator,std::string("richelbilderbeekNlSitemapGenerator")));
  m.insert(Pair(ProgramType::rubiksClock,std::string("rubiksClock")));
  m.insert(Pair(ProgramType::searchAndDestroyChess,std::string("searchAndDestroyChess")));
  m.insert(Pair(ProgramType::secretMessage,std::string("secretMessage")));
  m.insert(Pair(ProgramType::simBrainiac,std::string("simBrainiac")));
  m.insert(Pair(ProgramType::simImmuneResponse,std::string("simImmuneResponse")));
  m.insert(Pair(ProgramType::simMysteryMachine,std::string("simMysteryMachine")));
  m.insert(Pair(ProgramType::simplifyNewick,std::string("simplifyNewick")));
  m.insert(Pair(ProgramType::simPredator,std::string("simPredator")));
  m.insert(Pair(ProgramType::simStagecraft,std::string("simStagecraft")));
  m.insert(Pair(ProgramType::soaSim,std::string("soaSim")));
  m.insert(Pair(ProgramType::solvePuzzleX,std::string("solvePuzzleX")));
  m.insert(Pair(ProgramType::spaceHarry,std::string("spaceHarry")));
  m.insert(Pair(ProgramType::staircaseCardCreator,std::string("staircaseCardCreator")));
  m.insert(Pair(ProgramType::stateObserver,std::string("stateObserver")));
  m.insert(Pair(ProgramType::styleSheetSetter,std::string("styleSheetSetter")));
  m.insert(Pair(ProgramType::superNsanaBros,std::string("superNsanaBros")));
  m.insert(Pair(ProgramType::surfacePlotter,std::string("surfacePlotter")));
  m.insert(Pair(ProgramType::tankBattalion,std::string("tankBattalion")));
  m.insert(Pair(ProgramType::testAbout,std::string("testAbout")));
  m.insert(Pair(ProgramType::testApproximator,std::string("testApproximator")));
  m.insert(Pair(ProgramType::testBinaryNewickVector,std::string("testBinaryNewickVector")));
  m.insert(Pair(ProgramType::testBouncingBallsWidget,std::string("testBouncingBallsWidget")));
  m.insert(Pair(ProgramType::testBouncingRectsWidget,std::string("testBouncingRectsWidget")));
  m.insert(Pair(ProgramType::testBroadcastServer,std::string("testBroadcastServer")));
  m.insert(Pair(ProgramType::testCanvas,std::string("testCanvas")));
  m.insert(Pair(ProgramType::testChess,std::string("testChess")));
  m.insert(Pair(ProgramType::testDial,std::string("testDial")));
  m.insert(Pair(ProgramType::testEntrance,std::string("testEntrance")));
  m.insert(Pair(ProgramType::testExercise,std::string("testExercise")));
  m.insert(Pair(ProgramType::testFunctionParser,std::string("testFunctionParser")));
  m.insert(Pair(ProgramType::testGnuplotInterface,std::string("testGnuplotInterface")));
  m.insert(Pair(ProgramType::testGraphicsProxyWidget,std::string("testGraphicsProxyWidget")));
  m.insert(Pair(ProgramType::testGravityWidget,std::string("testGravityWidget")));
  m.insert(Pair(ProgramType::testGroupWidget,std::string("testGroupWidget")));
  m.insert(Pair(ProgramType::testHugeVector,std::string("testHugeVector")));
  m.insert(Pair(ProgramType::testLazy_init,std::string("testLazy_init")));
  m.insert(Pair(ProgramType::testLed,std::string("testLed")));
  m.insert(Pair(ProgramType::testManyDigitNewick,std::string("testManyDigitNewick")));
  m.insert(Pair(ProgramType::testMultiApproximator,std::string("testMultiApproximator")));
  m.insert(Pair(ProgramType::testMultipleChoiceQuestion,std::string("testMultipleChoiceQuestion")));
  m.insert(Pair(ProgramType::testMultiVector,std::string("testMultiVector")));
  m.insert(Pair(ProgramType::testNdsmake,std::string("testNdsmake")));
  m.insert(Pair(ProgramType::testNeuralNet,std::string("testNeuralNet")));
  m.insert(Pair(ProgramType::testNewick,std::string("testNewick")));
  m.insert(Pair(ProgramType::testNewickVector,std::string("testNewickVector")));
  m.insert(Pair(ProgramType::testOpenQuestion,std::string("testOpenQuestion")));
  m.insert(Pair(ProgramType::testPylos,std::string("testPylos")));
  m.insert(Pair(ProgramType::testQrcFile,std::string("testQrcFile")));
  m.insert(Pair(ProgramType::testQtArrowItems,std::string("testQtArrowItems")));
  m.insert(Pair(ProgramType::testQtCreatorProFile,std::string("testQtCreatorProFile")));
  m.insert(Pair(ProgramType::testQtHideAndShowDialog,std::string("testQtHideAndShowDialog")));
  m.insert(Pair(ProgramType::testQtKeyboardFriendlyGraphicsView,std::string("testQtKeyboardFriendlyGraphicsView")));
  m.insert(Pair(ProgramType::testQtModels,std::string("testQtModels")));
  m.insert(Pair(ProgramType::testQtOcrWidget,std::string("testQtOcrWidget")));
  m.insert(Pair(ProgramType::testQtRoundedEditRectItem,std::string("testQtRoundedEditRectItem")));
  m.insert(Pair(ProgramType::testQtRoundedRectItem,std::string("testQtRoundedRectItem")));
  m.insert(Pair(ProgramType::testQtRoundedTextRectItem,std::string("testQtRoundedTextRectItem")));
  m.insert(Pair(ProgramType::testQuestion,std::string("testQuestion")));
  m.insert(Pair(ProgramType::testReversi,std::string("testReversi")));
  m.insert(Pair(ProgramType::testSelectFileDialog,std::string("testSelectFileDialog")));
  m.insert(Pair(ProgramType::testServerPusher,std::string("testServerPusher")));
  m.insert(Pair(ProgramType::testShape,std::string("testShape")));
  m.insert(Pair(ProgramType::testShinyButton,std::string("testShinyButton")));
  m.insert(Pair(ProgramType::testSimpleLinearRegression,std::string("testSimpleLinearRegression")));
  m.insert(Pair(ProgramType::testStopwatch,std::string("testStopwatch")));
  m.insert(Pair(ProgramType::testTextPositionWidget,std::string("testTextPositionWidget")));
  m.insert(Pair(ProgramType::testTicTacToe,std::string("testTicTacToe")));
  m.insert(Pair(ProgramType::testTimedServerPusher,std::string("testTimedServerPusher")));
  m.insert(Pair(ProgramType::testToggleButton,std::string("testToggleButton")));
  m.insert(Pair(ProgramType::testTwoDigitNewick,std::string("testTwoDigitNewick")));
  m.insert(Pair(ProgramType::thorVeen,std::string("thorVeen")));
  m.insert(Pair(ProgramType::thresholdFilterer,std::string("thresholdFilterer")));
  m.insert(Pair(ProgramType::thresholdFiltererVcl,std::string("thresholdFiltererVcl")));
  m.insert(Pair(ProgramType::ticTacToe,std::string("ticTacToe")));
  m.insert(Pair(ProgramType::ticTacToeLearner,std::string("ticTacToeLearner")));
  m.insert(Pair(ProgramType::ticTacToeValuer,std::string("ticTacToeValuer")));
  m.insert(Pair(ProgramType::timePoll,std::string("timePoll")));
  m.insert(Pair(ProgramType::tronCollection,std::string("tronCollection")));
  m.insert(Pair(ProgramType::ubuntuOneWatcher,std::string("ubuntuOneWatcher")));
  m.insert(Pair(ProgramType::vanDenBogaart,std::string("vanDenBogaart")));
  m.insert(Pair(ProgramType::virtualBastard,std::string("virtualBastard")));
  m.insert(Pair(ProgramType::visualAbc,std::string("visualAbc")));
  m.insert(Pair(ProgramType::xeNonZero,std::string("xeNonZero")));
  m.insert(Pair(ProgramType::zork,std::string("zork")));
  assert(m.left.size() == m.right.size());
  #ifndef NDEBUG
  if (static_cast<int>(m.left.size()) != static_cast<int>(ProgramType::n_types))
  {
    TRACE(m.left.size());
    TRACE(static_cast<int>(ProgramType::n_types));
    TRACE("Copy the contents of ProgramType (except n_types) to above here");
  }
  #endif
  assert(static_cast<int>(m.left.size()) == static_cast<int>(ProgramType::n_types));
  return m;
}

const boost::bimap<ribi::ProgramType,std::string> ribi::ProgramTypes::CreateScreenNameMap()
{
  #ifndef NDEBUG
  Test();
  #endif

  boost::bimap<ProgramType,std::string> m;
  typedef boost::bimap<ProgramType,std::string>::value_type Pair;
  ///Generated with Gnumeric:
  /// =CONCATENATE("m.insert(Pair(ProgramType::",A1,",std::string(\"",A1,"\")));")
  ///where A1 to Ax contain the programType enum values
  m.insert(Pair(ProgramType::aminoAcidFighter,std::string("Amino Acid Fighter")));
  m.insert(Pair(ProgramType::asciiArter,std::string("AsciiArter")));
  m.insert(Pair(ProgramType::athleticLand,std::string("Athletic Land")));
  m.insert(Pair(ProgramType::athleticLandVcl,std::string("Athletic Land (VCL)")));
  m.insert(Pair(ProgramType::barbaImage,std::string("BarbaImage")));
  m.insert(Pair(ProgramType::beerWanter,std::string("BeerWanter")));
  m.insert(Pair(ProgramType::bochum,std::string("Bochum")));
  m.insert(Pair(ProgramType::boenken,std::string("Boenken")));
  m.insert(Pair(ProgramType::brainweaver,std::string("Brainweaver")));
  m.insert(Pair(ProgramType::bristol,std::string("Bristol")));
  m.insert(Pair(ProgramType::chrisWiley,std::string("Chris Wiley")));
  m.insert(Pair(ProgramType::codeToHtml,std::string("CodeToHtml")));
  m.insert(Pair(ProgramType::connectThree,std::string("ConnectThree")));
  m.insert(Pair(ProgramType::corridor,std::string("Corridor")));
  m.insert(Pair(ProgramType::createGlossary,std::string("CreateGlossary")));
  m.insert(Pair(ProgramType::createQtProjectZipFile,std::string("CreateQtProjectZipFile")));
  m.insert(Pair(ProgramType::crossPoll,std::string("CrossPoll")));
  m.insert(Pair(ProgramType::dasWahreSchlagerfest,std::string("Das Wahre Schlagerfest")));
  m.insert(Pair(ProgramType::dotMatrix,std::string("DotMatrix")));
  m.insert(Pair(ProgramType::encranger,std::string("Encranger")));
  m.insert(Pair(ProgramType::everythingToPiecesShooter,std::string("EverythingToPiecesShooter")));
  m.insert(Pair(ProgramType::fakeEvy,std::string("Fake Evy")));
  m.insert(Pair(ProgramType::filterOperationer,std::string("FilterOperationer")));
  m.insert(Pair(ProgramType::filterOperationerVcl,std::string("FilterOperationer (VCL)")));
  m.insert(Pair(ProgramType::fryskLeareLieder,std::string("Frysk Leare Lieder")));
  m.insert(Pair(ProgramType::functionPlotter,std::string("FunctionPlotter")));
  m.insert(Pair(ProgramType::gaborFilter,std::string("GaborFilter")));
  m.insert(Pair(ProgramType::grayCoder,std::string("GrayCoder")));
  m.insert(Pair(ProgramType::gtst,std::string("GTST")));
  m.insert(Pair(ProgramType::histogramEqualizationer,std::string("HistogramEqualizationer")));
  m.insert(Pair(ProgramType::histogramEqualizationerVcl,std::string("HistogramEqualizationer (VCL)")));
  m.insert(Pair(ProgramType::hometrainer,std::string("Hometrainer")));
  m.insert(Pair(ProgramType::imageRotater,std::string("ImageRotater")));
  m.insert(Pair(ProgramType::imageRotaterClx,std::string("ImageRotater (CLX)")));
  m.insert(Pair(ProgramType::imageRotaterVcl,std::string("ImageRotater (VCL)")));
  m.insert(Pair(ProgramType::k3OpEenRij,std::string("K3 Op Een Rij")));
  m.insert(Pair(ProgramType::kalmanFilterer,std::string("KalmanFilterer")));
  m.insert(Pair(ProgramType::keySender,std::string("KeySender")));
  m.insert(Pair(ProgramType::knokfighter,std::string("Knokfighter")));
  m.insert(Pair(ProgramType::kTouchLectureCreator,std::string("KTouch Lecture Creator")));
  m.insert(Pair(ProgramType::lambdaBot,std::string("LambdaBot")));
  m.insert(Pair(ProgramType::learyCircumplex,std::string("LearyCircumplex")));
  m.insert(Pair(ProgramType::logisticGrowthSimulator,std::string("LogisticGrowthSimulator")));
  m.insert(Pair(ProgramType::loose,std::string("Loose")));
  m.insert(Pair(ProgramType::martianCafeTuinemaTycoon,std::string("MartianCafeTuinemaTycoon")));
  m.insert(Pair(ProgramType::mazeCreator,std::string("MazeCreator")));
  m.insert(Pair(ProgramType::maziak,std::string("Maziak")));
  m.insert(Pair(ProgramType::metZnDrieen,std::string("Met Z'n Drieen")));
  m.insert(Pair(ProgramType::midiLessonCreator,std::string("MIDI Lesson Creator")));
  m.insert(Pair(ProgramType::morpher,std::string("Morpher")));
  m.insert(Pair(ProgramType::multiEncranger,std::string("MultiEncranger")));
  m.insert(Pair(ProgramType::muscaDomestica,std::string("MuscaDomestica")));
  m.insert(Pair(ProgramType::musicTheory,std::string("MusicTheory")));
  m.insert(Pair(ProgramType::ndsmake,std::string("ndsmake")));
  m.insert(Pair(ProgramType::ndsPaint,std::string("NDS Paint")));
  m.insert(Pair(ProgramType::paperRockScissors,std::string("PaperRockScissors")));
  m.insert(Pair(ProgramType::pause,std::string("Pause")));
  m.insert(Pair(ProgramType::perfectElasticCollision,std::string("PerfectElasticCollision")));
  m.insert(Pair(ProgramType::picToCode,std::string("PicToCode")));
  m.insert(Pair(ProgramType::pixelator,std::string("Pixelator")));
  m.insert(Pair(ProgramType::pixelatorVcl,std::string("Pixelator (VCL)")));
  m.insert(Pair(ProgramType::pokeVolley,std::string("PokeVolley")));
  m.insert(Pair(ProgramType::pong,std::string("Pong")));
  m.insert(Pair(ProgramType::primeExpert,std::string("PrimeExpert")));
  m.insert(Pair(ProgramType::projectRichelBilderbeek,std::string("ProjectRichelBilderbeek")));
  m.insert(Pair(ProgramType::pylos,std::string("Pylos")));
  m.insert(Pair(ProgramType::qmakeWatcher,std::string("qmake Watcher")));
  m.insert(Pair(ProgramType::quadraticSolver,std::string("QuadraticSolver")));
  m.insert(Pair(ProgramType::rampal,std::string("Rampal")));
  m.insert(Pair(ProgramType::randomCode,std::string("RandomCode")));
  m.insert(Pair(ProgramType::rasper,std::string("Rasper")));
  m.insert(Pair(ProgramType::refrigeratorPuzzleSolver,std::string("RefrigeratorPuzzleSolver")));
  m.insert(Pair(ProgramType::regexTester,std::string("RegexTester")));
  m.insert(Pair(ProgramType::reversi,std::string("Reversi")));
  m.insert(Pair(ProgramType::richelBilderbeekGallery,std::string("RichelBilderbeekGallery")));
  m.insert(Pair(ProgramType::richelbilderbeekNlSitemapGenerator,std::string("RichelbilderbeekNlSitemapGenerator")));
  m.insert(Pair(ProgramType::rubiksClock,std::string("Rubik's Clock")));
  m.insert(Pair(ProgramType::searchAndDestroyChess,std::string("SearchAndDestroyChess")));
  m.insert(Pair(ProgramType::secretMessage,std::string("SecretMessage")));
  m.insert(Pair(ProgramType::simBrainiac,std::string("SimBrainiac")));
  m.insert(Pair(ProgramType::simImmuneResponse,std::string("SimImmuneResponse")));
  m.insert(Pair(ProgramType::simMysteryMachine,std::string("SimMysteryMachine")));
  m.insert(Pair(ProgramType::simplifyNewick,std::string("SimplifyNewick")));
  m.insert(Pair(ProgramType::simPredator,std::string("SimPredator")));
  m.insert(Pair(ProgramType::simStagecraft,std::string("SimStagecraft")));
  m.insert(Pair(ProgramType::soaSim,std::string("SoaSim")));
  m.insert(Pair(ProgramType::solvePuzzleX,std::string("SolvePuzzleX")));
  m.insert(Pair(ProgramType::spaceHarry,std::string("SpaceHarry")));
  m.insert(Pair(ProgramType::staircaseCardCreator,std::string("StaircaseCardCreator")));
  m.insert(Pair(ProgramType::stateObserver,std::string("StateObserver")));
  m.insert(Pair(ProgramType::styleSheetSetter,std::string("StyleSheetSetter")));
  m.insert(Pair(ProgramType::superNsanaBros,std::string("Super Nsana Bros")));
  m.insert(Pair(ProgramType::surfacePlotter,std::string("SurfacePlotter")));
  m.insert(Pair(ProgramType::tankBattalion,std::string("Tank Battalion")));
  m.insert(Pair(ProgramType::testAbout,std::string("Test About")));
  m.insert(Pair(ProgramType::testApproximator,std::string("Test Approximator")));
  m.insert(Pair(ProgramType::testBinaryNewickVector,std::string("Test BinaryNewickVector")));
  m.insert(Pair(ProgramType::testBouncingBallsWidget,std::string("Test BouncingBallsWidget")));
  m.insert(Pair(ProgramType::testBouncingRectsWidget,std::string("Test BouncingRectsWidget")));
  m.insert(Pair(ProgramType::testBroadcastServer,std::string("Test BroadcastServer")));
  m.insert(Pair(ProgramType::testCanvas,std::string("Test Canvas")));
  m.insert(Pair(ProgramType::testChess,std::string("Test Chess")));
  m.insert(Pair(ProgramType::testDial,std::string("Test Dial")));
  m.insert(Pair(ProgramType::testEntrance,std::string("Test Entrance")));
  m.insert(Pair(ProgramType::testExercise,std::string("Test Exercise")));
  m.insert(Pair(ProgramType::testFunctionParser,std::string("Test FunctionParser")));
  m.insert(Pair(ProgramType::testGnuplotInterface,std::string("Test GnuplotInterface")));
  m.insert(Pair(ProgramType::testGraphicsProxyWidget,std::string("Test GraphicsProxyWidget")));
  m.insert(Pair(ProgramType::testGravityWidget,std::string("Test GravityWidget")));
  m.insert(Pair(ProgramType::testGroupWidget,std::string("Test GroupWidget")));
  m.insert(Pair(ProgramType::testHugeVector,std::string("Test HugeVector")));
  m.insert(Pair(ProgramType::testLazy_init,std::string("Test Lazy_init")));
  m.insert(Pair(ProgramType::testLed,std::string("Test Led")));
  m.insert(Pair(ProgramType::testManyDigitNewick,std::string("Test ManyDigitNewick")));
  m.insert(Pair(ProgramType::testMultiApproximator,std::string("Test MultiApproximator")));
  m.insert(Pair(ProgramType::testMultipleChoiceQuestion,std::string("Test MultipleChoiceQuestion")));
  m.insert(Pair(ProgramType::testMultiVector,std::string("Test MultiVector")));
  m.insert(Pair(ProgramType::testNdsmake,std::string("Test ndsmake")));
  m.insert(Pair(ProgramType::testNeuralNet,std::string("Test NeuralNet")));
  m.insert(Pair(ProgramType::testNewick,std::string("Test Newick")));
  m.insert(Pair(ProgramType::testNewickVector,std::string("Test NewickVector")));
  m.insert(Pair(ProgramType::testOpenQuestion,std::string("Test OpenQuestion")));
  m.insert(Pair(ProgramType::testPylos,std::string("Test Pylos")));
  m.insert(Pair(ProgramType::testQrcFile,std::string("Test QrcFile")));
  m.insert(Pair(ProgramType::testQtArrowItems,std::string("Test QtArrowItems")));
  m.insert(Pair(ProgramType::testQtCreatorProFile,std::string("Test QtCreatorProFile")));
  m.insert(Pair(ProgramType::testQtHideAndShowDialog,std::string("Test QtHideAndShowDialog")));
  m.insert(Pair(ProgramType::testQtKeyboardFriendlyGraphicsView,std::string("Test QtKeyboardFriendlyGraphicsView")));
  m.insert(Pair(ProgramType::testQtModels,std::string("Test QtModels")));
  m.insert(Pair(ProgramType::testQtOcrWidget,std::string("Test QtOcrWidget")));
  m.insert(Pair(ProgramType::testQtRoundedEditRectItem,std::string("Test QtRoundedEditRectItem")));
  m.insert(Pair(ProgramType::testQtRoundedRectItem,std::string("Test QtRoundedRectItem")));
  m.insert(Pair(ProgramType::testQtRoundedTextRectItem,std::string("Test QtRoundedTextRectItem")));
  m.insert(Pair(ProgramType::testQuestion,std::string("Test Question")));
  m.insert(Pair(ProgramType::testReversi,std::string("Test Reversi")));
  m.insert(Pair(ProgramType::testSelectFileDialog,std::string("Test SelectFileDialog")));
  m.insert(Pair(ProgramType::testServerPusher,std::string("Test ServerPusher")));
  m.insert(Pair(ProgramType::testShape,std::string("Test Shape")));
  m.insert(Pair(ProgramType::testShinyButton,std::string("Test ShinyButton")));
  m.insert(Pair(ProgramType::testSimpleLinearRegression,std::string("Test SimpleLinearRegression")));
  m.insert(Pair(ProgramType::testStopwatch,std::string("Test Stopwatch")));
  m.insert(Pair(ProgramType::testTextPositionWidget,std::string("Test TextPositionWidget")));
  m.insert(Pair(ProgramType::testTicTacToe,std::string("Test TicTacToe")));
  m.insert(Pair(ProgramType::testTimedServerPusher,std::string("Test TimedServerPusher")));
  m.insert(Pair(ProgramType::testToggleButton,std::string("Test ToggleButton")));
  m.insert(Pair(ProgramType::testTwoDigitNewick,std::string("Test TwoDigitNewick")));
  m.insert(Pair(ProgramType::thorVeen,std::string("Thor Veen")));
  m.insert(Pair(ProgramType::thresholdFilterer,std::string("ThresholdFilterer")));
  m.insert(Pair(ProgramType::thresholdFiltererVcl,std::string("ThresholdFilterer (VCL)")));
  m.insert(Pair(ProgramType::ticTacToe,std::string("TicTacToe")));
  m.insert(Pair(ProgramType::ticTacToeLearner,std::string("TicTacToe Learner")));
  m.insert(Pair(ProgramType::ticTacToeValuer,std::string("TicTacToe Valuer")));
  m.insert(Pair(ProgramType::timePoll,std::string("TimePoll")));
  m.insert(Pair(ProgramType::tronCollection,std::string("Tron Collection")));
  m.insert(Pair(ProgramType::ubuntuOneWatcher,std::string("UbuntuOne Watcher")));
  m.insert(Pair(ProgramType::vanDenBogaart,std::string("Van Den Bogaart")));
  m.insert(Pair(ProgramType::virtualBastard,std::string("Virtual Bastard")));
  m.insert(Pair(ProgramType::visualAbc,std::string("Visual ABC")));
  m.insert(Pair(ProgramType::xeNonZero,std::string("XeNonZero")));
  m.insert(Pair(ProgramType::zork,std::string("Zork")));
  assert(m.left.size() == m.right.size());
  #ifndef NDEBUG
  if (static_cast<int>(m.left.size()) != static_cast<int>(ProgramType::n_types))
  {
    TRACE(m.left.size());
    TRACE(static_cast<int>(ProgramType::n_types));
    TRACE("Copy the contents of ProgramType (except n_types) to above here");
  }
  #endif
  assert(static_cast<int>(m.left.size()) == static_cast<int>(ProgramType::n_types));
  return m;
}

const std::vector<std::string>
  ribi::ProgramTypes::GetAllEnumNames() noexcept
{
  if (m_map_to_enumname.right.empty()) { m_map_to_enumname = CreateEnumNameMap(); }
  assert(!m_map_to_enumname.right.empty());

  //Copy right map of bimap
  std::vector<std::string> v;
  for (auto t: m_map_to_enumname.right) { v.push_back(t.first); }
  assert(!v.empty());
  assert(m_map_to_enumname.right.size() == v.size());
  return v;
}

const std::vector<std::string>
  ribi::ProgramTypes::GetAllScreenNames() noexcept
{
  if (m_map_to_screenname.right.empty()) { m_map_to_screenname = CreateScreenNameMap(); }
  assert(!m_map_to_screenname.right.empty());

  //Copy right map of bimap
  std::vector<std::string> v;
  for (auto t: m_map_to_screenname.right) { v.push_back(t.first); }
  assert(!v.empty());
  assert(m_map_to_screenname.right.size() == v.size());
  return v;
}

const std::vector<ribi::ProgramType>
  ribi::ProgramTypes::GetAll() noexcept
{
  if (m_map_to_enumname.left.empty()) { m_map_to_enumname = CreateEnumNameMap(); }
  assert(!m_map_to_enumname.left.empty());

  //Copy left map of bimap
  std::vector<ProgramType> v;
  for (auto t: m_map_to_enumname.left) { v.push_back(t.first); }
  assert(!v.empty());
  assert(m_map_to_enumname.left.size() == v.size());
  return v;
}

const std::string ribi::ProgramTypes::ProgramTypeToEnumName(const ProgramType t) noexcept
{
  if (m_map_to_enumname.left.empty()) { m_map_to_enumname = CreateEnumNameMap(); }
  assert(m_map_to_enumname.left.find(t) != m_map_to_enumname.left.end());
  return m_map_to_enumname.left.find(t)->second;
}

const std::string ribi::ProgramTypes::ProgramTypeToScreenName(const ProgramType t) noexcept
{
  if (m_map_to_screenname.left.empty()) { m_map_to_screenname = CreateEnumNameMap(); }
  assert(m_map_to_screenname.left.find(t) != m_map_to_screenname.left.end());
  return m_map_to_screenname.left.find(t)->second;
}

#ifndef NDEBUG
void ribi::ProgramTypes::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Started ribi::ProgramTypes::Test");
  assert(GetAll().size() == GetAllEnumNames().size());
  assert(GetAll().size() == GetAllScreenNames().size());
  TRACE("Finished ribi::ProgramTypes::Test successfully");
}
#endif
