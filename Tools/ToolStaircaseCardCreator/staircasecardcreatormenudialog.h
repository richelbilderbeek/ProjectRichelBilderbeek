#ifndef STAIRCASECARDCREATORMENUDIALOG_H
#define STAIRCASECARDCREATORMENUDIALOG_H

#include <string>
#include <vector>

#include "menudialog.h"
//#include "staircasecardcreatorfwd.h"

namespace ribi {
namespace scc {

///GUI independent staircasecardcreator menu dialog
struct StaircaseCardCreatorMenuDialog : public MenuDialog
{
  StaircaseCardCreatorMenuDialog();
  ~StaircaseCardCreatorMenuDialog() noexcept {}
  const ribi::About GetAbout() const noexcept;
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

} //~namespace scc
} //~namespace ribi

#endif // STAIRCASECARDCREATORMENUDIALOG_H
