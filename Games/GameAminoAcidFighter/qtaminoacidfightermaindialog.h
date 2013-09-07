#ifndef QTAMINOACIDFIGHTERMAINDIALOG_H
#define QTAMINOACIDFIGHTERMAINDIALOG_H

#include <QDialog>

struct QGraphicsScene;
struct QGraphicsPixmapItem;

namespace Ui {
  class QtAminoAcidFighterMainDialog;
}

namespace ribi {
namespace aaf {

class QtAminoAcidFighterMainDialog : public QDialog
{
  Q_OBJECT

public:
  explicit QtAminoAcidFighterMainDialog(QWidget *parent = 0);
  ~QtAminoAcidFighterMainDialog();

private:
  Ui::QtAminoAcidFighterMainDialog *ui;
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

} //~namespace aaf
} //~namespace ribi

#endif // QTAMINOACIDFIGHTERMAINDIALOG_H
