#ifndef TESTCONCEPTMAPMENUDIALOG_H
#define TESTCONCEPTMAPMENUDIALOG_H

#include "menudialog.h"

namespace ribi {

///GUI independent TestConceptMap menu dialog
struct TestConceptMapMenuDialog : public MenuDialog
{
  TestConceptMapMenuDialog();
  const About GetAbout() const noexcept;
  const Help GetHelp() const noexcept;
  const boost::shared_ptr<const Program> GetProgram() const noexcept;
  const std::string GetVersion() const noexcept;
  const std::vector<std::string> GetVersionHistory() const noexcept;

  private:
  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

};

} //~namespace ribi

#endif // TESTCONCEPTMAPMENUDIALOG_H
