#ifndef QTAMINOACIDFIGHTERMAINDIALOG_H
#define QTAMINOACIDFIGHTERMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

struct QGraphicsScene;
struct QGraphicsPixmapItem;

namespace Ui {
  class QtAafMainDialog;
}

namespace ribi {
namespace aaf {

class QtAafMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtAafMainDialog(QWidget *parent = 0);
  QtAafMainDialog(const QtAafMainDialog&) = delete;
  QtAafMainDialog& operator=(const QtAafMainDialog&) = delete;
  ~QtAafMainDialog() noexcept;

private:
  Ui::QtAafMainDialog *ui;
  QTimer * const m_timer;
  QGraphicsScene * const m_scene;
  QGraphicsPixmapItem * const m_sprite;
  double m_angle;

  void resizeEvent(QResizeEvent*);
  void keyPressEvent(QKeyEvent* e);

private slots:
  void onTick();
  void onCheck();
  void onButtonLeft();
  void onButtonRight();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace aaf
} //~namespace ribi

#endif // QTAMINOACIDFIGHTERMAINDIALOG_H
