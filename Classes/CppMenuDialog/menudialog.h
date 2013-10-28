#ifndef MENUDIALOG_H
#define MENUDIALOG_H

#include <vector>
#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>

#include "about.h"
#include "help.h"
#include "richelbilderbeekprogram.h"
#pragma GCC diagnostic pop

namespace ribi {

///Class for all ProjectRichelBilderbeek menu dialogs
struct MenuDialog
{
  MenuDialog() {}

  virtual ~MenuDialog() noexcept {}

  ///Convert the C style array and string to C++ equivalents
  ///This is used when menu
  static const std::vector<std::string> ConvertArguments(const int argc, const char * const argv[]) noexcept;

  ///Start the command line version
  ///First performs a default parse, then passed arguments on to ExecuteSpecific
  ///Returns the error code to give back to the operatings system
  ///Make it a non-const member function: a menu is allowed to have state
  int Execute(const std::vector<std::string>& argv) noexcept;

  ///Obtain the About information of this class
  virtual const About GetAbout() const noexcept = 0;

  ///Obtain the help information of this class
  virtual const Help GetHelp() const noexcept = 0;

  ///Obtain information about the program
  virtual const boost::shared_ptr<const Program> GetProgram() const noexcept = 0;

  ///Obtain the version of this class
  virtual const std::string GetVersion() const noexcept = 0;

  ///Obtain the version history of this class
  virtual const std::vector<std::string> GetVersionHistory() const noexcept = 0;

  protected:
  ///When Execute has done the default parse, the arguments are passed to ExecuteSpecific.
  ///Here the program itself is called.
  ///Returns the error code to give back to the operatings system
  ///Make it a non-const member function: a menu is allowed to have state

  virtual int ExecuteSpecific(const std::vector<std::string>& argv) noexcept = 0;

};

} //namespace ribi

#endif // MENUDIALOG_H
