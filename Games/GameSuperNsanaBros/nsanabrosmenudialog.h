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

struct NsanaBrosMenuDialog final : public MenuDialog
{
  NsanaBrosMenuDialog();

  About GetAbout() const noexcept override;
  Help GetHelp() const noexcept override;
  boost::shared_ptr<const Program> GetProgram() const noexcept override;
  std::string GetVersion() const noexcept override;
  std::vector<std::string> GetVersionHistory() const noexcept override;

  const NsanaBrosOptionsDialog * GetOptionsDialog() const;
  boost::shared_ptr<NsanaBrosOptionsDialog> UseOptionsDialog();

  ~NsanaBrosMenuDialog() noexcept;
  //friend void boost::checked_delete<>(NsanaBrosMenuDialog *);
  private:

  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept override;

  boost::scoped_ptr<NsanaBrosGameDialog> m_game;
  boost::shared_ptr<NsanaBrosOptionsDialog> m_options;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // NSANABROSMENUDIALOG_H
