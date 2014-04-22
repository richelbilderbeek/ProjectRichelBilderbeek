#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtk3opeenrijresources.h"

#include <cassert>
#pragma GCC diagnostic pop

ribi::QtK3OpEenRijResources::QtK3OpEenRijResources(
  const Tribool is_player3_kathleen)
  : ConnectThreeResources(
    {
      "K3OpEenRijComputer1.png",
      "K3OpEenRijComputer2.png",
      "K3OpEenRijComputer3.png"
    },
    "K3OpEenRijComputerGrey.png",
    "K3OpEenRij.css",
    "K3OpEenRijEmpty.png",
    "K3OpEenRijIcon.png",
    {
      "K3OpEenRijInstructions1.png",
      "K3OpEenRijInstructions2.png"
    },
    "K3OpEenRijInstructions3.png",
    CreatePlayerNames(is_player3_kathleen),
    CreatePlayerGreyNames(is_player3_kathleen),
    "Stoppen",
    "Winnaar"
  )
{

}

std::vector<std::string> ribi::QtK3OpEenRijResources::CreatePlayerNames(const Tribool is_player3_kathleen)
{
  if (is_player3_kathleen == Tribool::True)
  {
    return
    {
      "K3OpEenRijKaren.png",
      "K3OpEenRijKristel.png",
      "K3OpEenRijKathleen.png"
    };
  }
  else if (is_player3_kathleen == Tribool::False)
  {
    return
    {
      "K3OpEenRijKaren.png",
      "K3OpEenRijKristel.png",
      "K3OpEenRijJosje.png"
    };
  }
  else
  {
    assert(is_player3_kathleen == Tribool::Indeterminate);
    return
    {
      "K3OpEenRijKaren.png",
      "K3OpEenRijKristel.png",
      "K3OpEenRijKathleen.png",
      "K3OpEenRijJosje.png"
    };
  }
}

std::vector<std::string> ribi::QtK3OpEenRijResources::CreatePlayerGreyNames(const Tribool is_player3_kathleen)
{
  if (is_player3_kathleen == Tribool::True)
  {
    return
    {
      "K3OpEenRijKarenGrey.png",
      "K3OpEenRijKristelGrey.png",
      "K3OpEenRijKathleenGrey.png"
    };
  }
  else if (is_player3_kathleen == Tribool::False)
  {
    return
    {
      "K3OpEenRijKarenGrey.png",
      "K3OpEenRijKristelGrey.png",
      "K3OpEenRijJosjeGrey.png"
    };
  }
  else
  {
    assert(is_player3_kathleen == Tribool::Indeterminate);
    return
    {
      "K3OpEenRijKarenGrey.png",
      "K3OpEenRijKristelGrey.png",
      "K3OpEenRijKathleenGrey.png",
      "K3OpEenRijJosjeGrey.png"
    };
  }
}
