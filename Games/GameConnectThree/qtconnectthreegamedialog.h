#ifndef QTCONNECTTHREEGAMEDIALOG_H
#define QTCONNECTTHREEGAMEDIALOG_H
//---------------------------------------------------------------------------
#include <bitset>
//---------------------------------------------------------------------------
#include <boost/signals2.hpp>
//---------------------------------------------------------------------------
#include <QDialog>
//---------------------------------------------------------------------------
namespace Ui {
  class QtConnectThreeGameDialog;
}
struct QtConnectThreeWidget;
//---------------------------------------------------------------------------
class QtConnectThreeGameDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtConnectThreeGameDialog(
    QWidget *parent = 0,
    const std::bitset<3>& is_player_human = std::bitset<3>(true));
  boost::signals2::signal<void ()> m_signal_close;


  ~QtConnectThreeGameDialog();

protected:
  void changeEvent(QEvent *e);

public slots:
  void DoComputerTurn();

private:
  Ui::QtConnectThreeGameDialog *ui;
  boost::shared_ptr<QtConnectThreeWidget> m_board;
  const std::bitset<3>& m_is_player_human;
  void OnValidMove();
};
//---------------------------------------------------------------------------
#endif // QTCONNECTTHREEGAMEDIALOG_H
