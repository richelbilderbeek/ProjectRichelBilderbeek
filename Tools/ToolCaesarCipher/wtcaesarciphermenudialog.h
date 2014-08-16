#ifndef WTCAESARCIPHERMENUDIALOG_H
#define WTCAESARCIPHERMENUDIALOG_H

#include <Wt/WContainerWidget>

namespace ribi {

struct WtCaesarCipherMenuDialog : public Wt::WContainerWidget
{
  WtCaesarCipherMenuDialog();

  private:
  Wt::WWidget * CreateNewAboutDialog() const;
  Wt::WWidget * CreateNewMainDialog() const;
  Wt::WWidget * CreateNewWelcomeDialog() const;
};

} //~namespace ribi

#endif // WTCAESARCIPHERMENUDIALOG_H
