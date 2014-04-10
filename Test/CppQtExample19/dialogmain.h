#ifndef DIALOGMAIN_H
#define DIALOGMAIN_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QDialog>
#pragma GCC diagnostic pop

struct QGraphicsScene;
struct QGraphicsPixmapItem;

namespace Ui {
  class DialogMain;
}

class DialogMain : public QDialog
{
  Q_OBJECT

public:
  explicit DialogMain(QWidget *parent = 0);
  DialogMain(const DialogMain&) = delete;
  DialogMain& operator=(const DialogMain&) = delete;
  ~DialogMain();

private:
  Ui::DialogMain *ui;
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
};

#endif // DIALOGMAIN_H
