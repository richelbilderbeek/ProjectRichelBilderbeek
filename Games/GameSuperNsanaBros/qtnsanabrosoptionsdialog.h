#ifndef QTNSANABROSOPTIONSDIALOG_H
#define QTNSANABROSOPTIONSDIALOG_H
//---------------------------------------------------------------------------
#include <boost/scoped_ptr.hpp>
//---------------------------------------------------------------------------
#include <QDialog>
//---------------------------------------------------------------------------
namespace Ui {
  class QtNsanaBrosOptionsDialog;
}
//---------------------------------------------------------------------------
struct NsanaBrosOptionsDialog;
//---------------------------------------------------------------------------
class QtNsanaBrosOptionsDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtNsanaBrosOptionsDialog(
    const NsanaBrosOptions * const options = 0,
    QWidget *parent = 0);
  ~QtNsanaBrosOptionsDialog();

protected:
  void changeEvent(QEvent *e);

private:
  Ui::QtNsanaBrosOptionsDialog *ui;
  boost::scoped_ptr<NsanaBrosOptionsDialog> m_dialog;
};
//---------------------------------------------------------------------------
#endif // QTNSANABROSOPTIONSDIALOG_H
