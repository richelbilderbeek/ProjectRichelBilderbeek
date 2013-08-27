//---------------------------------------------------------------------------
/*
RichelBilderbeek::ProgramType, enum for a program by Richel Bilderbeek
Copyright (C 2013 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option any later version.

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
#ifndef RICHELBILDERBEEKPROGRAMTYPE_H
#define RICHELBILDERBEEKPROGRAMTYPE_H

#include <vector>

namespace RichelBilderbeek {

enum class ProgramType
{
  aminoAcidFighter,
  asciiArter,
  barbaImage,
  beerWanter,
  billysGarden,
  boenken,
  brainweaver,
  bristol,
  callstackCounter,
  chrisWiley,
  codeToHtml,
  connectThree,
  corridor,
  createGlossary,
  createQtProjectZipFile,
  dasWahreSchlagerfest,
  dotMatrix,
  everythingToPiecesShooter,
  fakeEvy,
  filterOperationer,
  filterOperationerWindowsOnly,
  fryskLeareLiederSource_1_0,
  functionPlotter,
  gaborFilter,
  gaborFilterWindowsOnly,
  grayCoder,
  gtst,
  histogramEqualizationer,
  hometrainer,
  hometrainer_1_9,
  hometrainer_exercises_French,
  hometrainerExerciseIronCarbonDiagram,
  hometrainerExerciseMilling,
  imageRotaterClx,
  imageRotaterVcl,
  k3OpEenRij,
  kalmanFilterer,
  keySender,
  knokfighter,
  knokfighterSource_1_0,
  kTouchLectureCreator,
  lambdaBot,
  learyCircumplex,
  logisticGrowthSimulator,
  loose,
  martianCafeTuinemaTycoonSource_1_0,
  mazeCreator,
  maziak,
  metZnDrieenSource_1_3,
  midiLessonCreator,
  morpher,
  multiEncranger,
  muscaDomestica,
  musicTheory,
  ndsmake,
  ndsPaint,
  paperRockScissors,
  pause,
  perfectElasticCollision,
  picToCode,
  pixelator,
  pokeVolleySource_2_0,
  pong,
  primeExpert,
  pylos,
  qmakeWatcher,
  quadraticSolver,
  rampal,
  randomCode,
  rasper,
  refrigeratorPuzzleSolver,
  regexTester,
  reversiConsoleSource_1_0,
  reversiSource_1_0,
  richelBilderbeek,
  richelBilderbeekGallery,
  richelbilderbeekNlSitemapGenerator,
  rubiksClock,
  searchAndDestroyChess,
  secretMessage,
  secretMessageVcl,
  simBrainiac,
  simImmuneResponse,
  simMysteryMachine,
  simplifyNewick,
  simPredatorSource_1_0,
  simStagecraft,
  soaSim,
  solvePuzzleX,
  spaceHarrySource_1_0,
  staircaseCardCreator,
  stateObserver,
  styleSheetSetter,
  superNsanaBros,
  surfacePlotter,
  surfacePlotterWindowsOnly,
  tankBattalion,
  testAbout,
  testApproximator,
  testBinaryNewickVector,
  testBouncingBallsWidget,
  testBouncingRectsWidget,
  testBroadcastServer,
  testCanvas,
  testChess,
  testDial,
  testEncranger,
  testEntrance,
  testExercise,
  testFunctionParser,
  testGnuplotInterface,
  testGraphicsProxyWidget,
  testGravityWidget,
  testGroupWidget,
  testHugeVector,
  testLazy_init,
  testLed,
  testManyDigitNewick,
  testMultiApproximator,
  testMultipleChoiceQuestion,
  testMultiVector,
  testNdsmake,
  testNeuralNet,
  testNewick,
  testNewickVector,
  testOpenQuestion,
  testPrimeExpert,
  testPylos,
  testQrcFile,
  testQtArrowItems,
  testQtCreatorProFile,
  testQtHideAndShowDialog,
  testQtKeyboardFriendlyGraphicsView,
  testQtModels,
  testQtOcrWidget,
  testQtRoundedEditRectItem,
  testQtRoundedRectItem,
  testQtRoundedTextRectItem,
  testQuestion,
  testReversi,
  testSelectFileDialog,
  testServerPusher,
  testShape,
  testShinyButton,
  testStopwatch,
  testTextPositionWidget,
  testTicTacToe,
  testTimedServerPusher,
  testToggleButton,
  testTwoDigitNewick,
  thorVeen,
  thresholdFilterer,
  ticTacToe,
  ticTacToeLearner,
  ticTacToeValuer,
  timePoll,
  tronCollection,
  tronCollection_0_9,
  ubuntuOneWatcher,
  vanDenBogaart,
  virtualBastard,
  visualAbc,
  xeNonZero,
  zork,

  n_types //Used for debugging
};

std::vector<ProgramType> GetAllProgramTypes();

} //~namespace RichelBilderbeek {

#endif // RICHELBILDERBEEKPROGRAMTYPE_H
