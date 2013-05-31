#ifndef WTNSANABROSMENUDIALOG_H
#define WTNSANABROSMENUDIALOG_H
//---------------------------------------------------------------------------
#include <boost/scoped_ptr.hpp>
#include <boost/signals2.hpp>
//---------------------------------------------------------------------------
#include <Wt/WContainerWidget>
//---------------------------------------------------------------------------
struct NsanaBrosMenuDialog;
//---------------------------------------------------------------------------
struct WtNsanaBrosMenuDialog : public Wt::WContainerWidget
{
  WtNsanaBrosMenuDialog();

  boost::signals2::signal<void ()> m_signal_close;

  private:
  boost::scoped_ptr<NsanaBrosMenuDialog> m_dialog;

  void OnStartClick();
  void OnOptionsClick();
  void OnAboutClick();
  void OnCloseClick();

  void ShowMenu();
  void ShowGame();
  void ShowOptions();
  void ShowAbout();

};
//---------------------------------------------------------------------------
#endif // WTNSANABROSMENUDIALOG_H
