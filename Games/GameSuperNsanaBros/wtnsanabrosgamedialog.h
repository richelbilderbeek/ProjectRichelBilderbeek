#ifndef WTNSANABROSGAMEDIALOG_H
#define WTNSANABROSGAMEDIALOG_H
//---------------------------------------------------------------------------
#include <boost/scoped_ptr.hpp>
#include <boost/signals2.hpp>
//---------------------------------------------------------------------------
#include <Wt/WContainerWidget>
//---------------------------------------------------------------------------
struct NsanaBrosGameDialog;
struct WtNsanaBrosGameAreaWidget;
struct WtNsanaBrosKeysWidget;
//---------------------------------------------------------------------------
struct WtNsanaBrosGameDialog : public Wt::WContainerWidget
{
  WtNsanaBrosGameDialog();

  boost::signals2::signal<void ()> m_signal_close;

  private:
  boost::scoped_ptr<NsanaBrosGameDialog> m_dialog;
  WtNsanaBrosGameAreaWidget * m_area_widget;
  WtNsanaBrosKeysWidget * m_keys_widget;

  void OnCloseClick();
  void ShowGame();

};
//---------------------------------------------------------------------------
#endif // WTNSANABROSGAMEDIALOG_H
