#ifndef QTNSANABROSGAMEDIALOG_H
#define QTNSANABROSGAMEDIALOG_H

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <QDialog>
#include <QTimer>

namespace Ui {
  class QtNsanaBrosGameDialog;
}

namespace ribi {

struct NsanaBrosGame;
//struct NsanaBrosGameDialog;
struct NsanaBrosOptions;

class QtNsanaBrosGameDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtNsanaBrosGameDialog(
    const NsanaBrosOptions * const options = 0,
    QWidget *parent = 0);
  QtNsanaBrosGameDialog(const QtNsanaBrosGameDialog&) = delete;
  QtNsanaBrosGameDialog& operator=(const QtNsanaBrosGameDialog&) = delete;
  ~QtNsanaBrosGameDialog();

protected:
  void changeEvent(QEvent *e);
  void keyPressEvent(QKeyEvent *);
  void keyReleaseEvent(QKeyEvent *);

public slots:
  void OnTimerQt();

private:
  Ui::QtNsanaBrosGameDialog *ui;
  boost::scoped_ptr<NsanaBrosGame> m_game;
  QTimer m_timer;
};

} //~namespace ribi

#endif // QTNSANABROSGAMEDIALOG_H
