#ifndef QTNSANABROSMENUDIALOG_H
#define QTNSANABROSMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/scoped_ptr.hpp>

#include <QDialog>
#pragma GCC diagnostic pop

namespace Ui {
  class QtNsanaBrosMenuDialog;
}

namespace ribi {

struct NsanaBrosMenuDialog;
struct QtNsanaBrosOptionsDialog;

class QtNsanaBrosMenuDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtNsanaBrosMenuDialog(QWidget *parent = 0);
  QtNsanaBrosMenuDialog(const QtNsanaBrosMenuDialog&) = delete;
  QtNsanaBrosMenuDialog& operator=(const QtNsanaBrosMenuDialog&) = delete;
  ~QtNsanaBrosMenuDialog();

private:
  Ui::QtNsanaBrosMenuDialog *ui;
  boost::scoped_ptr<NsanaBrosMenuDialog> m_dialog;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

private slots:
  void on_button_quit_clicked();
  void on_button_about_clicked();
  void on_button_options_clicked();
  void on_button_start_clicked();
};

} //~namespace ribi

#endif // QTNSANABROSMENUDIALOG_H
