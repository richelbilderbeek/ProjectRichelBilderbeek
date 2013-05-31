#ifndef SECRETMESSAGEMENUDIALOG_H
#define SECRETMESSAGEMENUDIALOG_H
//---------------------------------------------------------------------------
#include <string>
#include <vector>
//---------------------------------------------------------------------------
#include "about.h"
//---------------------------------------------------------------------------
namespace SecretMessage {
//---------------------------------------------------------------------------
struct MenuDialog
{
  ///Obtain this class its About information
  static const About GetAbout();

  ///Obtain this class its version
  static const std::string GetVersion();

  ///Obtain this class its version history
  static const std::vector<std::string> GetVersionHistory();
};
//---------------------------------------------------------------------------
} //~namespace SecretMessage
//---------------------------------------------------------------------------
#endif // SECRETMESSAGEMENUDIALOG_H
