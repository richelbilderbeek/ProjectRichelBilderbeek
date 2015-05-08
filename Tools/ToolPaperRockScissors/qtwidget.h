#ifndef QTWIDGET_H
#define QTWIDGET_H

#include <QWidget>
#include <QPixmap>

#include "simulation.h"

namespace Ui {
  class QtWidget;
}

struct QImage;

class QtWidget : public QWidget
{
  Q_OBJECT

public:
  explicit QtWidget(
    const int width = 600,
    const int height = 400,
    QWidget *parent = 0);
  ~QtWidget();

protected:
  void paintEvent(QPaintEvent *);
private:
  Ui::QtWidget *ui;
  QPixmap m_pixmap;
  Simulation m_simulation;

private slots:
  void OnTimer();
};

#endif // QTWIDGET_H
