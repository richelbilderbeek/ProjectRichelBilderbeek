#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorPperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtk3opeenrijresources.h"

#include <cassert>

QtK3OpEenRijResources::QtK3OpEenRijResources(
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
    {
      "K3OpEenRijInstructions1.png",
      "K3OpEenRijInstructions2.png"
    },
    "K3OpEenRijInstructions3.png",
    CreatePlayerNames(is_player3_kathleen),
    CreatePlayerGreyNames(is_player3_kathleen)
  )
{

}

const std::vector<std::string> QtK3OpEenRijResources::CreatePlayerNames(const boost::logic::tribool is_player3_kathleen)
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

const std::vector<std::string> QtK3OpEenRijResources::CreatePlayerGreyNames(const boost::logic::tribool is_player3_kathleen)
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
