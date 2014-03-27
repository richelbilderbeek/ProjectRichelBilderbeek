#ifndef TESTREVERSIMENUDIALOG_H
#define TESTREVERSIMENUDIALOG_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/scoped_ptr.hpp>

#include "about.h"
#include "menudialog.h"
#pragma GCC diagnostic pop

namespace ribi {

struct TestReversi;

struct TestReversiMenuDialog : public MenuDialog
{
  TestReversiMenuDialog();
  ~TestReversiMenuDialog() noexcept {}
  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept;

  About GetAbout() const noexcept;
  Help GetHelp() const noexcept;
  boost::shared_ptr<const Program> GetProgram() const noexcept;
  std::string GetVersion() const noexcept;
  std::vector<std::string> GetVersionHistory() const noexcept;

  private:

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // TESTREVERSIMENUDIALOG_H
