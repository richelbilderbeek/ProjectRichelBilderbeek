#ifndef QTMYSTERYMACHINEDIALOG_H
#define QTMYSTERYMACHINEDIALOG_H
//---------------------------------------------------------------------------
#include <boost/scoped_ptr.hpp>
//---------------------------------------------------------------------------
#include <QDialog>
//---------------------------------------------------------------------------
namespace Ui {
  class QtSimMysteryMachineMainDialog;
}
//---------------------------------------------------------------------------
struct QtMysteryMachineWidget;
//---------------------------------------------------------------------------
class QtSimMysteryMachineMainDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtSimMysteryMachineMainDialog(QWidget *parent = 0);
  ~QtSimMysteryMachineMainDialog();

protected:
  void changeEvent(QEvent *e);

private:
  Ui::QtSimMysteryMachineMainDialog *ui;
  boost::scoped_ptr<QtMysteryMachineWidget> m_machine;

private slots:
};
//---------------------------------------------------------------------------
#endif // QTMYSTERYMACHINEDIALOG_H
