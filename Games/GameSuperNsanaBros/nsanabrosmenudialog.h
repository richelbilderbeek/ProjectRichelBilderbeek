#ifndef NSANABROSMENUDIALOG_H
#define NSANABROSMENUDIALOG_H

#include "menudialog.h"
#include "nsanabrosstlfwdheader.h"

namespace ribi {

struct NsanaBrosMenuDialog : public MenuDialog
{
  NsanaBrosMenuDialog();

  const About GetAbout() const noexcept;
  const std::string GetVersion() const noexcept;
  const std::vector<std::string> GetVersionHistory() const noexcept;

  const NsanaBrosOptionsDialog * GetOptionsDialog() const;
  boost::shared_ptr<NsanaBrosOptionsDialog> UseOptionsDialog();

  private:
  ~NsanaBrosMenuDialog() {}
  friend void boost::checked_delete<>(NsanaBrosMenuDialog *);

  boost::scoped_ptr<NsanaBrosGameDialog> m_game;
  boost::shared_ptr<NsanaBrosOptionsDialog> m_options;

};

} //~namespace ribi

#endif // NSANABROSMENUDIALOG_H
