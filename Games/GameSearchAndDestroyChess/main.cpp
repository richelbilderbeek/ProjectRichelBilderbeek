#include <cassert>
#include <string>
#include <fstream>
#include <iostream>

#ifdef SADC_USE_THREADS
#include <thread>
#endif

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

#include "chessgame.h"
#include "chessmoves.h"
#include "searchanddestroychessmenudialog.h"
#include "trace.h"
///FileToVector reads a file and converts it to a std::vector<std::string>
///From http://www.richelbilderbeek.nl/CppFileToVector.htm
const std::vector<std::string> FileToVector(const std::string& filename)
{
  assert(boost::filesystem::exists(filename));
  std::vector<std::string> v;
  std::ifstream in(filename.c_str());
  std::string s;
  for (int i=0; !in.eof(); ++i)
  {
    std::getline(in,s);
    v.push_back(s);
  }
  return v;
}

/*
//From http://www.richelbilderbeek/CppAskUserForString.htm
const std::string AskUserForString()
{
  std::string s;
  std::getline(std::cin,s);
  return s;
}

bool AskUserForYesNo()
{
  while (1)
  {
    const std::string s = AskUserForString();
    if (s.empty()==true) continue;
    if (s[0] == 'y' || s[0] == 'Y' || s == "yes" || s == "Yes" || s == "YES") return true;
    if (s[0] == 'n' || s[0] == 'N' || s == "no" || s == "No" || s == "NO")    return false;
  }
}

void ClearScreen()
{
  //'clear' the screen
  for (int i=0; i!=50; ++i) std::cout << std::endl;
}
*/

///Goal:
///- Input: a game its moves
///- Output: valid yes/no

///NEVER FORGET:
/// - Prefer Factory over copy constructor
int main(int argc, char* argv[])
{
  START_TRACE();

  #ifdef SADC_USE_THREADS
  std::thread t(
    []
  #endif
    {
      FTRACE("Testing in main");
      //SearchAndDestroyChess::MenuDialog::Test();
      ribi::Chess::Game::Test();
    }
  #ifdef SADC_USE_THREADS
  );
  #endif

 // Declare the supported options.
  boost::program_options::options_description d("Allowed options for [my_program]");
  std::string filename = "chess.txt";
  d.add_options()
      ("help",
        "produce this help message")
      ("filename",
         boost::program_options::value<std::string>(&filename),
         "load from file 'arg'");

  boost::program_options::variables_map m;
  boost::program_options::store(
    boost::program_options::parse_command_line(
      argc, argv, d), m);
  boost::program_options::notify(m);

  //If one of the options is set to 'help'...
  if (m.count("help"))
  {
    //Display the options_description
    std::cout << d << "\n";
  }

  if (m.count("filename"))
  {
    filename = m["filename"].as<std::string>();
    std::cout
      << "Filename is set to '"
      << m["filename"].as<std::string>()
      << "'\n";
  }
  else
  {
    std::cout << "No filename set, using '" << filename << "'\n";
  }

  if (!boost::filesystem::exists(filename))
  {
    std::cout << "Filename '" + filename + "' does not exist.\n";
    const auto v = ribi::Chess::Moves::GetGameKasparovVersusTheWorld();
    std::ofstream file(filename.c_str());
    std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(file,"\n"));
    std::cout << "Filename '" + filename + "' created with example game.\n";
  }
  assert(boost::filesystem::exists(filename));
  const std::vector<std::string> v = FileToVector(filename);

  if (ribi::Chess::Game::CanDoGame(v))
  {
    std::cout << "Y" << std::endl;
  }
  else
  {
    std::cout << "N" << std::endl;
    const int n = ribi::Chess::Game::CanDoGameUntil(v);
    std::cout << n << std::endl;
    std::copy(v.begin(),v.begin() + n + 1,std::ostream_iterator<std::string>(std::cout,"\n"));
    std::cout << std::flush;

  }
  #ifdef SADC_USE_THREADS
  while (1) {}
  t.join();
  #endif

  /*
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

    if ( (game.GetWhoseTurn() == ChessPiece::white && isPlayerOneHuman == true)
      || (game.GetWhoseTurn() == ChessPiece::black && isPlayerTwoHuman == true) )
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
        << (game.GetWinner() == ChessPiece::white ? "white" : "black")
        << " player." << std::endl
        << "Press any key to start a new game" << std::endl;
      const std::string input = AskUserForString();
      if (input == "q" || input == "Q" || input == "exit"    || input == "quit") break;
      game = ChessGame();
    }


    if ( (game.GetWhoseTurn() == ChessPiece::white && isPlayerOneHuman == true)
      || (game.GetWhoseTurn() == ChessPiece::black && isPlayerTwoHuman == true) )
    {
      //Human input
      ClearScreen();


      std::cout
        << (game.GetWhoseTurn() == ChessPiece::white ? "white" : "black")
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
  */
}

