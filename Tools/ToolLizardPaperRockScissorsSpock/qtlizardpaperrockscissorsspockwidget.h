#ifndef QTLIZARDPAPERROCKSCISSORSSPOCKWIDGET_H
#define QTLIZARDPAPERROCKSCISSORSSPOCKWIDGET_H

#include <QWidget>
#include <QPixmap>

#include "simulation.h"

namespace Ui {
  class QtLizardPaperRockScissorsSpockWidget;
}

struct QImage;

class QtLizardPaperRockScissorsSpockWidget : public QWidget
{
  Q_OBJECT

public:
  using Init = Simulation::Initialization;

  explicit QtLizardPaperRockScissorsSpockWidget(
    const int width = 300,
    const int height = 200,
    const Init initialization = Init::random,
    QWidget *parent = 0
  );
  QtLizardPaperRockScissorsSpockWidget(const QtLizardPaperRockScissorsSpockWidget&) = delete;
  QtLizardPaperRockScissorsSpockWidget& operator=(const QtLizardPaperRockScissorsSpockWidget&) = delete;
  ~QtLizardPaperRockScissorsSpockWidget();

  void SetAll(
    const int width,
    const int height,
    const Init initialization
  );

protected:
  void paintEvent(QPaintEvent *);
private:
  Ui::QtLizardPaperRockScissorsSpockWidget *ui;
  QPixmap m_pixmap;
  Simulation m_simulation;

private slots:
  void OnTimer();
};

#endif // QTLIZARDPAPERROCKSCISSORSSPOCKWIDGET_H
