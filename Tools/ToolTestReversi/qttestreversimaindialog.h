#ifndef DIALOGMAIN_H
#define DIALOGMAIN_H
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
#include <QDialog>
//---------------------------------------------------------------------------
struct ReversiWidget;
namespace Ui {
  class DialogMain;
}
//---------------------------------------------------------------------------
class DialogMain : public QDialog
{
  Q_OBJECT

public:
  explicit DialogMain(QWidget *parent = 0);
  ~DialogMain();

protected:
  void changeEvent(QEvent *e);

private:
  Ui::DialogMain *ui;
  boost::shared_ptr<ReversiWidget> m_reversi;
};
//---------------------------------------------------------------------------
#endif // DIALOGMAIN_H
