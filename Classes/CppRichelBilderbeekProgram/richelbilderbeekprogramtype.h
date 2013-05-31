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
  asciiArter,
  barbaImage,
  beerWanter,
  bochum,
  boenken,
  chrisWiley,
  codeToHtml,
  connectThree,
  createGlossary,
  createQtProjectZipFile,
  createSitemap,
  crossPoll,
  dasWahreSchlagerfest,
  dotMatrix,
  encranger,
  filterOperationer,
  fryskLeareLieder,
  functionPlotter,
  gaborFilter,
  gnuplotInterface,
  grayCoder,
  gtst,
  histogramEqualizationer,
  hometrainer,
  imageRotater,
  k3OpEenRij,
  kalmanFilterer,
  keySender,
  kTouchLectureCreator,
  knokfighter,
  learyCircumplex,
  logisticGrowthSimulator,
  loose,
  mazeCreator,
  maziak,
  morpher,
  multiEncranger,
  muscaDomestica,
  musicTheory,
  ndsMake,
  pause,
  newickVector,
  paperRockScissors,
  perfectElasticCollision,
  picToCode,
  pixelator,
  pokeVolley,
  pylos,
  qmakeWatcher,
  quadraticSolver,
  randomCode,
  rasper,
  refrigeratorPuzzleSolver,
  regexTester,
  reversi,
  richelBilderbeekGallery,
  richelBilderbeekNlSitemapGenerator,
  rubiksClock,
  searchAndDestroyChess,
  secretMessage,
  simBrainiac,
  simImmuneResponse,
  simMysteryMachine,
  simplifyNewick,
  simStagecraft,
  soaSim,
  solvePuzzleX,
  spaceHarry,
  stateObserver,
  styleSheetSetter,
  surfacePlotter,
  testAbout,
  testBinaryNewickVector,
  //testBouncingBallsWidget,
  //testBouncingRectsWidget,
  testBroadcastServer,
  testChess,
  testDial,
  testEncranger,
  testEntrance,
  testExercise,
  testFunctionParser,
  //testGraphicsProxyWidget,
  //testGravityWidget,
  testGroupWidget,
  //testHugeVector,
  testLed,
  //testManyDigitNewick,
  testMultiVector,
  testNdsMake,
  testNeuralNet,
  //testNewick,
  //testNewickVector,
  testPrimeExpert,
  testPylos,
  testQrcFile,
  testQtArrowItems,
  testQtCreatorProFile,
  //testQtHideAndShowDialog,
  testQtKeyboardFriendlyGraphicsView,
  testQtModels,
  testQtRoundedEditRectItem,
  testQtRoundedRectItem,
  testQtRoundedTextRectItem,
  testQuestion,
  //testReversi,
  testSelectFile,
  testServerPusher,
  testShape,
  testShinyButton,
  testStopwatch,
  //testTextPositionWidget,
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
  twoDigitNewick,
  ubuntuOneWatcher,
  visualAbc,
  n_types //Used for debugging
};

std::vector<ProgramType> GetAllProgramTypes();

} //~namespace RichelBilderbeek {

#endif // RICHELBILDERBEEKPROGRAMTYPE_H
