#ifndef WTTESTNEWICKVECTORDIALOG_H
#define WTTESTNEWICKVECTORDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

#include <string>
#include <vector>
#include <boost/signals2.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/tuple/tuple.hpp>

#include <Wt/WCheckBox>
#include <Wt/WContainerWidget>
#include <Wt/WPushButton>
#include <Wt/WTable>
#include <Wt/WTextArea>

#include "about.h"
#include "testnewickvectordialog.h"
#pragma GCC diagnostic pop

namespace ribi {

struct WtTestNewickVectorDialog : public Wt::WContainerWidget
{
  WtTestNewickVectorDialog();
  WtTestNewickVectorDialog(const WtTestNewickVectorDialog&) = delete;
  WtTestNewickVectorDialog& operator=(const WtTestNewickVectorDialog&) = delete;
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
