#ifndef NSANABROSMENUDIALOG_H
#define NSANABROSMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/scoped_ptr.hpp>
#include "menudialog.h"
#include "nsanabrosstlfwdheader.h"
#pragma GCC diagnostic pop

namespace ribi {

struct NsanaBrosMenuDialog : public MenuDialog
{
  NsanaBrosMenuDialog();

  const About GetAbout() const noexcept;
  const Help GetHelp() const noexcept;
  const boost::shared_ptr<const Program> GetProgram() const noexcept;
  const std::string GetVersion() const noexcept;
  const std::vector<std::string> GetVersionHistory() const noexcept;

  const NsanaBrosOptionsDialog * GetOptionsDialog() const;
  boost::shared_ptr<NsanaBrosOptionsDialog> UseOptionsDialog();

  ~NsanaBrosMenuDialog() noexcept;
  //friend void boost::checked_delete<>(NsanaBrosMenuDialog *);
  private:

  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept;

  boost::scoped_ptr<NsanaBrosGameDialog> m_game;
  boost::shared_ptr<NsanaBrosOptionsDialog> m_options;
};

} //~namespace ribi

#endif // NSANABROSMENUDIALOG_H
