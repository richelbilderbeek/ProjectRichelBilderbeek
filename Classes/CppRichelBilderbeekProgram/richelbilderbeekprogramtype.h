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
  chrisWiley,
  codeToHtml,
  connectThree,
  corridor,
  createGlossary,
  createQtZipFile,
  dasWahreSchlagerfest,
  everythingToPiecesShooter,
  fakeEvy,
  filterOperationer,
  filterOperationerWindowsOnly,
  fryskLeareLieder,
  gaborFilter,
  gtst,
  hometrainer,
  k3OpEenRij,
  kalmanFilterer,
  keySender,
  knokfighter,
  kTouchLectureCreator,
  lambdaBot,
  loose,
  martianCafeTuinemaTycoon,
  mazeCreator,
  maziak,
  metZnDrieenSource_1_3,
  midiLessonCreator,
  multiEncranger,
  muscaDomestica,
  musicTheory,
  ndsmake,
  ndsPaint,
  paperRockScissors,
  pause,
  perfectElasticCollision,
  picToCode,
  pokeVolleySource_2_0,
  pong,
  primeExpert,
  pylos,
  qmakeWatcher,
  rampal,
  randomCode,
  rasper,
  regexTester,
  reversiConsole,
  reversi,
  richelBilderbeekGallery,
  richelbilderbeekNlSitemapGenerator,
  rubiksClock,
  searchAndDestroyChess,
  secretMessage,
  simMysteryMachine,
  simplifyNewick,
  simPredator,
  soaSim,
  solvePuzzleX,
  spaceHarry,
  staircaseCardCreator,
  stateObserver,
  styleSheetSetter,
  superNsanaBros,
  surfacePlotter,
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
  ticTacToe,
  ticTacToeLearner,
  ticTacToeValuer,
  timePoll,
  tronCollection,
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
