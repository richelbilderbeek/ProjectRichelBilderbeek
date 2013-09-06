
//---------------------------------------------------------------------------
#ifndef WTSIMMYSTERYMACHINEMENUDIALOG_H
#define WTSIMMYSTERYMACHINEMENUDIALOG_H
//---------------------------------------------------------------------------
#include <Wt/WContainerWidget>
//---------------------------------------------------------------------------
namespace ribi {

struct WtSimMysteryMachineMenuDialog : public Wt::WContainerWidget
{
  WtSimMysteryMachineMenuDialog();

  private:
  Wt::WWidget * CreateNewAboutDialog() const;
  Wt::WWidget * CreateNewMainDialog() const;
  Wt::WWidget * CreateNewWelcomeDialog() const;
};
//---------------------------------------------------------------------------

} //~namespace ribi

#endif // WTSIMMYSTERYMACHINEMENUDIALOG_H
