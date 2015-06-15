#include "k3opeenrijmenudialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <cassert>
#include <iostream>
#include <sstream>
#include <stdexcept>

//#include <QPixmap>

#include "connectthree.h"
#include "connectthreewidget.h"
#include "imagecanvas.h"
#include "qtk3opeenrijresources.h"
#include "richelbilderbeekprogram.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

int ribi::K3OpEenRijMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  using namespace ::ribi::con3;
  #ifndef NDEBUG
  Test();
  #endif

  const int argc = static_cast<int>(argv.size());

  if (argc == 2 && (argv[1] == "-d" || argv[1] == "--demo"))
  {

    //Play a ConnectThreeGame, but change the graphics
    boost::shared_ptr<ConnectThree> c {
      new ConnectThree(15,5)
    };
    const std::bitset<3> is_player_human(0);
    while (c->GetWinner() == Winner::no_winner)
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
      case Winner::player1  : std::cout << "Karen won the game"; break;
      case Winner::player2  : std::cout << "Kristel won the game"; break;
      case Winner::player3  : std::cout << "Josje won the game"; break;
      case Winner::draw     : std::cout << "The game ended in a draw"; break;
      case Winner::no_winner:
        assert(!"Should not get here");
        throw std::logic_error("Should not respond to no winner");
    }

    std::cout << std::endl;
    return 0;
  }
  else if (argc == 2 && (argv[1] == "-1" || argv[1] == "--Karen"))
  {
    Show(0);
    return 0;
  }
  else if (argc == 2 && (argv[1] == "-2" || argv[1] == "--Kristel"))
  {
    Show(1);
    return 0;
  }
  else if (argc == 2 && (argv[1] == "-3" || argv[1] == "--Josje"))
  {
    Show(2);
    return 0;
  }
  else if (argc == 2 && (argv[1] == "-4" || argv[1] == "--Kathleen"))
  {
    Show(3);
    return 0;
  }
  else
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
}

ribi::About ribi::K3OpEenRijMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "K3OpEenRij",
    "K3-themed connect-three game",
    "the 6th of August 2013",
    "2007-2015",
    "http://www.richelbilderbeek.nl/GameK3OpEenRij.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("ConnectThree version: " + con3::ConnectThree::GetVersion());
  a.AddLibrary("ConnectThreeWidget version: " + con3::ConnectThreeWidget::GetVersion());
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  a.AddLibrary("Special thanks to Mark Wiering for his excellent bug reports");
  return a;
}

ribi::Help ribi::K3OpEenRijMenuDialog::GetHelp() const noexcept
{
  return Help(
    GetAbout().GetFileTitle(),
    GetAbout().GetFileDescription(),
    {
      Help::Option('d',"demo","Display a demo game"),
      Help::Option('1',"Karen","Display Karen"),
      Help::Option('2',"Kristel","Display Kristel"),
      Help::Option('3',"Josje","Display Josje"),
      Help::Option('4',"Kathleen","Display Kathleen")
    },
    {
      GetAbout().GetFileTitle() + " -d",
      GetAbout().GetFileTitle() + " --demo",
      GetAbout().GetFileTitle() + " -1",
      GetAbout().GetFileTitle() + " --Karen"
    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::K3OpEenRijMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramK3OpEenRij
  };
  assert(p);
  return p;
}

std::string ribi::K3OpEenRijMenuDialog::GetVersion() const noexcept
{
  return "6.3";
}

std::vector<std::string> ribi::K3OpEenRijMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2007-01-03: version 3.0: initial C++ Builder verion",
    "2009-12-31: version 4.0: replaced Kathleen by Josje, game arena always visible, made screens smaller, removed useless JPEGs",
    "2013-08-06: version 5.0: port to Qt Creator",
    "2013-08-06: version 5.1: allow selection of both Kathleen and Josje",
    "2013-08-09: version 6.0: implemented suggestions and bugfixes from Mark Wiering's report",
    "2014-01-23: version 6.1: added command line demo",
    "2014-01-30: version 6.2: added extra command line option to display the artists",
    "2015-06-09: version 6.3: show how to choose Kathleen in the menu screen, clean up files when program closes",
  };
}

void ribi::K3OpEenRijMenuDialog::Show(const int girl_index) const noexcept
{
  QtK3OpEenRijResources r(girl_index == 3 ? Tribool::True : Tribool::False);
  assert(r.GetPlayersFilenames().size() == 3);
  assert(girl_index >= 0);
  assert(girl_index >= 0);
  const std::string filename = r.GetPlayersFilenames()[girl_index == 3 ? 2 : girl_index];
  QtK3OpEenRijResources::CreateFile(filename);
  const boost::shared_ptr<ImageCanvas> canvas {
    new ImageCanvas(filename,78)
  };
  std::cout << (*canvas) << std::endl;
}

#ifndef NDEBUG
void ribi::K3OpEenRijMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  boost::shared_ptr<con3::ConnectThree> c {
    new con3::ConnectThree(15,5)
  };
  const std::bitset<3> is_player_human(0);
  while (c->GetWinner() == con3::Winner::no_winner)
  {
    c->DoMove(c->SuggestMove(is_player_human));
  }
}
#endif
