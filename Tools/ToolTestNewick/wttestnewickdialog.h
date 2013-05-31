//---------------------------------------------------------------------------
#ifndef WTTESTNEWICKDIALOG_H
#define WTTESTNEWICKDIALOG_H
//---------------------------------------------------------------------------
#include <string>
#include <vector>
#include <boost/signals2.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/tuple/tuple.hpp>
//---------------------------------------------------------------------------
#include <Wt/WContainerWidget>
#include <Wt/WPushButton>
#include <Wt/WTable>
#include <Wt/WTextArea>
//---------------------------------------------------------------------------
#include "about.h"
#include "testnewickdialog.h"
//---------------------------------------------------------------------------
struct WtTestNewickDialog : public Wt::WContainerWidget
{
  WtTestNewickDialog();
  boost::signals2::signal<void ()> m_signal_about;
  boost::signals2::signal<void ()> m_signal_close;
  boost::signals2::signal<void ()> m_signal_any_change;
  private:
  TestNewickDialog m_dialog;
  Wt::WLineEdit * const m_edit_newick;
  Wt::WLineEdit * const m_edit_password;
  Wt::WLineEdit * const m_edit_theta;
  Wt::WTable * const m_table;
  Wt::WTextArea * const m_text;
  void Display();
  void OnAbout();
  void OnCalculate();
  void OnClose();
};
//---------------------------------------------------------------------------
#endif // WTTESTNEWICKDIALOG_H
