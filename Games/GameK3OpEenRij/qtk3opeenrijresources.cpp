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

QtK3OpEenRijResources::QtK3OpEenRijResources()
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
    {
      "K3OpEenRijPlayer1.png",
      "K3OpEenRijPlayer2.png",
      "K3OpEenRijPlayer3.png"
    },
    {
      "K3OpEenRijPlayer1Grey.png",
      "K3OpEenRijPlayer2Grey.png",
      "K3OpEenRijPlayer3Grey.png"
    }
  )
{

}
