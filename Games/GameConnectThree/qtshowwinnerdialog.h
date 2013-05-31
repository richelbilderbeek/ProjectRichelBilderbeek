#ifndef QTSHOWWINNERDIALOG_H
#define QTSHOWWINNERDIALOG_H
//---------------------------------------------------------------------------
#include <string>
//---------------------------------------------------------------------------
#include <QDialog>
//---------------------------------------------------------------------------
namespace Ui {
  class QtShowWinnerDialog;
}
//---------------------------------------------------------------------------
class QtShowWinnerDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtShowWinnerDialog(QWidget *parent = 0);
  ~QtShowWinnerDialog();
  void SetPixmap(const std::string& filename);

protected:
  void changeEvent(QEvent *e);

private:
  Ui::QtShowWinnerDialog *ui;
};
//---------------------------------------------------------------------------
#endif // QTSHOWWINNERDIALOG_H
