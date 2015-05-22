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
  using Init = PaperRockScissorsSimulation::Initialization;

  explicit QtPaperRockScissorsWidget(
    const int width = 600,
    const int height = 400,
    const Init initialization = Init::random,
    QWidget *parent = 0
  );
  QtPaperRockScissorsWidget(const QtPaperRockScissorsWidget&) = delete;
  QtPaperRockScissorsWidget& operator=(const QtPaperRockScissorsWidget&) = delete;
  ~QtPaperRockScissorsWidget();

  void SetAll(
    const int width,
    const int height,
    const Init initialization
  );

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
