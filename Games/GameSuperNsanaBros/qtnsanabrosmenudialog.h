#ifndef QTNSANABROSMENUDIALOG_H
#define QTNSANABROSMENUDIALOG_H
//---------------------------------------------------------------------------
#include <boost/scoped_ptr.hpp>
//---------------------------------------------------------------------------
#include <QDialog>
//---------------------------------------------------------------------------
namespace Ui {
  class QtNsanaBrosMenuDialog;
}
//---------------------------------------------------------------------------
struct NsanaBrosMenuDialog;
struct QtNsanaBrosOptionsDialog;
//---------------------------------------------------------------------------
class QtNsanaBrosMenuDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtNsanaBrosMenuDialog(QWidget *parent = 0);
  ~QtNsanaBrosMenuDialog();

protected:
  void changeEvent(QEvent *e);

private:
  Ui::QtNsanaBrosMenuDialog *ui;
  boost::scoped_ptr<NsanaBrosMenuDialog> m_dialog;

private slots:
  void on_button_quit_clicked();
  void on_button_about_clicked();
  void on_button_options_clicked();
  void on_button_start_clicked();
};
//---------------------------------------------------------------------------
#endif // QTNSANABROSMENUDIALOG_H
