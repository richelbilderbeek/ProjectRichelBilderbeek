#ifndef SEARCHANDDESTROYCHESSMENUDIALOG_H
#define SEARCHANDDESTROYCHESSMENUDIALOG_H

#include "menudialog.h"

namespace ribi {
namespace sadc {

///The logic behind the menu dialog
struct MenuDialog : public ::ribi::MenuDialog
{
  ///Creates the resources needed
  MenuDialog();

  ///Obtain the about information
  ///
  ///\note
  ///This is a non-static method, to ensure users of this class
  ///call MenuDialog its constructor: this is where
  ///the resources needed are created
  const About GetAbout() const noexcept;

  ///Obtain the version
  const std::string GetVersion() const noexcept;

  ///Obtain the version history
  const std::vector<std::string> GetVersionHistory() const noexcept;

  private:
  #ifndef NDEBUG
  static void Test();
  #endif
};

} //~namespace sadc
} //~namespace ribi

#endif // SEARCHANDDESTROYCHESSMENUDIALOG_H
