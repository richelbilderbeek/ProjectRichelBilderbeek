#ifndef QTCONNECTTHREEMENUDIALOG_H
#define QTCONNECTTHREEMENUDIALOG_H
//---------------------------------------------------------------------------
#include <string>
#include <vector>
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
#include <QDialog>
//---------------------------------------------------------------------------
namespace Ui {
  class QtConnectThreeMenuDialog;
}
struct QtSelectPlayerWidget;
//---------------------------------------------------------------------------
class QtConnectThreeMenuDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtConnectThreeMenuDialog(QWidget *parent = 0);
  ~QtConnectThreeMenuDialog();

protected:
  void changeEvent(QEvent *e);
  void mousePressEvent(QMouseEvent *);

private:
  Ui::QtConnectThreeMenuDialog *ui;
  boost::shared_ptr<QtSelectPlayerWidget> m_select;

private slots:
  void OnClickAbout();
  void OnClickStart();
};
//---------------------------------------------------------------------------
#endif // QTCONNECTTHREEMENUDIALOG_H
