#ifndef QTEVERYTHINGTOPIECESSHOOTERMAINDIALOG_H
#define QTEVERYTHINGTOPIECESSHOOTERMAINDIALOG_H
/*
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>

#include "qthideandshowdialog.h"
#include <QPixmap>
#include <QTimer>
#pragma GCC diagnostic pop

namespace Ui {
  class QtEverythingToPiecesShooterMainDialog;
}

namespace ribi {

///QtEverythingToPiecesShooterMainDialog displays EverythingToPiecesShooter and handles user events
class QtEverythingToPiecesShooterMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtEverythingToPiecesShooterMainDialog(
    QWidget *parent = 0,
  );
  QtEverythingToPiecesShooterMainDialog(const QtEverythingToPiecesShooterMainDialog&) = delete;
  QtEverythingToPiecesShooterMainDialog& operator=(const QtEverythingToPiecesShooterMainDialog&) = delete;
  ~QtEverythingToPiecesShooterMainDialog() noexcept;

protected:
  void paintEvent(QPaintEvent*);
  void keyPressEvent(QKeyEvent*);

private:
  //UI
  Ui::QtEverythingToPiecesShooterMainDialog *ui;
  //Graphics
  boost::shared_ptr<QPixmap> m_background;
  //Other Qthings
  ///The main game timer
  boost::shared_ptr<QTimer> m_timer;
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

private slots:
  void OnTimer();

};

} //~namespace ribi
*/
#endif // QTEVERYTHINGTOPIECESSHOOTERMAINDIALOG_H
