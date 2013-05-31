#ifndef WTNSANABROSOPTIONSDIALOG_H
#define WTNSANABROSOPTIONSDIALOG_H
//---------------------------------------------------------------------------
#include <boost/scoped_ptr.hpp>
#include <boost/signals2.hpp>
//---------------------------------------------------------------------------
#include <Wt/WContainerWidget>
//---------------------------------------------------------------------------
struct NsanaBrosOptionsDialog;
//---------------------------------------------------------------------------
struct WtNsanaBrosOptionsDialog : public Wt::WContainerWidget
{
  WtNsanaBrosOptionsDialog();

  boost::signals2::signal<void ()> m_signal_close;

  private:
  boost::scoped_ptr<NsanaBrosOptionsDialog> m_dialog;

  void OnCloseClick();
  void ShowOptions();

};
//---------------------------------------------------------------------------
#endif // WTNSANABROSGAMEDIALOG_H
