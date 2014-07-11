//---------------------------------------------------------------------------
/*
  SearchAndDestroyChess, a special kind of chess game
  Copyright (C) 2008  Richel Bilderbeek

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#include <string>
#include <iostream>
#include "UnitChessGame.h"
#include "UnitEnumChessPieceColor.h"
#include "UnitEnumChessPieceType.h"
#include "UnitChessPiece.h"

#pragma hdrstop

//---------------------------------------------------------------------------
//From http://www.richelbilderbeek/CppAskUserForString.htm
const std::string AskUserForString()
{
  std::string s;
  std::getline(std::cin,s);
  return s;
}
//---------------------------------------------------------------------------
const bool AskUserForYesNo()
{
  while (1)
  {
    const std::string s = AskUserForString();
    if (s.empty()==true) continue;
    if (s[0] == 'y' || s[0] == 'Y' || s == "yes" || s == "Yes" || s == "YES") return true;
    if (s[0] == 'n' || s[0] == 'N' || s == "no" || s == "No" || s == "NO")    return false;
  }
}
//---------------------------------------------------------------------------
void ClearScreen()
{
  //'clear' the screen
  for (int i=0; i!=50; ++i) std::cout << std::endl;
}
//---------------------------------------------------------------------------
void ShowLicence()
{
  std::cout
    << std::string(79,'*') << std::endl
    << "LICENCE" << std::endl
    << std::endl
    << "SearchAndDestroyChess, a special kind of chess game" << std::endl
    << "Copyright (C) 2008  Richel Bilderbeek" << std::endl
    << std::endl
    << "This program is free software: you can redistribute it and/or modify" << std::endl
    << "it under the terms of the GNU General Public License as published by" << std::endl
    << "the Free Software Foundation, either version 3 of the License, or" << std::endl
    << "(at your option) any later version." << std::endl
    << std::endl
    << "This program is distributed in the hope that it will be useful," << std::endl
    << "but WITHOUT ANY WARRANTY; without even the implied warranty of" << std::endl
    << "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the" << std::endl
    << "GNU General Public License for more details." << std::endl
    << "You should have received a copy of the GNU General Public License" << std::endl
    << "along with this program.  If not, see <http://www.gnu.org/licenses/>." << std::endl
    << std::string(79,'*') << std::endl
    << "Programmed at the 4th, 5th and 6th July 2008" << std::endl
    << "by Richel Bilderbeek" << std::endl
    << "http://www.richelbilderbeek.nl"
    << std::endl;
}

#pragma argsused
int main()
{
  ShowLicence();

  std::cout
    << std::string(79,'*')
    << std::endl
    << "Welcome to Search And Destroy Chess."
    << std::endl
    << "White player, please"
    << std::endl
    << "press any key to start the game"
    << std::endl;
  AskUserForString();

  ClearScreen();

  std::cout << "Is player #1 (white) a human player (y/n) ?" << std::endl;
  const bool isPlayerOneHuman = AskUserForYesNo();
  std::cout << "Is player #2 (black) a human player (y/n) ?" << std::endl;
  const bool isPlayerTwoHuman = AskUserForYesNo();


  ChessGame game;
  while(1)
  {
    game.CoutGame();

    if ( (game.GetWhoseTurn() == white && isPlayerOneHuman == true)
      || (game.GetWhoseTurn() == black && isPlayerTwoHuman == true) )
    {
      //Human move
      const std::string input = AskUserForString();

      if (input == "q" || input == "Q" || input == "exit"    || input == "quit") break;
      if (input == "r" || input == "R" || input == "restart" || input == "new ")
      {
        game = ChessGame();
        continue;
      }

      ChessMove move;

      const bool validInput = game.ParseMove(input,move);
      if (validInput == false) continue;

      const bool validMove = game.CanDoMove(move);
      if (validMove == false) continue;

      game.DoMove(move);
    }
    else
    {
      //Computer move
      const ChessMove move = game.SuggestMove();
      game.DoMove(move);
    }

    if (game.IsGameOver()==true)
    {
      game.CoutGame();

      std::cout
        << "Game won by "
        << (game.GetWinner() == white ? "white" : "black")
        << " player." << std::endl
        << "Press any key to start a new game" << std::endl;
      const std::string input = AskUserForString();
      if (input == "q" || input == "Q" || input == "exit"    || input == "quit") break;
      game = ChessGame();
    }


    if ( (game.GetWhoseTurn() == white && isPlayerOneHuman == true)
      || (game.GetWhoseTurn() == black && isPlayerTwoHuman == true) )
    {
      //Human input
      ClearScreen();


      std::cout
        << (game.GetWhoseTurn() == white ? "white" : "black")
        << " player, please" << std::endl
        << "press any key to view the board" << std::endl;
      AskUserForString();
      ClearScreen();
    }
  }

  ShowLicence();
  std::cout
    << "press any key to quit"
    << std::endl;
  AskUserForString();

}
//---------------------------------------------------------------------------
