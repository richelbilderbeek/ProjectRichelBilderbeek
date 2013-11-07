#ifndef DIALOGGAME_H
#define DIALOGGAME_H
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
#include <QDialog>
//---------------------------------------------------------------------------
namespace Ui {
  class DialogGame;
}
struct QtGameWidget;
//---------------------------------------------------------------------------
class DialogGame : public QDialog
{
  Q_OBJECT

public:
  explicit DialogGame(QWidget *parent = 0);
  ~DialogGame();

protected:
  void changeEvent(QEvent *e);

private:
  boost::shared_ptr<QtGameWidget> m_game;
  Ui::DialogGame *ui;
};
//---------------------------------------------------------------------------
#endif // DIALOGGAME_H
