//---------------------------------------------------------------------------
#ifndef WTMYSTERYMACHINEDIALOG_H
#define WTMYSTERYMACHINEDIALOG_H
//---------------------------------------------------------------------------
#include <boost/scoped_ptr.hpp>
#include <boost/signals2.hpp>
//---------------------------------------------------------------------------
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
//---------------------------------------------------------------------------
struct WtMysteryMachineWidget;
//---------------------------------------------------------------------------
///WtSimMysteryMachineMainDialog displays a
///WtMysteryMachineWidget
struct WtSimMysteryMachineMainDialog : public Wt::WContainerWidget
{
  WtSimMysteryMachineMainDialog();

  private:

  ///The user interface
  struct Ui
  {
    Ui();
    WtMysteryMachineWidget * const m_machine;
  } ui;
};
//---------------------------------------------------------------------------
#endif // WTMYSTERYMACHINEDIALOG_H
