//---------------------------------------------------------------------------
#ifndef WTTESTNEWICKVECTORDIALOG_H
#define WTTESTNEWICKVECTORDIALOG_H
//---------------------------------------------------------------------------
#include <string>
#include <vector>
#include <boost/signals2.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/tuple/tuple.hpp>
//---------------------------------------------------------------------------
#include <Wt/WCheckBox>
#include <Wt/WContainerWidget>
#include <Wt/WPushButton>
#include <Wt/WTable>
#include <Wt/WTextArea>
//---------------------------------------------------------------------------
#include "about.h"
#include "testnewickvectordialog.h"

namespace ribi {

struct WtTestNewickVectorDialog : public Wt::WContainerWidget
{
  WtTestNewickVectorDialog();
  boost::signals2::signal<void ()> m_signal_about;
  boost::signals2::signal<void ()> m_signal_any_change;
  private:
  TestNewickVectorDialog m_dialog;
  Wt::WCheckBox * const m_box_show_calculation;
  Wt::WCheckBox * const m_box_compare;
  Wt::WLineEdit * const m_edit_newick;
  Wt::WLineEdit * const m_edit_password;
  Wt::WLineEdit * const m_edit_theta;
  Wt::WTextArea * const m_text;
  void Display();
  void OnAbout();
  void OnCalculate();
};

} //~namespace ribi

#endif // WTTESTNEWICKVECTORDIALOG_H
