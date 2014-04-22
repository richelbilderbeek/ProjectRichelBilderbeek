#ifndef QTATHLETICLANDMAINDIALOG_H
#define QTATHLETICLANDMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

struct QGraphicsScene;
struct QGraphicsPixmapItem;

namespace Ui {
  class QtAthleticLandMainDialog;
}

namespace ribi {
namespace athl {

struct QtAthleticLandMainWidget;

class QtAthleticLandMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtAthleticLandMainDialog(QWidget *parent = 0);
  QtAthleticLandMainDialog(const QtAthleticLandMainDialog&) = delete;
  QtAthleticLandMainDialog& operator=(const QtAthleticLandMainDialog&) = delete;
  ~QtAthleticLandMainDialog() noexcept;

private:
  Ui::QtAthleticLandMainDialog *ui;
  void keyPressEvent(QKeyEvent *event);

  QtAthleticLandMainWidget * const m_main_widget;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace aaf
} //~namespace ribi

#endif // QTATHLETICLANDMAINDIALOG_H
