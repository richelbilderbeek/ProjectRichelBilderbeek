#ifndef SEARCHANDDESTROYCHESSMENUDIALOG_H
#define SEARCHANDDESTROYCHESSMENUDIALOG_H

#include "about.h"

namespace SearchAndDestroyChess {

///The logic behind the menu dialog
struct MenuDialog
{
  ///Creates the resources needed
  MenuDialog();

  ///Obtain the about information
  ///
  ///\note
  ///This is a non-static method, to ensure users of this class
  ///call MenuDialog its constructor: this is where
  ///the resources needed are created
  const About GetAbout() const;

  ///Obtain the version
  static const std::string GetVersion();

  ///Obtain the version history
  static const std::vector<std::string> GetVersionHistory();

  static void Test();
};

} //! namespace SearchAndDestroyChess

#endif // SEARCHANDDESTROYCHESSMENUDIALOG_H
