#include "qtk3opeenrijresources.h"

#include <cassert>

ribi::QtK3OpEenRijResources::QtK3OpEenRijResources(
  const boost::logic::tribool is_player3_kathleen)
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

const std::vector<std::string> ribi::QtK3OpEenRijResources::CreatePlayerNames(const boost::logic::tribool is_player3_kathleen)
{
  if (is_player3_kathleen)
  {
    return
    {
      "K3OpEenRijKaren.png",
      "K3OpEenRijKristel.png",
      "K3OpEenRijKathleen.png"
    };
  }
  else if (!is_player3_kathleen)
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
    //assert(is_player3_kathleen == boost::logic::indeterminate);
    return
    {
      "K3OpEenRijKaren.png",
      "K3OpEenRijKristel.png",
      "K3OpEenRijKathleen.png",
      "K3OpEenRijJosje.png"
    };
  }
}

const std::vector<std::string> ribi::QtK3OpEenRijResources::CreatePlayerGreyNames(const boost::logic::tribool is_player3_kathleen)
{
  if (is_player3_kathleen)
  {
    return
    {
      "K3OpEenRijKarenGrey.png",
      "K3OpEenRijKristelGrey.png",
      "K3OpEenRijKathleenGrey.png"
    };
  }
  else if (!is_player3_kathleen)
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
    //assert(is_player3_kathleen == boost::logic::indeterminate);
    return
    {
      "K3OpEenRijKarenGrey.png",
      "K3OpEenRijKristelGrey.png",
      "K3OpEenRijKathleenGrey.png",
      "K3OpEenRijJosjeGrey.png"
    };
  }
}
