#ifndef SIMMYSTERYMACHINEMENUDIALOG_H
#define SIMMYSTERYMACHINEMENUDIALOG_H
//---------------------------------------------------------------------------
#include "about.h"
//---------------------------------------------------------------------------
struct SimMysteryMachineMenuDialog
{
  SimMysteryMachineMenuDialog();
  static const About GetAbout();
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();
};
//---------------------------------------------------------------------------
#endif // SIMMYSTERYMACHINEMENUDIALOG_H
