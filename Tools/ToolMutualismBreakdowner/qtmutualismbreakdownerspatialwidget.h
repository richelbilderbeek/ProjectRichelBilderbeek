#ifndef QTPAPERROCKSCISSORSWIDGET_H
#define QTPAPERROCKSCISSORSWIDGET_H

#include <QWidget>
#include <QPixmap>

#include "paperrockscissorssimulation.h"

namespace Ui {
  class QtPaperRockScissorsWidget;
}

struct QImage;

class QtPaperRockScissorsWidget : public QWidget
{
  Q_OBJECT

public:
  explicit QtPaperRockScissorsWidget(
    const int width = 600,
    const int height = 400,
    QWidget *parent = 0
  );
  QtPaperRockScissorsWidget(const QtPaperRockScissorsWidget&) = delete;
  QtPaperRockScissorsWidget& operator=(const QtPaperRockScissorsWidget&) = delete;
  ~QtPaperRockScissorsWidget();

protected:
  void paintEvent(QPaintEvent *);
private:
  Ui::QtPaperRockScissorsWidget *ui;
  QPixmap m_pixmap;
  PaperRockScissorsSimulation m_simulation;

private slots:
  void OnTimer();
};

#endif // QTPAPERROCKSCISSORSWIDGET_H
