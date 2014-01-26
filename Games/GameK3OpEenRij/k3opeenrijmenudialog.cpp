#include "k3opeenrijmenudialog.h"

#include <cassert>
#include <iostream>
#include <sstream>

#include "connectthree.h"
#include "connectthreewidget.h"
#include "trace.h"

int ribi::K3OpEenRijMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
  const int argc = static_cast<int>(argv.size());
  if (argc != 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }

  //Play a ConnectThreeGame, but change the graphics
  boost::shared_ptr<ConnectThree> c {
    new ConnectThree(15,5)
  };
  const std::bitset<3> is_player_human(0);
  while (c->GetWinner() == ConnectThree::no_player)
  {
    c->DoMove(c->SuggestMove(is_player_human));
    std::stringstream s;
    s << (*c);
    std::string t { s.str() };
    //Replace
    std::replace(t.begin(),t.end(),'1','K'); //Karen
    std::replace(t.begin(),t.end(),'2','R'); //kRistel
    std::replace(t.begin(),t.end(),'3','J'); //Josje
    std::cout << t << std::endl
      << std::endl;
  }

  switch (c->GetWinner())
  {
    case ConnectThree::player1: std::cout << "Karen won the game"; break;
    case ConnectThree::player2: std::cout << "Kristel won the game"; break;
    case ConnectThree::player3: std::cout << "Josje won the game"; break;
    case ConnectThree::draw   : std::cout << "The game ended in a draw"; break;
  }

  std::cout << std::endl;

  return 0;
}

const ribi::About ribi::K3OpEenRijMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "K3OpEenRij",
    "K3-themed connect-three game",
    "the 6th of August 2013",
    "2007-2014",
    "http://www.richelbilderbeek.nl/GameK3OpEenRij.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("ConnectThree version: " + ConnectThree::GetVersion());
  a.AddLibrary("ConnectThreeWidget version: " + ConnectThreeWidget::GetVersion());
  a.AddLibrary("Special thanks to Mark Wiering for his excellent bug reports");
  return a;
}

const ribi::Help ribi::K3OpEenRijMenuDialog::GetHelp() const noexcept
{
  return Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {

    },
    {

    }
  );
}

const boost::shared_ptr<const ribi::Program> ribi::K3OpEenRijMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramK3OpEenRij
  };
  assert(p);
  return p;
}

const std::string ribi::K3OpEenRijMenuDialog::GetVersion() const noexcept
{
  return "6.0";
}

const std::vector<std::string> ribi::K3OpEenRijMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2007-01-03: version 3.0: initial C++ Builder verion",
    "2009-12-31: version 4.0: replaced Kathleen by Josje, game arena always visible, made screens smaller, removed useless JPEGs",
    "2013-08-06: version 5.0: port to Qt Creator",
    "2013-08-06: version 5.1: allow selection of both Kathleen and Josje",
    "2013-08-09: version 6.0: implemented suggestions and bugfixes from Mark Wiering's report",
    "2014-01-23: version 6.1: added command line demo"
  };
}

#ifndef NDEBUG
void ribi::K3OpEenRijMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::K3OpEenRijMenuDialog::Test");
  TRACE("Finished ribi::K3OpEenRijMenuDialog::Test successfully");
}
#endif
