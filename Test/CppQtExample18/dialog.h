#ifndef DIALOG_H
#define DIALOG_H

#include <boost/shared_ptr.hpp>
#include <QDialog>
struct QGraphicsPixmapItem;
struct QGraphicsScene;

namespace Ui {
  class Dialog;
}

class Dialog : public QDialog
{
  Q_OBJECT

public:
  explicit Dialog(QWidget *parent = 0);
  ~Dialog();

protected:
  void changeEvent(QEvent *e);

private:
  Ui::Dialog *ui;
  boost::shared_ptr<QGraphicsScene> m_scene;
  boost::shared_ptr<QGraphicsPixmapItem> m_background;
};

#endif // DIALOG_H
