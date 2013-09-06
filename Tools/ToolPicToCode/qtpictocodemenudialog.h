#ifndef QTPICTOCODEMENUDIALOG_H
#define QTPICTOCODEMENUDIALOG_H
//---------------------------------------------------------------------------
#include <QDialog>
//---------------------------------------------------------------------------
namespace Ui {
  class QtPicToCodeMenuDialog;
}
//---------------------------------------------------------------------------

namespace ribi {

class QtPicToCodeMenuDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtPicToCodeMenuDialog(QWidget *parent = 0);
  ~QtPicToCodeMenuDialog();

protected:


private:
  Ui::QtPicToCodeMenuDialog *ui;

private slots:
  void on_button_quit_clicked();
  void on_button_about_clicked();
  void on_button_start_clicked();
};

} //~namespace ribi

#endif // QTPICTOCODEMENUDIALOG_H
