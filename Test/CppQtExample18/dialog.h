#ifndef DIALOG_H
#define DIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include <QDialog>
#pragma GCC diagnostic pop

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
  Dialog(const Dialog&) = delete;
  Dialog& operator=(const Dialog&) = delete;
  ~Dialog();

private:
  Ui::Dialog *ui;
  boost::shared_ptr<QGraphicsScene> m_scene;
  boost::shared_ptr<QGraphicsPixmapItem> m_background;
};

#endif // DIALOG_H
